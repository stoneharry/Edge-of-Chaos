/*
 * ArcEmu MMORPG Server
 * Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
 * Copyright (C) 2008-2011 <http://www.ArcEmu.org/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "StdAfx.h"

void WorldSession::HandleUseItemOpcode(WorldPacket & recvPacket)
{
	CHECK_INWORLD_RETURN

	typedef std::list<Aura*> AuraList;

	Player* p_User = GetPlayer();
	LOG_DETAIL("WORLD: got use Item packet, data length = %i", recvPacket.size());
	int8 tmp1, slot;
	uint8 castFlags;
	uint64 item_guid;
	uint8 cn;
	uint32 spellId = 0;
	uint32 glyphIndex;
	bool found = false;

	recvPacket >> tmp1;
	recvPacket >> slot;
	recvPacket >> cn;
	recvPacket >> spellId;
	recvPacket >> item_guid;
	recvPacket >> glyphIndex;
	recvPacket >> castFlags;

	Item* tmpItem = NULL;
	tmpItem = p_User->GetItemInterface()->GetInventoryItem(tmp1, slot);
	if(!tmpItem)
		tmpItem = p_User->GetItemInterface()->GetInventoryItem(slot);
	if(!tmpItem)
		return;
	ItemPrototype* itemProto = tmpItem->GetProto();

	// only some consumable items can be used in arenas
	if( ( itemProto->Class == ITEM_CLASS_CONSUMABLE ) &&
		!itemProto->HasFlag( ITEM_FLAG_USEABLE_IN_ARENA ) &&
		( GetPlayer()->m_bg != NULL ) &&
		IS_ARENA( GetPlayer()->m_bg->GetType() ) )
	{
		GetPlayer()->GetItemInterface()->BuildInventoryChangeError(tmpItem, NULL, INV_ERR_NOT_DURING_ARENA_MATCH);
		return;
	}

	if(tmpItem->IsSoulbound())     // SouldBind item will be used after SouldBind()
	{
		if(sScriptMgr.CallScriptedItem(tmpItem, _player))
			return;
	}

	if(_player->getDeathState() == CORPSE)
		return;

	if(itemProto->Bonding == ITEM_BIND_ON_USE)
		tmpItem->SoulBind();

	if(sScriptMgr.CallScriptedItem(tmpItem, _player))
		return;

	if(itemProto->InventoryType != 0 && !_player->GetItemInterface()->IsEquipped(itemProto->ItemId))  //Equipable items cannot be used before they're equipped. Prevents exploits
		return;//Prevents exploits such as keeping an on-use trinket in your bag and using WPE to use it from your bag in mid-combat.

	if(itemProto->QuestId)
	{
		// Item Starter
		Quest* qst = QuestStorage.LookupEntry(itemProto->QuestId);
		if(!qst)
			return;

		WorldPacket data;
		sQuestMgr.BuildQuestDetails(&data, qst, tmpItem, 0, language, _player);
		SendPacket(&data);
	}

	// Let's check if the item even has that spell
	for(int i = 0; i < 5; ++i)
	{
		if(itemProto->Spells[i].Trigger == USE && itemProto->Spells[i].Id == spellId)
		{
			found = true;
			break;//found 1 already
		}
	}

	// Let's see if it is an onuse spellid
	if(tmpItem->HasOnUseSpellID(spellId))
		found = true;

	// We didn't find the spell, so the player is probably trying to cheat
	// with an edited itemcache.wdb
	//
	// Altough this could also happen after a DB update
	// if he/she didn't delete his/her cache.
	if(found == false)
	{

		this->Disconnect();
		Anticheat_Log->writefromsession(this, "Player tried to use an item with a spell that didn't match the spell in the database.");
		Anticheat_Log->writefromsession(this, "Possibly corrupted or intentionally altered itemcache.wdb");
		Anticheat_Log->writefromsession(this, "Itemid: %lu", itemProto->ItemId);
		Anticheat_Log->writefromsession(this, "Spellid: %lu", spellId);
		Anticheat_Log->writefromsession(this, "Player was disconnected");

		return;
	}

	SpellCastTargets targets(recvPacket, _player);
	HandleClientCastFlags(recvPacket, castFlags, targets);

	SpellEntry* spellInfo = dbcSpell.LookupEntryForced(spellId);
	if(spellInfo == NULL)
	{
		LOG_ERROR("WORLD: unknown spell id %i", spellId);
		return;
	}

	if(spellInfo->AuraInterruptFlags & AURA_INTERRUPT_ON_STAND_UP)
	{
		if(p_User->CombatStatus.IsInCombat() || p_User->IsMounted())
		{
			_player->GetItemInterface()->BuildInventoryChangeError(tmpItem, NULL, INV_ERR_CANT_DO_IN_COMBAT);
			return;
		}

		if(p_User->GetStandState() != 1)
			p_User->SetStandState(STANDSTATE_SIT);
		// loop through the auras and removing existing eating spells
	}
	else   // cebernic: why not stand up
	{
		if(!p_User->CombatStatus.IsInCombat() && !p_User->IsMounted())
		{
			if(p_User->GetStandState())
			{
				p_User->SetStandState(STANDSTATE_STAND);
			}
		}
	}

	// cebernic: remove stealth on using item
	if(!(spellInfo->AuraInterruptFlags & SPELL_ATTR1_NOT_BREAK_STEALTH))
	{
		if(p_User->IsStealth())
			p_User->RemoveAllAuraType(SPELL_AURA_MOD_STEALTH);
	}

	if(itemProto->RequiredLevel)
	{
		if(_player->getLevel() < itemProto->RequiredLevel)
		{
			_player->GetItemInterface()->BuildInventoryChangeError(tmpItem, NULL, INV_ERR_ITEM_RANK_NOT_ENOUGH);
			return;
		}
	}

	if(itemProto->RequiredSkill)
	{
		if(!_player->_HasSkillLine(itemProto->RequiredSkill))
		{
			_player->GetItemInterface()->BuildInventoryChangeError(tmpItem, NULL, INV_ERR_ITEM_RANK_NOT_ENOUGH);
			return;
		}

		if(itemProto->RequiredSkillRank)
		{
			if(_player->_GetSkillLineCurrent(itemProto->RequiredSkill, false) < itemProto->RequiredSkillRank)
			{
				_player->GetItemInterface()->BuildInventoryChangeError(tmpItem, NULL, INV_ERR_ITEM_RANK_NOT_ENOUGH);
				return;
			}
		}
	}

	if((itemProto->AllowableClass && !(_player->getClassMask() & itemProto->AllowableClass)) || (itemProto->AllowableRace && !(_player->getRaceMask() & itemProto->AllowableRace)))
	{
		_player->GetItemInterface()->BuildInventoryChangeError(tmpItem, NULL, INV_ERR_YOU_CAN_NEVER_USE_THAT_ITEM);
		return;
	}

	if(!_player->Cooldown_CanCast(spellInfo))
	{
		_player->SendCastResult(spellInfo->Id, SPELL_FAILED_NOT_READY, cn, 0);
		return;
	}


	if(_player->m_currentSpell)
	{
		_player->SendCastResult(spellInfo->Id, SPELL_FAILED_SPELL_IN_PROGRESS, cn, 0);
		return;
	}

	if(itemProto->ForcedPetId >= 0)
	{
		if(itemProto->ForcedPetId == 0)
		{
			if(_player->GetGUID() != targets.m_unitTarget)
			{
				_player->SendCastResult(spellInfo->Id, SPELL_FAILED_BAD_TARGETS, cn, 0);
				return;
			}
		}
		else
		{

			if(!_player->GetSummon() || _player->GetSummon()->GetEntry() != (uint32)itemProto->ForcedPetId)
			{
				_player->SendCastResult(spellInfo->Id, SPELL_FAILED_SPELL_IN_PROGRESS, cn, 0);
				return;
			}
		}
	}

	Spell* spell = sSpellFactoryMgr.NewSpell(_player, spellInfo, false, NULL);
	spell->extra_cast_number = cn;
	spell->i_caster = tmpItem;
	spell->m_glyphslot = glyphIndex;

	//GetPlayer()->setCurrentSpell(spell);
	spell->prepare(&targets);

#ifdef ENABLE_ACHIEVEMENTS
	_player->GetAchievementMgr().UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_USE_ITEM, itemProto->ItemId, 0, 0);
#endif

}

void WorldSession::HandleSpellClick(WorldPacket & recvPacket)
{
	CHECK_INWORLD_RETURN

	LOG_DETAIL("WORLD: got CMSG_SPELLCLICK packet, data length = %i", recvPacket.size());

	if(_player->getDeathState() == CORPSE)
		return;

	uint64 target_guid; // this will store the guid of the object we are going to use it's spell. There must be a dbc that indicates what spells a unit has

	recvPacket >> target_guid;

	//we have only 1 example atm for entry : 28605
	Unit* target_unit = _player->GetMapMgr()->GetUnit(target_guid);

	if(!target_unit)
		return;

	if( !_player->isInRange( target_unit, MAX_INTERACTION_RANGE ) )
		return;

	if( target_unit->IsVehicle() ){
		if( target_unit->GetVehicleComponent() != NULL )
			target_unit->GetVehicleComponent()->AddPassenger( _player );
		return;
	}

	uint32 creature_id = target_unit->GetEntry();
	uint32 cast_spell_id = 0;

	if(!_player->HasAurasWithNameHash(SPELL_HASH_LIGHTWELL_RENEW) && target_unit->RemoveAura(59907))
	{
		SpellClickSpell *sp = SpellClickSpellStorage.LookupEntry( creature_id );
		if( sp == NULL ){
			if( target_unit->IsCreature() ){
				Creature *c = TO< Creature* >( target_unit );
				
				sChatHandler.BlueSystemMessage( this, "NPC Id %u ( %s ) has no spellclick spell associated with it.", c->GetProto()->Id, c->GetCreatureInfo()->Name  );
				LOG_ERROR("Spellclick packet received for creature %u but there is no spell associated with it.", creature_id );
				return;
			}
		}

		cast_spell_id = sp->SpellID;

		target_unit->CastSpell(_player, cast_spell_id, true);

		if(!target_unit->HasAura(59907))
			TO_CREATURE(target_unit)->Despawn(0, 0); //IsCreature() check is not needed, refer to r2387 and r3230

		return;
	}
	
	SpellClickSpell *sp = SpellClickSpellStorage.LookupEntry( creature_id );
	if( sp == NULL ){
		if( target_unit->IsCreature() ){
			Creature *c = TO< Creature* >( target_unit );

			sChatHandler.BlueSystemMessage( this, "NPC Id %u ( %s ) has no spellclick spell associated with it.", c->GetProto()->Id, c->GetCreatureInfo()->Name  );
			LOG_ERROR("Spellclick packet received for creature %u but there is no spell associated with it.", creature_id );
			return;
		}
	}

	cast_spell_id = sp->SpellID;

	if(cast_spell_id == 0)
		return;

	SpellEntry* spellInfo = dbcSpell.LookupEntryForced(cast_spell_id);
	if(spellInfo == NULL)
		return;
	Spell* spell = sSpellFactoryMgr.NewSpell(_player, spellInfo, false, NULL);
	SpellCastTargets targets(target_guid);
	spell->prepare(&targets);
}

void WorldSession::HandleCastSpellOpcode(WorldPacket & recvPacket)
{
	CHECK_INWORLD_RETURN

	uint32 spellId;
	uint8 cn, castFlags;

	recvPacket >> cn >> spellId  >> castFlags;
	// check for spell id
	SpellEntry* spellInfo = dbcSpell.LookupEntryForced(spellId);

	if(!spellInfo)
	{
		_player->SendCastResult(spellInfo->Id, SPELL_FAILED_DONT_REPORT, cn, 0);
		LOG_ERROR("WORLD: unknown spell id %i", spellId);
		return;
	}

	LOG_DETAIL("WORLD: got cast spell packet, spellId - %i (%s), data length = %i",
	           spellId, spellInfo->SpellName[0], recvPacket.size());

	// Cheat Detection only if player and not from an item
	// this could fuck up things but meh it's needed ALOT of the newbs are using WPE now
	// WPE allows them to mod the outgoing packet and basically choose what ever spell they want :(

	if(!GetPlayer()->HasSpell(spellId))
	{
		_player->SendCastResult(spellInfo->Id, SPELL_FAILED_DONT_REPORT, cn, 0);
		sCheatLog.writefromsession(this, "Cast spell %lu but doesn't have that spell.", spellId);
		LOG_DETAIL("WORLD: Spell isn't cast because player \'%s\' is cheating", GetPlayer()->GetName());
		_player->SendCastResult(spellInfo->Id, SPELL_FAILED_SPELL_IN_PROGRESS, cn, 0);
		return;
	}
	if(spellInfo->Attributes & SPELL_ATTR0_PASSIVE)
	{
		_player->SendCastResult(spellInfo->Id, SPELL_FAILED_DONT_REPORT, cn, 0);
		sCheatLog.writefromsession(this, "Cast passive spell %lu.", spellId);
		LOG_DETAIL("WORLD: Spell isn't cast because player \'%s\' is cheating", GetPlayer()->GetName());
		return;
	}

	if(GetPlayer()->GetOnMeleeSpell() != spellId)
	{
		//autoshot 75
		if((spellInfo->AttributesEx2 & SPELL_ATTR2_AUTOREPEAT_FLAG) /*spellInfo->Attributes == 327698*/)	// auto shot..
		{
			//sLog.outString( "HandleSpellCast: Auto Shot-type spell cast (id %u, name %s)" , spellInfo->Id , spellInfo->Name );
			Item* weapon = GetPlayer()->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_RANGED);
			if(!weapon)
				return;
			uint32 spellid;
			switch(weapon->GetProto()->SubClass)
			{
				case 2:			 // bows
				case 3:			 // guns
				case 18:		 // crossbow
					spellid = SPELL_RANGED_GENERAL;
					break;
				case 16:			// thrown
					spellid = SPELL_RANGED_THROW;
					break;
				case 19:			// wands
					spellid = SPELL_RANGED_WAND;
					break;
				default:
					spellid = 0;
					break;
			}

			if(!spellid)
				spellid = spellInfo->Id;

			if(!_player->m_onAutoShot)
			{
				_player->m_AutoShotTarget = _player->GetSelection();
				uint32 duration = _player->GetBaseAttackTime(RANGED);
				SpellCastTargets targets(recvPacket, GetPlayer());
				if(!targets.m_unitTarget)
				{
					_player->SendCastResult(spellInfo->Id, SPELL_FAILED_BAD_TARGETS, cn, 0);
					LOG_DEBUG("Cancelling auto-shot cast because targets.m_unitTarget is null!");
					return;
				}
				SpellEntry* sp = dbcSpell.LookupEntry(spellid);

				_player->m_AutoShotSpell = sp;
				_player->m_AutoShotDuration = duration;
				//This will fix fast clicks
				if(_player->m_AutoShotAttackTimer < 500)
					_player->m_AutoShotAttackTimer = 500;
				_player->m_onAutoShot = true;
			}

			return;
		}

		if(_player->m_currentSpell)
		{
			_player->SendCastResult(spellInfo->Id, SPELL_FAILED_SPELL_IN_PROGRESS, cn, 0);
			return;
		}

		SpellCastTargets targets(recvPacket, GetPlayer());
		HandleClientCastFlags(recvPacket, castFlags, targets);

		// some anticheat stuff
		if(spellInfo->self_cast_only)
		{
			if(targets.m_unitTarget && targets.m_unitTarget != _player->GetGUID())
			{
				targets.m_unitTarget = _player->GetGUID();
			}
		}

		Spell* spell = sSpellFactoryMgr.NewSpell(GetPlayer(), spellInfo, false, NULL);
		spell->extra_cast_number = cn;
		spell->prepare(&targets);
		if(_player->confirm_item_send && spellId != 52644)
		{
			sChatHandler.BlueSystemMessage(this, "Cache sending canceled");
			_player->confirm_item_send = false;
		}
	}
}

void WorldSession::HandleCancelCastOpcode(WorldPacket & recvPacket)
{
	CHECK_INWORLD_RETURN

	uint32 spellId;
	recvPacket >> spellId;

	if(GetPlayer()->m_currentSpell)
		GetPlayer()->m_currentSpell->cancel();
}

void WorldSession::HandleCancelAuraOpcode(WorldPacket & recvPacket)
{

	CHECK_INWORLD_RETURN

	uint32 spellId;
	recvPacket >> spellId;

	if(spellId == 8326 || spellId == 9036) //you may never cancel "ghost" auras.
		return;

	if(_player->m_currentSpell && _player->m_currentSpell->GetProto()->Id == spellId)
		_player->m_currentSpell->cancel();
	else
	{
		SpellEntry* info = dbcSpell.LookupEntryForced(spellId);
		Aura * a = _player->FindAura(spellId);
		if(a)
		{
			if(!a->IsPositive())
				return;
			if(info->Attributes & SPELL_ATTR0_NEGATIVE_1)
				return;
		}
		if(info->Attributes & static_cast<uint32>(SPELL_ATTR0_CANT_CANCEL))
			return;
		if(info != NULL)
			_player->RemoveAllAuraById(spellId);
	}
}

void WorldSession::HandleCancelChannellingOpcode(WorldPacket & recvPacket)
{

	CHECK_INWORLD_RETURN

	uint32 spellId;
	recvPacket >> spellId;

	Player* plyr = GetPlayer();
	if(!plyr)
		return;
	if(plyr->m_currentSpell)
		plyr->m_currentSpell->cancel();
}

void WorldSession::HandleCancelAutoRepeatSpellOpcode(WorldPacket & recv_data)
{
	CHECK_INWORLD_RETURN

	//sLog.outString("Received CMSG_CANCEL_AUTO_REPEAT_SPELL message.");
	//on original we automatically enter combat when creature got close to us
//	GetPlayer()->GetSession()->OutPacket(SMSG_CANCEL_COMBAT);
	GetPlayer()->m_onAutoShot = false;
}

void WorldSession::HandlePetCastSpell(WorldPacket & recvPacket)
{

	CHECK_INWORLD_RETURN

	uint64 guid = 0;
	uint8  castCount = 0;
	uint32 spellid = 0;
	uint8  castflags = 0;
	uint32 targetmask = 0;

	recvPacket >> guid;
	recvPacket >> castCount;
	recvPacket >> spellid;
	recvPacket >> castflags;

	SpellEntry* sp = dbcSpell.LookupEntryForced(spellid);
	if(sp == NULL)
		return;
	Unit * caster = _player->GetMapMgrUnit(guid);
	if(caster == NULL)
	{
		recvPacket.rfinish();
		return;
	}
	if(!_player->summonhandler.HasSummon(caster) && _player->GetCharmedUnitGUID() != caster->GetGUID())
	{
		recvPacket.rfinish();
		return;
	}

	SpellCastTargets targets;
	targets.read( recvPacket, caster );
	HandleClientCastFlags(recvPacket, castflags, targets);
	bool check = false;
	for(list<AI_Spell*>::iterator itr = caster->GetAIInterface()->m_spells.begin(); itr != caster->GetAIInterface()->m_spells.end(); ++itr)//.......meh. this is a crappy way of doing this, I bet.
	{
		if((*itr)->spell->Id == spellid)
		{
			check = true;
			break;
		}
	}
	if(caster->IsCreature())
	{
		Creature* c = TO< Creature* >(caster);
		if(c->GetProto()->spelldataid != 0)
		{
			CreatureSpellDataEntry* spe = dbcCreatureSpellData.LookupEntry(c->GetProto()->spelldataid);
				if(spe != NULL)
				for(uint32 i = 0; i < 3; i++)
					if(spe->Spells[ i ] == spellid)
					{
						check = true;
						break;
					}
		}
		for(uint32 i = 0; i < 8; i++)
			if(c->GetProto()->AISpells[ i ] == spellid)
			{
				check = true;
				break;
			}
	}
	if(!check)
		return;

	Spell* pSpell = sSpellFactoryMgr.NewSpell(caster, sp, false, 0);
	pSpell->prepare(&targets);
}

void WorldSession::HandleCancelTotem(WorldPacket & recv_data)
{

	CHECK_INWORLD_RETURN

	uint8 slot;
	recv_data >> slot;

	if(slot >= UNIT_SUMMON_SLOTS)
	{
		LOG_ERROR("Player %u %s tried to cancel a summon at slot %u, slot number is out of range. ( tried to crash the server? )", _player->GetLowGUID(), _player->GetName(), slot);
		return;
	}

	_player->summonhandler.RemoveSummonFromSlot(slot);
}

void WorldSession::HandleUpdateProjectilePosition(WorldPacket & recv_data)
{
    uint64 casterGuid;
    uint32 spellId;
    uint8 castCount;
    float x, y, z;    // Position of missile hit

    casterGuid = recv_data.unpackGUID();
    recv_data >> spellId;
    recv_data >> castCount;
    recv_data >> x;
    recv_data >> y;
    recv_data >> z;

    WorldPacket data(SMSG_SET_PROJECTILE_POSITION, 21);
    data << uint64(casterGuid);
    data << uint8(castCount);
    data << float(x);
    data << float(y);
    data << float(z);
    SendPacket(&data);
}

void WorldSession::HandleClientCastFlags(WorldPacket& recvPacket, uint8 castFlags, SpellCastTargets& targets)
{
	// some spell cast packet including more data (for projectiles?)
	if (castFlags & 0x02)
	{
		// not sure about these two
		float elevation, speed;
		recvPacket >> elevation;
		recvPacket >> speed;

		targets.m_elevation = elevation;
		targets.m_speed = speed;

		uint8 hasMovementData;
		recvPacket >> hasMovementData;
		if (hasMovementData)
		{
			recvPacket.rfinish();
			// movement packet for caster of the spell
			/*recvPacket.read_skip<uint32>(); // MSG_MOVE_STOP - hardcoded in client
			uint64 guid;
			recvPacket.readPackGUID(guid);

			MovementInfo movementInfo;
			movementInfo.guid = guid;
			ReadMovementInfo(recvPacket, &movementInfo);*/
		}
	}
}