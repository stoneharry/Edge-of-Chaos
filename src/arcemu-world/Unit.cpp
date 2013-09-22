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

float baseMoveSpeed[9] =
{
    2.5f,                  // MOVE_WALK
    7.0f,                  // MOVE_RUN
    4.5f,                  // MOVE_RUN_BACK
    4.722222f,             // MOVE_SWIM
    2.5f,                  // MOVE_SWIM_BACK
    3.141594f,             // MOVE_TURN_RATE
    7.0f,                  // MOVE_FLIGHT
    4.5f,                  // MOVE_FLIGHT_BACK
    3.14f                  // MOVE_PITCH_RATE
};

float playerBaseMoveSpeed[9] = {
    2.5f,                  // MOVE_WALK
    7.0f,                  // MOVE_RUN
    4.5f,                  // MOVE_RUN_BACK
    4.722222f,             // MOVE_SWIM
    2.5f,                  // MOVE_SWIM_BACK
    3.141594f,             // MOVE_TURN_RATE
    7.0f,                  // MOVE_FLIGHT
    4.5f,                  // MOVE_FLIGHT_BACK
    3.14f                  // MOVE_PITCH_RATE
};
Unit::Unit()
{
	int i;

	m_attackTimer = 0;
	m_attackTimer_1 = 0;
	m_dualWield = false;

	m_ignoreArmorPctMaceSpec = 0;
	m_ignoreArmorPct = 0;
	m_fearmodifiers = 0;
	m_state = 0;
	m_special_state = 0;
	m_deathState = ALIVE;
	m_meleespell = 0;
	m_addDmgOnce = 0;

	m_ObjectSlots[0] = 0;
	m_ObjectSlots[1] = 0;
	m_ObjectSlots[2] = 0;
	m_ObjectSlots[3] = 0;
	m_silenced = 0;
	disarmed   = false;

	//DK:modifiers
	PctRegenModifier = 0;
	for(i = 0; i < 4; i++)
	{
		PctPowerRegenModifier[i] = 1;
	}
	m_speedModifier = 0;
	m_mountedspeedModifier = 0;
	m_maxSpeed = 0;
	for(i = 0; i < 32 ; i++)
	{
		MechanicsDispels[i] = 0;
		MechanicsResistancesPCT[i] = 0;
		ModDamageTakenByMechPCT[i] = 0;
	}
	m_pacified = 0;
	m_interruptRegen = 0;
	m_resistChance = 0;
	m_powerRegenPCT = 0;
	RAPvModifier = 0;
	APvModifier = 0;
	stalkedby = 0;

	m_extraattacks = 0;
	m_stunned = 0;
	m_manashieldamt = 0;
	m_rooted = 0;
	m_triggerSpell = 0;
	m_triggerDamage = 0;
	m_canMove = 0;
	m_noInterrupt = 0;
	m_modlanguage = -1;
	m_magnetcaster = 0;

	m_CombatResult_Dodge = 0;
	m_CombatResult_Parry = 0;

	m_useAI = false;
	for(i = 0; i < 10; i++)
	{
		dispels[i] = 0;
		CreatureAttackPowerMod[i] = 0;
		CreatureRangedAttackPowerMod[i] = 0;
	}
	//REMIND:Update these if you make any changes
	CreatureAttackPowerMod[UNIT_TYPE_MISC] = 0;
	CreatureRangedAttackPowerMod[UNIT_TYPE_MISC] = 0;
	CreatureAttackPowerMod[11] = 0;
	CreatureRangedAttackPowerMod[11] = 0;

	m_invisibility = 0;
	m_invisible = false;
	m_invisFlag = INVIS_FLAG_NORMAL;
	m_mageInvisibility = false;

	for(i = 0; i < INVIS_FLAG_TOTAL; i++)
	{
		m_invisDetect[i] = 0;
	}

	m_stealthLevel = 0;
	m_stealthDetectBonus = 0;
	m_stealth = 0;
	m_can_stealth = true;

	for(i = 0; i < 5; i++)
		BaseStats[i] = 0;

	m_H_regenTimer = 2000;
	m_P_regenTimer = 2000;

	//	if(GetTypeId() == TYPEID_PLAYER) //only player for now
	//		CalculateActualArmor();

	m_aiInterface = new AIInterface();
	m_aiInterface->Init(this, AITYPE_AGRO, MOVEMENTTYPE_NONE);

	m_emoteState = 0;
	m_oldEmote = 0;

	BaseDamage[0] = 0;
	BaseOffhandDamage[0] = 0;
	BaseRangedDamage[0] = 0;
	BaseDamage[1] = 0;
	BaseOffhandDamage[1] = 0;
	BaseRangedDamage[1] = 0;

	m_CombatUpdateTimer = 0;
	for(i = 0; i < SCHOOL_COUNT; i++)
	{
		SchoolImmunityList[i] = 0;
		BaseResistance[i] = 0;
		HealDoneMod[i] = 0;
		HealDonePctMod[i] = 0;
		HealTakenMod[i] = 0;
		HealTakenPctMod[i] = 0;
		DamageTakenMod[i] = 0;
		SchoolCastPrevent[i] = 0;
		DamageTakenPctMod[i] = 0;
		SpellCritChanceSchool[i] = 0;
		PowerCostMod[i] = 0;
		PowerCostPctMod[i] = 0; // armor penetration & spell penetration
		AttackerCritChanceMod[i] = 0;
		CritMeleeDamageTakenPctMod[i] = 0;
		CritRangedDamageTakenPctMod[i] = 0;
		m_generatedThreatModifyer[i] = 0;
		DoTPctIncrease[i] = 0;
	}
	DamageTakenPctModOnHP35 = 1;
	RangedDamageTaken = 0;
	AOEDmgMod = 1.0f;

	for(i = 0; i < 5; i++)
	{
		m_detectRangeGUID[i] = 0;
		m_detectRangeMOD[i] = 0;
	}

	trackStealth = false;

	m_threatModifyer = 0;
	memset(m_auras, 0, (MAX_TOTAL_AURAS_END)*sizeof(Aura*));

	// diminishing return stuff
	memset(m_diminishAuraCount, 0, DIMINISHING_GROUP_COUNT);
	memset(m_diminishCount, 0, DIMINISHING_GROUP_COUNT * 2);
	memset(m_diminishTimer, 0, DIMINISHING_GROUP_COUNT * 2);
	memset(m_auraStackCount, 0, MAX_NEGATIVE_VISUAL_AURAS_END);
	memset(m_auravisuals, 0, MAX_NEGATIVE_VISUAL_AURAS_END * sizeof(uint32));

	m_diminishActive = false;
	dynObj = 0;
	pLastSpell = 0;
	m_flyspeedModifier = 0;
	bInvincible = false;
	m_redirectSpellPackets = 0;
	can_parry = false;
	bProcInUse = false;
	spellcritperc = 0;

	polySpell = 0;
	RangedDamageTaken = 0;
	m_procCounter = 0;
	m_damgeShieldsInUse = false;
//	fearSpell = 0;
	m_extraAttackCounter = false;
	CombatStatus.SetUnit(this);
	m_chargeSpellsInUse = false;
//	m_spellsbusy=false;
	m_interruptedRegenTime = 0;
	m_hitfrommeleespell	 = 0;
	m_damageSplitTarget = NULL;
	m_extrastriketarget = false;
	m_extrastriketargetc = 0;
	trigger_on_stun = 0;
	trigger_on_stun_chance = 100;
	trigger_on_stun_victim = 0;
	trigger_on_stun_chance_victim = 100;
	trigger_on_chill = 0;
	trigger_on_chill_chance = 100;
	trigger_on_chill_victim = 0;
	trigger_on_chill_chance_victim = 100;
	m_soulSiphon.amt = 0;
	m_soulSiphon.max = 0;
	m_modelhalfsize = 1.0f; //worst case unit size. (Should be overwritten)

	m_blockfromspell		= 0;
	m_dodgefromspell		= 0;
	m_parryfromspell		= 0;
	m_BlockModPct			= 0;

	m_damageShields.clear();
	m_reflectSpellSchool.clear();
	m_procSpells.clear();
	m_chargeSpells.clear();
	m_chargeSpellRemoveQueue.clear();
	tmpAura.clear();
	m_extraStrikeTargets.clear();

	asc_frozen = 0;
	asc_enraged = 0;
	asc_seal = 0;
	asc_bleed = 0;

	Tagged = false;
	TaggerGuid = 0;

	m_singleTargetAura.clear();

	vehicle = NULL;
	currentvehicle = NULL;

	m_noFallDamage = false;
	z_axisposition = 0.0f;
	m_safeFall     = 0;
	m_auraRaidUpdateMask = 0;
	movement_info = MovementInfo();
}

Unit::~Unit()
{
	//start to remove badptrs, if you delete from the heap null the ptr's damn!
	RemoveAllAuras();

	delete m_aiInterface;
	m_aiInterface = NULL;


	if(m_currentSpell)
	{
		m_currentSpell->cancel();
		m_currentSpell = NULL;
	}

	if(m_damageSplitTarget)
	{
		delete m_damageSplitTarget;
		m_damageSplitTarget = NULL;
	}

	// reflects not created by auras need to be deleted manually
	for(std::list<struct ReflectSpellSchool*>::iterator i = m_reflectSpellSchool.begin(); i != m_reflectSpellSchool.end(); ++i)
		delete *i;
	m_reflectSpellSchool.clear();

	for(std::list<ExtraStrike*>::iterator itx = m_extraStrikeTargets.begin(); itx != m_extraStrikeTargets.end(); ++itx)
	{
		ExtraStrike* es = *itx;
		LOG_ERROR("ExtraStrike added to Unit %u by Spell ID %u wasn't removed when removing the Aura", GetGUID(), es->spell_info->Id);
		delete es;
	}
	m_extraStrikeTargets.clear();

	// delete auras which did not get added to unit yet
	for(std::map< uint32, Aura* >::iterator i = tmpAura.begin(); i != tmpAura.end(); i++)
		delete i->second;
	tmpAura.clear();

	for(std::list<SpellProc*>::iterator itr = m_procSpells.begin(); itr != m_procSpells.end(); ++itr)
		delete *itr;
	m_procSpells.clear();

	m_singleTargetAura.clear();

	RemoveGarbage();
}

void Unit::Update(uint32 p_time)
{
	_UpdateSpells(p_time);

	RemoveGarbage();

	if(!IsDead())
	{
		//-----------------------POWER & HP REGENERATION-----------------
		/* Please don't do temp fixes. Better report to me. Thx. Shady */
		if(p_time >= m_H_regenTimer)
			RegenerateHealth();
		else
			m_H_regenTimer -= static_cast<uint16>(p_time);

		if(p_time >= m_P_regenTimer)
		{
			RegeneratePower(false);
			m_interruptedRegenTime = 0;
		}
		else
		{
			m_P_regenTimer -= static_cast<uint16>(p_time);
			if(m_interruptedRegenTime)
			{
				if(p_time >= m_interruptedRegenTime)
					RegeneratePower(true);
				else
					m_interruptedRegenTime -= p_time;
			}
		}


		if(m_aiInterface != NULL)
		{
			if(m_useAI)
				m_aiInterface->Update(p_time);
			else if(!m_aiInterface->MoveDone())  //pending move
				m_aiInterface->UpdateMovementSpline();
		}

		if(m_diminishActive)
		{
			uint32 count = 0;
			for(uint32 x = 0; x < DIMINISHING_GROUP_COUNT; ++x)
			{
				// diminishing return stuff
				if(m_diminishTimer[x] && !m_diminishAuraCount[x])
				{
					if(p_time >= m_diminishTimer[x])
					{
						// resetting after 15 sec
						m_diminishTimer[x] = 0;
						m_diminishCount[x] = 0;
					}
					else
					{
						// reducing, still.
						m_diminishTimer[x] -= static_cast<uint16>(p_time);
						++count;
					}
				}
			}
			if(!count)
				m_diminishActive = false;
		}

		/*		//if health changed since last time. Would be perfect if it would work for creatures too :)
				if(m_updateMask.GetBit(UNIT_FIELD_HEALTH))
					EventHealthChangeSinceLastUpdate();*/
	}
}

bool Unit::canReachWithAttack(Unit* pVictim)
{
	if(GetMapId() != pVictim->GetMapId())
		return false;

//	float targetreach = pVictim->GetCombatReach();
	float selfreach;
	if(IsPlayer())
		selfreach = 5.0f; // minimum melee range, UNIT_FIELD_COMBATREACH is too small and used eg. in melee spells
	else
		selfreach = m_floatValues[UNIT_FIELD_COMBATREACH];

	float targetradius;
//	targetradius = pVictim->m_floatValues[UNIT_FIELD_BOUNDINGRADIUS]; //this is plain wrong. Represents i have no idea what :)
	targetradius = pVictim->GetModelHalfSize();
	float selfradius;
//	selfradius = m_floatValues[UNIT_FIELD_BOUNDINGRADIUS];
	selfradius = GetModelHalfSize();
//	float targetscale = pVictim->m_floatValues[OBJECT_FIELD_SCALE_X];
//	float selfscale = m_floatValues[OBJECT_FIELD_SCALE_X];

	//float distance = sqrt(GetDistanceSq(pVictim));
	float delta_x = pVictim->GetPositionX() - GetPositionX();
	float delta_y = pVictim->GetPositionY() - GetPositionY();
	float distance = sqrt(delta_x * delta_x + delta_y * delta_y);


//	float attackreach = (((targetradius*targetscale) + selfreach) + (((selfradius*selfradius)*selfscale)+1.50f));
	float attackreach = targetradius + selfreach + selfradius;

	//formula adjustment for player side.
	if(IsPlayer())
	{
		// latency compensation!!
		// figure out how much extra distance we need to allow for based on our movespeed and latency.
		if(pVictim->IsPlayer() && TO< Player* >(pVictim)->IsMoving())
		{
			// this only applies to PvP.
			uint32 lat = TO< Player* >(pVictim)->GetSession() ? TO< Player* >(pVictim)->GetSession()->GetLatency() : 0;

			// if we're over 500 get fucked anyway.. your gonna lag! and this stops cheaters too
			lat = (lat > 500) ? 500 : lat;

			// calculate the added distance
			attackreach += m_runSpeed * 0.001f * lat;
		}

		if(TO< Player* >(this)->IsMoving())
		{
			// this only applies to PvP.
			uint32 lat = TO< Player* >(this)->GetSession() ? TO< Player* >(this)->GetSession()->GetLatency() : 0;

			// if we're over 500 get fucked anyway.. your gonna lag! and this stops cheaters too
			lat = (lat > 500) ? 500 : lat;

			// calculate the added distance
			attackreach += m_runSpeed * 0.001f * lat;
		}
	}
	return (distance <= attackreach);
}

void Unit::GiveGroupXP(Unit* pVictim, Player* PlayerInGroup)
{
	if(!PlayerInGroup)
		return;
	if(!pVictim)
		return;
	if(!PlayerInGroup->InGroup())
		return;
	Group* pGroup = PlayerInGroup->GetGroup();
	uint32 xp;
	if(!pGroup)
		return;

	//Get Highest Level Player, Calc Xp and give it to each group member
	Player* pHighLvlPlayer = NULL;
	Player* pGroupGuy = NULL;
	int active_player_count = 0;
	Player* active_player_list[MAX_GROUP_SIZE_RAID];//since group is small we can afford to do this ratehr then recheck again the whole active player set
	int total_level = 0;
	float xp_mod = 1.0f;

	GroupMembersSet::iterator itr;
	pGroup->Lock();
	for(uint32 i = 0; i < pGroup->GetSubGroupCount(); i++)
	{
		for(itr = pGroup->GetSubGroup(i)->GetGroupMembersBegin(); itr != pGroup->GetSubGroup(i)->GetGroupMembersEnd(); ++itr)
		{
			pGroupGuy = (*itr)->m_loggedInPlayer;
			if(pGroupGuy &&
			        pGroupGuy->isAlive() &&
//				PlayerInGroup->GetInstanceID()==pGroupGuy->GetInstanceID() &&
			        pVictim->GetMapMgr() == pGroupGuy->GetMapMgr() &&
			        pGroupGuy->GetDistanceSq(pVictim) < 100 * 100
			  )
			{
				active_player_list[active_player_count] = pGroupGuy;
				active_player_count++;
				total_level += pGroupGuy->getLevel();
				if(pHighLvlPlayer)
				{
					if(pGroupGuy->getLevel() > pHighLvlPlayer->getLevel())
						pHighLvlPlayer = pGroupGuy;
				}
				else
					pHighLvlPlayer = pGroupGuy;
			}
		}
	}
	pGroup->Unlock();
	if(active_player_count < 1) //killer is always close to the victim. This should never execute
	{
		if(PlayerInGroup == 0)
		{
			PlayerInfo* pleaderinfo = pGroup->GetLeader();
			if(!pleaderinfo->m_loggedInPlayer)
				return;

			PlayerInGroup = pleaderinfo->m_loggedInPlayer;
		}

		xp = CalculateXpToGive(pVictim, PlayerInGroup);
		PlayerInGroup->GiveXP(xp, pVictim->GetGUID(), true);
	}
	else
	{
		if(pGroup->GetGroupType() == GROUP_TYPE_PARTY)
		{
			/*if(active_player_count == 3)
				xp_mod = 1.1666f;
			else if(active_player_count == 4)
				xp_mod = 1.3f;
			else if(active_player_count == 5)
				xp_mod = 1.4f;
			else*/ xp_mod = 2; //in case we have only 2 members ;)
		}
		else if(pGroup->GetGroupType() == GROUP_TYPE_RAID)
			xp_mod = 0.5f;

		if(pHighLvlPlayer == 0)
		{
			PlayerInfo* pleaderinfo = pGroup->GetLeader();
			if(!pleaderinfo->m_loggedInPlayer)
				return;

			pHighLvlPlayer = pleaderinfo->m_loggedInPlayer;
		}

		xp = CalculateXpToGive(pVictim, pHighLvlPlayer);
		//I'm not sure about this formula is correct or not. Maybe some brackets are wrong placed ?
		for(int i = 0; i < active_player_count; i++)
		{
			Player* plr = active_player_list[i];
			plr->GiveXP(float2int32(((xp * plr->getLevel()) / total_level) * xp_mod), pVictim->GetGUID(), true);

			active_player_list[i]->SetFlag(UNIT_FIELD_AURASTATE, AURASTATE_FLAG_LASTKILLWITHHONOR);
			if(!sEventMgr.HasEvent(active_player_list[i], EVENT_LASTKILLWITHHONOR_FLAG_EXPIRE))
			{
				sEventMgr.AddEvent(TO_UNIT(active_player_list[i]), &Unit::EventAurastateExpire, (uint32)AURASTATE_FLAG_LASTKILLWITHHONOR, EVENT_LASTKILLWITHHONOR_FLAG_EXPIRE, 20000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
			}
			else
			{
				sEventMgr.ModifyEventTimeLeft(active_player_list[i], EVENT_LASTKILLWITHHONOR_FLAG_EXPIRE, 20000);
			}

			if(plr->GetSummon() && plr->GetSummon()->CanGainXP())
			{
				uint32 pet_xp = (uint32)(CalculateXpToGive(pVictim, plr->GetSummon()) * xp_mod);   // vojta: this isn't blizzlike probably but i have no idea, feel free to correct it
				if(pet_xp > 0)
					plr->GetSummon()->GiveXP(pet_xp);
			}
		}
	}
}

uint32 Unit::HandleProc(uint32 flag, Unit* victim, SpellEntry* CastingSpell, bool is_triggered, uint32 dmg, uint32 abs, uint32 weapon_damage_type)
{
	uint32 resisted_dmg = 0;
	++m_procCounter;
	bool can_delete = !bProcInUse; //if this is a nested proc then we should have this set to TRUE by the father proc
	bProcInUse = true; //locking the proc list

	/* hmm what's a reasonable value here */
	if(m_procCounter > 40)
	{
		/* something has proceed over 10 times in a loop :/ dump the spellids to the crashlog, as the crashdump will most likely be useless. */
		// BURLEX FIX ME!
		//OutputCrashLogLine("HandleProc %u SpellId %u (%s) %u", flag, spellId, sSpellStore.LookupString(sSpellStore.LookupEntry(spellId)->Name), m_procCounter);
		return 0;
	}

	try
	{
	std::list<SpellProc*>::iterator itr, itr2;
	for(itr = m_procSpells.begin(); itr != m_procSpells.end();)    // Proc Trigger Spells for Victim
	{
		itr2 = itr;
		++itr;

		SpellProc* spell_proc = *itr2;

		// Check if list item was deleted elsewhere, so here it's removed and freed
		if(spell_proc->mDeleted)
		{
			if(can_delete)
			{
				m_procSpells.erase(itr2);
				delete spell_proc;
			}
			continue;
		}

		if(CastingSpell != NULL)
		{
			// A spell cannot proc itself
			if(CastingSpell->Id == spell_proc->mSpell->Id)
				continue;

			// If this is called by a triggered spell, check if it's allowed
			if(is_triggered && ! spell_proc->CanProcOnTriggered(victim, CastingSpell))
				continue;
		}

		// Check if this can proc
		if(! spell_proc->CanProc(victim, CastingSpell))
			continue;

		// Check for flags
		if(! spell_proc->CheckProcFlags(flag))
			continue;

		// Check proc class mask
		if(flag & PROC_ON_CAST_SPELL && CastingSpell && ! spell_proc->CheckClassMask(victim, CastingSpell))
			continue;

		uint32 spellId = spell_proc->mSpell->Id;

		SpellEntry* spe = spell_proc->mSpell;

		uint32 origId;
		if(spell_proc->mOrigSpell != NULL)
			origId = spell_proc->mOrigSpell->Id;
		else
			origId = 0;
		SpellEntry* ospinfo = dbcSpell.LookupEntry(origId);  //no need to check if exists or not since we were not able to register this trigger if it would not exist :P

		//this requires some specific spell check,not yet implemented
		//this sucks and should be rewrote
		if(spell_proc->mProcFlags & PROC_ON_CAST_SPECIFIC_SPELL)
		{
			if(CastingSpell == NULL)
				continue;

			//this is wrong, dummy is too common to be based on this, we should use spellgroup or something
			if(spe->SpellIconID != CastingSpell->SpellIconID)
			{
				if(!ospinfo->NormalizedSchoolMask())
					continue;
				if(ospinfo->SchoolMask != CastingSpell->NormalizedSchoolMask())
					continue;
				if(CastingSpell->EffectImplicitTargetA[0] == 1 ||
				        CastingSpell->EffectImplicitTargetA[1] == 1 ||
				        CastingSpell->EffectImplicitTargetA[2] == 1)  //Prevents school based procs affecting caster when self buffing
					continue;
			}
			else if(spe->SpellIconID == 1)
				continue;
		}

		uint32 proc_Chance = spell_proc->CalcProcChance(victim, CastingSpell);

		//Custom procchance modifications based on equipped weapon speed.
		if(this->IsPlayer() && (
		            spe->NameHash == SPELL_HASH_MAGTHERIDON_MELEE_TRINKET ||
		            spe->NameHash == SPELL_HASH_ROMULO_S_POISON ||
		            spe->NameHash == SPELL_HASH_BLACK_TEMPLE_MELEE_TRINKET ||
		            spe->NameHash == SPELL_HASH_FROSTBRAND_ATTACK || spellId == 16870))
		{
			float ppm = 1.0f;
			switch(spe->NameHash)
			{
				case SPELL_HASH_MAGTHERIDON_MELEE_TRINKET:
					ppm = 1.5f;
					break; // dragonspine trophy
				case SPELL_HASH_ROMULO_S_POISON:
					ppm = 1.5f;
					break; // romulo's
				case SPELL_HASH_BLACK_TEMPLE_MELEE_TRINKET:
					ppm = 1.0f;
					break; // madness of the betrayer
				case SPELL_HASH_FROSTBRAND_ATTACK:
					ppm = 9.0f;
					break; // Frostbrand Weapon
			}
			switch(spellId)
			{
				case 16870:
					ppm = 2.0f;
					break; //druid: clearcasting
			}

			Item* mh = TO< Player* >(this)->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_MAINHAND);
			Item* of = TO< Player* >(this)->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_OFFHAND);

			if(mh != NULL && of != NULL)
			{
				uint32 mhs = mh->GetProto()->Delay;
				uint32 ohs = of->GetProto()->Delay;
				proc_Chance = float2int32((mhs + ohs) * 0.001f * ppm / 0.6f);
			}
			else if(mh != NULL)
			{
				uint32 mhs = mh->GetProto()->Delay;
				proc_Chance = float2int32(mhs * 0.001f * ppm / 0.6f);
			}
			else
				proc_Chance = 0;

			if(TO< Player* >(this)->IsInFeralForm())
			{
				if(TO< Player* >(this)->GetShapeShift() == FORM_CAT)
				{
					proc_Chance = float2int32(ppm / 0.6f);
				}
				else if(TO< Player* >(this)->GetShapeShift() == FORM_BEAR || TO< Player* >(this)->GetShapeShift() == FORM_DIREBEAR)
				{
					proc_Chance = float2int32(ppm / 0.24f);
				}
			}
		}
		if(Player * p = GetSpellModOwner())
			p->ApplySpellMod(spe->Id, SPELLMOD_CHANCE_OF_SUCCESS, proc_Chance);
		if(!Rand(proc_Chance))
			continue;

		//check if we can trigger due to time limitation
		if(ospinfo->proc_interval)
		{
			uint32 now_in_ms = getMSTime();
			if(spell_proc->mLastTrigger + ospinfo->proc_interval > now_in_ms)
				continue; //we can't trigger it yet.
			spell_proc->mLastTrigger = now_in_ms; // consider it triggered
		}

		//since we did not allow to remove auras like these with interrupt flag we have to remove them manually.
		if(spell_proc->mProcFlags & PROC_REMOVEONUSE)
			RemoveAura(origId);

		int dmg_overwrite[3] = { 0, 0, 0 };

		// give spell_proc a chance to handle the effect
		if(spell_proc->DoEffect(victim, CastingSpell, flag, dmg, abs, dmg_overwrite, weapon_damage_type))
			continue;

		//these are player talents. Fuckem they pull the emu speed down
		if(IsPlayer())
		{
			if(ospinfo->ProcOnNameHash[0] != 0)
			{
				if(CastingSpell == NULL)
					continue;

				if(CastingSpell->NameHash != ospinfo->ProcOnNameHash[0] &&
				        CastingSpell->NameHash != ospinfo->ProcOnNameHash[1] &&
				        CastingSpell->NameHash != ospinfo->ProcOnNameHash[2])
					continue;
			}

			uint32 talentlevel = 0;
			switch(origId)
			{
					//mace specialization
				case 12284:
					{talentlevel = 1;}
					break;
				case 12701:
					{talentlevel = 2;}
					break;
				case 12702:
					{talentlevel = 3;}
					break;
				case 12703:
					{talentlevel = 4;}
					break;
				case 12704:
					{talentlevel = 5;}
					break;

					//Unbridled Wrath
				case 12999:
					{talentlevel = 1;}
					break;
				case 13000:
					{talentlevel = 2;}
					break;
				case 13001:
					{talentlevel = 3;}
					break;
				case 13002:
					{talentlevel = 4;}
					break;
			}

			switch(spellId)
			{
				case 32747: //Deadly Throw Interrupt (rogue arena gloves set)
					{
						if(CastingSpell == NULL)
							continue;
						if(CastingSpell->NameHash != SPELL_HASH_DEADLY_THROW)
							continue;
					}
					break;
				case 16959://Druid - Primal Fury Proc
					{
						if(!IsPlayer())
							continue;
						Player* p = TO< Player* >(this);
						if(p->GetShapeShift() != FORM_BEAR && p->GetShapeShift() != FORM_DIREBEAR)
							continue;
					}
					break;
				case 16953: //Druid - Blood Frenzy Proc
					{
						if(!IsPlayer() || !CastingSpell)
							continue;
						Player* p = TO< Player* >(this);
						if(p->GetShapeShift() != FORM_CAT || (
						            CastingSpell->NameHash != SPELL_HASH_CLAW &&
						            CastingSpell->NameHash != SPELL_HASH_RAKE &&
						            CastingSpell->NameHash != SPELL_HASH_RAVAGE &&
						            CastingSpell->NameHash != SPELL_HASH_SHRED))
							continue;
					}
					break;
				case 14189: //Seal Fate
					{
						if(!this->IsPlayer() ||
						        !CastingSpell ||
						        CastingSpell->Id == 14189 ||
						        CastingSpell->Id == 16953 ||
						        CastingSpell->Id == 16959)
							continue;
						if(CastingSpell->Effect[0] != SPELL_EFFECT_ADD_COMBO_POINTS &&
						        CastingSpell->Effect[1] != SPELL_EFFECT_ADD_COMBO_POINTS &&
						        CastingSpell->Effect[2] != SPELL_EFFECT_ADD_COMBO_POINTS &&
						        CastingSpell->NameHash != SPELL_HASH_MANGLE__CAT_)
							continue;
					}
					break;
				case 17106: //druid intensity
					{
						if(CastingSpell == NULL)
							continue;
						if(CastingSpell->Id != 5229)  //enrage
							continue;
					}
					break;
				case 31616: //Nature's Guardian
					{
						//yep, another special case: Nature's grace
						if(GetHealthPct() > 30)
							continue;
					}
					break;
				case 37309: //Bloodlust
					{
						if(!this->IsPlayer())
							continue;
						if(TO< Player* >(this)->GetShapeShift() != FORM_BEAR ||
						        TO< Player* >(this)->GetShapeShift() != FORM_DIREBEAR)
							continue;
					}
					break;
				case 37310://Bloodlust
					{
						if(!this->IsPlayer() || TO< Player* >(this)->GetShapeShift() != FORM_CAT)
							continue;
					}
					break;
				case 16459:
					{
						//sword specialization
						Item* itMH = TO< Player* >(this)->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_MAINHAND);
						Item* itOH = TO< Player* >(this)->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_OFFHAND);
						uint32 reqskillMH = 0;
						uint32 reqskillOH = 0;

						if(itMH != NULL)
							reqskillMH = GetSkillByProto(itMH->GetProto()->Class, itMH->GetProto()->SubClass);

						if(itOH != NULL)
							reqskillOH = GetSkillByProto(itOH->GetProto()->Class, itOH->GetProto()->SubClass);

						if(reqskillMH != SKILL_SWORDS && reqskillMH != SKILL_2H_SWORDS && reqskillOH != SKILL_SWORDS && reqskillOH != SKILL_2H_SWORDS)
							continue;
					}
					break;
				case 12721:
					{
						//deep wound requires a melee weapon
						Item* it;
						it = TO< Player* >(this)->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_MAINHAND);
						if(it != NULL)
						{
							//class 2 means weapons ;)
							if(it->GetProto()->Class != 2)
								continue;
						}
						else continue; //no weapon no joy
					}
					break;
					//Warrior - Sword and Board
				case 50227:
					{
						if(CastingSpell == NULL)
							continue;

						if(CastingSpell->NameHash != SPELL_HASH_DEVASTATE && CastingSpell->NameHash != SPELL_HASH_REVENGE)
							continue;
					}
					break;
					//Warrior - Safeguard
				case 46946:
				case 46947:
					{
						if(CastingSpell == NULL)
							continue;

						if(CastingSpell->NameHash != SPELL_HASH_INTERVENE)
							continue;
					}
					break;
					//Warrior - Taste for Blood
				case 60503:
					{
						if(CastingSpell == NULL)
							continue;

						if(CastingSpell->NameHash != SPELL_HASH_REND)
							continue;
					}
					break;
					//Warrior - Unbridled Wrath
				case 12964:
					{
						//let's recalc chance to cast since we have a full 100 all time on this one
						Item* it;
						it = TO< Player* >(this)->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_MAINHAND);
						if(it == NULL)
							continue; //no weapon no joy
						//float chance=float(it->GetProto()->Delay)*float(talentlevel)/600.0f;
						uint32 chance = it->GetProto()->Delay * talentlevel / 300; //zack this had a very low proc rate. Kinda like a wasted talent
						uint32 myroll = RandomUInt(100);
						if(myroll > chance)
							continue;
					}
					break;
					//Warrior - Gag Order
				case 18498:
					{
						if(CastingSpell == NULL)
							continue;

						if(CastingSpell->NameHash != SPELL_HASH_SHIELD_BASH &&
						        CastingSpell->NameHash != SPELL_HASH_HEROIC_THROW)
							continue;
					}
					break;
					//Warrior - Bloodsurge
				case 46916:
					{
						if(CastingSpell == NULL)
							continue;

						if(CastingSpell->NameHash != SPELL_HASH_HEROIC_STRIKE &&
						        CastingSpell->Id != 23881 &&
						        CastingSpell->NameHash != SPELL_HASH_WHIRLWIND)
							continue;
					}
					break;
////////////////////////////////////////////////////////////////////////////
					// Mage ignite talent only for fire dmg
				case 12654:
					{
						if(CastingSpell == NULL)
							continue;
						if(CastingSpell->NormalizedSchoolMask() != SCHOOL_FIRE)
							continue;
						SpellEntry* spellInfo = dbcSpell.LookupEntry(spellId);   //we already modified this spell on server loading so it must exist
						SpellDuration* sd = dbcSpellDuration.LookupEntryForced(spellInfo->DurationIndex);
						uint32 tickcount = GetDuration(sd) / spellInfo->EffectAmplitude[0] ;
						dmg_overwrite[0] = ospinfo->EffectBasePoints[0] * dmg / (100  * tickcount);
					}
					break;
					//druid - Primal Fury
				case 37116:
				case 37117:
					{
						if(!this->IsPlayer())
							continue;
						Player* mPlayer = TO_PLAYER(this);
						if(!mPlayer->IsInFeralForm() ||
						        (mPlayer->GetShapeShift() != FORM_CAT &&
						         mPlayer->GetShapeShift() != FORM_BEAR &&
						         mPlayer->GetShapeShift() != FORM_DIREBEAR))
							continue;
					}
					break;
					//rogue - blade twisting
				case 31125:
					{
						if(CastingSpell == NULL)
							continue;//this should not occur unless we made a fuckup somewhere
						//only trigger effect for specified spells
						if(CastingSpell->NameHash != SPELL_HASH_BACKSTAB &&  //backstab
						        CastingSpell->NameHash != SPELL_HASH_SINISTER_STRIKE && //sinister strike
						        CastingSpell->NameHash != SPELL_HASH_SHIV && //shiv
						        CastingSpell->NameHash != SPELL_HASH_GOUGE)  //gouge
							continue;
					}
					break;
					//priest - Grace
				case 47930:
					{
						if(CastingSpell == NULL)
							continue;
						if(CastingSpell->NameHash != SPELL_HASH_PENANCE &&
						        CastingSpell->NameHash != SPELL_HASH_FLASH_HEAL &&
						        CastingSpell->NameHash != SPELL_HASH_GREATER_HEAL)
							continue;
					}
					break;
					//warlock - Improved Shadow Bolt
				case 17794:
				case 17798:
				case 17797:
				case 17799:
				case 17800:
					{
						if(CastingSpell == NULL)
							continue;//this should not occur unless we made a fuckup somewhere
						//only trigger effect for specified spells
						if(CastingSpell->NameHash != SPELL_HASH_SHADOW_BOLT) //shadow bolt
							continue;
					}
					break;
					// warlock - Seed of Corruption
				case 27285:
					{
						bool can_proc_now = false;
						//if we proced on spell tick
						if(flag & PROC_ON_SPELL_HIT_VICTIM)
						{
							if(!CastingSpell)
								continue;
							//only trigger effect for specified spells
							if(CastingSpell->NameHash != SPELL_HASH_SEED_OF_CORRUPTION)
								continue;
							//this spell builds up n time
							spell_proc->mProcCharges += dmg;
							if((int32)spell_proc->mProcCharges >= ospinfo->EffectBasePoints[ 1 ] &&  //if charge built up
							        dmg < this->GetUInt32Value(UNIT_FIELD_HEALTH))    //if this is not a killer blow
								can_proc_now = true;
						}
						else can_proc_now = true; //target died
						if(can_proc_now == false)
							continue;
						Unit* new_caster = victim;
						if(new_caster && new_caster->isAlive())
						{
							SpellEntry* spellInfo = dbcSpell.LookupEntry(spellId);   //we already modified this spell on server loading so it must exist
							Spell* spell = sSpellFactoryMgr.NewSpell(new_caster, spellInfo , true, NULL);
							SpellCastTargets targets;
							targets.m_destX = GetPositionX();
							targets.m_destY = GetPositionY();
							targets.m_destZ = GetPositionZ();
							spell->prepare(&targets);
						}
						spell_proc->mDeleted = true;
						continue;
					}
					break;
					// warlock - Improved Drain Soul
				case 18371:
					{
						if(!CastingSpell)
							continue;
						//only trigger effect for specified spells
						if(CastingSpell->NameHash != SPELL_HASH_DRAIN_SOUL)
							continue;
						//null check was made before like 2 times already :P
						dmg_overwrite[0] = (ospinfo->EffectBasePoints[2] + 1) * GetMaxPower(POWER_TYPE_MANA) / 100;
					}
					break;
					// warlock - Unstable Affliction
				case 31117:
					{
						//null check was made before like 2 times already :P
						dmg_overwrite[0] = (ospinfo->EffectBasePoints[0] + 1) * 9;
					}
					break;

					//warlock - Nighfall
				case 17941:
					{
						if(CastingSpell == NULL)
							continue;//this should not occur unless we made a fuckup somewhere
						//only trigger effect for specified spells
						if(CastingSpell->NameHash != SPELL_HASH_CORRUPTION &&  //Corruption
						        CastingSpell->NameHash != SPELL_HASH_DRAIN_LIFE) //Drain Life
							continue;
					}
					break;
					//warlock - Shadow Embrace
				case 32386:
				case 32388:
				case 32389:
				case 32390:
				case 32391:
					{
						if(CastingSpell == NULL)
							continue;
						else
						{
							if(CastingSpell->NameHash != SPELL_HASH_FIRE_SHIELD_II &&  // Corruption
							        CastingSpell->NameHash != SPELL_HASH_CURSE_OF_AGONY && //CoA
							        CastingSpell->NameHash != SPELL_HASH_SIPHON_LIFE && //Siphon Life
							        CastingSpell->NameHash != SPELL_HASH_SEED_OF_CORRUPTION)  //SoC
								continue;
						}
					}
					break;
					//warlock - Aftermath
				case 18118:
					{
						if(CastingSpell == NULL)
							continue;//this should not occur unless we made a fuckup somewhere
						//only trigger effect for specified spells
						skilllinespell* skillability = objmgr.GetSpellSkill(CastingSpell->Id);
						if(!skillability)
							continue;
						if(skillability->skilline != SKILL_DESTRUCTION)
							continue;
					}
					break;
					//warlock - Nether Protection
				case 30300:
					{
						if(CastingSpell == NULL)
							continue;//this should not occur unless we made a fuckup somewhere
						//only trigger effect for specified spells
						if(!(CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING))
							continue;
						if(CastingSpell->NormalizedSchoolMask() != SCHOOL_FIRE &&
						        CastingSpell->NormalizedSchoolMask() != SCHOOL_SHADOW)
							continue;
					}
					break;
					//warlock - Soul Leech - this whole spell should get rewritten. Uses bad formulas, bad trigger method, spell is rewritten ...
				case 30294:
					{
						if(CastingSpell == NULL)
							continue;//this should not occur unless we made a fuckup somewhere
						//only trigger effect for specified spells
						uint32 amount;
						switch(CastingSpell->NameHash)
						{
							case SPELL_HASH_SHADOW_BOLT: //Shadow Bolt
							case SPELL_HASH_SOUL_FIRE: //Soul Fire
							case SPELL_HASH_INCINERATE: //Incinerate
							case SPELL_HASH_SEARING_PAIN: //Searing Pain
							case SPELL_HASH_CONFLAGRATE: //Conflagrate
							case SPELL_HASH_CHAOS_BOLT: //Chaos Bolt
								{
									amount = CastingSpell->EffectBasePoints[0] + 1;
								}
								break;
							case SPELL_HASH_SHADOWBURN: //Shadowburn
								{
									amount = CastingSpell->EffectBasePoints[1] + 1;
								}
								break;
							default:
								amount = 0;
						}
						if(!amount)
							continue;
						SpellEntry* spellInfo = dbcSpell.LookupEntry(spellId);
						Spell* spell = sSpellFactoryMgr.NewSpell(this, spellInfo , true, NULL);
						spell->SetUnitTarget(this);
						spell->Heal(amount * (ospinfo->EffectBasePoints[0] + 1) / 100);
						delete spell;
						spell = NULL;
						continue;
					}
					break;
					//warlock - pyroclasm
				case 18093:
					{
						if(CastingSpell == NULL)
							continue;//this should not occur unless we made a fuckup somewhere
						//only trigger effect for specified spells
						if(CastingSpell->NameHash != SPELL_HASH_RAIN_OF_FIRE &&  //Rain of Fire
						        CastingSpell->NameHash != SPELL_HASH_HELLFIRE_EFFECT && //Hellfire
						        CastingSpell->NameHash != SPELL_HASH_SOUL_FIRE)  //Soul Fire
							continue;
					}
					break;
				case 54274:
				case 54276:
				case 54277:
					{
						if(CastingSpell == NULL)
							continue;

						if(CastingSpell->NameHash != SPELL_HASH_CONFLAGRATE)
							continue;
					}
					break;
					//Mage - Missile Barrage
				case 44401:
					{
						if(CastingSpell == NULL)
							continue;

						if(CastingSpell->NameHash != SPELL_HASH_ARCANE_BLAST &&
						        CastingSpell->NameHash != SPELL_HASH_ARCANE_BARRAGE &&
						        CastingSpell->NameHash != SPELL_HASH_FIREBALL &&
						        CastingSpell->NameHash != SPELL_HASH_FROSTBOLT &&
						        CastingSpell->NameHash != SPELL_HASH_FROSTFIRE_BOLT)
							continue;
					}
					break;
					//mage - Improved Scorch
				case 22959:
					{
						if(CastingSpell == NULL)
							continue;//this should not occur unless we made a fuckup somewhere
						//only trigger effect for specified spells
						if(CastingSpell->NameHash != SPELL_HASH_SCORCH)   //Scorch
							continue;
					}
					break;
					//mage - Combustion
				case 28682:
					{
						if(CastingSpell == NULL)
							continue;//this should not occur unless we made a fuckup somewhere
						//only trigger effect for specified spells
						if(!(CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING)
						        || CastingSpell->NormalizedSchoolMask() != SCHOOL_FIRE)
							continue;
						if(flag & PROC_ON_SPELL_CRIT_HIT)
						{
							spell_proc->mProcCharges++;
							if(spell_proc->mProcCharges >= 3)   //whatch that number cause it depends on original stack count !
							{
								RemoveAllAuraByNameHash(SPELL_HASH_COMBUSTION);
								continue;
							}
						}
					}
					break;
					//mage - Winter's Chill
				case 12579:
					// Winter's Chill shouldn't proc on self
					if(victim == this || CastingSpell->NormalizedSchoolMask() != SCHOOL_FROST)
						continue;
					break;
					//item - Thunderfury
				case 21992:
					if(victim == this)
						continue;
					break;
					//warrior - Intimidating Shout
				case 5246:
					if(victim == this)
						continue;
					break;

					//priest - Borrowed time
				case 59887:
				case 59888:
				case 59889:
				case 59890:
				case 59891:
					{
						if(CastingSpell == NULL)
							continue;
						if(CastingSpell->NameHash != SPELL_HASH_POWER_WORD__SHIELD)
							continue;
					}
					break;

					//priest - Inspiration
				case 15363:
				case 14893:
				case 15357:
				case 15359:
					{
						if(!CastingSpell || !(CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING))
							continue;
					}
					break;
					//priest - Blessed Recovery
				case 27813:
				case 27817:
				case 27818:
					{
						if(!IsPlayer() || !dmg)
							continue;
						SpellEntry* parentproc = dbcSpell.LookupEntryForced(origId);
						SpellEntry* spellInfo = dbcSpell.LookupEntryForced(spellId);
						if(!parentproc || !spellInfo)
							continue;
						int32 val = parentproc->EffectBasePoints[0] + 1;
						Spell* spell = sSpellFactoryMgr.NewSpell(this, spellInfo , true, NULL);
						spell->forced_basepoints[0] = (val * dmg) / 300; //per tick
						SpellCastTargets targets;
						targets.m_unitTarget = GetGUID();
						spell->prepare(&targets);
						continue;
					}
					break;


					//Shaman - Healing Way
				case 29203:
					{
						if(CastingSpell == NULL)
							continue;//this should not occur unless we made a fuckup somewhere
						//only trigger effect for specified spells
						if(CastingSpell->NameHash != SPELL_HASH_HEALING_WAVE)   //healing wave
							continue;
					}
					break;
					//Shaman - Elemental Devastation
				case 29177:
				case 29178:
				case 30165:
					{
						if(CastingSpell == NULL)
							continue;//this should not occur unless we made a fuckup somewhere
						//only trigger effect for specified spells
						if(!(CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING))  //healing wave
							continue;
					}
					break;
					//Shaman - Ancestral Fortitude
				case 16177:
				case 16236:
				case 16237:
					//Shaman - Earthliving Weapon
				case 51940:
				case 51989:
				case 52004:
				case 52005:
				case 52007:
				case 52008:
					{
						if(CastingSpell == NULL)
							continue;
						if(!(CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING))   //healing spell
							continue;
					}
					break;
					//Shaman - Tidal Waves
				case 51562:
				case 51563:
				case 51564:
				case 51565:
				case 51566:
					{
						if(CastingSpell == NULL)
							continue;
						if(!(CastingSpell->NameHash == SPELL_HASH_CHAIN_HEAL || CastingSpell->NameHash == SPELL_HASH_RIPTIDE))
							continue;
					}
					break;
					// Totem of the Third Wind
				case 42371:
				case 34132:
				case 46099:
				case 43729:
					{
						if(CastingSpell == NULL)
							continue;
						if(CastingSpell->NameHash != SPELL_HASH_LESSER_HEALING_WAVE)
							continue;
					}
					break;
					//Stonebreaker's Totem
				case 43749:
					{
						if(CastingSpell == NULL)
							continue;
						if(CastingSpell->NameHash != SPELL_HASH_EARTH_SHOCK && CastingSpell->NameHash != SPELL_HASH_FROST_SHOCK && CastingSpell->NameHash != SPELL_HASH_FLAME_SHOCK)
							continue;
					}
					break;
					// Librams of Justice
				case 34135:
				case 42369:
				case 43727:
				case 46093:
					{
						if(CastingSpell == NULL)
							continue;
						if(CastingSpell->NameHash != SPELL_HASH_FLASH_OF_LIGHT)
							continue;
					}
					break;
					//Libram of Divine Judgement
				case 43747:
					{
						if(CastingSpell == NULL)
							continue;
						if(CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_COMMAND && CastingSpell->NameHash != SPELL_HASH_JUDGEMENT)
							continue;
					}
					break;
				case 16246:
					{
						if(origId == 39805)
							continue; // Lightning Overload Proc is already free
						if(CastingSpell->NameHash != SPELL_HASH_LIGHTNING_BOLT &&
						        CastingSpell->NameHash != SPELL_HASH_CHAIN_LIGHTNING &&
						        CastingSpell->NameHash != SPELL_HASH_EARTH_SHOCK &&
						        CastingSpell->NameHash != SPELL_HASH_FLAME_SHOCK &&
						        CastingSpell->NameHash != SPELL_HASH_FROST_SHOCK)
							continue;
					}
					break;
					//shaman - windfury weapon
				case 8232:
				case 8235:
				case 10486:
				case 16362:
				case 25505:
					{
						if(!IsPlayer())
							continue;
						//!! The weird thing is that we need the spell that triggered this enchant spell in order to output logs ..we are using oldspell info too
						//we have to recalc the value of this spell
						SpellEntry* spellInfo = dbcSpell.LookupEntry(origId);
						uint32 AP_owerride = spellInfo->EffectBasePoints[0] + 1;
						uint32 dmg2 = TO< Player* >(this)->GetMainMeleeDamage(AP_owerride);
						SpellEntry* sp_for_the_logs = dbcSpell.LookupEntry(spellId);
						Strike(victim, MELEE, sp_for_the_logs, dmg2, 0, 0, true, false);
						Strike(victim, MELEE, sp_for_the_logs, dmg2, 0, 0, true, false);
						spellId = 33010; // WF animation
					}
					break;
					//rogue - Ruthlessness
				case 14157:
					{
						if(CastingSpell == NULL)
							continue;//this should not occur unless we made a fuckup somewhere
						//we need a finishing move for this
						if(!(CastingSpell->c_is_flags & SPELL_FLAG_IS_FINISHING_MOVE) || victim == this)
							continue;
						//should fix issue with combo points
						if(IsPlayer())
						{
							TO< Player* >(this)->m_spellcomboPoints++;
							TO< Player* >(this)->UpdateComboPoints();
						}
					}
					break;
					// rogue - T10 4P bonus
				case 70802:
					{
						// The rogue bonus set of T10 requires a finishing move
						if(!(CastingSpell && CastingSpell->c_is_flags & SPELL_FLAG_IS_FINISHING_MOVE))
							continue;
					}
					break;

					//warrior - improved berserker rage
				case 23690:
				case 23691:
					{
						if(!CastingSpell || CastingSpell->NameHash != SPELL_HASH_BERSERKER_RAGE)
							continue;
					}
					break;
					//mage - Arcane Concentration
				case 12536:
					{
						//requires damageing spell
						if(CastingSpell == NULL)
							continue;//this should not occur unless we made a fuckup somewhere
						if(!(CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING))
							continue;
					}
					break;
					//mage - Improved Blizzard
				case 12484:
				case 12485:
				case 12486:
					{
						if(CastingSpell == NULL)
							continue;
						if(CastingSpell->NameHash != SPELL_HASH_BLIZZARD || victim == this)   //Blizzard
							continue;
					}
					break;
					//mage - Master of Elements
				case 29077:
					{
						if(CastingSpell == NULL)
							continue;
						if(CastingSpell->NormalizedSchoolMask() != SCHOOL_FIRE && CastingSpell->NormalizedSchoolMask() != SCHOOL_FROST) //fire and frost critical's
							continue;
						dmg_overwrite[0] = CastingSpell->manaCost * (ospinfo->EffectBasePoints[0] + 1) / 100;
					}
					break;
					//Hunter - The Beast Within
				case 34471:
					{
						if(CastingSpell == NULL)
							continue;

						if(CastingSpell->Id != 19574)
							continue;
					}
					//Hunter - Thrill of the Hunt
				case 34720:
					{
						if(CastingSpell == NULL)
							continue;
						dmg_overwrite[0] = CastingSpell->manaCost * 40 / 100;
					}
					break;
					//priest - Reflective Shield
				case 33619:
					{
						if(!abs)
							continue;

						//requires Power Word: Shield active
						int power_word_id = HasAurasWithNameHash(SPELL_HASH_POWER_WORD__SHIELD);
						if(!power_word_id)
							power_word_id = 17;
						//make a direct strike then exit rest of handler
						int tdmg = abs * (ospinfo->EffectBasePoints[0] + 1) / 100;
						//somehow we should make this not caused any threat (to be done)
						SpellNonMeleeDamageLog(victim, power_word_id, tdmg, false, true);
						continue;
					}
					break;
					//rogue - combat potency
				case 35542:
				case 35545:
				case 35546:
				case 35547:
				case 35548:
					{
						if(!IsPlayer() || !dmg)
							continue;
						//this needs offhand weapon
						Item* it = TO< Player* >(this)->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_OFFHAND);
						if(it == NULL || it->GetProto()->InventoryType != INVTYPE_WEAPON)
							continue;
					}
					break;
					//paladin - Improved Lay on Hands
				case 20233:
				case 20236:
					{
						if(CastingSpell == NULL)
							continue;
						if(CastingSpell->NameHash != SPELL_HASH_LAY_ON_HANDS)
							continue;
					}
					break;
					//paladin - Infusion of Light
				case 53672:
				case 54149:
					{
						if(CastingSpell == NULL)
							continue;
						if(CastingSpell->NameHash != SPELL_HASH_HOLY_SHOCK)
							continue;
					}
					break;
					//paladin - Sacred Cleansing
				case 53659:
					{
						if(CastingSpell == NULL)
							continue;
						if(CastingSpell->NameHash != SPELL_HASH_CLEANSE)
							continue;
					}
					break;
					//paladin - Judgements of the Pure
				case 53655:
				case 53656:
				case 53657:
				case 54152:
				case 54153:
					{
						if(CastingSpell == NULL)
							continue;
						if(CastingSpell->Id != 53408 &&
						        CastingSpell->Id != 53407 &&
						        CastingSpell->Id != 20271)
							continue;
					}
					break;
				case 21183: //Paladin - Heart of the Crusader
				case 54498:
				case 54499:
					{
						if(CastingSpell == NULL)
							continue;
						if(CastingSpell->Id != 53408 &&
						        CastingSpell->Id != 53407 &&
						        CastingSpell->Id != 20271)
							continue;
					}
					break;
				case 54203: //Paladin - Sheath of Light
					{
						if(CastingSpell == NULL)
							continue;
						if(CastingSpell->NameHash != SPELL_HASH_FLASH_OF_LIGHT &&
						        CastingSpell->NameHash != SPELL_HASH_HOLY_LIGHT)
							continue;
						SpellEntry* spellInfo = dbcSpell.LookupEntry(54203);
						SpellDuration* sd = dbcSpellDuration.LookupEntryForced(spellInfo->DurationIndex);
						uint32 tickcount = GetDuration(sd) / spellInfo->EffectAmplitude[0] ;
						dmg_overwrite[0] = ospinfo->EffectBasePoints[0] * dmg / (100  * tickcount);
					}
					break;
				case 59578: //Paladin - Art of War
				case 53489:
					{
						if(CastingSpell == NULL)
							continue;
						if(CastingSpell->Id != 53408 &&
						        CastingSpell->Id != 53407 &&
						        CastingSpell->Id != 20271 &&
						        CastingSpell->NameHash != SPELL_HASH_DIVINE_STORM &&
						        CastingSpell->NameHash != SPELL_HASH_CRUSADER_STRIKE)
							continue;
					}
					break;

					//////////////////////////////////////////
					// WARRIOR								//
					//////////////////////////////////////////

					// Warrior - Improved Revenge
				case 12798:
					{
						if(!CastingSpell || CastingSpell->NameHash != SPELL_HASH_REVENGE)
							continue;
					}
					break;
					// Warrior - Unrelenting Assault
				case 64849:
				case 64850:
					{
						if(CastingSpell == NULL)
							continue;
						//trigger only on heal spell cast by NOT us
						if(!(CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING) || this == victim)
							continue;
						//this is not counting the bonus effects on heal
						dmg_overwrite[0] = (CastingSpell->EffectBasePoints[IsHealingSpell(CastingSpell) - 1] + 1) * (ospinfo->EffectBasePoints[0] + 1) / 100;
					}
					break;
					//paladin - Light's Grace
				case 31834:
					{
						if(CastingSpell == NULL)
							continue;//this should not occur unless we made a fuckup somewhere
						if(CastingSpell->NameHash != SPELL_HASH_HOLY_LIGHT)
							continue;
					}
					break;
					//paladin - Blessed Life
				case 31828:
					{
						//we should test is damage is from environment or not :S
						resisted_dmg = dmg / 2;
						continue; //there is no visual for this ?
					}
					break;
					//paladin - Judgements of the Wise
				case 54180:
					{
						if(CastingSpell == NULL)
							continue;
						if(CastingSpell->Id != 53408 && CastingSpell->Id != 53407 && CastingSpell->Id != 20271)
							continue;
						if(!IsPlayer())
							continue;
					}
					break;
				case 54172: //Paladin - Divine Storm heal effect
					{
						if(CastingSpell == NULL)
							continue;
						if(CastingSpell->NameHash != SPELL_HASH_DIVINE_STORM)
							continue;
					}
					break;
					//Energized
				case 43751:
					{
						if(CastingSpell == NULL)
							continue;
						if(CastingSpell->NameHash != SPELL_HASH_LIGHTNING_BOLT)
							continue;
					}
					break;
					//Spell Haste Trinket
					//http://www.wowhead.com/?item=28190 scarab of the infinite circle
				case 33370:
					{
						if(CastingSpell == NULL)
							continue;
						if(!(CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING))
							continue;
					}
					break;
				case 60487: // Extract of Necromantic Power
					{
						if(CastingSpell == NULL)
							continue;
						if(!(CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING))
							continue;
					}
					break;
				case 33953: // The Egg of Mortal essence
					{
						if(!CastingSpell)
							continue;
						if(!(CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING))
							continue;
					}
					break;
				case 60529: // Forethough Talisman
					{
						if(!CastingSpell)
							continue;
						if(!(CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING))
							continue;
					}
					break;
				case 53390: //Tidal Waves
					{
						if(!CastingSpell)
							continue;
						if(CastingSpell->NameHash != SPELL_HASH_CHAIN_HEAL &&
						        CastingSpell->NameHash != SPELL_HASH_RIPTIDE)
							continue;
					}
					break;
					//Earthliving
				case 51945:
				case 51990:
				case 51997:
				case 51998:
				case 51999:
				case 52000:
					{
						if(!CastingSpell)
							continue;
						if(!(CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING))
							continue;
					}
					break;
					//shaman - Lightning Overload
				case 39805:
					{
						if(CastingSpell == NULL)
							continue;//this should not occur unless we made a fuckup somewhere
						//trigger on lightning and chain lightning. Spell should be identical , well maybe next time :P
						if(CastingSpell->NameHash == SPELL_HASH_LIGHTNING_BOLT || CastingSpell->NameHash == SPELL_HASH_CHAIN_LIGHTNING)
						{
							CastSpell(this, 39805, true);
							spellId = CastingSpell->Id;
							origId = 39805;
						}
						else continue;
					}
					break;
					//item - Band of the Eternal Sage
				case 35084:
					{
						if(CastingSpell == NULL)
							continue;
						if(!(CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING))     //requires offensive spell. ! might not cover all spells
							continue;
					}
					break;
					//druid - Earth and Moon
				case 60431:
				case 60432:
				case 60433:
					{
						if(CastingSpell == NULL)
							continue;
						if(CastingSpell->NameHash != SPELL_HASH_WRATH &&
						        CastingSpell->NameHash != SPELL_HASH_STARFIRE)
							continue;
					}
					break;
					// druid - Celestial Focus
				case 16922:
					{
						if(CastingSpell == NULL)
							continue;
						if(CastingSpell->NameHash != SPELL_HASH_STARFIRE)
							continue;
					}
					break;
				case 37565: //setbonus
					{
						if(!CastingSpell || CastingSpell->NameHash != SPELL_HASH_FLASH_HEAL)
							continue;
					}
					break;
					//SETBONUSES
				case 37379:
					{
						if(!CastingSpell || CastingSpell->NormalizedSchoolMask() != SCHOOL_SHADOW || !(CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING))
							continue;
					}
					break;
				case 37378:
					{
						if(!CastingSpell || CastingSpell->NormalizedSchoolMask() != SCHOOL_FIRE || !(CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING))
							continue;
					}
					break;
				case 45062: // Vial of the Sunwell
				case 39950:	// Wave Trance
					{
						if(!CastingSpell ||  !(CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING))
							continue;
					}
					break;
				case 37234:
				case 37214:
				case 37601:
					{
						if(!CastingSpell ||  !(CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING))
							continue;
					}
					break;
				case 37237:
					{
						if(!CastingSpell || CastingSpell->NameHash != SPELL_HASH_LIGHTNING_BOLT)
							continue;
					}
					break;
					//Tier 7 Warlock setbonus
				case 61082:
					{
						if(CastingSpell == NULL)
							continue;
						if(CastingSpell->NameHash != SPELL_HASH_LIFE_TAP)
							continue;
					}
					break;
					//Tier 5 Paladin setbonus - Crystalforge Battlegear or Crystalforge Raiment
				case 37196:
				case 43838:
					{
						if(!CastingSpell)
							continue;
						//CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_THE_CRUSADER &&
						if(CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_JUSTICE &&
						        CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_LIGHT &&
						        CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_WISDOM &&
						        CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_RIGHTEOUSNESS &&
						        CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_BLOOD &&
						        CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_VENGEANCE &&
						        CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_COMMAND)
							continue;
					}
					break;
				case 43837:
					{
						if(!CastingSpell || (CastingSpell->NameHash != SPELL_HASH_FLASH_OF_LIGHT && CastingSpell->NameHash != SPELL_HASH_HOLY_LIGHT))
							continue;
					}
					break;
				case 37529:
					{
						if(!CastingSpell || CastingSpell->NameHash != SPELL_HASH_OVERPOWER)
							continue;
					}
					break;
				case 37517:
					{
						if(!CastingSpell || CastingSpell->Id == 37517 || CastingSpell->NameHash != SPELL_HASH_REVENGE)
							continue;
					}
					break;
				case 38333: // Ribbon of Sacrifice
					{
						if(!CastingSpell || !(CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING))
							continue;
					}
					//SETBONUSES END
					//http://www.wowhead.com/?item=32493 Ashtongue Talisman of Shadows
				case 40480:
					{
						if(CastingSpell == NULL || CastingSpell->NameHash != SPELL_HASH_CORRUPTION)
							continue;
					}
					break;

					//http://www.wowhead.com/?item=32496  Memento of Tyrande
				case 37656: //don't say damaging spell but EACH time spell is cast there is a chance (so can be healing spell)
					{
						if(CastingSpell == NULL)
							continue;
					}
					break;
					//http://www.wowhead.com/?item=32488 Ashtongue Talisman of Insight
				case 40483:
					{
						if(CastingSpell == NULL)
							continue;
						if(!(CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING))
							continue;
					}
					break;

					//http://www.wowhead.com/?item=32487 Ashtongue Talisman of Swiftness
				case 40487:
					{
						if(CastingSpell == NULL || CastingSpell->NameHash != SPELL_HASH_STEADY_SHOT)
							continue;
					}
					break;

					//http://www.wowhead.com/?item=32485 Ashtongue Talisman of Valor
				case 40459:
					{
						if(CastingSpell == NULL || (CastingSpell->NameHash != SPELL_HASH_MORTAL_STRIKE && CastingSpell->NameHash != SPELL_HASH_BLOODTHIRST && CastingSpell->NameHash != SPELL_HASH_SHIELD_SLAM))
							continue;
					}
					break;
				case 28804://Epiphany :Each spell you cast can trigger an Epiphany, increasing your mana regeneration by 24 for 30 sec.
					{
						if(!CastingSpell)
							continue;
					}
					break;
					//SETBONUSES END
					//item - Band of the Eternal Restorer
				case 35087:
					{
						if(CastingSpell == NULL)
							continue;
						if(!(CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING)) //requires healing spell.
							continue;
					}
					break;

					//http://www.wowhead.com/?item=32486 Ashtongue Talisman of Equilibrium
				case 40452: //Mangle has a 40% chance to grant 140 Strength for 8 sec
					{
						if(CastingSpell == NULL || CastingSpell->NameHash != SPELL_HASH_MANGLE__BEAR_ || CastingSpell->NameHash != SPELL_HASH_MANGLE__CAT_)
							continue;
					}
					break;
				case 40445: //Starfire has a 25% chance to grant up to 150 spell damage for 8 sec
					{
						if(CastingSpell == NULL || CastingSpell->NameHash != SPELL_HASH_STARFIRE)
							continue;
					}
					break;
				case 40446: //Rejuvenation has a 25% chance to grant up to 210 healing for 8 sec
					{
						if(CastingSpell == NULL || CastingSpell->NameHash != SPELL_HASH_REJUVENATION)
							continue;
					}
					break;

					//http://www.wowhead.com/?item=32490 Ashtongue Talisman of Acumen
				case 40441: //Each time your Shadow Word: Pain deals damage, it has a 10% chance to grant you 220 spell damage for 10 sec
					{
						if(CastingSpell == NULL || CastingSpell->NameHash != SPELL_HASH_SHADOW_WORD__PAIN)
							continue;
					}
					break;

					//http://www.wowhead.com/?item=32490 Ashtongue Talisman of Acumen
				case 40440: //Each time your Renew heals, it has a 10% chance to grant you 220 healing for 5 sec
					{
						if(CastingSpell == NULL || CastingSpell->NameHash != SPELL_HASH_RENEW)
							continue;
					}
					break;

					//http://www.wowhead.com/?item=32492 Ashtongue Talisman of Lethality
				case 37445: //using a mana gem grants you 225 spell damage for 15 sec
					{
						if(!CastingSpell || CastingSpell->NameHash != SPELL_HASH_REPLENISH_MANA)
							continue;
					}
					break;
				case 16886: // druid - Nature's Grace
					{
						// Remove aura if it exists so it gets reapplied
						RemoveAura(16886);
					}
					break;
				case 38395:
					{
						if(CastingSpell == NULL)
							continue;
						if(CastingSpell->NameHash != SPELL_HASH_IMMOLATE &&
						        CastingSpell->NameHash != SPELL_HASH_CORRUPTION)
							continue;
					}
					break;
			}
		}

		if(spellId == 17364 || spellId == 32175 || spellId == 32176)   //Stormstrike
			continue;
		if(spellId == 22858 && isInBack(victim)) //retatliation needs target to be not in front. Can be cast by creatures too
			continue;
		for(uint32 e = 0; e >= 3; e++)
		{
			dmg_overwrite[e] = objmgr.ApplySpellDamageLimit(spellId, dmg_overwrite[e]);
		}
		spell_proc->CastSpell(victim, CastingSpell, dmg_overwrite);

		if(origId == 39805)
		{
			// Remove lightning overload aura after procing
			RemoveAura(39805);
		}
	}
	}
	catch (...)
	{
		printf("Caught fatal exception in Unit.cpp <\n");
	}

	m_chargeSpellsInUse = true;
	std::map<uint32, struct SpellCharge>::iterator iter, iter2;
	iter = m_chargeSpells.begin();

	while(iter != m_chargeSpells.end())
	{
		iter2 = iter++;

		if(iter2->second.count)
		{
			if((iter2->second.ProcFlag & flag))
			{
				//Fixes for spells that don't lose charges when dmg is absorbed
				if(iter2->second.ProcFlag == 680 && dmg == 0)
					continue;

				if(CastingSpell)
				{
					SpellCastTime* sd = dbcSpellCastTime.LookupEntryForced(CastingSpell->CastingTimeIndex);
					if(!sd)
						continue; // this shouldn't happen though :P

					//if we did not proc these then we should not remove them
					if(CastingSpell->Id == iter2->second.spellId)
						continue;

					switch(iter2->second.spellId)
					{
						case 43339: // Shaman - Shamanist Focus
							{
								if(CastingSpell->NameHash != SPELL_HASH_EARTH_SHOCK &&
								        CastingSpell->NameHash != SPELL_HASH_FLAME_SHOCK &&
								        CastingSpell->NameHash != SPELL_HASH_FROST_SHOCK)
									continue;
							}
							break;
						case 12043: // Mage - Presence of Mind
							{
								//if(!sd->CastTime||sd->CastTime>10000) continue;
								if(sd->CastTime == 0)
									continue;
							}
							break;
						case 17116: // Shaman - Nature's Swiftness
						case 16188:	// Druid - Nature's Swiftness
							{
								//if( CastingSpell->School!=SCHOOL_NATURE||(!sd->CastTime||sd->CastTime>10000)) continue;
								if(CastingSpell->NormalizedSchoolMask() != SCHOOL_NATURE || sd->CastTime == 0)
									continue;
							}
							break;
						case 16166:
							{
								if(!(CastingSpell->NormalizedSchoolMask() == SCHOOL_FIRE || CastingSpell->NormalizedSchoolMask() == SCHOOL_FROST || CastingSpell->NormalizedSchoolMask() == SCHOOL_NATURE))
									continue;
							}
							break;
						case 14177: // Cold blood will get removed on offensive spell
							{
								if(!(CastingSpell->SpellFamilyFlags[0] & 0x6820206 || CastingSpell->SpellFamilyFlags[1] & 0x240009))
									continue;
							}
							break;
						case 46916: // Bloodsurge - Slam! effect should dissapear after casting Slam only
							{
								if(CastingSpell->NameHash != SPELL_HASH_SLAM)
									continue;
							}
							break;
						case 60503: // Taste for Blood should dissapear after casting Overpower
							{
								if(CastingSpell->NameHash != SPELL_HASH_OVERPOWER)
									continue;
							}
							break;
						case 23694: // Imp. Hamstring
							{
								if(CastingSpell->NameHash != SPELL_HASH_IMPROVED_HAMSTRING)
									continue;
							}
							break;
						case 65156: // Juggernaut
							{
								if(CastingSpell->NameHash != SPELL_HASH_MORTAL_STRIKE &&
								        CastingSpell->NameHash != SPELL_HASH_SLAM)
									continue;
							}
							break;
					}
				}
				if(iter2->second.lastproc != 0)
				{
					if(iter2->second.procdiff > 3000)
					{
						//--(iter2->second.count);
						RemoveAura(iter2->second.spellId);
					}
				}
				else
				{
					//--(iter2->second.count);		// done in Aura::Remove
					this->RemoveAura(iter2->second.spellId);
				}
			}
		}
		if(!iter2->second.count)
		{
			m_chargeSpells.erase(iter2);
		}
	}

	for(; !m_chargeSpellRemoveQueue.empty();)
	{
		iter = m_chargeSpells.find(m_chargeSpellRemoveQueue.front());
		if(iter != m_chargeSpells.end())
		{
			if(iter->second.count > 1)
				--iter->second.count;
			else
				m_chargeSpells.erase(iter);
		}
		m_chargeSpellRemoveQueue.pop_front();
	}

	m_chargeSpellsInUse = false;
	if(can_delete)   //are we the upper level of nested procs ? If yes then we can remove the lock
		bProcInUse = false;

	return resisted_dmg;
}

//damage shield is a triggered spell by owner to atacker
void Unit::HandleProcDmgShield(uint32 flag, Unit* attacker)
{
	//make sure we do not loop dmg procs
	if(this == attacker || !attacker)
		return;
	if(m_damgeShieldsInUse)
		return;
	m_damgeShieldsInUse = true;
	//charges are already removed in handleproc
	WorldPacket data(24);
	std::list<DamageProc>::iterator i;
	std::list<DamageProc>::iterator i2;
	for(i = m_damageShields.begin(); i != m_damageShields.end();)    // Deal Damage to Attacker
	{
		i2 = i++; //we should not proc on proc.. not get here again.. not needed.Better safe then sorry.
		if((flag & (*i2).m_flags))
		{
			if(PROC_MISC & (*i2).m_flags)
			{
				data.Initialize(SMSG_SPELLDAMAGESHIELD);
				data << this->GetGUID();
				data << attacker->GetGUID();
				data << (*i2).m_spellId;
				data << (*i2).m_damage;
				data << (1 << (*i2).m_school);
				SendMessageToSet(&data, true);
				this->DealDamage(attacker, (*i2).m_damage, 0, 0, (*i2).m_spellId);
			}
			else
			{
				SpellEntry*	ability = dbcSpell.LookupEntry((*i2).m_spellId);
				this->Strike(attacker, RANGED, ability, 0, 0, (*i2).m_damage, true, true);  //can dmg shields miss at all ?
			}
		}
	}
	m_damgeShieldsInUse = false;
}

bool Unit::IsCasting()
{
	return (m_currentSpell != NULL);
}

bool Unit::IsInInstance()
{
	MapInfo* pMapinfo = WorldMapInfoStorage.LookupEntry(this->GetMapId());
	if(pMapinfo)
		return (pMapinfo->type != INSTANCE_NULL);

	return false;
}

void Unit::RegenerateHealth()
{

	if(HasCreatureCustomFlag(CREATURE_CUSTOMFLAG_CANT_REGEN_HEALTH))
	{
		m_H_regenTimer = sizeof(uint16);
		return;
	}

	m_H_regenTimer = 2000;//set next regen time

	if(!isAlive())
		return;

	// player regen
	if(this->IsPlayer())
	{
		// These only NOT in combat
		if(!CombatStatus.IsInCombat())
		{
			TO< Player* >(this)->RegenerateHealth(false);
		}
		else
			TO< Player* >(this)->RegenerateHealth(true);
	}
	else
	{
		// Only regen health out of combat
		if(!CombatStatus.IsInCombat())
			TO< Creature* >(this)->RegenerateHealth();
	}
}

void Unit::RegeneratePower(bool isinterrupted)
{
	// This is only 2000 IF the power is not rage
	if(isinterrupted)
		m_interruptedRegenTime = 2000;
	else
		m_P_regenTimer = 2000;//set next regen time

	if(!isAlive())
		return;

	if( !IsPlayer() && IsVehicle() ){
		uint32 powertype = GetPowerType();
		float wrate = sWorld.getRate( RATE_VEHICLES_POWER_REGEN );
		float amount = wrate * 20.0f;
		SetPower( powertype, GetPower( powertype ) + amount );
	}

	//druids regen every tick, which is every 100ms, at one energy, as of 3.0.2
	//I don't know how mana has changed exactly, but it has, will research it - optical
	if(IsPlayer() && GetPowerType() == POWER_TYPE_ENERGY)
	{
		TO< Player* >(this)->RegenerateEnergy();
		// druids regen mana when shapeshifted
		if(getClass() == DRUID)
		{
			TO< Player* >(this)->RegenerateMana(isinterrupted);
		}
		return;
	}

	// player regen
	if(this->IsPlayer())
	{
		uint32 powertype = GetPowerType();
		switch(powertype)
		{
			case POWER_TYPE_MANA:
				TO< Player* >(this)->RegenerateMana(isinterrupted);
				break;

			case POWER_TYPE_RAGE:
				{
					// These only NOT in combat
					if(!CombatStatus.IsInCombat())
					{
						m_P_regenTimer = 3000;
						if(HasAura(12296))
							TO< Player* >(this)->LooseRage(20);
						else
							TO< Player* >(this)->LooseRage(30);
					}
					else
					{
						if(HasAura(12296))
						{
							m_P_regenTimer = 3000;
							TO< Player* >(this)->LooseRage(-10);
						}
					}

				}
				break;

			case POWER_TYPE_FOCUS:
				{
					m_P_regenTimer = 350; // This seems to be the exact Blizzlike timer
					uint32 cur = GetPower(POWER_TYPE_FOCUS);
					uint32 mm = GetMaxPower(POWER_TYPE_FOCUS);
					if(cur >= mm)
						return;
					cur += 2;
					SetPower(POWER_TYPE_FOCUS, (cur >= mm) ? mm : cur);
				}
				break;

			case POWER_TYPE_RUNIC_POWER:
				{
					if(!CombatStatus.IsInCombat())
					{
						uint32 cur = GetUInt32Value(UNIT_FIELD_POWER7);
						SetPower(POWER_TYPE_RUNIC_POWER, cur - 20);
					}
				}
				break;
		}

		/*

		There is a problem here for druids.
		Druids when shapeshifted into bear have 2 power with different regen timers
		a) Mana (which regenerates while shapeshifted
		b) Rage

		Mana has a regen timer of 2 seconds
		Rage has a regen timer of 3 seconds

		I think the only viable way of fixing this is to have 2 different timers
		to check each individual power.

		Atm, mana is being regen at 3 seconds while shapeshifted...

		*/


		// druids regen mana when shapeshifted
		if(getClass() == DRUID && powertype != POWER_TYPE_MANA)
			TO< Player* >(this)->RegenerateMana(isinterrupted);
	}
	else
	{
		uint32 powertype = GetPowerType();
		switch(powertype)
		{
			case POWER_TYPE_MANA:
				TO< Creature* >(this)->RegenerateMana();
				break;
			case POWER_TYPE_FOCUS:
				TO< Creature* >(this)->RegenerateFocus();
				m_P_regenTimer = 4000;
				break;
		}
	}
}

void Unit::CalculateResistanceReduction(Unit* pVictim, dealdamage* dmg, SpellEntry* ability, float ArmorPctReduce)
{
	if(this == NULL || !IsInWorld() || pVictim == NULL || !pVictim->IsInWorld())
		return;
	float AverageResistance = 0.0f;
	float ArmorReduce;

	if((*dmg).school_type == 0)//physical
	{
		if(this->IsPlayer())
			ArmorReduce = PowerCostPctMod[0] + ((float)pVictim->GetResistance(0) * (ArmorPctReduce + TO< Player* >(this)->CalcRating(PLAYER_RATING_MODIFIER_ARMOR_PENETRATION_RATING)) / 100.0f);
		else
			ArmorReduce = 0.0f;

		if(ArmorReduce >= pVictim->GetResistance(0))		// fully penetrated :O
			return;

//		double Reduction = double(pVictim->GetResistance(0)) / double(pVictim->GetResistance(0)+400+(85*getLevel()));
		//dmg reduction formula from xinef
		double Reduction = 0;
		if(getLevel() < 60) Reduction = double(pVictim->GetResistance(0) - ArmorReduce) / double(pVictim->GetResistance(0) + 400 + (85 * getLevel()));
		else if(getLevel() > 59 && getLevel() < PLAYER_LEVEL_CAP) Reduction = double(pVictim->GetResistance(0) - ArmorReduce) / double(pVictim->GetResistance(0) - 22167.5 + (467.5 * getLevel()));
		//
		else Reduction = double(pVictim->GetResistance(0) - ArmorReduce) / double(pVictim->GetResistance(0) + 10557.5);
		if(Reduction > 0.75f) Reduction = 0.75f;
		else if(Reduction < 0) Reduction = 0;
		if(Reduction) dmg[0].full_damage = (uint32)(dmg[0].full_damage * (1 - Reduction));	 // no multiply by 0
	}
	else
	{
		// applying resistance to other type of damage
		int32 RResist = float2int32((pVictim->GetResistance((*dmg).school_type) + ((pVictim->getLevel() > getLevel()) ? (pVictim->getLevel() - this->getLevel()) * 5 : 0)) - PowerCostPctMod[(*dmg).school_type]);
		if(RResist < 0)
			RResist = 0;
		AverageResistance = (float)(RResist) / (float)(getLevel() * 5) * 0.75f;
		if(AverageResistance > 0.75f)
			AverageResistance = 0.75f;

		// NOT WOWWIKILIKE but i think it's actually to add some fullresist chance from resistances
		if(!ability || !(ability->Attributes & SPELL_ATTR0_UNAFFECTED_BY_INVULNERABILITY))
		{
			float Resistchance = (float)pVictim->GetResistance((*dmg).school_type) / (float)pVictim->getLevel();
			Resistchance *= Resistchance;
			if(Rand(Resistchance))
				AverageResistance = 1.0f;
		}

		if(AverageResistance > 0)
			(*dmg).resisted_damage = (uint32)(((*dmg).full_damage) * AverageResistance);
		else
			(*dmg).resisted_damage = 0;
	}
}

uint32 Unit::GetSpellDidHitResult(Unit* pVictim, uint32 weapon_damage_type, SpellEntry* ability)
{
	Item* it = NULL;
	float hitchance          = 0.0f;
	float dodge				 = 0.0f;
	float parry				 = 0.0f;
	float block				 = 0.0f;

	float hitmodifier		 = 0;
	int32 self_skill;
	int32 victim_skill;
	uint32 SubClassSkill	 = SKILL_UNARMED;

	bool backAttack			 = !pVictim->isInFront(this);   // isInBack is bugged!
	uint32 vskill            = 0;

	//==========================================================================================
	//==============================Victim Skill Base Calculation===============================
	//==========================================================================================
	if(pVictim->IsPlayer())
	{
		vskill = TO< Player* >(pVictim)->_GetSkillLineCurrent(SKILL_DEFENSE);
		if(weapon_damage_type != RANGED && !backAttack)
		{
			//--------------------------------block chance----------------------------------------------
			block = pVictim->GetFloatValue(PLAYER_BLOCK_PERCENTAGE); //shield check already done in Update chances
			//--------------------------------dodge chance----------------------------------------------
			if(pVictim->m_stunned <= 0)
			{
				dodge = pVictim->GetFloatValue(PLAYER_DODGE_PERCENTAGE);
			}
			//--------------------------------parry chance----------------------------------------------
			if(pVictim->can_parry && !pVictim->disarmed)
			{
				if(TO< Player* >(pVictim)->HasSpell(3127) || TO< Player* >(pVictim)->HasSpell(18848))
				{
					parry = pVictim->GetFloatValue(PLAYER_PARRY_PERCENTAGE);
				}
			}
		}
		victim_skill = float2int32(vskill + TO< Player* >(pVictim)->CalcRating(PLAYER_RATING_MODIFIER_DEFENCE));
	}
	//--------------------------------mob defensive chances-------------------------------------
	else
	{
		if(weapon_damage_type != RANGED && !backAttack)
			dodge = pVictim->GetStat(STAT_AGILITY) / 14.5f; // what is this value?
		victim_skill = pVictim->getLevel() * 5;
		if(pVictim->IsCreature())
		{
			Creature* c = TO_CREATURE(pVictim);
			if(c->GetCreatureInfo()->Rank == ELITE_WORLDBOSS)
			{
				victim_skill = std::max(victim_skill, ((int32)this->getLevel() + 3) * 5); //used max to avoid situation when lowlvl hits boss.
			}
		}
	}
	//==========================================================================================
	//==============================Attacker Skill Base Calculation=============================
	//==========================================================================================
	if(this->IsPlayer())
	{
		self_skill = 0;
		Player* pr = TO< Player* >(this);
		hitmodifier = pr->GetHitFromMeleeSpell();

		switch(weapon_damage_type)
		{
			case MELEE:   // melee main hand weapon
				it = disarmed ? NULL : pr->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_MAINHAND);
				hitmodifier += pr->CalcRating(PLAYER_RATING_MODIFIER_MELEE_HIT);
				self_skill = float2int32(pr->CalcRating(PLAYER_RATING_MODIFIER_MELEE_MAIN_HAND_SKILL));
				break;
			case OFFHAND: // melee offhand weapon (dualwield)
				it = disarmed ? NULL : pr->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_OFFHAND);
				hitmodifier += pr->CalcRating(PLAYER_RATING_MODIFIER_MELEE_HIT);
				self_skill = float2int32(pr->CalcRating(PLAYER_RATING_MODIFIER_MELEE_OFF_HAND_SKILL));
				break;
			case RANGED:  // ranged weapon
				it = disarmed ? NULL : pr->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_RANGED);
				hitmodifier += pr->CalcRating(PLAYER_RATING_MODIFIER_RANGED_HIT);
				self_skill = float2int32(pr->CalcRating(PLAYER_RATING_MODIFIER_RANGED_SKILL));
				break;
		}

		// erm. some spells don't use ranged weapon skill but are still a ranged spell and use melee stats instead
		// i.e. hammer of wrath
		if(ability && ability->NameHash == SPELL_HASH_HAMMER_OF_WRATH)
		{
			it = pr->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_MAINHAND);
			hitmodifier += pr->CalcRating(PLAYER_RATING_MODIFIER_MELEE_HIT);
			self_skill = float2int32(pr->CalcRating(PLAYER_RATING_MODIFIER_MELEE_MAIN_HAND_SKILL));
		}
		if(it)
			SubClassSkill = GetSkillByProto(it->GetProto()->Class, it->GetProto()->SubClass);
		else
			SubClassSkill = SKILL_UNARMED;

		if(SubClassSkill == SKILL_FIST_WEAPONS)
			SubClassSkill = SKILL_UNARMED;

		//chances in feral form don't depend on weapon skill
		if(TO< Player* >(this)->IsInFeralForm())
		{
			uint8 form = TO< Player* >(this)->GetShapeShift();
			if(form == FORM_CAT || form == FORM_BEAR || form == FORM_DIREBEAR)
			{
				SubClassSkill = SKILL_FERAL_COMBAT;
				// Adjust skill for Level * 5 for Feral Combat
				self_skill += pr->getLevel() * 5;
			}
		}


		self_skill += pr->_GetSkillLineCurrent(SubClassSkill);
	}
	else
	{
		self_skill = this->getLevel() * 5;
		if(IsCreature())
		{
			Creature* c = TO_CREATURE(this);
			if(c->GetCreatureInfo()->Rank == ELITE_WORLDBOSS)
				self_skill = std::max(self_skill, ((int32)pVictim->getLevel() + 3) * 5); //used max to avoid situation when lowlvl hits boss.
		}
	}
	//==========================================================================================
	//==============================Special Chances Base Calculation============================
	//==========================================================================================
	//<THE SHIT> to avoid Linux bug.
	float diffVcapped = (float)self_skill;
	if(int32(pVictim->getLevel() * 5) > victim_skill)
		diffVcapped -= (float)victim_skill;
	else
		diffVcapped -= (float)(pVictim->getLevel() * 5);

	float diffAcapped = (float)victim_skill;
	if(int32(this->getLevel() * 5) > self_skill)
		diffAcapped -= (float)self_skill;
	else
		diffAcapped -= (float)(getLevel() * 5);
	//<SHIT END>

	//--------------------------------by victim state-------------------------------------------
	if(pVictim->IsPlayer() && pVictim->GetStandState()) //every not standing state is >0
	{
		hitchance = 100.0f;
	}

	//--------------------------------by damage type and by weapon type-------------------------
	if(weapon_damage_type == RANGED)
	{
		dodge = 0.0f;
		parry = 0.0f;
	}

	//--------------------------------by skill difference---------------------------------------
	float vsk = (float)self_skill - (float)victim_skill;
	dodge = std::max(0.0f, dodge - vsk * 0.04f);
	if(parry)
		parry = std::max(0.0f, parry - vsk * 0.04f);
	if(block)
		block = std::max(0.0f, block - vsk * 0.04f);

	if(vsk > 0)
		hitchance = std::max(hitchance, 95.0f + vsk * 0.02f + hitmodifier);
	else
	{
		if(pVictim->IsPlayer())
			hitchance = std::max(hitchance, 95.0f + vsk * 0.1f + hitmodifier);   //wowwiki multiplier - 0.04 but i think 0.1 more balanced
		else
			hitchance = std::max(hitchance, 100.0f + vsk * 0.6f + hitmodifier);   //not wowwiki but more balanced
	}

	/*if(ability && ability->SpellFamilyFlags)
	{
		if(Player * p = GetSpellModOwner())
			p->ApplySpellMod(ability->Id, SPELLMOD_RESIST_MISS_CHANCE, hitchance);
	}*/

	if(ability && ability->Attributes & SPELL_ATTR0_IMPOSSIBLE_DODGE_PARRY_BLOCK)
	{
		dodge = 0.0f;
		parry = 0.0f;
		block = 0.0f;
	}

	//==========================================================================================
	//==============================One Roll Processing=========================================
	//==========================================================================================
	//--------------------------------cumulative chances generation----------------------------
	float chances[4];
	chances[0] = std::max(0.0f, 100.0f - hitchance);
	chances[1] = chances[0] + dodge;
	chances[2] = chances[1] + parry;
	chances[3] = chances[2] + block;


	//--------------------------------roll------------------------------------------------------
	float Roll = RandomFloat(100.0f);
	uint32 r = 0;
	while(r < 4 && Roll > chances[r])
	{

		r++;
	}

	uint32 roll_results[5] = { SPELL_DID_HIT_MISS, SPELL_DID_HIT_DODGE, SPELL_DID_HIT_PARRY, SPELL_DID_HIT_BLOCK, SPELL_DID_HIT_SUCCESS };
	return roll_results[r];
}

void Unit::Strike(Unit* pVictim, uint32 weapon_damage_type, SpellEntry* ability, int32 add_damage, int32 pct_dmg_mod, uint32 exclusive_damage, bool disable_proc, bool skip_hit_check, bool force_crit)
{
//==========================================================================================
//==============================Unacceptable Cases Processing===============================
//==========================================================================================
	if(!pVictim || !pVictim->isAlive() || !isAlive()  || IsStunned() || IsPacified() || IsFeared())
		return;

//==========================================================================================
//==============================Variables Initialization====================================
//==========================================================================================
	dealdamage dmg			  = {0, 0, 0};

	Item* it = NULL;

	float hitchance          = 0.0f;
	float dodge				 = 0.0f;
	float parry				 = 0.0f;
	float glanc              = 0.0f;
	float block				 = 0.0f;
	float crit				 = 0.0f;
	float crush              = 0.0f;

	uint32 targetEvent		 = 0;
	uint32 hit_status		 = 0;

	uint32 blocked_damage	 = 0;
	int32  realdamage		 = 0;

	uint32 vstate			 = 1;
	uint32 aproc			 = 0;
	uint32 vproc			 = 0;

	float hitmodifier		 = 0;
	float ArmorPctReduce	 = m_ignoreArmorPct;
	int32 self_skill;
	int32 victim_skill;
	uint32 SubClassSkill	 = SKILL_UNARMED;

	bool backAttack			 = !pVictim->isInFront(this);
	uint32 vskill            = 0;
	bool disable_dR			 = false;

	if(ability)
		dmg.school_type = ability->NormalizedSchoolMask();
	else
	{
		if(IsCreature())
			dmg.school_type = TO< Creature* >(this)->BaseAttackType;
		else
			dmg.school_type = SCHOOL_NORMAL;
	}

//==========================================================================================
//==============================Victim Skill Base Calculation===============================
//==========================================================================================
	if(pVictim->IsPlayer())
	{
		Player* plr = TO< Player* >(pVictim);
		vskill = plr->_GetSkillLineCurrent(SKILL_DEFENSE);

		if(!backAttack)
		{
			// not an attack from behind so we may dodge/parry/block

			//uint32 pClass = plr->getClass();
			//uint32 pLevel = (getLevel() > PLAYER_LEVEL_CAP) ? PLAYER_LEVEL_CAP : getLevel();

			if(weapon_damage_type != RANGED)
			{
				// cannot dodge/parry ranged attacks

				if(pVictim->m_stunned <= 0)
				{
					// can dodge as long as we're not stunned
					dodge = plr->GetDodgeChance();
				}

				if(pVictim->can_parry && !disarmed)
				{
					// can parry as long as we're not disarmed
					parry = plr->GetParryChance();
				}
			}
			// can block ranged attacks

			// Is an offhand equipped and is it a shield?
			Item* it2 = plr->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_OFFHAND);
			if(it2 != NULL && it2->GetProto()->InventoryType == INVTYPE_SHIELD)
			{
				block = plr->GetBlockChance();
			}
		}
		victim_skill = float2int32(vskill + floorf(plr->CalcRating(PLAYER_RATING_MODIFIER_DEFENCE)));
	}
//--------------------------------mob defensive chances-------------------------------------
	else
	{
		// not a player, must be a creature
		Creature* c = TO< Creature* >(pVictim);

		// mobs can dodge attacks from behind
		if(!pVictim->isTrainingDummy() && weapon_damage_type != RANGED && pVictim->m_stunned <= 0)
		{
			dodge = pVictim->GetUInt32Value(UNIT_FIELD_AGILITY) / 14.5f;
			dodge += pVictim->GetDodgeFromSpell();
		}

		if(!backAttack)
		{
			// can parry attacks from the front
			// TODO different bosses have different parry rates (db patch?)
			if(!pVictim->isTrainingDummy() && !disarmed)    // TODO this is wrong
			{
				parry = c->GetBaseParry();
				parry += pVictim->GetParryFromSpell();
			}

			// TODO add shield check/block chance here
			// how do we check what the creature has equipped?
		}

		victim_skill = pVictim->getLevel() * 5;
		if(pVictim->IsCreature())
		{
			if(c->GetCreatureInfo()->Rank == ELITE_WORLDBOSS)
			{
				victim_skill = std::max(victim_skill, ((int32)getLevel() + 3) * 5);     //used max to avoid situation when lowlvl hits boss.
			}
		}
	}
//==========================================================================================
//==============================Attacker Skill Base Calculation=============================
//==========================================================================================
	if(this->IsPlayer())
	{
		self_skill = 0;
		Player* pr = TO< Player* >(this);
		hitmodifier = pr->GetHitFromMeleeSpell();

		switch(weapon_damage_type)
		{
			case MELEE:   // melee main hand weapon
				it = disarmed ? NULL : pr->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_MAINHAND);
				self_skill = float2int32(pr->CalcRating(PLAYER_RATING_MODIFIER_MELEE_MAIN_HAND_SKILL));
				if(it)
				{
					dmg.school_type = it->GetProto()->Damage[0].Type;
					if(it->GetProto()->SubClass == ITEM_SUBCLASS_WEAPON_MACE)
						ArmorPctReduce += m_ignoreArmorPctMaceSpec;
				}
				break;
			case OFFHAND: // melee offhand weapon (dualwield)
				it = disarmed ? NULL : pr->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_OFFHAND);
				self_skill = float2int32(pr->CalcRating(PLAYER_RATING_MODIFIER_MELEE_OFF_HAND_SKILL));
				hit_status |= HITSTATUS_DUALWIELD;//animation
				if(it)
				{
					dmg.school_type = it->GetProto()->Damage[0].Type;
					if(it->GetProto()->SubClass == ITEM_SUBCLASS_WEAPON_MACE)
						ArmorPctReduce += m_ignoreArmorPctMaceSpec;
				}
				break;
			case RANGED:  // ranged weapon
				it = disarmed ? NULL : pr->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_RANGED);
				self_skill = float2int32(pr->CalcRating(PLAYER_RATING_MODIFIER_RANGED_SKILL));
				if(it)
					dmg.school_type = it->GetProto()->Damage[0].Type;
				break;
		}

		if(it)
		{
			SubClassSkill = GetSkillByProto(it->GetProto()->Class, it->GetProto()->SubClass);
			if(SubClassSkill == SKILL_FIST_WEAPONS)
				SubClassSkill = SKILL_UNARMED;
		}
		else
			SubClassSkill = SKILL_UNARMED;


		//chances in feral form don't depend on weapon skill
		if(pr->IsInFeralForm())
		{
			uint8 form = pr->GetShapeShift();
			if(form == FORM_CAT || form == FORM_BEAR || form == FORM_DIREBEAR)
			{
				SubClassSkill = SKILL_FERAL_COMBAT;
				self_skill += pr->getLevel() * 5;
			}
		}

		self_skill += pr->_GetSkillLineCurrent(SubClassSkill);
		crit = GetFloatValue(PLAYER_CRIT_PERCENTAGE);
	}
	else
	{
		self_skill = this->getLevel() * 5;
		if(IsCreature())
		{
			Creature* c = TO_CREATURE(this);
			if(c->GetCreatureInfo()->Rank == ELITE_WORLDBOSS)
				self_skill = std::max(self_skill, ((int32)pVictim->getLevel() + 3) * 5); //used max to avoid situation when lowlvl hits boss.
		}
		crit = 5.0f; //will be modified later
	}
//==========================================================================================
//==============================Special Chances Base Calculation============================
//==========================================================================================

//--------------------------------crushing blow chance--------------------------------------
	//http://www.wowwiki.com/Crushing_blow
	if(pVictim->IsPlayer() && !this->IsPlayer() && !ability && !dmg.school_type)
	{
		int32 baseDefense = TO< Player* >(pVictim)->_GetSkillLineCurrent(SKILL_DEFENSE, false);
		int32 skillDiff = self_skill - baseDefense;
		if(skillDiff >= 15)
			crush = -15.0f + 2.0f * skillDiff;
		else
			crush = 0.0f;
	}
//--------------------------------glancing blow chance--------------------------------------
	//http://www.wowwiki.com/Glancing_blow
	// did my own quick research here, seems base glancing against equal level mob is about 5%
	// and goes up 5% each level. Need to check this further.
	float diffAcapped = victim_skill - std::min((float)self_skill, getLevel() * 5.0f);

	if(this->IsPlayer() && !pVictim->IsPlayer() && !ability)
	{
		glanc = 5.0f + diffAcapped;
		if(glanc < 0)
			glanc = 0.0f;
	}
//==========================================================================================
//==============================Advanced Chances Modifications==============================
//==========================================================================================
//--------------------------------by talents------------------------------------------------
	if(pVictim->IsPlayer())
	{
		if(weapon_damage_type != RANGED)
		{
			crit += TO< Player* >(pVictim)->res_M_crit_get();
			hitmodifier += TO< Player* >(pVictim)->m_resist_hit[ MOD_MELEE ];
		}
		else
		{
			crit += TO< Player* >(pVictim)->res_R_crit_get(); //this could be ability but in that case we overwrite the value
			hitmodifier += TO< Player* >(pVictim)->m_resist_hit[ MOD_RANGED ];
		}
	}
	crit += (float)(pVictim->AttackerCritChanceMod[0]);
//--------------------------------by skill difference---------------------------------------

	float vsk = (float)(self_skill - victim_skill);
	dodge = std::max(0.0f, dodge - vsk * 0.04f);
	if(parry)
		parry = std::max(0.0f, parry - vsk * 0.04f);
	if(block)
		block = std::max(0.0f, block - vsk * 0.04f);

	crit += pVictim->IsPlayer() ? vsk * 0.04f : min(vsk * 0.2f, 0.0f);

	// http://www.wowwiki.com/Miss
	float misschance;
	float ask = -vsk;
	if(pVictim->IsPlayer())
	{
		if(ask > 0)
			misschance = ask * 0.04f;
		else
			misschance = ask * 0.02f;
	}
	else
	{
		if(ask <= 10)
			misschance = ask * 0.1f;
		else
			misschance = 2 + (ask - 10) * 0.4f;
	}
	hitchance = 100.0f - misschance; // base miss chances are worked out further down

	if(ability && ability->SpellFamilyFlags)
	{
		if(Player * p = GetSpellModOwner())
		{
			p->ApplySpellMod(ability->Id, SPELLMOD_CRITICAL_CHANCE, crit);
			p->ApplySpellMod(ability->Id, SPELLMOD_RESIST_MISS_CHANCE, hitchance);
		}
	}
//--------------------------------by ratings------------------------------------------------
	crit -= pVictim->IsPlayer() ? TO< Player* >(pVictim)->CalcRating(PLAYER_RATING_MODIFIER_MELEE_CRIT_RESILIENCE) : 0.0f;
	if(crit < 0) crit = 0.0f;
	if(this->IsPlayer())
	{
		Player* plr = TO< Player* >(this);
		hitmodifier += (weapon_damage_type == RANGED) ? plr->CalcRating(PLAYER_RATING_MODIFIER_RANGED_HIT) : plr->CalcRating(PLAYER_RATING_MODIFIER_MELEE_HIT);

		float expertise_bonus = plr->CalcRating(PLAYER_RATING_MODIFIER_EXPERTISE);
		if(weapon_damage_type == MELEE)
			expertise_bonus += plr->GetUInt32Value(PLAYER_EXPERTISE);
		else if(weapon_damage_type == OFFHAND)
			expertise_bonus += plr->GetUInt32Value(PLAYER_OFFHAND_EXPERTISE);

		dodge -= expertise_bonus;
		if(dodge < 0)
			dodge = 0.0f;

		parry -= expertise_bonus;
		if(parry < 0)
			parry = 0.0f;
	}
//--------------------------------by aura mods-------------------------
	//Aura 248 SPELL_AURA_MOD_COMBAT_RESULT_CHANCE
	dodge += m_CombatResult_Dodge;
	if(dodge < 0)
		dodge = 0.0f;

	//parry += m_CombatResult_Parry;
	//if( parry < 0 )
	//parry = 0.0f;

//--------------------------------by damage type and by weapon type-------------------------
	if(weapon_damage_type == RANGED)
	{
		dodge = 0.0f;
		parry = 0.0f;
		glanc = 0.0f;
	}

	if(this->IsPlayer())
	{
		it = TO< Player* >(this)->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_OFFHAND);
		if(!ability && it != NULL
		        && (it->GetProto()->InventoryType == INVTYPE_WEAPON || it->GetProto()->InventoryType == INVTYPE_WEAPONOFFHAND))
		{
			// offhand weapon can either be a 1 hander weapon or an offhander weapon
			hitmodifier -= 24.0f; //dualwield miss chance
		}
		else
		{
			hitmodifier -= 5.0f; // base miss chance
		}
	}
	else
	{
		// mobs base hit chance
		hitmodifier -= 5.0f;
	}

	hitchance += hitmodifier;

	//Hackfix for Surprise Attacks
	if(this->IsPlayer() && ability && TO< Player* >(this)->m_finishingmovesdodge && ability->c_is_flags & SPELL_FLAG_IS_FINISHING_MOVE)
		dodge = 0.0f;

	if(skip_hit_check)
	{
		hitchance = 100.0f;
		dodge = 0.0f;
		parry = 0.0f;
		block = 0.0f;
	}

	if(ability != NULL && ability->Attributes & SPELL_ATTR0_IMPOSSIBLE_DODGE_PARRY_BLOCK)
	{
		dodge = 0.0f;
		parry = 0.0f;
		block = 0.0f;
	}

	if(ability && ability->AttributesEx2 & SPELL_ATTR2_CANT_CRIT)
		crit = 0.0f;

//--------------------------------by victim state-------------------------------------------
	if(pVictim->IsPlayer() && pVictim->GetStandState()) //every not standing state is >0
	{
		hitchance = 100.0f;
		dodge = 0.0f;
		parry = 0.0f;
		block = 0.0f;
		crush = 0.0f;
		crit = 100.0f;
	}
	if(backAttack)
	{
		if(pVictim->IsPlayer())
		{
			//However mobs can dodge attacks from behind
			dodge = 0.0f;
		}
		parry = 0.0f;
		block = 0.0f;
	}
//==========================================================================================
//==============================One Roll Processing=========================================
//==========================================================================================
	//--------------------------------cumulative chances generation----------------------------
	float chances[7];
	chances[0] = std::max(0.0f, 100.0f - hitchance);
	chances[1] = chances[0] + dodge;
	chances[2] = chances[1] + parry;
	chances[3] = chances[2] + glanc;
	chances[4] = chances[3] + block;
	chances[5] = chances[4] + crit;
	chances[6] = chances[5] + crush;

	//printf("%s:-\n", IsPlayer() ? "Player" : "Mob");
	//printf(" miss: %.2f\n", chances[0]);
	//printf("dodge: %.2f\n", dodge);
	//printf("parry: %.2f\n", parry);
	//printf("glanc: %.2f\n", glanc);
	//printf("block: %.2f\n", block);
	//printf(" crit: %.2f\n", crit);
	//printf("crush: %.2f\n", crush);

//--------------------------------roll------------------------------------------------------
	float Roll = RandomFloat(100.0f);
	uint32 r = 0;
	while(r < 7 && Roll > chances[r])
	{
		r++;
	}
	if(force_crit)
		r = 5;
//--------------------------------postroll processing---------------------------------------
	uint32 abs = 0;


	//trigger hostile action in ai
	pVictim->GetAIInterface()->HandleEvent(EVENT_HOSTILEACTION, this, 0);

	switch(r)
	{
//--------------------------------miss------------------------------------------------------
		case 0:
			hit_status |= HITSTATUS_MISS;
			// dirty ai agro fix
			if(pVictim->IsCreature() && pVictim->GetAIInterface()->getNextTarget() == NULL)
				pVictim->GetAIInterface()->AttackReaction(this, 1, 0);
			break;
//--------------------------------dodge-----------------------------------------------------
		case 1:
			// dirty ai agro fix
			if(pVictim->IsCreature() && pVictim->GetAIInterface()->getNextTarget() == NULL)
				pVictim->GetAIInterface()->AttackReaction(this, 1, 0);

			CALL_SCRIPT_EVENT(pVictim, OnTargetDodged)(this);
			CALL_SCRIPT_EVENT(this, OnDodged)(this);
			targetEvent = 1;
			vstate = DODGE;
			vproc |= PROC_ON_DODGE_VICTIM;
			pVictim->Emote(EMOTE_ONESHOT_PARRYUNARMED);			// Animation
			if(this->IsPlayer() && this->getClass() == WARRIOR)
			{

				TO< Player* >(this)->AddComboPoints(pVictim->GetGUID(), 1);
				TO< Player* >(this)->UpdateComboPoints();
				if(!sEventMgr.HasEvent(TO< Player* >(this), EVENT_COMBO_POINT_CLEAR_FOR_TARGET))
					sEventMgr.AddEvent(TO< Player* >(this), &Player::NullComboPoints, (uint32)EVENT_COMBO_POINT_CLEAR_FOR_TARGET, (uint32)5000, (uint32)1, (uint32)0);
				else
					sEventMgr.ModifyEventTimeLeft(TO< Player* >(this), EVENT_COMBO_POINT_CLEAR_FOR_TARGET, 5000 , 0);
			}

			pVictim->SetFlag(UNIT_FIELD_AURASTATE, AURASTATE_FLAG_DODGE_BLOCK);
			if(!sEventMgr.HasEvent(pVictim, EVENT_DODGE_BLOCK_FLAG_EXPIRE))
				sEventMgr.AddEvent(pVictim, &Unit::EventAurastateExpire, (uint32)AURASTATE_FLAG_DODGE_BLOCK, EVENT_DODGE_BLOCK_FLAG_EXPIRE, 5000, 1, 0);
			else sEventMgr.ModifyEventTimeLeft(pVictim, EVENT_DODGE_BLOCK_FLAG_EXPIRE, 5000, 0);
			break;
//--------------------------------parry-----------------------------------------------------
		case 2:
			// dirty ai agro fix
			if(pVictim->IsCreature() && pVictim->GetAIInterface()->getNextTarget() == NULL)
				pVictim->GetAIInterface()->AttackReaction(this, 1, 0);

			CALL_SCRIPT_EVENT(pVictim, OnTargetParried)(this);
			CALL_SCRIPT_EVENT(this, OnParried)(this);
			targetEvent = 3;
			vstate = PARRY;
			pVictim->Emote(EMOTE_ONESHOT_PARRYUNARMED);			// Animation
			if(pVictim->IsPlayer())
			{
				pVictim->SetFlag(UNIT_FIELD_AURASTATE, AURASTATE_FLAG_PARRY);	//SB@L: Enables spells requiring parry
				if(!sEventMgr.HasEvent(pVictim, EVENT_PARRY_FLAG_EXPIRE))
					sEventMgr.AddEvent(pVictim, &Unit::EventAurastateExpire, (uint32)AURASTATE_FLAG_PARRY, EVENT_PARRY_FLAG_EXPIRE, 5000, 1, 0);
				else
					sEventMgr.ModifyEventTimeLeft(pVictim, EVENT_PARRY_FLAG_EXPIRE, 5000);
				if(TO< Player* >(pVictim)->getClass() == 1 || TO< Player* >(pVictim)->getClass() == 4)      //warriors for 'revenge' and rogues for 'riposte'
				{
					pVictim->SetFlag(UNIT_FIELD_AURASTATE, AURASTATE_FLAG_DODGE_BLOCK);	//SB@L: Enables spells requiring dodge
					if(!sEventMgr.HasEvent(pVictim, EVENT_DODGE_BLOCK_FLAG_EXPIRE))
						sEventMgr.AddEvent(pVictim, &Unit::EventAurastateExpire, (uint32)AURASTATE_FLAG_DODGE_BLOCK, EVENT_DODGE_BLOCK_FLAG_EXPIRE, 5000, 1, 0);
					else
						sEventMgr.ModifyEventTimeLeft(pVictim, EVENT_DODGE_BLOCK_FLAG_EXPIRE, 5000);
				}
			}
			break;
//--------------------------------not miss,dodge or parry-----------------------------------
		default:
			hit_status |= HITSTATUS_HITANIMATION;//hit animation on victim
			if(pVictim->SchoolImmunityList[0])
				vstate = IMMUNE;
			else
			{
//--------------------------------state proc initialization---------------------------------
				vproc |= PROC_ON_ANY_DAMAGE_VICTIM;
				if(weapon_damage_type != RANGED)
				{
					aproc |= PROC_ON_MELEE_ATTACK;
					vproc |= PROC_ON_MELEE_ATTACK_VICTIM;
				}
				else
				{
					aproc |= PROC_ON_RANGED_ATTACK;
					vproc |= PROC_ON_RANGED_ATTACK_VICTIM;
					if(ability && ability->Id == 3018 && IsPlayer() && getClass() == HUNTER)
						aproc |= PROC_ON_AUTO_SHOT_HIT;
				}
//--------------------------------base damage calculation-----------------------------------
				if(exclusive_damage)
					dmg.full_damage = exclusive_damage;
				else
				{
					if(weapon_damage_type == MELEE && ability)
						dmg.full_damage = CalculateDamage(this, pVictim, MELEE, ability->SpellFamilyFlags, ability);
					else
						dmg.full_damage = CalculateDamage(this, pVictim, weapon_damage_type, 0, ability);
				}

				if(pct_dmg_mod > 0)
					dmg.full_damage = dmg.full_damage * pct_dmg_mod / 100;

				dmg.full_damage += add_damage;

				dmg.full_damage += pVictim->DamageTakenMod[dmg.school_type];
				if(weapon_damage_type == RANGED)
				{
					dmg.full_damage += pVictim->RangedDamageTaken;
				}

				if(ability && ability->Mechanic == MECHANIC_BLEEDING)
					disable_dR = true;


				dmg.full_damage += float2int32(dmg.full_damage * pVictim->DamageTakenPctMod[ dmg.school_type ]);

				if(dmg.school_type != SCHOOL_NORMAL)
					dmg.full_damage += float2int32(dmg.full_damage * (GetDamageDonePctMod(dmg.school_type) - 1));

				if(ability != NULL && ability->NameHash == SPELL_HASH_SHRED)
					dmg.full_damage += float2int32(dmg.full_damage *  pVictim->ModDamageTakenByMechPCT[MECHANIC_BLEEDING]);
				if(ability != NULL && ability->NameHash == SPELL_HASH_MAUL)
					dmg.full_damage += float2int32(dmg.full_damage *  pVictim->ModDamageTakenByMechPCT[MECHANIC_BLEEDING]);

				//pet happiness state dmg modifier
				if(IsPet() && !TO< Pet* >(this)->IsSummonedPet())
					dmg.full_damage = (dmg.full_damage <= 0) ? 0 : float2int32(dmg.full_damage * TO< Pet* >(this)->GetHappinessDmgMod());

				if(dmg.full_damage < 0)
					dmg.full_damage = 0;
//--------------------------------check for special hits------------------------------------
				switch(r)
				{
//--------------------------------glancing blow---------------------------------------------
					case 3:
						{
							float low_dmg_mod = 1.5f - (0.05f * diffAcapped);
							if(low_dmg_mod < 0.01)
								low_dmg_mod = 0.01f;
							if(low_dmg_mod > 0.91)
								low_dmg_mod = 0.91f;
							float high_dmg_mod = 1.2f - (0.03f * diffAcapped);
							if(high_dmg_mod > 0.99)
								high_dmg_mod = 0.99f;
							if(high_dmg_mod < 0.2)
								high_dmg_mod = 0.2f;

							float damage_reduction = (high_dmg_mod + low_dmg_mod) / 2.0f;
							if(damage_reduction > 0)
							{
								dmg.full_damage = float2int32(damage_reduction * dmg.full_damage);
							}
							hit_status |= HITSTATUS_GLANCING;
						}
						break;
//--------------------------------block-----------------------------------------------------
					case 4:
						{
							Item* shield = TO< Player* >(pVictim)->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_OFFHAND);
							if(shield != NULL)
							{
								targetEvent = 2;
								pVictim->Emote(EMOTE_ONESHOT_PARRYSHIELD);// Animation

								if(shield->GetProto()->InventoryType == INVTYPE_SHIELD)
								{
									float block_multiplier = (100.0f + TO< Player* >(pVictim)->m_modblockabsorbvalue) / 100.0f;
									if(block_multiplier < 1.0f)block_multiplier = 1.0f;

									blocked_damage = float2int32((shield->GetProto()->Block + ((TO< Player* >(pVictim)->m_modblockvaluefromspells + pVictim->GetUInt32Value(PLAYER_RATING_MODIFIER_BLOCK))) + ((pVictim->GetStat(STAT_STRENGTH) / 2.0f) - 1.0f)) * block_multiplier);

									if(Rand(m_BlockModPct))
										blocked_damage *= 2;
								}
								else
								{
									blocked_damage = 0;
								}

								if(dmg.full_damage <= (int32)blocked_damage)
									vstate = BLOCK;
								if(blocked_damage)
								{
									CALL_SCRIPT_EVENT(pVictim, OnTargetBlocked)(this, blocked_damage);
									CALL_SCRIPT_EVENT(this, OnBlocked)(pVictim, blocked_damage);
									vproc |= PROC_ON_BLOCK_VICTIM;
								}
								if(pVictim->IsPlayer())  //not necessary now but we'll have blocking mobs in future
								{
									pVictim->SetFlag(UNIT_FIELD_AURASTATE, AURASTATE_FLAG_DODGE_BLOCK);	//SB@L: Enables spells requiring dodge
									if(!sEventMgr.HasEvent(pVictim, EVENT_DODGE_BLOCK_FLAG_EXPIRE))
										sEventMgr.AddEvent(pVictim, &Unit::EventAurastateExpire, (uint32)AURASTATE_FLAG_DODGE_BLOCK, EVENT_DODGE_BLOCK_FLAG_EXPIRE, 5000, 1, 0);
									else
										sEventMgr.ModifyEventTimeLeft(pVictim, EVENT_DODGE_BLOCK_FLAG_EXPIRE, 5000);
								}
							}
						}
						break;
//--------------------------------critical hit----------------------------------------------
					case 5:
						{
							hit_status |= HITSTATUS_CRICTICAL;
							int32 dmgbonus = dmg.full_damage;
							//sLog.outString( "DEBUG: Critical Strike! Full_damage: %u" , dmg.full_damage );
							if(ability && ability->SpellFamilyFlags)
							{
								int32 dmg_bonus_pct = 100;
								if(Player * p = GetSpellModOwner())
									p->ApplySpellMod(ability->Id, SPELLMOD_CRIT_DAMAGE_BONUS, dmg_bonus_pct);
								dmgbonus = dmgbonus * dmg_bonus_pct / 100;
							}

							//sLog.outString( "DEBUG: After CritMeleeDamageTakenPctMod: %u" , dmg.full_damage );
							if(IsPlayer())
							{
								if(weapon_damage_type != RANGED)
								{
									dmg.full_damage += dmg.full_damage * TO< Player* >(this)->m_modphyscritdmgPCT / 100;
								}
								if(!pVictim->IsPlayer())
									dmg.full_damage += float2int32(dmg.full_damage * TO< Player* >(this)->IncreaseCricticalByTypePCT[TO_CREATURE(pVictim)->GetCreatureInfo()->Type]);
								//sLog.outString( "DEBUG: After IncreaseCricticalByTypePCT: %u" , dmg.full_damage );
							}

							dmg.full_damage += dmgbonus;

							if(weapon_damage_type == RANGED)
								dmg.full_damage = dmg.full_damage - float2int32(dmg.full_damage * CritRangedDamageTakenPctMod[dmg.school_type]);
							else
								dmg.full_damage = dmg.full_damage - float2int32(dmg.full_damage * CritMeleeDamageTakenPctMod[dmg.school_type]);

							if(pVictim->IsPlayer())
							{
								//Resilience is a special new rating which was created to reduce the effects of critical hits against your character.
								float dmg_reduction_pct = 2.0f * TO< Player* >(pVictim)->CalcRating(PLAYER_RATING_MODIFIER_MELEE_CRIT_RESILIENCE) / 100.0f;
								if(dmg_reduction_pct > 1.0f)
									dmg_reduction_pct = 1.0f; //we cannot resist more then he is criticalling us, there is no point of the critical then :P
								dmg.full_damage = float2int32(dmg.full_damage - dmg.full_damage * dmg_reduction_pct);
								//sLog.outString( "DEBUG: After Resilience check: %u" , dmg.full_damage );
							}

							if(pVictim->IsCreature() && TO< Creature* >(pVictim)->GetCreatureInfo()->Rank != ELITE_WORLDBOSS)
								pVictim->Emote(EMOTE_ONESHOT_WOUNDCRITICAL);

							vproc |= PROC_ON_CRIT_HIT_VICTIM;
							aproc |= PROC_ON_CRIT_ATTACK;

							if(weapon_damage_type == RANGED)
							{
								vproc |= PROC_ON_RANGED_CRIT_ATTACK_VICTIM;
								aproc |= PROC_ON_RANGED_CRIT_ATTACK;
							}

							if(IsPlayer())
							{
								this->SetFlag(UNIT_FIELD_AURASTATE, AURASTATE_FLAG_CRITICAL);
								if(!sEventMgr.HasEvent(this, EVENT_CRIT_FLAG_EXPIRE))
									sEventMgr.AddEvent(this, &Unit::EventAurastateExpire, uint32(AURASTATE_FLAG_CRITICAL) , EVENT_CRIT_FLAG_EXPIRE, 5000, 1, 0);
								else sEventMgr.ModifyEventTimeLeft(this, EVENT_CRIT_FLAG_EXPIRE, 5000);
							}

							CALL_SCRIPT_EVENT(pVictim, OnTargetCritHit)(this, dmg.full_damage);
							CALL_SCRIPT_EVENT(this, OnCritHit)(pVictim, dmg.full_damage);
						}
						break;
//--------------------------------crushing blow---------------------------------------------
					case 6:
						hit_status |= HITSTATUS_CRUSHINGBLOW;
						dmg.full_damage = (dmg.full_damage * 3) >> 1;
						break;
//--------------------------------regular hit-----------------------------------------------
					default:
						break;
				}
//==========================================================================================
//==============================Post Roll Damage Processing=================================
//==========================================================================================
//--------------------------absorption------------------------------------------------------
				uint32 dm = dmg.full_damage;
				abs = pVictim->AbsorbDamage(dmg.school_type, (uint32*)&dm);

				if(dmg.full_damage > (int32)blocked_damage)
				{
					uint32 sh = pVictim->ManaShieldAbsorb(dmg.full_damage);
//--------------------------armor reducing--------------------------------------------------
					if(sh)
					{
						dmg.full_damage -= sh;
						if(dmg.full_damage && !disable_dR)
							CalculateResistanceReduction(pVictim, &dmg, ability, ArmorPctReduce);
						dmg.full_damage += sh;
						abs += sh;
					}
					else if(!disable_dR)
						CalculateResistanceReduction(pVictim, &dmg, ability, ArmorPctReduce);
				}

				if(abs)
					vproc |= PROC_ON_ABSORB;

				if(dmg.school_type == SCHOOL_NORMAL)
				{
					abs += dmg.resisted_damage;
					dmg.resisted_damage = 0;
				}

				realdamage = dmg.full_damage - abs - dmg.resisted_damage - blocked_damage;
				if(realdamage < 0)
				{
					realdamage = 0;
					vstate = IMMUNE;
					if(!(hit_status & HITSTATUS_BLOCK))
						hit_status |= HITSTATUS_ABSORBED;
					else
						hit_status |= HITSTATUS_BLOCK;
				}
				CALL_SCRIPT_EVENT(this, OnHit)(pVictim, realdamage);
			}
			break;
	}

//==========================================================================================
//==============================Post Roll Special Cases Processing==========================
//==========================================================================================
//------------------------------- Special Effects Processing
	// Paladin: Blessing of Sacrifice, and Warlock: Soul Link
	if(pVictim->m_damageSplitTarget)
	{
		dmg.full_damage = pVictim->DoDamageSplitTarget(dmg.full_damage, dmg.school_type, true);
		realdamage = dmg.full_damage;
	}

	//--------------------------special states processing---------------------------------------
	if(pVictim->IsCreature())
	{
		if(pVictim->GetAIInterface() && (pVictim->GetAIInterface()->getAIState() == STATE_EVADE ||
										 pVictim->GetAIInterface()->getAIState() == STATE_EVADE_TIMING_OUT ||
		                                 (pVictim->GetAIInterface()->GetIsSoulLinked() && pVictim->GetAIInterface()->getSoullinkedWith() != this)))
		{
			vstate = EVADE;
			realdamage = 0;
			dmg.full_damage = 0;
			dmg.resisted_damage = 0;
		}
	}
	if(pVictim->IsPlayer() && TO< Player* >(pVictim)->GodModeCheat == true)
	{
		dmg.resisted_damage = dmg.full_damage; //godmode
	}
//--------------------------dirty fixes-----------------------------------------------------
	//vstate=1-wound,2-dodge,3-parry,4-interrupt,5-block,6-evade,7-immune,8-deflect
	// the above code was remade it for reasons : damage shield needs moslty same flags as handleproc + dual wield should proc too ?

	uint32 resisted_dmg;

	//damage shield must come before handleproc to not loose 1 charge : spell gets removed before last charge
	if((realdamage > 0 || vproc & PROC_ON_BLOCK_VICTIM) && weapon_damage_type != OFFHAND)
	{
		pVictim->HandleProcDmgShield(vproc, this);
		HandleProcDmgShield(aproc, pVictim);
	}

	HandleProc(aproc, pVictim, ability, disable_proc, realdamage, abs, weapon_damage_type);   //maybe using dmg.resisted_damage is better sometimes but then if using godmode dmg is resisted instead of absorbed....bad
	m_procCounter = 0;

	resisted_dmg = pVictim->HandleProc(vproc, this, ability, disable_proc, realdamage, abs, weapon_damage_type);
	pVictim->m_procCounter = 0;

	if(resisted_dmg)
	{
		dmg.resisted_damage += resisted_dmg;
		dmg.full_damage -= resisted_dmg;
		realdamage -= resisted_dmg;
	}

//--------------------------spells triggering-----------------------------------------------
	if(realdamage > 0 && ability == 0)
	{
		if(IsPlayer() && TO< Player* >(this)->m_onStrikeSpells.size())
		{
			SpellCastTargets targets;
			targets.m_unitTarget = pVictim->GetGUID();
			targets.m_targetMask = TARGET_FLAG_UNIT;
			Spell* cspell;

			// Loop on hit spells, and strike with those.
			for(map< SpellEntry*, pair< uint32, uint32 > >::iterator itr = TO< Player* >(this)->m_onStrikeSpells.begin();
			        itr != TO< Player* >(this)->m_onStrikeSpells.end(); ++itr)
			{
				if(itr->second.first)
				{
					// We have a *periodic* delayed spell.
					uint32 t = getMSTime();
					if(t > itr->second.second)    // Time expired
					{
						// Set new time
						itr->second.second = t + itr->second.first;
					}

					// Cast.
					cspell = sSpellFactoryMgr.NewSpell(this, itr->first, true, NULL);
					cspell->prepare(&targets);
				}
				else
				{
					cspell = sSpellFactoryMgr.NewSpell(this, itr->first, true, NULL);
					cspell->prepare(&targets);
				}
			}
		}

		if(IsPlayer() && TO< Player* >(this)->m_onStrikeSpellDmg.size())
		{
			map< uint32, OnHitSpell >::iterator it2 = TO< Player* >(this)->m_onStrikeSpellDmg.begin();
			map< uint32, OnHitSpell >::iterator itr;
			uint32 range, dmg2;
			for(; it2 != TO< Player* >(this)->m_onStrikeSpellDmg.end();)
			{
				itr = it2;
				++it2;

				dmg2 = itr->second.mindmg;
				range = itr->second.maxdmg - itr->second.mindmg;
				if(range != 0)
					dmg2 += RandomUInt(range);

				SpellNonMeleeDamageLog(pVictim, itr->second.spellid, dmg2, true);
			}
		}

		//ugly hack for shadowfiend restoring mana
		if(GetSummonedByGUID() != 0 && GetEntry() == 19668)
		{
			Player* owner = GetMapMgr()->GetPlayer((uint32)GetSummonedByGUID());
			uint32 amount = static_cast< uint32 >(owner->GetMaxPower( POWER_TYPE_MANA ) * 0.05f);
			if(owner != NULL)
				Energize(owner, 34650, amount, POWER_TYPE_MANA);
		}
		//ugly hack for Bloodsworm restoring hp
		if(GetUInt64Value(UNIT_FIELD_SUMMONEDBY) != 0 && GetUInt32Value(OBJECT_FIELD_ENTRY) == 28017)
		{
			Player* owner = GetMapMgr()->GetPlayer((uint32)GetUInt64Value(UNIT_FIELD_SUMMONEDBY));
			if(owner != NULL)
				Heal(owner, 50452, float2int32(1.5f * realdamage));
		}
	}

//==========================================================================================
//==============================Data Sending================================================
//==========================================================================================
	if(!ability)
	{
		if(dmg.full_damage > 0)
		{
			if(dmg.full_damage == (int32)abs)
				hit_status |= HITSTATUS_ABSORBED;
			else if(dmg.full_damage <= (int32)dmg.resisted_damage)
			{
				hit_status |= HITSTATUS_RESIST;
				vproc |= PROC_ON_ABSORB;
				dmg.resisted_damage = dmg.full_damage;
			}
		}

		if(dmg.full_damage < 0)
			dmg.full_damage = 0;

		if(realdamage < 0)
			realdamage = 0;

		SendAttackerStateUpdate(this, pVictim, &dmg, realdamage, abs, blocked_damage, hit_status, vstate);
	}
	else
	{
		if(realdamage > 0)  //FIX ME: add log for miss,block etc for ability and ranged
		{
			// here we send "dmg.resisted_damage" for "AbsorbedDamage", "0" for "ResistedDamage", and "false" for "PhysicalDamage" even though "School" is "SCHOOL_NORMAL"   o_O
			SendSpellNonMeleeDamageLog(this, pVictim, ability->Id, realdamage, static_cast<uint8>(dmg.school_type), dmg.resisted_damage, 0, false, blocked_damage, ((hit_status & HITSTATUS_CRICTICAL) != 0), true);
		}
		//FIX ME: add log for miss,block etc for ability and ranged
		//example how it works
		//SendSpellLog(this,pVictim,ability->Id,SPELL_LOG_MISS);
	}

	if(ability && realdamage == 0)
	{
		SendSpellLog(this, pVictim, ability->Id, SPELL_LOG_RESIST);
	}
//==========================================================================================
//==============================Damage Dealing==============================================
//==========================================================================================

	if(this->IsPlayer() && ability)
		TO< Player* >(this)->m_casted_amount[dmg.school_type] = (uint32)(realdamage + abs);

	// invincible people don't take damage
	if(pVictim->bInvincible == false)
	{
		if(realdamage)
		{
			DealDamage(pVictim, realdamage, 0, targetEvent, 0);
			//pVictim->HandleProcDmgShield(PROC_ON_MELEE_ATTACK_VICTIM,this);
			//		HandleProcDmgShield(PROC_ON_MELEE_ATTACK_VICTIM,pVictim);

			if(pVictim->GetCurrentSpell())
				pVictim->GetCurrentSpell()->AddTime(0);
		}
		else
		{
			// have to set attack target here otherwise it wont be set
			// because dealdamage is not called.
			//setAttackTarget(pVictim);
			this->CombatStatus.OnDamageDealt(pVictim);
		}
	}
//==========================================================================================
//==============================Post Damage Dealing Processing==============================
//==========================================================================================
//--------------------------durability processing-------------------------------------------
	if(pVictim->IsPlayer())
	{
		TO< Player* >(pVictim)->GetItemInterface()->ReduceItemDurability();
		if(!this->IsPlayer())
		{
			Player* pr = TO< Player* >(pVictim);
			if(Rand(pr->GetSkillUpChance(SKILL_DEFENSE) * sWorld.getRate(RATE_SKILLCHANCE)))
			{
				pr->_AdvanceSkillLine(SKILL_DEFENSE, float2int32(1.0f * sWorld.getRate(RATE_SKILLRATE)));
				pr->UpdateChances();
			}
		}
		else
		{
			TO< Player* >(this)->GetItemInterface()->ReduceItemDurability();
		}
	}
	else
	{
		if(this->IsPlayer())//not pvp
		{
			TO< Player* >(this)->GetItemInterface()->ReduceItemDurability();
			Player* pr = TO< Player* >(this);
			if(Rand(pr->GetSkillUpChance(SubClassSkill) * sWorld.getRate(RATE_SKILLCHANCE)))
			{
				pr->_AdvanceSkillLine(SubClassSkill, float2int32(1.0f * sWorld.getRate(RATE_SKILLRATE)));
				//pr->UpdateChances();
			}
		}
	}
	//--------------------------rage processing-------------------------------------------------
	//http://www.wowwiki.com/Formulas:Rage_generation

	if(dmg.full_damage && IsPlayer() && GetPowerType() == POWER_TYPE_RAGE && !ability)
	{
		float rageconversion = ((0.0091107836f * getLevel() * getLevel()) + 3.225598133f * getLevel()) + 4.2652911f;
		float weaponSpeedHitFactor = GetFloatValue(UNIT_FIELD_BASEATTACKTIME) / 1000.0f * 1.75f;
		if(hit_status & HITSTATUS_CRICTICAL)
			weaponSpeedHitFactor *= 2;
		float addRage = (dmg.full_damage / rageconversion * 7.5f + weaponSpeedHitFactor) / 2;
		AddPctN(addRage, GetTotalAuraModifier(213));
		addRage *= 20; // MORE RAGE!
		addRage = addRage * 1.5;
		ModPower(POWER_TYPE_RAGE, float2int32(addRage));
	}

	RemoveAurasByInterruptFlag(AURA_INTERRUPT_ON_START_ATTACK);
//--------------------------extra strikes processing----------------------------------------
	if(!m_extraAttackCounter)
	{
		int32 extra_attacks = m_extraattacks;
		m_extraAttackCounter = true;
		m_extraattacks = 0;

		while(extra_attacks > 0)
		{
			extra_attacks--;
			Strike(pVictim, weapon_damage_type, NULL, 0, 0, 0, false, false);
		}

		m_extraAttackCounter = false;
	}

	if(m_extrastriketargetc > 0 && !m_extrastriketarget)
	{
		m_extrastriketarget = true;

		std::list<ExtraStrike*>::iterator itx, itx2;
		for(itx = m_extraStrikeTargets.begin(); itx != m_extraStrikeTargets.end();)
		{
			itx2 = itx++;
			ExtraStrike* ex = *itx2;

			for(set<Object*>::iterator itr = m_objectsInRange.begin(); itr != m_objectsInRange.end(); ++itr)
			{
				if((*itr) == pVictim || !(*itr)->IsUnit())
					continue;

				if(CalcDistance(*itr) < 5.0f && isAttackable(this, (*itr)) && (*itr)->isInFront(this) && !TO_UNIT(*itr)->IsPacified())
				{
					// Sweeping Strikes hits cannot be dodged, missed or parried (from wowhead)
					bool skip_hit_check2 = ex->spell_info->Id == 12328 ? true : false;
					//zack : should we use the spell id the registered this extra strike when striking ? It would solve a few proc on proc problems if so ;)
//					Strike( TO< Unit* >( *itr ), weapon_damage_type, ability, add_damage, pct_dmg_mod, exclusive_damage, false, skip_hit_check );
					Strike(TO< Unit* >(*itr), weapon_damage_type, ex->spell_info, add_damage, pct_dmg_mod, exclusive_damage, false, skip_hit_check2);
					break;
				}
			}

			// Sweeping Strikes charges are used up regardless whether there is a secondary target in range or not. (from wowhead)
			if(ex->charges > 0)
			{
				ex->charges--;
				if(ex->charges <= 0)
				{
					m_extrastriketargetc--;
					m_extraStrikeTargets.erase(itx2);
					delete ex;
				}
			}
		}

		m_extrastriketarget = false;
	}
}

void Unit::smsg_AttackStop(Unit* pVictim)
{
	if(!pVictim)
		return;

	WorldPacket data(SMSG_ATTACKSTOP, 24);
	if(IsPlayer())
	{
		data << pVictim->GetNewGUID();
		data << uint8(0);
		data << uint32(0);
		TO< Player* >(this)->GetSession()->SendPacket(&data);
		data.clear();
	}

	data << GetNewGUID();
	data << pVictim->GetNewGUID();
	data << uint32(0);
	SendMessageToSet(&data, true);
	// stop swinging, reset pvp timeout

	if(pVictim->IsPlayer())
	{
		pVictim->CombatStatusHandler_ResetPvPTimeout();
		CombatStatusHandler_ResetPvPTimeout();
	}
	else
	{
		if(!IsPlayer() || getClass() == ROGUE)
		{
			m_cTimer = getMSTime() + 8000;
			sEventMgr.RemoveEvents(this, EVENT_COMBAT_TIMER);
			sEventMgr.AddEvent(this, &Unit::EventUpdateFlag, EVENT_COMBAT_TIMER, 8000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
			if(pVictim->IsUnit())   // there could be damage coming from objects/enviromental
				sEventMgr.AddEvent(pVictim, &Unit::EventUpdateFlag, EVENT_COMBAT_TIMER, 8000, 1, 0);
		}
		else
		{
		}
	}
}

void Unit::smsg_AttackStop(uint64 victimGuid)
{
	WorldPacket data(20);
	data.Initialize(SMSG_ATTACKSTOP);
	data << GetNewGUID();
	FastGUIDPack(data, victimGuid);
	data << uint32(0);
	SendMessageToSet(&data, IsPlayer());
}

void Unit::smsg_AttackStart(Unit* pVictim)
{
	// Send out ATTACKSTART
	WorldPacket data(SMSG_ATTACKSTART, 16);
	data << GetGUID();
	data << pVictim->GetGUID();
	SendMessageToSet(&data, false);
	LOG_DEBUG("WORLD: Sent SMSG_ATTACKSTART");

	// FLAGS changed so other players see attack animation
	//    addUnitFlag(UNIT_FLAG_COMBAT);
	//    setUpdateMaskBit(UNIT_FIELD_FLAGS );
	if(IsPlayer())
	{
		Player* pThis = TO< Player* >(this);
		if(pThis->cannibalize)
		{
			sEventMgr.RemoveEvents(pThis, EVENT_CANNIBALIZE);
			pThis->SetEmoteState(0);
			pThis->cannibalize = false;
		}
	}
}

uint8 Unit::FindVisualSlot(uint32 SpellId, bool IsPos)
{
	uint32 from, to;
	uint8 visualslot = 0xFF;
	if(IsPos)
	{
		from = 0;
		to = MAX_POSITIVE_VISUAL_AURAS_END;
	}
	else
	{
		from = MAX_NEGATIVE_VISUAL_AURAS_START;
		to = MAX_NEGATIVE_VISUAL_AURAS_END;
	}
	//check for already visual same aura
	for(uint32 i = from; i < to; i++)
		if(m_auravisuals[i] == SpellId)
		{
			visualslot = static_cast<uint8>(i);
			break;
		}
	if(visualslot == 0xFF)
		for(uint32 i = from; i < to; i++)
			if(m_auravisuals[i] == 0)
			{
				visualslot = static_cast<uint8>(i);
				break;
			}
	return visualslot;
}

void Unit::AddAura(Aura* aur)
{
	if(aur == NULL)
		return;

	if(!(isAlive() || (aur->GetSpellProto()->AttributesEx3 & SPELL_ATTR3_DEATH_PERSISTENT)))
	{
		delete aur;
		return;
	}

	if(m_mapId != 530 && (m_mapId != 571 || (IsPlayer() && !TO_PLAYER(this)->HasSpellwithNameHash(SPELL_HASH_COLD_WEATHER_FLYING))))
		// can't use flying auras in non-outlands or non-northrend (northrend requires cold weather flying)
	{
		for(uint32 i = 0; i < 3; ++i)
		{
			if(aur->GetSpellProto()->EffectApplyAuraName[i] == SPELL_AURA_ENABLE_FLIGHT_WITH_UNMOUNTED_SPEED || aur->GetSpellProto()->EffectApplyAuraName[i] == SPELL_AURA_ENABLE_FLIGHT2)
			{
				delete aur;
				return;
			}
		}
	}

	if(aur->GetSpellProto()->NormalizedSchoolMask() && SchoolImmunityList[aur->GetSpellProto()->NormalizedSchoolMask()])
	{
		delete aur;
		return;
	}

	// If this aura can only affect one target at a time
	if(aur->GetSpellProto()->AttributesEx5 &  SPELL_ATTR5_SINGLE_TARGET_SPELL)
	{
		// remove aura from the previous applied target
		Unit* caster = aur->GetUnitCaster();
		uint64 prev_target_guid = 0;

		if(caster != NULL)
		{
			prev_target_guid = caster->GetCurrentUnitForSingleTargetAura(aur->GetSpellProto());

			if(prev_target_guid && prev_target_guid != aur->GetTarget()->GetGUID())
			{
				Unit* prev_target = this->GetMapMgr()->GetUnit(prev_target_guid);
				if(prev_target != NULL)
					prev_target->RemoveAllAuraByNameHash(aur->GetSpellProto()->NameHash);
			}
		}

		// remove aura from this unit. other player/unit may have casted on this target
		// this is necessary for the following case:
		//  1) attacker A cast on target A
		//  2) attacker B cast on target B
		//  3) attacker A cast on target B, and aura is removed from target A
		//  4) attacker B cast on target A, and aura is not removed from target B, because caster A is now the one that casted on target B
		if(prev_target_guid && prev_target_guid != aur->GetTarget()->GetGUID())
			RemoveAllAuraByNameHash(aur->GetSpellProto()->NameHash);
	}

	uint16 AuraSlot = 0xFFFF;
	//all this code block is to try to find a valid slot for our new aura.
	if(!aur->IsPassive())
	{
		uint32 AlreadyApplied = 0, CheckLimit, StartCheck;
		if(aur->IsPositive())
		{
			StartCheck = MAX_POSITIVE_AURAS_EXTEDED_START; //also check talents to make sure they will not stack. Maybe not required ?
			CheckLimit = MAX_POSITIVE_AURAS_EXTEDED_END;
		}
		else
		{
			StartCheck = MAX_NEGATIVE_AURAS_EXTEDED_START;
			CheckLimit = MAX_NEGATIVE_AURAS_EXTEDED_END;
		}
		// Nasty check for Blood Fury debuff (spell system based on namehashes is bs anyways)
		if(aur->GetSpellProto()->always_apply == false)
		{
			//uint32 aurName = aur->GetSpellProto()->Name;
			//uint32 aurRank = aur->GetSpellProto()->Rank;
			uint32 maxStack = aur->GetSpellProto()->StackAmount;
			if(aur->GetSpellProto()->procCharges > 0)
			{
				int charges = aur->GetSpellProto()->procCharges;
				Unit* ucaster = aur->GetUnitCaster();
				if(aur->GetSpellProto()->SpellFamilyFlags && ucaster != NULL)
				{
					if(Player *p = GetSpellModOwner())
						p->ApplySpellMod(aur->GetSpellProto()->Id, SPELLMOD_CHARGES, charges);
				}
				maxStack = charges;
			}
			if(IsPlayer() && TO< Player* >(this)->AuraStackCheat)
				maxStack = 999;

			SpellEntry* info = aur->GetSpellProto();
			//uint32 flag3 = aur->GetSpellProto()->Flags3;

			AuraCheckResponse acr;
			WorldPacket data(21);
			bool deleteAur = false;

			//check if we already have this aura by this caster -> update duration
			for(uint32 x = StartCheck; x < CheckLimit; x++)
			{
				if(m_auras[x])
				{
					if(m_auras[x]->GetSpellId() == aur->GetSpellId())
					{
						if(!aur->IsPositive()
						        && m_auras[x]->m_casterGuid != aur->m_casterGuid
						        && (m_auras[x]->GetSpellProto()->c_is_flags & SPELL_FLAG_IS_MAXSTACK_FOR_DEBUFF) == 0
						  )
						{
							continue;
						}
						AlreadyApplied++;
						//update duration,the same aura (update the whole stack whenever we cast a new one)
						m_auras[x]->ResetDuration();

						if(maxStack <= AlreadyApplied)
						{
							ModVisualAuraStackCount(m_auras[x], 0);
							if(AlreadyApplied == 1)
								m_auras[x]->UpdateModifiers();
							deleteAur = true;
							break;
						}
					}
					else if((aur->pSpellId != m_auras[x]->GetSpellProto()->Id))     // if this is a proc spell then it should not remove it's mother : test with combustion later
					{
						// Check for auras by specific type.
						if(info->BGR_one_buff_on_target > 0 && m_auras[x]->GetSpellProto()->BGR_one_buff_on_target & info->BGR_one_buff_on_target && maxStack == 0)
						{
							deleteAur = HasAurasOfBuffType(info->BGR_one_buff_on_target, aur->m_casterGuid, 0);
						}
						// Check for auras with the same name and a different rank.
						else
						{
							acr = AuraCheck(info, m_auras[x], aur->GetCaster());
							if(acr.Error == AURA_CHECK_RESULT_HIGHER_BUFF_PRESENT)
							{
								deleteAur = true;
							}
							else if(acr.Error == AURA_CHECK_RESULT_LOWER_BUFF_PRESENT)
							{
								// remove the lower aura
								m_auras[x]->Remove();

								// no more checks on bad ptr
								continue;
							}
						}
					}
				}
				else if(AuraSlot == 0xFFFF)
				{
					AuraSlot = static_cast<uint16>(x);
				}
			}

			if(deleteAur)
			{
				sEventMgr.RemoveEvents(aur);

				// Once stacked 5 times, each application of Deadly poison also causes the poison on the Rogue's other weapon to apply
				// http://www.wowhead.com/?item=43233#comments
				if(AlreadyApplied >= maxStack && info->c_is_flags & SPELL_FLAG_IS_POISON)
				{
					Player* caster = aur->GetPlayerCaster();
					if(caster != NULL)
					{
						switch(info->NameHash)
						{
							case SPELL_HASH_DEADLY_POISON_IX:
							case SPELL_HASH_DEADLY_POISON_VIII:
							case SPELL_HASH_DEADLY_POISON_VII:
							case SPELL_HASH_DEADLY_POISON_VI:
							case SPELL_HASH_DEADLY_POISON_V:
							case SPELL_HASH_DEADLY_POISON_IV:
							case SPELL_HASH_DEADLY_POISON_III:
							case SPELL_HASH_DEADLY_POISON_II:
							case SPELL_HASH_DEADLY_POISON:
								{
									Item* mh = caster->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_MAINHAND);
									Item* oh = caster->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_OFFHAND);

									if(mh != NULL && oh != NULL)
									{
										uint32 mh_spell = 0;
										uint32 oh_spell = 0;
										bool is_mh_deadly_poison = false;
										bool is_oh_deadly_poison = false;

										// Find mainhand enchantment
										EnchantmentInstance* ench = mh->GetEnchantment(TEMP_ENCHANTMENT_SLOT);
										if(ench)
										{
											EnchantEntry* Entry = ench->Enchantment;
											for(uint32 c = 0; c < 3; c++)
											{
												if(Entry->type[c] && Entry->spell[c])
												{
													SpellEntry* sp = dbcSpell.LookupEntryForced(Entry->spell[c]);
													if(sp && sp->c_is_flags & SPELL_FLAG_IS_POISON)
													{
														switch(sp->NameHash)
														{
															case SPELL_HASH_DEADLY_POISON_IX:
															case SPELL_HASH_DEADLY_POISON_VIII:
															case SPELL_HASH_DEADLY_POISON_VII:
															case SPELL_HASH_DEADLY_POISON_VI:
															case SPELL_HASH_DEADLY_POISON_V:
															case SPELL_HASH_DEADLY_POISON_IV:
															case SPELL_HASH_DEADLY_POISON_III:
															case SPELL_HASH_DEADLY_POISON_II:
															case SPELL_HASH_DEADLY_POISON:
																is_mh_deadly_poison = true;
																break;
														}

														mh_spell = Entry->spell[c];
														break;
													}
												}
											}

											// Find offhand enchantment
											ench = oh->GetEnchantment(TEMP_ENCHANTMENT_SLOT);
											if(ench)
											{
												EnchantEntry* Entry = ench->Enchantment;
												for(uint32 c = 0; c < 3; c++)
												{
													if(Entry->type[c] && Entry->spell[c])
													{
														SpellEntry* sp = dbcSpell.LookupEntryForced(Entry->spell[c]);
														if(sp && sp->c_is_flags & SPELL_FLAG_IS_POISON)
														{
															switch(sp->NameHash)
															{
																case SPELL_HASH_DEADLY_POISON_IX:
																case SPELL_HASH_DEADLY_POISON_VIII:
																case SPELL_HASH_DEADLY_POISON_VII:
																case SPELL_HASH_DEADLY_POISON_VI:
																case SPELL_HASH_DEADLY_POISON_V:
																case SPELL_HASH_DEADLY_POISON_IV:
																case SPELL_HASH_DEADLY_POISON_III:
																case SPELL_HASH_DEADLY_POISON_II:
																case SPELL_HASH_DEADLY_POISON:
																	is_oh_deadly_poison = true;
																	break;
															}

															oh_spell = Entry->spell[c];
															break;
														}
													}
												}
											}
										}

										// Only apply if both weapons are enchanted and enchantment is poison and enchantment type is different
										if(mh_spell && oh_spell && mh_spell != oh_spell && is_mh_deadly_poison != is_oh_deadly_poison)
										{
											if(mh_spell != info->Id)
												caster->CastSpell(aur->GetTarget(), mh_spell, true);
											else
												caster->CastSpell(aur->GetTarget(), oh_spell, true);
										}
									}

									break;
								}
						}
					}
				}

				delete aur;
				return;
			}
		}
		else
		{
			//these auras stack to infinite and with anything. Don't ask me why there is no better solution for them :P
			for(uint32 x = StartCheck; x < CheckLimit; x++)
				if(!m_auras[x])
				{
					AuraSlot = static_cast<uint16>(x);
					break;
				}
		}
	}
	else
	{
		//talents just get applied always. Maybe we should check stack for these as well?
		for(uint32 x = MAX_PASSIVE_AURAS_START; x < MAX_PASSIVE_AURAS_END; x++)
			if(!m_auras[x])
			{
				AuraSlot = static_cast<uint16>(x);
				break;
			}
//			else if( m_auras[x]->GetID()==aur->GetID() ) printf("OMG stacking talents ?\n");
	}


	//check if we can store this aura in some empty slot
	if(AuraSlot == 0xFFFF)
	{
		LOG_ERROR("Aura error in active aura. ");
		sEventMgr.RemoveEvents(aur);
		delete aur;
		/*
				if ( aur != NULL )
					{
						delete [] aur;
						aur = NULL;
					}
			*/
		return;
	}

	//Zack : if all mods were resisted it means we did not apply anything and we do not need to delete this spell either
	if(aur->TargetWasImuneToMods())
	{
		//TODO : notify client that we are immune to this spell
		sEventMgr.RemoveEvents(aur);
		delete aur;
		return;
	}

	uint8 visualslot = 0xFF;
	//search for a visual slot
	if(!aur->IsPassive() || (aur->m_spellProto->AttributesEx & 1024))
		visualslot = FindVisualSlot(aur->GetSpellId(), aur->IsPositive());
	aur->m_visualSlot = visualslot;
	// Zack : No idea how a new aura can already have a slot. Leaving it for compatibility
	if(aur->m_auraSlot != 0xffff)
		m_auras[ aur->m_auraSlot ] = NULL;

	aur->m_auraSlot = AuraSlot;

	m_auras[ AuraSlot ] = aur;
	UpdateAuraForGroup(visualslot);

	ModVisualAuraStackCount(aur, 1);

	aur->ApplyModifiers(true);

	// We add 500ms here to allow for the last tick in DoT spells. This is a dirty hack, but at least it doesn't crash like my other method.
	// - Burlex
	if(aur->GetDuration() > 0)
	{
		sEventMgr.AddEvent(aur, &Aura::Remove, EVENT_AURA_REMOVE, aur->GetDuration() + 500, 1,
		                   EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT | EVENT_FLAG_DELETES_OBJECT);
	}

	//have to hate these relocate events. They run in a separate thread :P
	aur->RelocateEvents();

	// Reaction from enemy AI
	if(!aur->IsPositive() && aur->IsCombatStateAffecting())	  // Creature
	{
		Unit* pCaster = aur->GetUnitCaster();
		if(pCaster && pCaster->isAlive() && this->isAlive())
		{
			pCaster->CombatStatus.OnDamageDealt(this);

			if(IsCreature())
				m_aiInterface->AttackReaction(pCaster, 1, aur->GetSpellId());
		}
		/*if(isAlive() && CanAgroHash(aur->m_spellProto->NameHash)) //no threat for hunter's mark
		{
			Unit * pCaster = aur->GetUnitCaster();
			if(!pCaster) return;

			addAttacker(pCaster);

			GetAIInterface()->AttackReaction(pCaster, 1, aur->GetSpellId());
		}*/
	}

	if(aur->GetSpellProto()->AuraInterruptFlags & AURA_INTERRUPT_ON_INVINCIBLE)
	{
		Unit* pCaster = aur->GetUnitCaster();
		if(pCaster)
		{
			pCaster->RemoveStealth();
			pCaster->RemoveInvisibility();
			pCaster->RemoveAllAuraByNameHash(SPELL_HASH_ICE_BLOCK);
			pCaster->RemoveAllAuraByNameHash(SPELL_HASH_DIVINE_SHIELD);
			pCaster->RemoveAllAuraByNameHash(SPELL_HASH_BLESSING_OF_PROTECTION);
		}
	}

	// If this aura can only affect one target at a time, store this target GUID for future reference
	if(aur->GetSpellProto()->AttributesEx5 &  SPELL_ATTR5_SINGLE_TARGET_SPELL)
	{
		Unit* caster = aur->GetUnitCaster();
		if(caster != NULL)
			caster->SetCurrentUnitForSingleTargetAura(aur->GetSpellProto(), this->GetGUID());
	}

	/* Set aurastates */
	uint32 flag = 0;
	if(aur->GetSpellProto()->Mechanic == MECHANIC_ENRAGED && !asc_enraged++)
		flag |= AURASTATE_FLAG_ENRAGED;
	else if(aur->GetSpellProto()->Mechanic == MECHANIC_BLEEDING && !asc_bleed++)
		flag |= AURASTATE_FLAG_BLEED;
	if(aur->GetSpellProto()->BGR_one_buff_on_target & SPELL_TYPE_SEAL && !asc_seal++)
		flag |= AURASTATE_FLAG_JUDGEMENT;

	SetFlag(UNIT_FIELD_AURASTATE, flag);
}

void Unit::AddAura(Object * caster, uint32 aur, uint32 dur)
{
	SpellEntry * sp = dbcSpell.LookupEntry(aur);
	if(sp == NULL)
		return;
	Aura * a = sSpellFactoryMgr.NewAura(sp, GetDuration(dbcSpellDuration.LookupEntry(sp->DurationIndex)), caster, this);
	AddAura(a);
	if(dur != 0 && a != NULL)
		a->SetDuration(dur);
}

bool Unit::RemoveAura(Aura* aur)
{
	if(aur == NULL)
		return false;

	aur->Remove();
	return true;
}

bool Unit::RemoveAura(uint32 spellId)
{
	//this can be speed up, if we know passive \pos neg
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; x++)
		if(m_auras[x] && m_auras[x]->GetSpellId() == spellId)
		{
			m_auras[x]->Remove();
			return true;  // sky: yes, only one, see bug charges/auras queues
		}
	return false;
}

bool Unit::RemoveAuras(uint32* SpellIds)
{
	if(!SpellIds || *SpellIds == 0)
		return false;

	uint32 x, y;
	bool res = false;
	for(x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; x++)
	{
		if(m_auras[x])
		{
			for(y = 0; SpellIds[y] != 0; y++)
			{
				if(m_auras[x] && m_auras[x]->GetSpellId() == SpellIds[y])
				{
					m_auras[x]->Remove();
					res = true;
				}
			}
		}
	}
	return res;
}

bool Unit::RemoveAurasByHeal()
{
	bool res = false;
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; x++)
	{
		if(m_auras[x])
		{
			switch(m_auras[x]->GetSpellId())
			{
					// remove after heal
				case 35321:
				case 38363:
				case 39215:
					{
						m_auras[x]->Remove();
						res = true;
					}
					break;
					// remove when healed to 100%
				case 31956:
				case 38801:
				case 43093:
					{
						if(GetUInt32Value(UNIT_FIELD_HEALTH) == GetUInt32Value(UNIT_FIELD_MAXHEALTH))
						{
							m_auras[x]->Remove();
							res = true;
						}
					}
					break;
					// remove at p% health
				case 38772:
					{
						uint32 p = m_auras[x]->GetSpellProto()->EffectBasePoints[1];
						if(GetUInt32Value(UNIT_FIELD_MAXHEALTH) * p <= GetUInt32Value(UNIT_FIELD_HEALTH) * 100)
						{
							m_auras[x]->Remove();
							res = true;
						}
					}
					break;
			}
		}
	}

	return res;
}

bool Unit::AuraActionIf( AuraAction *action, AuraCondition *condition ){
	bool done = false;

	for( uint32 i = MAX_TOTAL_AURAS_START; i < MAX_TOTAL_AURAS_END; i++ ){
		Aura *aura = m_auras[ i ];

		if( aura == NULL )
			continue;

		if( (*condition)( aura ) ){
			(*action)( aura );
			done = true;
		}
	}

	return done;
}

void Unit::ClearAllAreaAuraTargets()
{
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; x++)
	{
		Aura* a = m_auras[ x ];

		if(a == NULL)
			continue;

		if(a->m_areaAura)   // This was not casted by us, so no removal
			continue;

		if(a->IsAreaAura())
			a->ClearAATargets();
	}
}

void Unit::RemoveAllAreaAuraByOther()
{
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; x++)
	{
		Aura* a = m_auras[ x ];

		if(a == NULL)   // empty slot
			continue;

		if(!a->m_areaAura)   // not area aura, or we casted it
			continue;

		a->Remove();
	}
}

bool Unit::RemoveAura(uint32 spellId, uint64 guid)
{
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; x++)
	{
		if(m_auras[x])
		{
			if(m_auras[x]->GetSpellId() == spellId && m_auras[x]->m_casterGuid == guid)
			{
				m_auras[x]->Remove();
				return true;
			}
		}
	}
	return false;
}

bool Unit::RemoveAuraByItemGUID(uint32 spellId, uint64 guid)
{
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; x++)
	{
		if(m_auras[x])
		{
			if(m_auras[x]->GetSpellId() == spellId && m_auras[x]->itemCasterGUID == guid)
			{
				m_auras[x]->Remove();
				return true;
			}
		}
	}
	return false;
}

bool Unit::RemoveAuraByNameHash(uint32 namehash)
{
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; x++)
	{
		if(m_auras[x])
		{
			if(m_auras[x]->GetSpellProto()->NameHash == namehash)
			{
				m_auras[x]->Remove();
				return true;
			}
		}
	}
	return false;
}

bool Unit::RemoveAllAuras(uint32 spellId, uint64 guid)
{
	bool res = false;
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; x++)
	{
		if(m_auras[x])
		{
			if(m_auras[x]->GetSpellId() == spellId)
			{
				if(!guid || m_auras[x]->m_casterGuid == guid)
				{
					m_auras[x]->Remove();
					res = true;
				}
			}
		}
	}
	return res;
}

uint32 Unit::RemoveAllAuraByNameHash(uint32 namehash)
{
	uint32 res = 0;
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; x++)
	{
		if(m_auras[x])
		{
			if(m_auras[x]->GetSpellProto()->NameHash == namehash)
			{
				m_auras[x]->Remove();
				res++;
			}
		}
	}
	return res;
}

uint32 Unit::RemoveAllAuraById(uint32 Id)
{
	uint32 res = 0;
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; x++)
	{
		if(m_auras[x])
		{
			if(m_auras[x]->GetSpellId() == Id)
			{
				m_auras[x]->Remove();
				res++;
			}
		}
	}
	return res;
}

void Unit::RemoveNegativeAuras()
{
	for(uint32 x = MAX_NEGATIVE_AURAS_EXTEDED_START; x < MAX_REMOVABLE_AURAS_END; x++)
	{
		if(m_auras[x])
		{
			if(m_auras[x]->GetSpellProto()->AttributesEx3 & SPELL_ATTR3_DEATH_PERSISTENT)
				continue;
			else
				m_auras[x]->Remove();
		}
	}
}

void Unit::RemoveAllAuras()
{
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; x++)
		if(m_auras[x])
			m_auras[x]->Remove();
}

void Unit::RemoveAllNonPersistentAuras()
{
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; x++)
		if(m_auras[x])
		{
			if(m_auras[x]->GetSpellProto()->AttributesEx3 & SPELL_ATTR3_DEATH_PERSISTENT)
				continue;
			else
				m_auras[x]->Remove();
		}
}

//ex:to remove morph spells
void Unit::RemoveAllAuraType(uint32 auratype, uint32 skip)
{
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; x++)
		if(m_auras[x] && m_auras[x]->HasModType(auratype) && m_auras[x]->GetSpellId() != skip)
			m_auras[x]->Remove();//remove all morph auras containing to this spell (like wolf morph also gives speed)
}


//ex:to remove morph spells
void Unit::RemoveAllAuraFromSelfType2(uint32 auratype, uint32 butskip_hash)
{
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; x++)
		if(m_auras[x])
		{
			SpellEntry* proto = m_auras[x]->GetSpellProto();
			if(proto->BGR_one_buff_from_caster_on_self == auratype
			        && proto->NameHash != butskip_hash
			        && m_auras[x]->GetCaster() == this
			  )
				RemoveAura(m_auras[x]->GetSpellId());//remove all morph auras containing to this spell (like wolf morph also gives speed)
		}
}

void Unit::RemoveAllAurasByStances(uint32 mask)
{
	Aura* aura;

	for(uint32 i = MAX_REMOVABLE_AURAS_START; i < MAX_REMOVABLE_AURAS_END; ++i)
	{
		aura = m_auras[i];
		if(aura == NULL || ! aura->IsPositive())
			continue;

		if(aura->GetSpellProto()->Stances & mask)
			aura->Remove();
	}
}

bool Unit::SetAurDuration(uint32 spellId, Unit* caster, uint32 duration)
{
	LOG_DEBUG("setAurDuration2");
	Aura* aur = FindAura(spellId, caster->GetGUID());
	if(!aur)
		return false;
	aur->SetDuration(duration);
	sEventMgr.ModifyEventTimeLeft(aur, EVENT_AURA_REMOVE, duration);

	return true;
}

bool Unit::SetAurDuration(uint32 spellId, uint32 duration)
{
	Aura* aur = FindAura(spellId);

	if(!aur)
		return false;


	LOG_DEBUG("setAurDuration2");
	aur->SetDuration(duration);
	sEventMgr.ModifyEventTimeLeft(aur, EVENT_AURA_REMOVE, duration);

	return true;
}


Aura* Unit::FindAuraByNameHash(uint32 namehash, uint64 guid)
{
	Aura* aura;
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; x++)
	{
		aura = m_auras[x];
		if(aura != NULL && aura->GetSpellProto()->NameHash == namehash && aura->m_casterGuid == guid)
			return aura;
	}
	return NULL;
}

Aura* Unit::FindAuraByNameHash(uint32 namehash)
{
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; x++)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash == namehash)
			return m_auras[x];
	return NULL;
}

Aura* Unit::FindAura(uint32 spellId)
{
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; x++)
		if(m_auras[x])
			if(m_auras[x]->GetSpellId() == spellId)
				return m_auras[x];
	return NULL;
}

Aura* Unit::FindAura(uint32* spellId)
{
	Aura* aura;
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; x++)
	{
		aura = m_auras[x];

		if(aura == NULL)
			continue;

		for(uint8 j = 0; ; j ++)
		{
			if(! spellId[j])
				break;

			if(aura->GetSpellId() == spellId[j])
				return aura;
		}
	}

	return NULL;
}

Aura* Unit::FindAura(uint32 spellId, uint64 guid)
{
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; x++)
		if(m_auras[x])
			if(m_auras[x]->GetSpellId() == spellId && m_auras[x]->m_casterGuid == guid)
				return m_auras[x];
	return NULL;
}

Aura* Unit::FindAuraWithAuraEffect(uint32 effect, uint32* x)
{
	Aura* aura;
	for(; *x < MAX_TOTAL_AURAS_END ; (*x)++)
	{
		aura = m_auras[*x];
		if(aura != NULL &&
		        ((aura->GetSpellProto()->Effect[0] == SPELL_EFFECT_APPLY_AURA && aura->GetSpellProto()->EffectApplyAuraName[0] == effect) ||
		         (aura->GetSpellProto()->Effect[1] == SPELL_EFFECT_APPLY_AURA && aura->GetSpellProto()->EffectApplyAuraName[1] == effect) ||
		         (aura->GetSpellProto()->Effect[2] == SPELL_EFFECT_APPLY_AURA && aura->GetSpellProto()->EffectApplyAuraName[2] == effect)))
			return aura;
	}

	return NULL;
}

void Unit::_UpdateSpells(uint32 time)
{
	/* to avoid deleting the current spell */
	if(m_currentSpell != NULL)
	{
//		m_spellsbusy=true;
		m_currentSpell->update(time);
//		m_spellsbusy=false;
	}
}

void Unit::castSpell(Spell* pSpell)
{
	// check if we have a spell already casting etc
	if(m_currentSpell && pSpell != m_currentSpell)
	{
		m_currentSpell->cancel();
	}

	m_currentSpell = pSpell;
	pLastSpell = pSpell->GetProto();
}

int32 Unit::GetSpellDmgAPBonus(SpellEntry*spellInfo, bool isdot)
{
	if( spellInfo->c_is_flags & SPELL_FLAG_IS_NOT_USING_DMG_BONUS || spellInfo->AttributesEx3 & SPELL_ATTR3_NO_DONE_BONUS)
		return 0;

	float plus_damage = 0.0f;
	if( spellInfo->ap_coef >= 0.0f && !isdot )
	{
		if(getClass() == HUNTER && GetRangedAttackPower() > GetAttackPower())
			plus_damage += float2int32(spellInfo->ap_coef * GetRangedAttackPower());
		else
			plus_damage += float2int32(/*plus_damage + (*/spellInfo->ap_coef * GetAttackPower());
	}
	if( spellInfo->ap_dot_coef >= 0.0f && isdot )
	{
		if(getClass() == HUNTER && GetRangedAttackPower() > GetAttackPower())
			plus_damage += float2int32(spellInfo->ap_dot_coef * GetRangedAttackPower());
		else
		plus_damage += float2int32(/*plus_damage + (*/spellInfo->ap_dot_coef * GetAttackPower());
		if( Player * p = GetSpellModOwner() )
		{
			int durmod = 0;
			p->ApplySpellMod(spellInfo->Id, SPELLMOD_DURATION, durmod);
			plus_damage += plus_damage * durmod / 15000;
		}
	}
	return plus_damage;
}

int32 Unit::GetSpellDmgBonus(Unit* pVictim, SpellEntry* spellInfo, int32 base_dmg, bool isdot)
{
	float plus_damage = 0.0f;
	Unit* caster = this;
	uint32 school = spellInfo->NormalizedSchoolMask();

	if( spellInfo->c_is_flags & SPELL_FLAG_IS_NOT_USING_DMG_BONUS || spellInfo->AttributesEx3 & SPELL_ATTR3_NO_DONE_BONUS)
		return 0;

	if( caster->IsPlayer() && !caster->ClassUsesSpellPower() )
		return 0;

//------------------------------by school---------------------------------------------------
	plus_damage += static_cast< float >( caster->GetDamageDoneMod(school) );
	plus_damage += static_cast< float >( base_dmg * ( caster->GetDamageDonePctMod(school)-1) ); //value is initialized with 1
//------------------------------by victim type----------------------------------------------
	if( !pVictim->IsPlayer() && caster->IsPlayer() )
		plus_damage += static_cast< float >( TO< Player* >(caster)->IncreaseDamageByType[TO< Creature* >(pVictim)->GetCreatureInfo()->Type] );
//==========================================================================================
//==============================+Spell Damage Bonus Modifications===========================
//==========================================================================================
//------------------------------by cast duration--------------------------------------------

	// do not execute this if plus dmg is 0 or lower
	if( plus_damage > 0.0f )
	{
		bool a = true;
		if( spellInfo->Dspell_coef_override >= 0.0f && !isdot && caster->ClassUsesSpellPower())
		{
			plus_damage += float2int32(/*plus_damage + (*/plus_damage * spellInfo->Dspell_coef_override);
			a = false;
		}
		if( spellInfo->OTspell_coef_override >= 0.0f && isdot && caster->ClassUsesSpellPower())
		{
			plus_damage += float2int32(/*plus_damage + (*/plus_damage * spellInfo->OTspell_coef_override);
			if( caster->IsPlayer() && a)
			{
				int durmod = 0;
				if(Player * p = caster->GetSpellModOwner())
					p->ApplySpellMod(spellInfo->Id, SPELLMOD_DURATION, durmod);
				plus_damage += plus_damage * durmod / 15000;
			}
			a = false;
		}
		if(a && caster->ClassUsesSpellPower())
		{
			//Bonus to DD part
			if( spellInfo->fixed_dddhcoef >= 0.0f && !isdot )
				plus_damage = float2int32(plus_damage * spellInfo->fixed_dddhcoef);
			//Bonus to DoT part
			else if( spellInfo->fixed_hotdotcoef >= 0.0f && isdot )
			{
				plus_damage = float2int32(plus_damage * spellInfo->fixed_hotdotcoef);
				if( caster->IsPlayer() )
				{
					int32 durmod = 0;
					if(Player * p = GetSpellModOwner())
						p->ApplySpellMod(spellInfo->Id, SPELLMOD_DURATION, durmod);
					plus_damage += static_cast< float >( plus_damage * durmod / 15000 );
				}
			}
			//In case we dont fit in previous cases do old thing
			else
			{
				plus_damage += float2int32(plus_damage + (plus_damage * spellInfo->casttime_coef));
				float td = static_cast< float >( GetDuration( dbcSpellDuration.LookupEntry( spellInfo->DurationIndex ) ) );
				if( spellInfo->NameHash == SPELL_HASH_MOONFIRE
					|| spellInfo->NameHash == SPELL_HASH_IMMOLATE
					|| spellInfo->NameHash == SPELL_HASH_ICE_LANCE
					|| spellInfo->NameHash == SPELL_HASH_PYROBLAST )
					plus_damage = plus_damage * ( 1.0f - ( ( td / 15000.0f ) / ( ( td / 15000.0f ) ) ) );
			}
		}
	}

//==========================================================================================
//==============================Bonus Adding To Main Damage=================================
//==========================================================================================

	if((pVictim->HasAuraWithMechanics(MECHANIC_ENSNARED) || pVictim->HasAuraWithMechanics(MECHANIC_DAZED)) && caster->IsPlayer())
		plus_damage += static_cast< float >(TO< Player* >(caster)->m_IncreaseDmgSnaredSlowed);

	if(spellInfo->SpellFamilyFlags)
	{
		int32 bonus_damage = 0;
		int32 dmg_bonus_pct = 0;
		if(Player * p = caster->GetSpellModOwner())
		{
			p->ApplySpellMod(spellInfo->Id, SPELLMOD_BONUS_MULTIPLIER, dmg_bonus_pct);
			p->ApplySpellMod(spellInfo->Id, SPELLMOD_DAMAGE, bonus_damage);
		}
		plus_damage += static_cast< float >( (base_dmg + bonus_damage) * dmg_bonus_pct / 100 );
	}
	if(plus_damage > 0)
		plus_damage = objmgr.ApplySpellDamageLimit(spellInfo->Id, plus_damage);
	return static_cast< int32 >( plus_damage );
}

int32 Unit::GetSpellDamage(Spell* s, Unit * target, uint32 i, int32 base_dmg)
{
	if(s == NULL || s->GetProto() == NULL)
		return base_dmg;
	SpellEntry * spellInfo = s->GetProto();
	float basePointsPerLevel = spellInfo->EffectRealPointsPerLevel[i];
	int32 basePoints = base_dmg ? base_dmg : spellInfo->EffectBasePoints[i];
	int32 randomPoints = int32(spellInfo->EffectDieSides[i]);

    // base amount modification based on spell lvl vs caster lvl
	int32 level = int32(getLevel());
    if (level > int32(spellInfo->maxLevel) && spellInfo->maxLevel > 0)
        level = int32(spellInfo->maxLevel);
    else if (level < int32(spellInfo->baseLevel))
        level = int32(spellInfo->baseLevel);
    level -= int32(spellInfo->spellLevel);
    basePoints += int32(level * basePointsPerLevel);
    // roll in a range <1;EffectDieSides> as of patch 3.3.3
    switch (randomPoints)
    {
        case 0: break;
        case 1: basePoints += 1; break;                     // range 1..1
        default:
            int32 randvalue = (randomPoints >= 1)
                ? basePoints + rand() % randomPoints
                : 0;

            basePoints += randvalue;
            break;
    }

   float value = float(basePoints);

    // random damage
    // bonus amount from combo points
	if (IsPlayer())
	{
        if (uint8 comboPoints = TO_PLAYER(this)->m_comboPoints)
		{
			if (float comboDamage = spellInfo->EffectPointsPerComboPoint[i])
			{
                value += comboDamage* comboPoints;
				s->m_requiresCP = true;
				TO_PLAYER(this)->m_spellcomboPoints = 0;
			}
		}
	}

    // amount multiplication based on caster's level
    if (!basePointsPerLevel && (spellInfo->Attributes & SPELL_ATTR0_LEVEL_DAMAGE_CALCULATION && spellInfo->spellLevel) &&
            spellInfo->Effect[i] != SPELL_EFFECT_WEAPON_PERCENT_DAMAGE &&
            spellInfo->Effect[i] != SPELL_EFFECT_KNOCK_BACK &&
			spellInfo->Effect[i] != SPELL_EFFECT_ADD_EXTRA_ATTACKS &&
			spellInfo->EffectApplyAuraName[i] != SPELL_AURA_MOD_INCREASE_SPEED_ALWAYS &&
            spellInfo->EffectApplyAuraName[i] != SPELL_AURA_MOD_SPEED_NOT_STACK &&
            spellInfo->EffectApplyAuraName[i] != SPELL_AURA_MOD_INCREASE_SPEED &&
            spellInfo->EffectApplyAuraName[i] != SPELL_AURA_MOD_DECREASE_SPEED)
                //there are many more: slow speed, -healing pct
            value *= 0.25f * exp(getLevel() * (70 - spellInfo->spellLevel) / 1000.0f);
            //value = int32(value * (int32)getLevel() / (int32)(_spellInfo->spellLevel ? _spellInfo->spellLevel : 1));
    value = ApplyEffectModifiers(spellInfo, i, value);
	value = s->DoCalculateEffect(i, target, value);

    return int32(value);
}

float Unit::ApplyEffectModifiers(SpellEntry * sp, uint8 effect_index, float value)
{
    if (Player * modOwner = GetSpellModOwner())
    {
        modOwner->ApplySpellMod(sp->Id, SPELLMOD_ALL_EFFECTS, value);
        switch (effect_index)
        {
            case 0:
                modOwner->ApplySpellMod(sp->Id, SPELLMOD_EFFECT1, value);
                break;
            case 1:
                modOwner->ApplySpellMod(sp->Id, SPELLMOD_EFFECT2, value);
                break;
            case 2:
                modOwner->ApplySpellMod(sp->Id, SPELLMOD_EFFECT3, value);
                break;
        }
    }
 	return value;
}
void Unit::InterruptSpell()
{
	if(m_currentSpell)
	{
		m_currentSpell->cancel();
	}
}

void Unit::DeMorph()
{
	// hope it solves it :)
	uint32 displayid = this->GetNativeDisplayId();
	this->SetDisplayId(displayid);
	EventModelChange();
}

void Unit::Emote(EmoteType emote)
{
	if(emote == 0)
		return;

	WorldPacket data(SMSG_EMOTE, 12);
	data << uint32(emote);
	data << this->GetGUID();
	SendMessageToSet(&data, true);
}

void Unit::SendChatMessageAlternateEntry(uint32 entry, uint8 type, uint32 lang, const char* msg)
{
	size_t UnitNameLength = 0, MessageLength = 0;
	CreatureInfo* ci;

	ci = CreatureNameStorage.LookupEntry(entry);
	if(!ci)
		return;

	UnitNameLength = strlen((char*)ci->Name) + 1;
	MessageLength = strlen((char*)msg) + 1;

	WorldPacket data(SMSG_MESSAGECHAT, 35 + UnitNameLength + MessageLength);
	data << type;
	data << lang;
	data << GetGUID();
	data << uint32(0);			// new in 2.1.0
	data << uint32(UnitNameLength);
	data << ci->Name;
	data << uint64(0);
	data << uint32(MessageLength);
	data << msg;
	data << uint8(0x00);
	SendMessageToSet(&data, true);
}

void Unit::WipeHateList()
{
	GetAIInterface()->WipeHateList();
}
void Unit::ClearHateList()
{
	GetAIInterface()->ClearHateList();
}

void Unit::WipeTargetList()
{
	GetAIInterface()->WipeTargetList();
}

void Unit::SetFaction(uint32 factionId)
{
	SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, factionId);
	_setFaction();
	summonhandler.SyncFactions(factionId);
	if(IsPlayer())
	{
		Player * player = TO_PLAYER(this);
		if(player->GetSummon())
			player->GetSummon()->SetFaction(factionId);
	}
}

void Unit::AddInRangeObject(Object* pObj)
{
	if(pObj->IsUnit())
	{
		if(isHostile(this, pObj))
			m_oppFactsInRange.insert(pObj);

		if(isFriendly(this, pObj))
			m_sameFactsInRange.insert(pObj);
	}

	Object::AddInRangeObject(pObj);
}//427

void Unit::OnRemoveInRangeObject(Object* pObj)
{
	m_oppFactsInRange.erase(pObj);
	m_sameFactsInRange.erase(pObj);

	if(pObj->IsUnit())
	{

		Unit* pUnit = TO< Unit* >(pObj);
		GetAIInterface()->CheckTarget(pUnit);

		if(GetCharmedUnitGUID() == pObj->GetGUID())
			if(m_currentSpell)
				m_currentSpell->cancel();

	}
}

void Unit::ClearInRangeSet()
{
	Object::ClearInRangeSet();
}

//Events
void Unit::EventAddEmote(EmoteType emote, uint32 time)
{
	m_oldEmote = GetEmoteState();
	SetEmoteState(emote);
	sEventMgr.AddEvent(this, &Creature::EmoteExpire, EVENT_UNIT_EMOTE, time, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
}

void Unit::EmoteExpire()
{
	SetEmoteState(m_oldEmote);
	sEventMgr.RemoveEvents(this, EVENT_UNIT_EMOTE);
}

void Unit::MoveToWaypoint(uint32 wp_id)
{
	if(this->m_useAI && this->GetAIInterface() != NULL)
	{
		AIInterface* ai = GetAIInterface();
		WayPoint* wp = ai->getWayPoint(wp_id);
		if(!wp)
		{
			LOG_ERROR("WARNING: Invalid WP specified in MoveToWaypoint.");
			return;
		}

		ai->m_currentWaypoint = wp_id;
		if(wp->flags != 0)
			ai->SetRun();
		ai->MoveTo(wp->x, wp->y, wp->z, 0);
	}
}

void Unit::CalcDamage()
{
	if(IsPlayer())
		TO< Player* >(this)->CalcDamage();
	else
	{
		if(IsPet())
			TO< Pet* >(this)->UpdateAP();
		float r;
		float delta;
		float mult;

		float ap_bonus = GetAP() / 14000.0f;

		float bonus = ap_bonus * (GetBaseAttackTime(MELEE) + TO< Creature* >(this)->m_speedFromHaste);

		delta = float(TO_CREATURE(this)->ModDamageDone[0]);
		mult = float(TO_CREATURE(this)->ModDamageDonePct[0]);
		r = (BaseDamage[0] + bonus) * mult + delta;
		// give some diversity to pet damage instead of having a 77-78 damage range (as an example)
		SetMinDamage(r > 0 ? (IsPet() ? r * 0.9f : r) : 0);
		r = (BaseDamage[1] + bonus) * mult + delta;
		SetMaxDamage(r > 0 ? (IsPet() ? r * 1.1f : r) : 0);

		//	SetMinRangedDamage(BaseRangedDamage[0]*mult+delta);
		//	SetMaxRangedDamage(BaseRangedDamage[1]*mult+delta);

	}
}

//returns absorbed dmg
uint32 Unit::ManaShieldAbsorb(uint32 dmg)
{
	if(!m_manashieldamt)
		return 0;
	//mana shield group->16. the only

	uint32 mana = GetPower(POWER_TYPE_MANA);
	int32 effectbonus = 0;

	int32 potential = (mana * 50) / ((100 + effectbonus));
	if(potential > m_manashieldamt)
		potential = m_manashieldamt;

	if((int32)dmg < potential)
		potential = dmg;

	uint32 cost = (potential * (100 + effectbonus)) / 50;

	SetUInt32Value(UNIT_FIELD_POWER1, mana - cost);
	m_manashieldamt -= potential;
	if(!m_manashieldamt)
		RemoveAura(m_manaShieldId);
	return potential;
}

uint32 Unit::AbsorbDamage(uint32 School, uint32* dmg)
{
	if(dmg == NULL)
		return 0;

	if(School > 6)
		return 0;

	uint32 dmg_absorbed = 0;
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; x++)
	{
		if(m_auras[x] == NULL || ! m_auras[x]->IsAbsorb())
			continue;

		AbsorbAura* aur = TO< AbsorbAura* > (m_auras[x]);

		dmg_absorbed += aur->AbsorbDamage(School, dmg);
	}

	if(IsPlayer() && TO_PLAYER(this)->GodModeCheat)
	{
		dmg_absorbed += *dmg;
		*dmg = 0;
	}

	return dmg_absorbed;
}

bool Unit::setDetectRangeMod(uint64 guid, int32 amount)
{
	int next_free_slot = -1;
	for(int i = 0; i < 5; i++)
	{
		if(m_detectRangeGUID[i] == 0 && next_free_slot == -1)
		{
			next_free_slot = i;
		}
		if(m_detectRangeGUID[i] == guid)
		{
			m_detectRangeMOD[i] = amount;
			return true;
		}
	}
	if(next_free_slot != -1)
	{
		m_detectRangeGUID[next_free_slot] = guid;
		m_detectRangeMOD[next_free_slot] = amount;
		return true;
	}
	return false;
}

void Unit::unsetDetectRangeMod(uint64 guid)
{
	for(int i = 0; i < 5; i++)
	{
		if(m_detectRangeGUID[i] == guid)
		{
			m_detectRangeGUID[i] = 0;
			m_detectRangeMOD[i] = 0;
		}
	}
}

int32 Unit::getDetectRangeMod(uint64 guid)
{
	for(int i = 0; i < 5; i++)
	{
		if(m_detectRangeGUID[i] == guid)
		{
			return m_detectRangeMOD[i];
		}
	}
	return 0;
}

void Unit::SetStandState(uint8 standstate)
{
	//only take actions if standstate did change.
	StandState bef = GetStandState();
	if(bef == standstate)
		return;

	SetByte(UNIT_FIELD_BYTES_1, 0, standstate);
	if(standstate == STANDSTATE_STAND)  //standup
		RemoveAurasByInterruptFlag(AURA_INTERRUPT_ON_STAND_UP);

	if(IsPlayer())
		TO< Player* >(this)->GetSession()->OutPacket(SMSG_STANDSTATE_UPDATE, 1, &standstate);
}

void Unit::RemoveAurasByInterruptFlag(uint32 flag)
{
	Aura* a;
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; x++)
	{
		a = m_auras[x];
		if(a == NULL)
			continue;

		//some spells do not get removed all the time only at specific intervals
		if((a->m_spellProto->AuraInterruptFlags & flag) && !(a->m_spellProto->procFlags & PROC_REMOVEONUSE))
		{
			a->Remove();
			m_auras[x] = NULL;
		}
	}
}

bool Unit::HasAuraVisual(uint32 visualid)
{
	//passive auras do not have visual (at least when code was written)
	for(uint32 x = MAX_REMOVABLE_AURAS_START; x < MAX_REMOVABLE_AURAS_END; x++)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->SpellVisual[0] == visualid)
			return true;
	return false;
}

bool Unit::HasAura(uint32 spellid)
{
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; x++)
		if(m_auras[x] && m_auras[x]->GetSpellId() == spellid)
		{
			return true;
		}

	return false;
}

Aura* Unit::GetAuraWithSlot(uint32 slot)
{
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; x++)
		if(m_auras[x] && m_auras[x]->m_visualSlot == (uint16)slot)
		{
			return m_auras[x];
		}

	return NULL;
}

uint16 Unit::GetAuraStackCount(uint32 spellid)
{
	uint16 count = 0;
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; x++)
		if(m_auras[x] && m_auras[x]->GetSpellId() == spellid)
			count++;
	return count;
}

void Unit::DropAurasOnDeath()
{
	for(uint32 x = MAX_REMOVABLE_AURAS_START; x < MAX_REMOVABLE_AURAS_END; x++)
		if(m_auras[x])
		{
			if(m_auras[x] && m_auras[x]->GetSpellProto()->AttributesEx3 & SPELL_ATTR3_DEATH_PERSISTENT)
				continue;
			else
				m_auras[x]->Remove();
		}
}

void Unit::UpdateSpeed(uint32 ignorerspell)
{
	UpdateSpeedType(RUN, ignorerspell);
	UpdateSpeedType(FLY, ignorerspell);
	UpdateSpeedType(SWIM, ignorerspell);
	/*if(!GetMount())
	{
		m_runSpeed = m_base_runSpeed * (1.0f + ((float)m_speedModifier) / 100.0f);
	}
	else
	{
		m_runSpeed = m_base_runSpeed * (1.0f + ((float)m_mountedspeedModifier) / 100.0f);
		m_runSpeed += (m_speedModifier < 0) ? (m_base_runSpeed * ((float)m_speedModifier) / 100.0f) : 0;
	}



	m_flySpeed = PLAYER_NORMAL_FLIGHT_SPEED * (1.0f + ((float)m_flyspeedModifier) / 100.0f);

	// Limit speed due to effects such as http://www.wowhead.com/?spell=31896 [Judgement of Justice]
	if(m_maxSpeed && m_runSpeed > m_maxSpeed)
		m_runSpeed = m_maxSpeed;
	if(m_runSpeed <= 0)
		m_runSpeed = PLAYER_NORMAL_RUN_SPEED;
	if( IsPlayer() && TO_PLAYER(this)->m_changingMaps )
		TO< Player* >(this)->resend_speed = true;
	else
	{
		SetSpeeds( RUN, m_runSpeed );
		SetSpeeds( FLY, m_flySpeed );
	}*/
}

void Unit::UpdateSpeedType(uint32 type, uint32 ignorerspell)
{
	int32 main_speed_mod  = 0;
	float stack_bonus     = 1.0f;
	float non_stack_bonus = 1.0f;
	float basespeed = (IsControlledByPlayer() ? playerBaseMoveSpeed[type] : baseMoveSpeed[type]);
	if(IsCreature())
	{
		Creature * c = TO_CREATURE(this);
		switch(type)
		{
			case WALK:
			{
				if(basespeed != m_base_walkSpeed)
					basespeed = m_base_walkSpeed;
			}break;
			case RUN:
			{
				if(basespeed != m_base_runSpeed)
					basespeed = m_base_runSpeed;
			}break;
		};
	}
    switch (type)
    {
        // Only apply debuffs
        case FLYBACK:
        case RUNBACK:
        case SWIMBACK:
            break;
        case WALK:
            return;
        case RUN:
        {
			if (GetMount()) // Use on mount auras
            {
                main_speed_mod  = GetMaxPositiveAuraModifier(SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED, ignorerspell);
                stack_bonus     = GetTotalAuraMultiplier(SPELL_AURA_MOD_MOUNTED_SPEED_ALWAYS, ignorerspell);
                non_stack_bonus += GetMaxPositiveAuraModifier(172, ignorerspell) / 100.0f;
            }
            else
            {
                main_speed_mod  = GetMaxPositiveAuraModifier(SPELL_AURA_MOD_INCREASE_SPEED, ignorerspell);
                stack_bonus     = GetTotalAuraMultiplier(129, ignorerspell);
                non_stack_bonus += GetMaxPositiveAuraModifier(171, ignorerspell) / 100.0f;
            }
            break;
        }
        case SWIM:
        {
            main_speed_mod  = GetMaxPositiveAuraModifier(SPELL_AURA_MOD_INCREASE_SWIM_SPEED, ignorerspell);
            break;
        }
        case FLY:
        {
			if (GetTypeId() == TYPEID_UNIT && IsControlledByPlayer()) // not sure if good for pet
            {
                main_speed_mod  = GetMaxPositiveAuraModifier(206, ignorerspell);
                stack_bonus     = GetTotalAuraMultiplier(SPELL_AURA_MOD_VEHICLE_SPEED_ALWAYS, ignorerspell);

                // for some spells this mod is applied on vehicle owner
                int32 owner_speed_mod = 0;

				//if (Unit* owner = GetMapMgrUnit(GetCharmedByGUID()))
                    //owner_speed_mod = owner->GetMaxPositiveAuraModifier(206);

                main_speed_mod = std::max(main_speed_mod, owner_speed_mod);
            }
            else if (GetMount())
            {
                main_speed_mod  = GetMaxPositiveAuraModifier(207, ignorerspell);
                stack_bonus     = GetTotalAuraMultiplier(SPELL_AURA_MOD_MOUNTED_FLIGHT_SPEED_ALWAYS, ignorerspell);
            }
            else             // Use not mount (shapeshift for example) auras (should stack)
                main_speed_mod  = GetTotalAuraModifier(208) + GetTotalAuraModifier(206, ignorerspell);

            non_stack_bonus += GetMaxPositiveAuraModifier(SPELL_AURA_MOD_FLIGHT_SPEED_NOT_STACK, ignorerspell) / 100.0f;

            // Update speed for vehicle if available
            //if (GetTypeId() == TYPEID_PLAYER && GetVehicleBase())
               // GetVehicleBase()->UpdateSpeedType(FLY);
            break;
        }
        default:
            sLog.outError("Unit::UpdateSpeed: Unsupported move type (%d)", type);
            return;
    }

    // now we ready for speed calculation
    float speed = std::max(non_stack_bonus, stack_bonus);
    if (main_speed_mod)
        AddPctN(speed, main_speed_mod);

    switch (type)
    {
        case RUN:
        case SWIM:
        case FLY:
        {
            // Normalize speed by 191 aura SPELL_AURA_USE_NORMAL_MOVEMENT_SPEED if need
            // TODO: possible affect only on MOVE_RUN
            if (int32 normalization = GetMaxPositiveAuraModifier(191, ignorerspell))
            {
                // Use speed from aura
				float max_speed = normalization / basespeed;
                if (speed > max_speed)
                    speed = max_speed;
            }
            break;
        }
        default:
            break;
    }

    // Apply strongest slow aura mod to speed
    int32 slow = GetMaxNegativeAuraModifier(SPELL_AURA_MOD_DECREASE_SPEED, ignorerspell);
    if (slow)
    {
        AddPctN(speed, slow);
        if (float minSpeedMod = (float)GetMaxPositiveAuraModifier(305, ignorerspell))
        {
            float min_speed = minSpeedMod / 100.0f;
            if (speed < min_speed)
                speed = min_speed;
        }
    }
	SetSpeeds(type, (speed*basespeed));
    //SetSpeed(type, speed, forced);
}
bool Unit::HasBuff(uint32 spellid) // cebernic:it does not check passive auras & must be visible auras
{
	for(uint32 x = MAX_POSITIVE_AURAS_EXTEDED_START; x < MAX_POSITIVE_AURAS_EXTEDED_END; x++)
		if(m_auras[x] && m_auras[x]->GetSpellId() == spellid)
			return true;

	return false;
}

bool Unit::HasBuff(uint32 spellid, uint64 guid)
{
	for(uint32 x = MAX_POSITIVE_AURAS_EXTEDED_START; x < MAX_POSITIVE_AURAS_EXTEDED_END; x++)
		if(m_auras[x] && m_auras[x]->GetSpellId() == spellid && m_auras[x]->m_casterGuid == guid)
			return true;

	return false;
}

bool Unit::HasVisialPosAurasOfNameHashWithCaster(uint32 namehash, Unit* caster)
{
	for(uint32 i = MAX_POSITIVE_AURAS_EXTEDED_START; i < MAX_POSITIVE_AURAS_EXTEDED_END; ++i)
		if(m_auras[i] && m_auras[i]->GetSpellProto()->NameHash == namehash && m_auras[i]->GetCasterGUID() == caster->GetGUID())
			return true;

	return false;
}

uint8 Unit::CastSpell(Unit* Target, SpellEntry* Sp, bool triggered)
{
	if(Sp == NULL)
		return SPELL_FAILED_UNKNOWN;

	Spell* newSpell = sSpellFactoryMgr.NewSpell(this, Sp, triggered, 0);
	SpellCastTargets targets(0);
	if(Target)
	{
		targets.m_targetMask |= TARGET_FLAG_UNIT;
		targets.m_unitTarget = Target->GetGUID();
	}
	else
	{
		newSpell->GenerateTargets(&targets);
	}
	return newSpell->prepare(&targets);
}

uint8 Unit::CastSpell(Unit* Target, uint32 SpellID, bool triggered)
{
	SpellEntry* ent = dbcSpell.LookupEntryForced(SpellID);
	if(ent == NULL) return SPELL_FAILED_UNKNOWN;

	return CastSpell(Target, ent, triggered);
}

uint8 Unit::CastSpell(uint64 targetGuid, SpellEntry* Sp, bool triggered)
{
	if(Sp == NULL)
		return SPELL_FAILED_UNKNOWN;

	SpellCastTargets targets(targetGuid);
	Spell* newSpell = sSpellFactoryMgr.NewSpell(this, Sp, triggered, 0);
	return newSpell->prepare(&targets);
}

uint8 Unit::CastSpell(uint64 targetGuid, uint32 SpellID, bool triggered)
{
	SpellEntry* ent = dbcSpell.LookupEntryForced(SpellID);
	if(ent == NULL) return SPELL_FAILED_UNKNOWN;

	return CastSpell(targetGuid, ent, triggered);
}

uint8 Unit::CastSpell(Unit* Target, uint32 SpellID, uint32 forced_basepoints, bool triggered)
{
	return CastSpell(Target, dbcSpell.LookupEntryForced(SpellID), forced_basepoints, triggered);
}

uint8 Unit::CastSpell(Unit* Target, SpellEntry* Sp, uint32 forced_basepoints, bool triggered)
{
	if(Sp == NULL)
		return SPELL_FAILED_UNKNOWN;

	Spell* newSpell = sSpellFactoryMgr.NewSpell(this, Sp, triggered, 0);
	newSpell->forced_basepoints[0] = forced_basepoints;
	SpellCastTargets targets(0);
	if(Target != NULL)
	{
		targets.m_targetMask |= TARGET_FLAG_UNIT;
		targets.m_unitTarget = Target->GetGUID();
	}
	else
	{
		newSpell->GenerateTargets(&targets);
	}
	return newSpell->prepare(&targets);
}

uint8 Unit::CastSpell(Unit* Target, uint32 SpellID, uint32 forced_basepoints, int32 charges, bool triggered)
{
	return CastSpell(Target, dbcSpell.LookupEntryForced(SpellID), forced_basepoints, charges, triggered);
}

uint8 Unit::CastSpell(Unit* Target, SpellEntry* Sp, uint32 forced_basepoints, int32 charges, bool triggered)
{
	if(Sp == NULL)
		return SPELL_FAILED_UNKNOWN;

	Spell* newSpell = sSpellFactoryMgr.NewSpell(this, Sp, triggered, 0);
	newSpell->forced_basepoints[0] = forced_basepoints;
	newSpell->m_charges = charges;
	SpellCastTargets targets(0);
	if(Target != NULL)
	{
		targets.m_targetMask |= TARGET_FLAG_UNIT;
		targets.m_unitTarget = Target->GetGUID();
	}
	else
	{
		newSpell->GenerateTargets(&targets);
	}
	return newSpell->prepare(&targets);
}

void Unit::CastSpellAoF(float x, float y, float z, SpellEntry* Sp, bool triggered)
{
	if(Sp == NULL)
		return;

	SpellCastTargets targets;
	targets.m_destX = x;
	targets.m_destY = y;
	targets.m_destZ = z;
	targets.m_targetMask = TARGET_FLAG_DEST_LOCATION;
	Spell* newSpell = sSpellFactoryMgr.NewSpell(this, Sp, triggered, 0);
	newSpell->prepare(&targets);
}

void Unit::CastSpellAoF(float x, float y, float z, SpellEntry* Sp, bool triggered, int32 basepoints, int32 basepoints2, int32 basepoints3)
{
	if(Sp == NULL)
		return;

	SpellCastTargets targets;
	targets.m_destX = x;
	targets.m_destY = y;
	targets.m_destZ = z;
	targets.m_targetMask = TARGET_FLAG_DEST_LOCATION;
	Spell* newSpell = sSpellFactoryMgr.NewSpell(this, Sp, triggered, 0);
	newSpell->forced_basepoints[0] = basepoints;
	newSpell->forced_basepoints[1] = basepoints2;
	newSpell->forced_basepoints[2] = basepoints3;
	newSpell->prepare(&targets);
}

void Unit::PlaySpellVisual(uint64 target, uint32 spellVisual)
{
	WorldPacket data(SMSG_PLAY_SPELL_VISUAL, 12);
	data << target << spellVisual;
	SendMessageToSet(&data, true);
}

void Unit::Root()
{
	m_special_state |= UNIT_STATE_ROOT;

	if( !IsPlayer() ){
		m_aiInterface->m_canMove = false;
		m_aiInterface->StopMovement(1);
	}
	RemoveUnitMovementFlag(MOVEFLAG_MASK_MOVING);
	AddUnitMovementFlag(MOVEFLAG_ROOTED);
	m_rooted = 1;
	if(IsPlayer())
	{
		WorldPacket data( SMSG_FORCE_MOVE_ROOT, 12 );
		data << GetNewGUID();
		data << uint32( 1 );
		SendMessageToSet( &data, true);
	}
	else
	{
		WorldPacket data(SMSG_SPLINE_MOVE_ROOT, 8);
		data << GetNewGUID();
		SendMessageToSet(&data, true);
	}
}

void Unit::Unroot()
{
	m_special_state &= ~UNIT_STATE_ROOT;
		
	if( !IsPlayer() )
		m_aiInterface->m_canMove = true;

	RemoveUnitMovementFlag(MOVEFLAG_ROOTED);
	m_rooted = 0;
	if(IsPlayer())
	{
		WorldPacket data( SMSG_FORCE_MOVE_UNROOT, 12 );
		data << GetNewGUID();
		data << uint32( 5 );
		SendMessageToSet( &data, true);
	}
	else
	{
		WorldPacket data(SMSG_SPLINE_MOVE_UNROOT, 8);
		data << GetNewGUID();
		SendMessageToSet(&data, true);
	}
}

void Unit::RemoveAurasByBuffType(uint32 buff_type, const uint64 & guid, uint32 skip)
{
	uint64 sguid = buff_type >= SPELL_TYPE_BLESSING ? guid : 0;

	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; x++)
	{
		if(m_auras[x]  //have aura
		        && (m_auras[x]->GetSpellProto()->BGR_one_buff_on_target & buff_type) // aura is in same group
		        && m_auras[x]->GetSpellId() != skip // make sure to not do self removes in case aura will stack
		        && (!sguid || (sguid && m_auras[x]->m_casterGuid == sguid)) // we either remove everything or just buffs from us
		  )
			m_auras[x]->Remove();
	}
}

bool Unit::HasAurasOfBuffType(uint32 buff_type, const uint64 & guid, uint32 skip)
{
	uint64 sguid = (buff_type == SPELL_TYPE_BLESSING || buff_type == SPELL_TYPE_WARRIOR_SHOUT) ? guid : 0;

	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; x++)
	{
		if(m_auras[x] && m_auras[x]->GetSpellProto()->BGR_one_buff_on_target & buff_type && m_auras[x]->GetSpellId() != skip)
			if(!sguid || (m_auras[x]->m_casterGuid == sguid))
				return true;
	}

	return false;
}

uint32 Unit::FindAuraCountByHash(uint32 HashName, uint32 maxcount)
{
	uint32 count = 0;

	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; ++x)
	{
		if(m_auras[x] && (m_auras[x]->GetSpellProto()->NameHash == HashName))
		{
			count++;
			if(count == maxcount)
				break;
		}
	}

	return count;
}

AuraCheckResponse Unit::AuraCheck(SpellEntry* proto, Object* caster)
{
	AuraCheckResponse resp;

	// no error for now
	resp.Error = AURA_CHECK_RESULT_NONE;
	resp.Misc  = 0;

	uint32 name_hash = proto->NameHash;
	uint32 rank = proto->RankNumber;
	Aura* aura;
	SpellEntry* aura_sp;

	// look for spells with same namehash
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; x++)
	{
		aura = m_auras[x];
		if(aura != NULL && aura->GetSpellProto()->NameHash == name_hash)
		{
			// we've got an aura with the same name as the one we're trying to apply
			// but first we check if it has the same effects
			aura_sp = aura->GetSpellProto();

			if((aura_sp->Effect[0] == proto->Effect[0] && (aura_sp->Effect[0] != SPELL_EFFECT_APPLY_AURA || aura_sp->EffectApplyAuraName[0] == proto->EffectApplyAuraName[0])) &&
			        (aura_sp->Effect[1] == proto->Effect[1] && (aura_sp->Effect[1] != SPELL_EFFECT_APPLY_AURA || aura_sp->EffectApplyAuraName[1] == proto->EffectApplyAuraName[1])) &&
			        (aura_sp->Effect[2] == proto->Effect[2] && (aura_sp->Effect[2] != SPELL_EFFECT_APPLY_AURA || aura_sp->EffectApplyAuraName[2] == proto->EffectApplyAuraName[2])))
			{
				resp.Misc = aura->GetSpellProto()->Id;

				// compare the rank to our applying spell
				if(aura_sp->RankNumber > rank)
				{
					if(proto->Effect[0] == SPELL_EFFECT_TRIGGER_SPELL ||
					        proto->Effect[1] == SPELL_EFFECT_TRIGGER_SPELL ||
					        proto->Effect[2] == SPELL_EFFECT_TRIGGER_SPELL)
					{
						resp.Error = AURA_CHECK_RESULT_LOWER_BUFF_PRESENT;
					}
					else
						resp.Error = AURA_CHECK_RESULT_HIGHER_BUFF_PRESENT;
				}
				else
					resp.Error = AURA_CHECK_RESULT_LOWER_BUFF_PRESENT;

				// we found something, save some loops and exit
				break;
			}
		}
	}
	//LOG_DEBUG( "resp = %i", resp.Error );
	// return it back to our caller
	return resp;
}


AuraCheckResponse Unit::AuraCheck(SpellEntry* proto, Aura* aur, Object* caster)
{
	AuraCheckResponse resp;
	SpellEntry* aura_sp = aur->GetSpellProto();

	// no error for now
	resp.Error = AURA_CHECK_RESULT_NONE;
	resp.Misc  = 0;

	// look for spells with same namehash
	if(aur->GetSpellProto()->NameHash == proto->NameHash)
	{
		// we've got an aura with the same name as the one we're trying to apply
		// but first we check if it has the same effects
		if((aura_sp->Effect[0] == proto->Effect[0] && (aura_sp->Effect[0] != SPELL_EFFECT_APPLY_AURA || aura_sp->EffectApplyAuraName[0] == proto->EffectApplyAuraName[0])) &&
		        (aura_sp->Effect[1] == proto->Effect[1] && (aura_sp->Effect[1] != SPELL_EFFECT_APPLY_AURA || aura_sp->EffectApplyAuraName[1] == proto->EffectApplyAuraName[1])) &&
		        (aura_sp->Effect[2] == proto->Effect[2] && (aura_sp->Effect[2] != SPELL_EFFECT_APPLY_AURA || aura_sp->EffectApplyAuraName[2] == proto->EffectApplyAuraName[2])))
		{
			resp.Misc = aur->GetSpellProto()->Id;

			// compare the rank to our applying spell
			if(aur->GetSpellProto()->RankNumber > proto->RankNumber)
				resp.Error = AURA_CHECK_RESULT_HIGHER_BUFF_PRESENT;
			else
				resp.Error = AURA_CHECK_RESULT_LOWER_BUFF_PRESENT;
		}
	}

	// return it back to our caller
	return resp;
}

void Unit::OnPushToWorld()
{
	//Zack : we already relocated events on aura add ?
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; ++x)
	{
		if(m_auras[x] != 0)
			m_auras[x]->RelocateEvents();
	}

	if( GetVehicleComponent() != NULL )
		GetVehicleComponent()->InstallAccessories();

	z_axisposition = 0.0f;
	
	UnitLoadMiDisplayInfo(this);
}

//! Remove Unit from world
void Unit::RemoveFromWorld(bool free_guid)
{
	if( GetCurrentVehicle() != NULL )
		GetCurrentVehicle()->EjectPassenger( this );

	if( GetVehicleComponent() != NULL ){
		GetVehicleComponent()->RemoveAccessories();
		GetVehicleComponent()->EjectAllPassengers();
	}

	RemoveVehicleComponent();

	CombatStatus.OnRemoveFromWorld();
	if(GetSummonedCritterGUID() != 0)
	{
		SetSummonedCritterGUID(0);

		Unit* u = m_mapMgr->GetUnit(GetSummonedCritterGUID());
		if(u != NULL)
			u->Delete();
	}

	if(dynObj != 0)
		dynObj->Remove();

	for(uint8 i = 0; i < 4; ++i)
	{
		if(m_ObjectSlots[i] != 0)
		{
			GameObject* obj = m_mapMgr->GetGameObject(m_ObjectSlots[i]);
			if(obj)
				obj->ExpireAndDelete();

			m_ObjectSlots[i] = 0;
		}
	}

	ClearAllAreaAuraTargets();
	RemoveAllAreaAuraByOther();

	Object::RemoveFromWorld(free_guid);

	//zack: should relocate new events to new eventmanager and not to -1
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; ++x)
		if(m_auras[x] != 0)
		{
			if(m_auras[x]->m_deleted)
			{
				m_auras[x] = NULL;
				continue;
			}
			m_auras[x]->RelocateEvents();
		}

	m_aiInterface->WipeReferences();
}

void Unit::Deactivate(MapMgr* mgr)
{
	CombatStatus.Vanished();
	Object::Deactivate(mgr);
}

void Unit::RemoveAurasByInterruptFlagButSkip(uint32 flag, uint32 skip)
{
	Aura* a;
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; x++)
	{
		a = m_auras[x];
		if(a == 0)
			continue;

		//some spells do not get removed all the time only at specific intervals
		if((a->m_spellProto->AuraInterruptFlags & flag) && (a->m_spellProto->Id != skip) && a->m_spellProto->proc_interval == 0)
		{
			//the black sheep's of society
			if(a->m_spellProto->AuraInterruptFlags & AURA_INTERRUPT_ON_CAST_SPELL)
			{
				switch(a->GetSpellProto()->Id)
				{
						//priest - surge of light
					case 33151:
						{
							//our luck. it got triggered on smite..we do not remove it just yet
							if(m_currentSpell && m_currentSpell->GetProto()->NameHash == SPELL_HASH_SMITE)
								continue;

							//this spell gets removed only when casting smite
							SpellEntry* spi = dbcSpell.LookupEntryForced(skip);
							if(spi && spi->NameHash != SPELL_HASH_SMITE)
								continue;
						}
						break;
					case 34936:	// Backlash
						{
							if(m_currentSpell && m_currentSpell->GetProto()->NameHash == SPELL_HASH_SHADOW_BOLT)
								continue;
							if(m_currentSpell && m_currentSpell->GetProto()->NameHash == SPELL_HASH_INCINERATE)
								continue;
							SpellEntry* spi = dbcSpell.LookupEntryForced(skip);
							if(spi && spi->NameHash != SPELL_HASH_SHADOW_BOLT && spi->NameHash != SPELL_HASH_INCINERATE)
								continue;
						}
						break;
					case 59578: // Art of War
					case 53489:
						{
							if(m_currentSpell && m_currentSpell->m_spellInfo->NameHash == SPELL_HASH_FLASH_OF_LIGHT)
								continue;
							SpellEntry* spi = dbcSpell.LookupEntryForced(skip);
							if(spi && spi->NameHash != SPELL_HASH_FLASH_OF_LIGHT)
								continue;
						}
						break;
					case 17941: //Shadow Trance
						{
							if(m_currentSpell && m_currentSpell->GetProto()->NameHash == SPELL_HASH_SHADOW_BOLT)
								continue;
							SpellEntry* spi = dbcSpell.LookupEntryForced(skip);
							if(spi && spi->NameHash != SPELL_HASH_SHADOW_BOLT)
								continue;
						}
						break;
					case 16166: // [Shaman] Elemental Mastery
						{
							SpellEntry* spi = dbcSpell.LookupEntryForced(skip);
							if(spi && !(spi->NormalizedSchoolMask() == SCHOOL_FIRE || spi->NormalizedSchoolMask() == SCHOOL_FROST || spi->NormalizedSchoolMask() == SCHOOL_NATURE))
								continue;
						}
						break;
					case 48108: // Hot Streak
						{
							if(m_currentSpell && m_currentSpell->GetProto()->NameHash != SPELL_HASH_PYROBLAST)
								continue;
						}
						break;
				}
			}
			a->Remove();
		}
	}
}

int Unit::HasAurasWithNameHash(uint32 name_hash)
{
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; ++x)
	{
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash == name_hash)
			return m_auras[x]->m_spellProto->Id;
	}

	return 0;
}

bool Unit::HasAuraWithName(uint32 name, uint32 skipspell)
{
	for(uint32 i = MAX_TOTAL_AURAS_START; i < MAX_TOTAL_AURAS_END; ++i)
	{
		if(m_auras[ i ] != NULL && m_auras[ i ]->GetSpellProto()->Id != skipspell && m_auras[ i ]->GetSpellProto()->AppliesAura(name))
			return true;
	}

	return false;
}

bool Unit::HasFlyingAura(uint32 skipspell)
{
	for(uint32 i = MAX_TOTAL_AURAS_START; i < MAX_TOTAL_AURAS_END; ++i)
	{
		if(m_auras[ i ] != NULL && m_auras[i]->GetSpellId() != skipspell && (m_auras[ i ]->GetSpellProto()->AppliesAura(SPELL_AURA_ENABLE_FLIGHT) ||
			m_auras[ i ]->GetSpellProto()->AppliesAura(SPELL_AURA_ENABLE_FLIGHT2) || m_auras[ i ]->GetSpellProto()->AppliesAura(SPELL_AURA_ENABLE_FLIGHT_WITH_UNMOUNTED_SPEED) || 
			m_auras[ i ]->GetSpellProto()->AppliesAura(SPELL_AURA_MOD_MOUNTED_FLIGHT_SPEED_ALWAYS) || m_auras[ i ]->GetSpellProto()->AppliesAura(SPELL_AURA_ALLOW_FLIGHT) || 
			m_auras[ i ]->GetSpellProto()->AppliesAura(SPELL_AURA_MOD_VEHICLE_SPEED_ALWAYS) || m_auras[ i ]->GetSpellProto()->AppliesAura(SPELL_AURA_MOD_FLIGHT_SPEED_NOT_STACK)))
			return true;
	}

	return false;
}
uint32 Unit::GetAuraCountWithName(uint32 name)
{
	uint32 count = 0;

	for(uint32 i = MAX_TOTAL_AURAS_START; i < MAX_TOTAL_AURAS_END; ++i)
	{
		if(m_auras[ i ] != NULL && m_auras[ i ]->GetSpellProto()->AppliesAura(name))
			++count;
	}

	return count;
}

bool Unit::HasAuraWithMechanics(uint32 mechanic)
{
	for(uint32 x = MAX_NEGATIVE_AURAS_EXTEDED_START; x < MAX_NEGATIVE_AURAS_EXTEDED_END; ++x)
	{
		if(m_auras[x] && m_auras[x]->m_spellProto)
			if(Spell::GetMechanic(m_auras[x]->m_spellProto) == mechanic)
				return true;
	}

	return false;
}

bool Unit::IsPoisoned()
{
	for(uint32 x = MAX_NEGATIVE_AURAS_EXTEDED_START; x < MAX_NEGATIVE_AURAS_EXTEDED_END; ++x)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->c_is_flags & SPELL_FLAG_IS_POISON)
			return true;

	return false;
}


void Unit::SendAuraUpdate(uint32 AuraSlot, bool remove)
{
	BroadcastAuras();
/*	Aura* aur = m_auras[ AuraSlot ];

	ARCEMU_ASSERT(aur != NULL);

	WorldPacket data(SMSG_AURA_UPDATE, 30);

	if(remove)
	{
		data << WoWGuid(GetGUID());
		data << uint8(aur->m_visualSlot);
		data << uint32(0);
	}
	else
	{
		uint8 flags = (AFLAG_EFFECT_1 | AFLAG_EFFECT_2 | AFLAG_EFFECT_3);

		if(aur->IsPositive())
			flags |= AFLAG_CANCELLABLE;
		else
			flags |= AFLAG_NEGATIVE;

		if( aur->GetDuration() != 0 && !(aur->GetSpellProto()->AttributesEx5 & SPELL_ATTR5_HIDE_DURATION))
			flags |= AFLAG_DURATION;

		data << WoWGuid(GetGUID());
		data << uint8(aur->m_visualSlot);

		data << uint32(aur->GetSpellId());
		data << uint8(flags);

		Unit* caster = aur->GetUnitCaster();
		if(caster != NULL)
			data << uint8(caster->getLevel());
		else
			data << uint8(sWorld.m_levelCap);
		uint8 count;
		std::map< uint32, struct SpellCharge >::iterator iter;
		iter = m_chargeSpells.find(aur->GetSpellId());
		if(iter != m_chargeSpells.end())
			count = iter->second.count;
		else
			count = m_auraStackCount[ aur->m_visualSlot ];
		data << uint8(count);

		if((flags & AFLAG_NOT_CASTER) == 0)
			data << WoWGuid(aur->GetCasterGUID());

		if(flags & AFLAG_DURATION)
		{
			data << uint32(aur->GetDuration());
			data << uint32(aur->GetTimeLeft());
		}
	}

	SendMessageToSet(&data, true);*/
}

uint32 Unit::ModVisualAuraStackCount(Aura* aur, int32 count)
{
	if(!aur)
		return 0;

	uint8 slot = aur->m_visualSlot;
	if(slot >= MAX_NEGATIVE_VISUAL_AURAS_END)
		return 0;

	if(count < 0 && m_auraStackCount[slot] <= -count)
	{
		m_auraStackCount[slot] = 0;
		m_auravisuals[slot] = 0;

		SendAuraUpdate(slot, true);
	}
	else
	{
		m_auraStackCount[slot] += static_cast<uint8>(count);
		m_auravisuals[slot] = aur->GetSpellId();

		SendAuraUpdate(slot, false);
	}

	return m_auraStackCount[slot];
}

void Unit::RemoveAurasOfSchool(uint32 School, bool Positive, bool Immune)
{
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; ++x)
		if(m_auras[x]
		        && m_auras[x]->GetSpellProto()->NormalizedSchoolMask() == School
		        && (!m_auras[x]->IsPositive() || Positive)
		        && (!Immune && m_auras[x]->GetSpellProto()->Attributes & SPELL_ATTR0_UNAFFECTED_BY_INVULNERABILITY)
		  )
			m_auras[x]->Remove();
}

void Unit::EnableFlight()
{
	if(!IsInWorld())
		return;
	if(IsCreature())
		SetByteFlag( UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_UNK_2 );

	WorldPacket data(SMSG_MOVE_SET_CAN_FLY, 13);
	data << GetNewGUID();
	data << uint32(2);
	SendMessageToSet(&data, true);
	if(IsPlayer())
	{
		TO< Player* >(this)->z_axisposition = 0.0f;
		TO< Player* >(this)->m_setflycheat = true;
	}
	AddUnitMovementFlag(MOVEFLAG_CAN_FLY);
}

void Unit::DisableFlight()
{
	if(!IsInWorld())
		return;
	if(IsCreature())
		RemoveByteFlag( UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_UNK_2 );
	WorldPacket data(SMSG_MOVE_UNSET_CAN_FLY, 13);
	data << GetNewGUID();
	data << uint32(5);
	SendMessageToSet(&data, true);
	RemoveUnitMovementFlag(MOVEFLAG_CAN_FLY);
	if(IsPlayer())
	{
		TO_PLAYER(this)->m_flycheckdelay = getMSTime() + (10*IN_MILLISECONDS);
		TO< Player* >(this)->m_setflycheat = false;
	}
}

bool Unit::IsDazed()
{
	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; ++x)
	{
		if(m_auras[x])
		{
			if(m_auras[x]->GetSpellProto()->Mechanic == MECHANIC_ENSNARED)
				return true;
			for(uint32 y = 0; y < 3; y++)
				if(m_auras[x]->GetSpellProto()->EffectMechanic[y] == MECHANIC_ENSNARED)
					return true;
		}
	}

	return false;

}

void Unit::UpdateVisibility()
{
	ByteBuffer buf(3000);
	uint32 count;
	bool can_see;
	bool is_visible;
	Player *pl;
	Object * pObj;
	Player * plr;

	if( IsPlayer() )
	{
		plr = TO< Player* >( this );
		for( Object::InRangeSet::iterator itr2 = m_objectsInRange.begin(); itr2 != m_objectsInRange.end();)
		{
			pObj = (*itr2);
			++itr2;

			can_see = plr->CanSee(pObj);
			is_visible = plr->IsVisible( pObj->GetGUID() );
			if(can_see)
			{
				if(!is_visible)
				{
					buf.clear();
					count = pObj->BuildCreateUpdateBlockForPlayer( &buf, plr );
					plr->PushCreationData(&buf, count);
					plr->AddVisibleObject(pObj->GetGUID());
					if(pObj->IsUnit())
						plr->SendAurasForTarget(TO_UNIT(pObj));
				}
			}
			else
			{
				if(is_visible)
				{
					plr->SendDestroyObject( pObj->GetGUID() );
					plr->RemoveVisibleObject( pObj->GetGUID() );
				}
			}

			if( pObj->IsPlayer() )
			{
				pl = TO< Player* >( pObj );
				can_see = pl->CanSee( plr );
				is_visible = pl->IsVisible( plr->GetGUID() );
				if( can_see )
				{
					if(!is_visible)
					{
						buf.clear();
						count = plr->BuildCreateUpdateBlockForPlayer( &buf, pl );
						pl->PushCreationData(&buf, count);
						pl->AddVisibleObject(plr->GetGUID());
						pl->SendAurasForTarget(plr);
					}
				}
				else
				{
					if(is_visible)
					{
						pl->SendDestroyObject( plr->GetGUID() );
						pl->RemoveVisibleObject( plr->GetGUID() );
					}
				}
			}
		}
	}
	else			// For units we can save a lot of work
	{
		for(set< Object* >::iterator it2 = GetInRangePlayerSetBegin(); it2 != GetInRangePlayerSetEnd(); ++it2)
		{

            Player *p = TO< Player* >( *it2 );

			can_see = p->CanSee(this);
			is_visible = p->IsVisible( this->GetGUID() );
			if(!can_see)
			{
				if(is_visible)
				{
					p->SendDestroyObject( GetGUID() );
					p->RemoveVisibleObject( GetGUID() );
				}
			}
			else
			{
				if(!is_visible)
				{
					buf.clear();
					count = BuildCreateUpdateBlockForPlayer(&buf, p);
					p->PushCreationData(&buf, count);
					p->AddVisibleObject( this->GetGUID() );
					p->SendAurasForTarget(this);
				}
			}
		}
	}
}
void Unit::EventHealthChangeSinceLastUpdate()
{
	int pct = GetHealthPct();
	if(pct < 35)
	{
		uint32 toset = AURASTATE_FLAG_HEALTH35;
		if(pct < 20)
			toset |= AURASTATE_FLAG_HEALTH20;
		else
			RemoveFlag(UNIT_FIELD_AURASTATE, AURASTATE_FLAG_HEALTH20);
		SetFlag(UNIT_FIELD_AURASTATE, toset);
	}
	else
		RemoveFlag(UNIT_FIELD_AURASTATE, AURASTATE_FLAG_HEALTH35 | AURASTATE_FLAG_HEALTH20);

	if(pct < 75)
		RemoveFlag(UNIT_FIELD_AURASTATE, AURASTATE_FLAG_HEALTH75);
	else
		SetFlag(UNIT_FIELD_AURASTATE, AURASTATE_FLAG_HEALTH75);
}

int32 Unit::GetAP()
{
	int32 baseap = GetAttackPower() + GetAttackPowerMods();
	int32 totalap = float2int32(baseap * (GetFloatValue(UNIT_FIELD_ATTACK_POWER_MULTIPLIER) + 1));
	if(totalap >= 0)
		return float2int32(totalap);
	return	0;
}

int32 Unit::GetRAP()
{
	int32 baseap = GetRangedAttackPower() + GetRangedAttackPowerMods();
	float totalap = baseap * (GetRangedAttackPowerMultiplier() + 1);
	if(totalap >= 0)
		return float2int32(totalap);
	return	0;
}

void Unit::EventCastSpell(Unit* Target, SpellEntry* Sp)
{
	ARCEMU_ASSERT(Sp != NULL);
	Spell* pSpell = sSpellFactoryMgr.NewSpell(Target, Sp, true, NULL);
	SpellCastTargets targets(Target->GetGUID());
	pSpell->prepare(&targets);
}

void Unit::SetFacing(float newo)
{
	SetOrientation(newo);

	//generate smsg_monster_move
	WorldPacket data(SMSG_MONSTER_MOVE, 100);

	data << GetNewGUID();
	data << uint8(0); //vehicle seat index
	data << GetPositionX() << GetPositionY() << GetPositionZ();
	data << getMSTime();
	data << uint8(4); //set orientation
	data << newo;
	data << uint32(0x1000); //move flags: run
	data << uint32(0); //movetime
	data << uint32(1); //1 point
	data << GetPositionX() << GetPositionY() << GetPositionZ();

	SendMessageToSet(&data, true);
}

float Unit::get_chance_to_daze(Unit* target)
{
	if(target->getLevel() < CREATURE_DAZE_MIN_LEVEL)   // since 3.3.0
		return 0.0f;
	float attack_skill = getLevel() * 5.0f;
	float defense_skill;
	if(target->IsPlayer())
		defense_skill = float(TO< Player* >(target)->_GetSkillLineCurrent(SKILL_DEFENSE, false));
	else defense_skill = target->getLevel() * 5.0f;
	if(!defense_skill)
		defense_skill = 1;
	float chance_to_daze = attack_skill * 20 / defense_skill;//if level is equal then we get a 20% chance to daze
	chance_to_daze = chance_to_daze * std::min(target->getLevel() / 30.0f, 1.0f); //for targets below level 30 the chance decreases
	if(chance_to_daze > 40)
		return 40.0f;
	else
		return chance_to_daze;
}

void CombatStatusHandler::ClearMyHealers()
{
	// this is where we check all our healers
	HealedSet::iterator i;
	Player* pt;
	for(i = m_healers.begin(); i != m_healers.end(); ++i)
	{
		pt = m_Unit->GetMapMgr()->GetPlayer(*i);
		if(pt != NULL)
			pt->CombatStatus.RemoveHealed(m_Unit);
	}

	m_healers.clear();
}

void CombatStatusHandler::WeHealed(Unit* pHealTarget)
{
	if(!pHealTarget->IsPlayer() || !m_Unit->IsPlayer() || pHealTarget == m_Unit)
		return;

	if(pHealTarget->CombatStatus.IsInCombat())
	{
		m_healed.insert(pHealTarget->GetLowGUID());
		pHealTarget->CombatStatus.m_healers.insert(m_Unit->GetLowGUID());
	}

	UpdateFlag();
}

void CombatStatusHandler::RemoveHealed(Unit* pHealTarget)
{
	m_healed.erase(pHealTarget->GetLowGUID());
	UpdateFlag();
}

void CombatStatusHandler::UpdateFlag()
{
	bool n_status = InternalIsInCombat();
	if(n_status != m_lastStatus)
	{
		m_lastStatus = n_status;
		if(n_status)
		{
			//printf(I64FMT" is now in combat.\n", m_Unit->GetGUID());
			m_Unit->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_COMBAT);
			if(m_Unit->IsPlayer())
			{
				std::list<Pet*> summons = TO_PLAYER(m_Unit)->GetSummons();
				for(std::list<Pet*>::iterator itr = summons.begin(); itr != summons.end(); ++itr)
				{
					if((*itr)->GetPetOwner() == m_Unit)
						(*itr)->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PET_IN_COMBAT);
				}
			}
			if(!m_Unit->hasStateFlag(UF_ATTACKING)) 
				m_Unit->addStateFlag(UF_ATTACKING);
		}
		else
		{
			//printf(I64FMT" is no longer in combat.\n", m_Unit->GetGUID());
			m_Unit->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_COMBAT);
			if(m_Unit->IsPlayer())
			{
				std::list<Pet*> summons = TO_PLAYER(m_Unit)->GetSummons();
				for(std::list<Pet*>::iterator itr = summons.begin(); itr != summons.end(); ++itr)
				{
					if((*itr)->GetPetOwner() == m_Unit)
						(*itr)->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PET_IN_COMBAT);
				}
			}
			if(m_Unit->hasStateFlag(UF_ATTACKING)) 
				m_Unit->clearStateFlag(UF_ATTACKING);

			// remove any of our healers from combat too, if they are able to be.
			ClearAttackers();
			ClearHealers();
			if(m_Unit->IsPlayer())
				TO_PLAYER(m_Unit)->UpdatePotionCooldown();
		}
	}
}

bool CombatStatusHandler::InternalIsInCombat()
{
	if(m_Unit->IsPlayer() && m_Unit->GetMapMgr() && m_Unit->GetMapMgr()->IsCombatInProgress())
		return true;

	HealedSet::iterator itr = m_healed.begin();
	Player* pt;
	for(; itr != m_healed.end(); ++itr)
	{
		pt = m_Unit->GetMapMgr()->GetPlayer(*itr);
		if(pt)
		{
			if(pt->isAlive() && pt->CombatStatus.IsInCombat())
				return true;
		}
	}

	for(AttackerMap::iterator itr = m_attackTargets.begin(); itr != m_attackTargets.end(); ++itr)
	{
		Unit* pt;
		pt = m_Unit->GetMapMgr()->GetUnit(*itr);
		if(pt)
		{
			if(pt->isAlive() && pt->CombatStatus.IsInCombat())
				return true;
		}
	}
	
	for(AttackerMap::iterator itr = m_attackers.begin(); itr != m_attackers.end(); ++itr)
	{
		Unit* pt;
		pt = m_Unit->GetMapMgr()->GetUnit(*itr);
		if(pt)
		{
			if(pt->isAlive() && pt->CombatStatus.IsInCombat())
				return true;
		}
	}

	return false;
}

void CombatStatusHandler::AddAttackTarget(const uint64 & guid)
{
	if(guid == m_Unit->GetGUID())
		return;

	//we MUST be in world
	ARCEMU_ASSERT(m_Unit->IsInWorld());

	m_attackTargets.insert(guid);
	//printf("Adding attack target "I64FMT" to "I64FMT"\n", guid, m_Unit->GetGUID());
	if(m_Unit->IsPlayer() &&
	        m_primaryAttackTarget != guid)			// players can only have one attack target.
	{
		if(m_primaryAttackTarget)
			ClearPrimaryAttackTarget();

		m_primaryAttackTarget = guid;
	}

	UpdateFlag();
}

void CombatStatusHandler::ClearPrimaryAttackTarget()
{
	//printf("ClearPrimaryAttackTarget for "I64FMT"\n", m_Unit->GetGUID());
	if(m_primaryAttackTarget != 0)
	{
		Unit* pt = m_Unit->GetMapMgr()->GetUnit(m_primaryAttackTarget);
		if(pt != NULL)
		{
			// remove from their attacker set. (if we have no longer got any DoT's, etc)
			if(!IsAttacking(pt))
			{
				pt->CombatStatus.RemoveAttacker(m_Unit, m_Unit->GetGUID());
				m_attackTargets.erase(m_primaryAttackTarget);
			}

			m_primaryAttackTarget = 0;
		}
		else
		{
			m_attackTargets.erase(m_primaryAttackTarget);
			m_primaryAttackTarget = 0;
		}
	}

	UpdateFlag();
}

bool CombatStatusHandler::IsAttacking(Unit* pTarget)
{
	// check the target for any of our DoT's.
	for(uint32 i = MAX_NEGATIVE_AURAS_EXTEDED_START; i < MAX_NEGATIVE_AURAS_EXTEDED_END; ++i)
		if(pTarget->m_auras[i] != NULL)
			if(m_Unit->GetGUID() == pTarget->m_auras[i]->m_casterGuid && pTarget->m_auras[i]->IsCombatStateAffecting())
				return true;

	// place any additional checks here
	return false;
}

void CombatStatusHandler::RemoveAttackTarget(Unit* pTarget)
{
	// called on aura remove, etc.
	AttackerMap::iterator itr = m_attackTargets.find(pTarget->GetGUID());
	if(itr == m_attackTargets.end())
		return;

	if(!IsAttacking(pTarget))
	{
		//printf("Removing attack target "I64FMT" on "I64FMT"\n", pTarget->GetGUID(), m_Unit->GetGUID());
		m_attackTargets.erase(itr);
		if(m_primaryAttackTarget == pTarget->GetGUID())
			m_primaryAttackTarget = 0;

		UpdateFlag();
	}
	/*else
		printf("Cannot remove attack target "I64FMT" from "I64FMT"\n", pTarget->GetGUID(), m_Unit->GetGUID());*/
}

void CombatStatusHandler::RemoveAttacker(Unit* pAttacker, const uint64 & guid)
{
	AttackerMap::iterator itr = m_attackers.find(guid);
	if(itr == m_attackers.end())
		return;

	if((!pAttacker) || (!pAttacker->CombatStatus.IsAttacking(m_Unit)))
	{
		//printf("Removing attacker "I64FMT" from "I64FMT"\n", guid, m_Unit->GetGUID());
		m_attackers.erase(itr);
		UpdateFlag();
	}
	/*else
	{
		printf("Cannot remove attacker "I64FMT" from "I64FMT"\n", guid, m_Unit->GetGUID());
	}*/
}

void CombatStatusHandler::OnDamageDealt(Unit* pTarget)
{
	// we added an aura, or dealt some damage to a target. they need to have us as an attacker, and they need to be our attack target if not.
	//printf("OnDamageDealt to "I64FMT" from "I64FMT"\n", pTarget->GetGUID(), m_Unit->GetGUID());
	if(pTarget == m_Unit)
		return;

	//no need to be in combat if dead
	if(!pTarget->isAlive() || !m_Unit->isAlive())
		return;

	AttackerMap::iterator itr = m_attackTargets.find(pTarget->GetGUID());
	if(itr == m_attackTargets.end())
		AddAttackTarget(pTarget->GetGUID());

	itr = pTarget->CombatStatus.m_attackers.find(m_Unit->GetGUID());
	if(itr == pTarget->CombatStatus.m_attackers.end())
		pTarget->CombatStatus.AddAttacker(m_Unit->GetGUID());

	// update the timeout
	m_Unit->CombatStatusHandler_ResetPvPTimeout();
	m_Unit->summonhandler.OnOwnerAttack(pTarget);
}

void CombatStatusHandler::AddAttacker(const uint64 & guid)
{
	//we MUST be in world
	ARCEMU_ASSERT(m_Unit->IsInWorld());
	m_attackers.insert(guid);
	UpdateFlag();
}

void CombatStatusHandler::ClearAttackers()
{
	//If we are not in world, CombatStatusHandler::OnRemoveFromWorld() would have been already called so m_attackTargets
	//and m_attackers should be empty. If it's not, something wrong happened.

	// this is a FORCED function, only use when the reference will be destroyed.
	if (m_attackTargets.empty())
	{
		m_attackers.clear();
		m_attackTargets.clear();
		m_primaryAttackTarget = 0;
		UpdateFlag();
		return;
	}
	try
	{
	AttackerMap::iterator itr = m_attackTargets.begin();
	Unit* pt;
	for(; itr != m_attackTargets.end(); ++itr)
	{
		pt = m_Unit->GetMapMgr()->GetUnit(*itr);
		if(pt)
		{
			pt->CombatStatus.m_attackers.erase(m_Unit->GetGUID());
			pt->CombatStatus.UpdateFlag();
		}
	}

	for(itr = m_attackers.begin(); itr != m_attackers.end(); ++itr)
	{
		pt = m_Unit->GetMapMgr()->GetUnit(*itr);
		if(pt)
		{
			pt->CombatStatus.m_attackTargets.erase(m_Unit->GetGUID());
			pt->CombatStatus.UpdateFlag();
		}
	}
	}
	catch(...)
	{
		printf("Caught fatal exception in Unit.cpp <\n");
	}
	m_attackers.clear();
	m_attackTargets.clear();
	m_primaryAttackTarget = 0;
	UpdateFlag();
}

void CombatStatusHandler::ClearHealers()
{
	//If we are not in world, CombatStatusHandler::OnRemoveFromWorld() would have been already called so m_healed should
	//be empty. If it's not, something wrong happened.

	HealedSet::iterator itr = m_healed.begin();
	Player* pt;
	for(; itr != m_healed.end(); ++itr)
	{
		pt = m_Unit->GetMapMgr()->GetPlayer(*itr);
		if(pt)
		{
			pt->CombatStatus.m_healers.erase(m_Unit->GetLowGUID());
			pt->CombatStatus.UpdateFlag();
		}
	}

	for(itr = m_healers.begin(); itr != m_healers.end(); ++itr)
	{
		pt = m_Unit->GetMapMgr()->GetPlayer(*itr);
		if(pt)
		{
			pt->CombatStatus.m_healed.erase(m_Unit->GetLowGUID());
			pt->CombatStatus.UpdateFlag();
		}
	}

	m_healed.clear();
	m_healers.clear();
	UpdateFlag();
}

void CombatStatusHandler::OnRemoveFromWorld()
{
	ClearAttackers();
	ClearHealers();
}

bool CombatStatusHandler::IsInCombat() const
{
	// If the unit doesn't exist - OR - the unit exists but is not in world
	if(m_Unit == NULL || !m_Unit->IsInWorld())
		return false;

	switch(m_Unit->GetTypeId())
	{
		case TYPEID_UNIT:
			{
				if(m_Unit->IsPet() && TO< Pet* >(m_Unit)->GetPetAction() == PET_ACTION_ATTACK)
					return true;
				else if(m_Unit->IsPet())
					return m_lastStatus;
				else
					return m_Unit->GetAIInterface()->getAITargetsCount() == 0 ? false : true;
			}
			break;
		case TYPEID_PLAYER:
			{
				std::list<Pet*> summons = TO_PLAYER(m_Unit)->GetSummons();
				for(std::list<Pet*>::iterator itr = summons.begin(); itr != summons.end(); ++itr)
				{
					if((*itr)->GetPetOwner() == m_Unit && (*itr)->CombatStatus.IsInCombat())
						return true;
				}

				return m_lastStatus;
			}
			break;
		default:
			return false;
	}
}

void Unit::CombatStatusHandler_ResetPvPTimeout()
{
	if(!IsPlayer())
		return;

	m_lock.Acquire();
	EventMap::iterator itr = m_events.find(EVENT_ATTACK_TIMEOUT);
	if(itr != m_events.end())
	{
		for(; itr != m_events.upper_bound(EVENT_ATTACK_TIMEOUT); ++itr)
		{
			if(!itr->second->deleted)
			{
				itr->second->currTime = 5000;
				m_lock.Release();
				return;
			}
		}
	}

	sEventMgr.AddEvent(this, &Unit::CombatStatusHandler_UpdatePvPTimeout, EVENT_ATTACK_TIMEOUT, 5000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	m_lock.Release();
}

void Unit::CombatStatusHandler_UpdatePvPTimeout()
{
	CombatStatus.TryToClearAttackTargets();
}

void Unit::Heal(Unit* target, uint32 SpellId, uint32 amount)
{
	if(!target || !SpellId || !amount)
		return;

	uint32 ch = target->GetHealth();
	uint32 mh = target->GetMaxHealth();
	if(mh != ch)
	{
		ch += amount;
		uint32 overheal = 0;

		if(ch > mh)
		{
			target->SetHealth(mh);
			overheal = amount - mh;
			amount += (mh - ch);
		}
		else
			target->SetHealth(ch);

		Spell::SendHealSpellOnPlayer(this, target, amount, false, overheal, SpellId);

		target->RemoveAurasByHeal();
	}
}

void Unit::Energize(Unit* target, uint32 SpellId, uint32 amount, uint32 type)
{
	//Static energize
	if(!target || !SpellId || !amount)
		return;

	uint32 cur = target->GetPower(POWER_TYPE_MANA + type);
	uint32 max = target->GetMaxPower(POWER_TYPE_MANA + type);

	if(cur + amount > max)
		amount = max - cur;

	target->SetPower(POWER_TYPE_MANA + type, cur + amount);

	Spell::SendHealManaSpellOnPlayer(this, target, amount, type, SpellId);
}

void CombatStatusHandler::TryToClearAttackTargets()
{
	AttackerMap::iterator i, i2;
	Unit* pt;

	if(m_Unit->IsPlayer())
		TO< Player* >(m_Unit)->RemoveFlag(PLAYER_FLAGS, PLAYER_FLAG_CONTESTED_PVP);


	for(i = m_attackTargets.begin(); i != m_attackTargets.end();)
	{
		i2 = i++;
		pt = m_Unit->GetMapMgr()->GetUnit(*i2);
		if(pt == NULL)
		{
			m_attackTargets.erase(i2);
			continue;
		}

		RemoveAttackTarget(pt);
		pt->CombatStatus.RemoveAttacker(m_Unit, m_Unit->GetGUID());
	}
}

void CombatStatusHandler::AttackersForgetHate()
{
	AttackerMap::iterator i, i2;
	Unit* pt;

	for(i = m_attackTargets.begin(); i != m_attackTargets.end();)
	{
		i2 = i++;
		pt = m_Unit->GetMapMgr()->GetUnit(*i2);
		if(pt == NULL)
		{
			m_attackTargets.erase(i2);
			continue;
		}

		if(pt->GetAIInterface())
			pt->GetAIInterface()->RemoveThreatByPtr(m_Unit);
	}
}

void Unit::CancelSpell(Spell* ptr)
{
	/*
		if(ptr)
			ptr->cancel();
		else */
	if(m_currentSpell)
	{
		// this logically might seem a little bit twisted
		// crash situation : an already deleted spell will be called to get canceled by eventmanager
		// solution : We should not delay spell canceling more then second spell canceling.
		// problem : might remove spells that should not be removed. Not sure about it :(
		sEventMgr.RemoveEvents(this, EVENT_UNIT_DELAYED_SPELL_CANCEL);
		m_currentSpell->cancel();
	}
}

void Unit::EventStrikeWithAbility(uint64 guid, SpellEntry* sp, uint32 damage)
{
	Unit* victim = m_mapMgr ? m_mapMgr->GetUnit(guid) : NULL;
	if(victim)
		Strike(victim, RANGED, sp, 0, 0, 0, false, true);
}

void Unit::DispelAll(bool positive)
{
	for(uint32 i = MAX_TOTAL_AURAS_START; i < MAX_TOTAL_AURAS_END; ++i)
	{
		if(m_auras[i] != NULL)
			if((m_auras[i]->IsPositive() && positive) || !m_auras[i]->IsPositive())
				m_auras[i]->Remove();
	}
}

/* bool Unit::RemoveAllAurasByMechanic (renamed from MechanicImmunityMassDispel)
- Removes all auras on this unit that are of a specific mechanic.
- Useful for things like.. Apply Aura: Immune Mechanic, where existing (de)buffs are *always supposed* to be removed.
- I'm not sure if this goes here under unit.
* Arguments:
	- uint32 MechanicType
		*

* Returns;
	- False if no buffs were dispelled, true if more than 0 were dispelled.
*/
bool Unit::RemoveAllAurasByMechanic(uint32 MechanicType , uint32 MaxDispel = -1 , bool HostileOnly = true)
{
	//sLog.outString( "Unit::MechanicImmunityMassDispel called, mechanic: %u" , MechanicType );
	uint32 DispelCount = 0;
	for(uint32 x = (HostileOnly ? MAX_NEGATIVE_AURAS_EXTEDED_START : MAX_POSITIVE_AURAS_EXTEDED_START) ; x < MAX_REMOVABLE_AURAS_END ; x++)    // If HostileOnly = 1, then we use aura slots 40-56 (hostile). Otherwise, we use 0-56 (all)
	{
		if(DispelCount >= MaxDispel && MaxDispel > 0)
			return true;

		if(m_auras[x])
		{
			if(m_auras[x]->GetSpellProto()->Mechanic == MechanicType)   // Remove all mechanics of type MechanicType (my english goen boom)
			{
				//sLog.outString( "Removed aura. [AuraSlot %u, SpellId %u]" , x , m_auras[x]->GetSpellId() );
				// TODO: Stop moving if fear was removed.
				m_auras[x]->Remove(); // EZ-Remove
				DispelCount ++;
			}
			else if(MechanicType == MECHANIC_ENSNARED)   // if got immunity for slow, remove some that are not in the mechanics
			{
				for(int i = 0 ; i < 3 ; i++)
				{
					// SNARE + ROOT
					if(m_auras[x]->GetSpellProto()->EffectApplyAuraName[i] == SPELL_AURA_MOD_DECREASE_SPEED || m_auras[x]->GetSpellProto()->EffectApplyAuraName[i] == SPELL_AURA_MOD_ROOT)
					{
						m_auras[x]->Remove();
						break;
					}
				}
			}
		}
	}
	return (DispelCount == 0);
}

void Unit::RemoveAllMovementImpairing()
{
	for(uint32 x = MAX_NEGATIVE_AURAS_EXTEDED_START; x < MAX_REMOVABLE_AURAS_END; x++)
	{
		if(m_auras[x] != NULL)
		{
			if(m_auras[x]->GetSpellProto()->Mechanic == MECHANIC_ROOTED
			        || m_auras[x]->GetSpellProto()->Mechanic == MECHANIC_ENSNARED
			        || m_auras[x]->GetSpellProto()->Mechanic == MECHANIC_DAZED)

			{
				m_auras[x]->Remove();
			}
			else
			{
				for(int i = 0; i < 3; i++)
				{
					if(m_auras[x]->GetSpellProto()->EffectApplyAuraName[i] == SPELL_AURA_MOD_DECREASE_SPEED
					        || m_auras[x]->GetSpellProto()->EffectApplyAuraName[i] == SPELL_AURA_MOD_ROOT)
					{
						m_auras[x]->Remove();
						break;
					}
				}
			}
		}
	}
}

void Unit::setAttackTimer(int32 time, bool offhand)
{
	if(!time)
		time = offhand ? m_uint32Values[UNIT_FIELD_BASEATTACKTIME + 1] : m_uint32Values[UNIT_FIELD_BASEATTACKTIME];

	time = std::max(1000, float2int32(time * GetCastSpeedMod()));
	if(time > 300000)		// just in case.. shouldn't happen though
		time = offhand ? m_uint32Values[UNIT_FIELD_BASEATTACKTIME + 1] : m_uint32Values[UNIT_FIELD_BASEATTACKTIME];

	if(offhand)
		m_attackTimer_1 = getMSTime() + time;
	else
		m_attackTimer = getMSTime() + time;
}

bool Unit::isAttackReady(bool offhand)
{
	if(offhand)
		return (getMSTime() >= m_attackTimer_1) ? true : false;
	else
		return (getMSTime() >= m_attackTimer) ? true : false;
}

void Unit::ReplaceAIInterface(AIInterface* new_interface)
{
	delete m_aiInterface;	//be careful when you do this. Might screw unit states !
	m_aiInterface = new_interface;
}

void Unit::EventUpdateFlag()
{
	CombatStatus.UpdateFlag();
}

void Unit::EventModelChange()
{
	DisplayBounding* entry = DisplayBoundingStorage.LookupEntry(GetUInt32Value(UNIT_FIELD_DISPLAYID));

	//TODO: if has mount, grab mount model and add the z value of attachment 0
	if(entry)
		m_modelhalfsize = entry->high[2] / 2;
	else
		m_modelhalfsize = 1.0f;
}

void Unit::RemoveFieldSummon()
{
	uint64 guid = GetSummonedUnitGUID();
	if(guid && GetMapMgr())
	{
		Creature* summon = TO< Creature* >(GetMapMgr()->GetUnit(guid));
		if(summon)
		{
			summon->RemoveFromWorld(false, true);
		}
		SetSummonedUnitGUID(0);
	}
}

void Unit::AggroPvPGuards()
{
	Unit* tmpUnit;
	for(Object::InRangeSet::iterator i = GetInRangeSetBegin(); i != GetInRangeSetEnd(); ++i)
	{
		if((*i)->IsCreature())
		{
			tmpUnit = TO< Unit* >(*i);
			if(tmpUnit->GetAIInterface() && tmpUnit->GetAIInterface()->m_isNeutralGuard && CalcDistance(tmpUnit) <= (50.0f * 50.0f))
			{
				tmpUnit->GetAIInterface()->AttackReaction(this, 1, 0);
			}
		}
	}
}

//what is an Immobilize spell ? Have to add it later to spell effect handler
void Unit::EventStunOrImmobilize(Unit* proc_target, bool is_victim)
{
	if(this == proc_target)
		return; //how and why would we stun ourselves

	int32 t_trigger_on_stun, t_trigger_on_stun_chance;
	if(is_victim == false)
	{
		t_trigger_on_stun = trigger_on_stun;
		t_trigger_on_stun_chance = trigger_on_stun_chance;
	}
	else
	{
		t_trigger_on_stun = trigger_on_stun_victim;
		t_trigger_on_stun_chance = trigger_on_stun_chance_victim;
	}

	if(t_trigger_on_stun)
	{
		if(t_trigger_on_stun_chance < 100 && !Rand(t_trigger_on_stun_chance))
			return;

		SpellEntry* spellInfo = dbcSpell.LookupEntryForced(t_trigger_on_stun);

		if(!spellInfo)
			return;

		Spell* spell = sSpellFactoryMgr.NewSpell(this, spellInfo , true, NULL);
		SpellCastTargets targets;

		if(spellInfo->procFlags & PROC_TARGET_SELF)
			targets.m_unitTarget = GetGUID();
		else if(proc_target)
			targets.m_unitTarget = proc_target->GetGUID();
		else
			targets.m_unitTarget = GetGUID();
		spell->prepare(&targets);
	}
}

// Proc on chill effects (such as frostbolt slow effect)
void Unit::EventChill(Unit* proc_target, bool is_victim)
{
	if(this == proc_target)
		return; //how and why would we chill ourselves

	int32 t_trigger_on_chill, t_trigger_on_chill_chance;
	if(is_victim == false)
	{
		t_trigger_on_chill = trigger_on_chill;
		t_trigger_on_chill_chance = trigger_on_chill_chance;
	}
	else
	{
		t_trigger_on_chill = trigger_on_chill_victim;
		t_trigger_on_chill_chance = trigger_on_chill_chance_victim;
	}

	if(t_trigger_on_chill)
	{
		if(t_trigger_on_chill_chance < 100 && !Rand(t_trigger_on_chill_chance))
			return;

		SpellEntry* spellInfo = dbcSpell.LookupEntryForced(t_trigger_on_chill);

		if(!spellInfo)
			return;

		Spell* spell = sSpellFactoryMgr.NewSpell(this, spellInfo , true, NULL);
		SpellCastTargets targets;

		if(spellInfo->procFlags & PROC_TARGET_SELF)
			targets.m_unitTarget = GetGUID();
		else if(proc_target)
			targets.m_unitTarget = proc_target->GetGUID();
		else
			targets.m_unitTarget = GetGUID();
		spell->prepare(&targets);
	}
}

void Unit::RemoveExtraStrikeTarget(SpellEntry* spell_info)
{
	ExtraStrike* es;
	for(std::list<ExtraStrike*>::iterator i = m_extraStrikeTargets.begin(); i != m_extraStrikeTargets.end(); ++i)
	{
		es = *i;
		if(spell_info == es->spell_info)
		{
			m_extrastriketargetc--;
			m_extraStrikeTargets.erase(i);
			delete es;
			break;
		}
	}
}

void Unit::AddExtraStrikeTarget(SpellEntry* spell_info, uint32 charges)
{
	for(std::list<ExtraStrike*>::iterator i = m_extraStrikeTargets.begin(); i != m_extraStrikeTargets.end(); ++i)
	{
		//a pointer check or id check ...should be the same
		if(spell_info == (*i)->spell_info)
		{
			(*i)->charges = charges;
			return;
		}
	}

	ExtraStrike* es = new ExtraStrike;

	es->spell_info = spell_info;
	es->charges = charges;
	m_extraStrikeTargets.push_back(es);
	m_extrastriketargetc++;
}

uint32 Unit::DoDamageSplitTarget(uint32 res, uint32 school_type, bool melee_dmg)
{
	Unit* splittarget;
	uint32 splitdamage, tmpsplit;
	DamageSplitTarget* ds = m_damageSplitTarget;

	splittarget = (GetMapMgr() != NULL) ? GetMapMgr()->GetUnit(ds->m_target) : NULL;
	if(splittarget != NULL && res > 0)
	{
		// calculate damage
		tmpsplit = ds->m_flatDamageSplit;
		if(tmpsplit > res)
			tmpsplit = res; // prevent < 0 damage
		splitdamage = tmpsplit;
		res -= tmpsplit;
		tmpsplit = float2int32(ds->m_pctDamageSplit * res);
		if(tmpsplit > res)
			tmpsplit = res;
		splitdamage += tmpsplit;
		res -= tmpsplit;

		if(splitdamage)
		{
			splittarget->DealDamage(splittarget, splitdamage, 0, 0, 0);

			// Send damage log
			if(melee_dmg)
			{
				dealdamage sdmg;

				sdmg.full_damage = splitdamage;
				sdmg.resisted_damage = 0;
				sdmg.school_type = school_type;
				SendAttackerStateUpdate(this, splittarget, &sdmg, splitdamage, 0, 0, 0, ATTACK);
			}
			else
			{
				SendSpellNonMeleeDamageLog(this, splittarget, ds->m_spellId, splitdamage, static_cast<uint8>(school_type), 0, 0, true, 0, 0, true);
			}
		}
	}

	return res;
}

void Unit::RemoveReflect(uint32 spellid, bool apply)
{
	/**
	* Removes and deletes reflects from unit by spell id, does not remove aura which created it
	* In specific cases reflects can be created by a dummy spelleffect (eg. spell 28332 or 13043), then we need to remove it in ~unit
	*/
	for(std::list<struct ReflectSpellSchool*>::iterator i = m_reflectSpellSchool.begin(); i != m_reflectSpellSchool.end();)
		if(spellid == (*i)->spellId)
		{
			delete *i;
			i = m_reflectSpellSchool.erase(i);
			//break; better check all list elements
		}
		else
			++i;

	if(apply && spellid == 23920 && IsPlayer() && HasAurasWithNameHash(SPELL_HASH_IMPROVED_SPELL_REFLECTION))
	{
		Player* pPlayer = TO< Player* >(this);
		Group* pGroup = pPlayer->GetGroup();

		if(pGroup != NULL)
		{
			int32 targets = 0;
			if(pPlayer->HasAura(59088))
				targets = 2;
			else if(pPlayer->HasAura(59089))
				targets = 4;

			pGroup->Lock();
			for(uint32 i = 0; i < pGroup->GetSubGroupCount(); ++i)
			{
				SubGroup* subGroup = pGroup->GetSubGroup(i);
				for(GroupMembersSet::iterator itr = subGroup->GetGroupMembersBegin(); itr != subGroup->GetGroupMembersEnd() && targets > 0; ++itr)
				{
					Player* member = (*itr)->m_loggedInPlayer;
					if(member == NULL || member == pPlayer || !member->IsInWorld() || !member->isAlive() || member->HasAura(59725))
						continue;

					if(!IsInrange(pPlayer, member, 20))
						continue;
					pPlayer->CastSpell(member, 59725, true);
					targets -= 1;
				}
			}
			pGroup->Unlock();
		}
	}

	if(!apply && spellid == 59725 && IsPlayer())
	{
		Player* pPlayer = TO< Player* >(this);
		Group* pGroup = pPlayer->GetGroup();

		if(pGroup != NULL)
		{
			pGroup->Lock();
			for(uint32 i = 0; i < pGroup->GetSubGroupCount(); ++i)
			{
				for(GroupMembersSet::iterator itr = pGroup->GetSubGroup(i)->GetGroupMembersBegin(); itr != pGroup->GetSubGroup(i)->GetGroupMembersEnd(); ++itr)
				{
					Player* member = (*itr)->m_loggedInPlayer;
					if(member == NULL)
						continue;

					member->RemoveAura(59725);
				}
			}
			pGroup->Unlock();
		}
	}
}

void Unit::SetPower(uint32 type, int32 value)
{
	uint32 maxpower = GetUInt32Value(UNIT_FIELD_MAXPOWER1 + type);

	if(value < 0)
		value = 0;
	else if(value > (int32)maxpower)
		value = maxpower;

	SetUInt32Value(UNIT_FIELD_POWER1 + type, value);
}

void Unit::SendPowerUpdate(bool self)
{
	uint32 amount = GetUInt32Value(UNIT_FIELD_POWER1 + GetPowerType()); //save the amount, so we send the same to the player and everyone else

	WorldPacket data(SMSG_POWER_UPDATE, 14);
	FastGUIDPack(data, GetGUID());
	data << (uint8)GetPowerType();
	data << amount;
//	This was added in revision 1726.  Is it necessary?  To me, it seems to just be sending the packet twice.
//	If it is needed for something, put it back in I guess.
//	CopyAndSendDelayedPacket(&data);
	SendMessageToSet(&data, self);

	//VLack: On 3.1.3, create and send a field update packet to everyone else, as this is the only way to update their GUI with the power values.
	WorldPacket* pkt = BuildFieldUpdatePacket(UNIT_FIELD_POWER1 + GetPowerType(), amount);
	SendMessageToSet(pkt, false);
	delete pkt;
}

void Unit::UpdatePowerAmm()
{
	if(!IsPlayer())
		return;
	WorldPacket data(SMSG_POWER_UPDATE, 14);
	FastGUIDPack(data, GetGUID());
	data << uint8(GetPowerType());
	data << GetUInt32Value(UNIT_FIELD_POWER1 + GetPowerType());
	SendMessageToSet(&data, true);
}

void Unit::SetDualWield(bool enabled)
{
	m_dualWield = enabled;


	// Titan's grip
	if(!enabled && IsPlayer())
		RemoveAllAuraById(49152);
}

void Unit::AddGarbageAura(Aura* aur)
{
	m_GarbageAuras.push_back(aur);
}

void Unit::AddGarbageSpell(Spell* sp)
{
	m_GarbageSpells.push_back(sp);
}

void Unit::AddGarbagePet(Pet* pet)
{
	ARCEMU_ASSERT(pet->GetPetOwner()->GetGUID() == GetGUID() && !pet->IsInWorld());
	m_GarbagePets.push_back(pet);
}

void Unit::RemoveGarbage()
{
	try
	{
	std::list< Aura* >::iterator itr1;

	for(itr1 = m_GarbageAuras.begin(); itr1 != m_GarbageAuras.end(); ++itr1)
	{
		Aura* aur = *itr1;

		delete aur;
	}

	std::list< Spell* >::iterator itr2;

	for(itr2 = m_GarbageSpells.begin(); itr2 != m_GarbageSpells.end(); ++itr2)
	{
		Spell* sp = *itr2;

		delete sp;
	}

	std::list< Pet* >::iterator itr3;

	for(itr3 = m_GarbagePets.begin(); itr3 != m_GarbagePets.end(); ++itr3)
	{
		Pet* pet = *itr3;

		delete pet;
	}

	m_GarbageAuras.clear();
	m_GarbageSpells.clear();
	m_GarbagePets.clear();
	}
	catch (...)
	{
		printf("Fatal exception thrown when collecting Garbage <- Unit.cpp\n");
	}
}

void Unit::Tag(uint64 TaggerGUID)
{
	Tagged = true;
	this->TaggerGuid = TaggerGUID;
	m_uint32Values[ UNIT_DYNAMIC_FLAGS ] |= U_DYN_FLAG_TAGGED_BY_OTHER;

}

void Unit::UnTag()
{
	Tagged = false;
	TaggerGuid = 0;
	m_uint32Values[ UNIT_DYNAMIC_FLAGS ] &= ~U_DYN_FLAG_TAGGED_BY_OTHER;
}

bool Unit::IsTagged()
{
	return Tagged;
}

bool Unit::IsTaggable()
{
	if(!IsPet() && !Tagged)
		return true;
	else
		return false;
}

uint64 Unit::GetTaggerGUID()
{
	return TaggerGuid;
}

bool Unit::isLootable()
{
	if(IsTagged() && !IsPet() && !isCritter() && HasLoot() && !HasCreatureCustomFlag(CREATURE_CUSTOMFLAG_NO_LOOT) && ( GetCreatedByGUID() == 0 ))
		return true;
	else
		return false;
}

SpellProc* Unit::AddProcTriggerSpell(SpellEntry* spell, SpellEntry* orig_spell, uint64 caster, uint32 procChance, uint32 procFlags, uint32 procCharges, uint32* groupRelation, uint32* procClassMask, Object* obj)
{
	SpellProc* sp = NULL;
	if(spell != NULL)
		sp = GetProcTriggerSpell(spell->Id, caster);
	if(sp != NULL && ! sp->mDeleted)
		return sp;

	sp = sSpellProcMgr.NewSpellProc(this, spell, orig_spell, caster, procChance, procFlags, procCharges, groupRelation, procClassMask, obj);
	if(sp == NULL)
	{
		if(orig_spell != NULL)
			LOG_ERROR("Spell id %u tried to add a non-existent spell to Unit %p as SpellProc", orig_spell->Id, this);
		else
			LOG_ERROR("Something tried to add a non-existent spell to Unit %p as SpellProc", this);
		return NULL;
	}
	m_procSpells.push_back(sp);

	return sp;
}

SpellProc* Unit::AddProcTriggerSpell(uint32 spell_id, uint32 orig_spell_id, uint64 caster, uint32 procChance, uint32 procFlags, uint32 procCharges, uint32* groupRelation, uint32* procClassMask, Object* obj)
{
	return AddProcTriggerSpell(dbcSpell.LookupEntryForced(spell_id), dbcSpell.LookupEntryForced(orig_spell_id), caster, procChance, procFlags, procCharges, groupRelation, procClassMask, obj);
}

SpellProc* Unit::AddProcTriggerSpell(SpellEntry* sp, uint64 caster, uint32* groupRelation, uint32* procClassMask, Object* obj)
{
	return AddProcTriggerSpell(sp, sp, caster, sp->procChance, sp->procFlags, sp->procCharges, groupRelation, procClassMask, obj);
}

SpellProc* Unit::GetProcTriggerSpell(uint32 spellId, uint64 casterGuid)
{
	for(std::list<SpellProc*>::iterator itr = m_procSpells.begin(); itr != m_procSpells.end(); ++itr)
	{
		SpellProc* sp = *itr;
		if(sp->mSpell->Id == spellId && (casterGuid == 0 || sp->mCaster == casterGuid))
			return sp;
	}

	return NULL;
}

void Unit::RemoveProcTriggerSpell(uint32 spellId, uint64 casterGuid, uint64 misc)
{
	for(std::list<SpellProc*>::iterator itr = m_procSpells.begin(); itr != m_procSpells.end(); ++itr)
	{
		SpellProc* sp = *itr;
		if(sp->CanDelete(spellId, casterGuid, misc))
		{
			sp->mDeleted = true;
			return;
		}
	}
}

void Unit::TakeDamage(Unit* pAttacker, uint32 damage, uint32 spellid, bool no_remove_auras) {}
void Unit::Die(Unit* pAttacker, uint32 damage, uint32 spellid) {}

void Unit::SendPeriodicAuraLog(const WoWGuid & CasterGUID, const WoWGuid & TargetGUID, uint32 SpellID, uint32 School, uint32 Amount, uint32 abs_dmg, uint32 resisted_damage, uint32 Flags, bool is_critical)
{

	WorldPacket data(SMSG_PERIODICAURALOG, 47);

	data << TargetGUID;		   // target guid
	data << CasterGUID;		   // caster guid
	data << uint32(SpellID);						// spellid
	data << uint32(1);					    // unknown? need research?
	data << uint32(Flags | 0x1);			// aura school
	data << uint32(Amount);						   // amount of done to target / heal / damage
	data << uint32(0);				   // cebernic: unknown?? needs more research, but it should fix unknown damage type with suffered.
	data << uint32(School);
	data << uint32(abs_dmg);
	data << uint32(resisted_damage);
	data << uint8(is_critical);

	SendMessageToSet(&data, true);
}

void Unit::SendPeriodicHealAuraLog(const WoWGuid & CasterGUID, const WoWGuid & TargetGUID, uint32 SpellID, uint32 healed, uint32 over_healed, bool is_critical)
{

	WorldPacket data(SMSG_PERIODICAURALOG, 41);

	data << TargetGUID;
	data << CasterGUID;
	data << SpellID;
	data << uint32(1);
	data << uint32(FLAG_PERIODIC_HEAL);
	data << uint32(healed);
	data << uint32(over_healed);
	data << uint32(0);		// I don't know what it is. maybe something related to absorbed heal?
	data << uint8(is_critical);

	SendMessageToSet(&data, true);
}


void Unit::Phase(uint8 command, uint32 newphase)
{

	Object::Phase(command, newphase);

	for(std::set<Object*>::iterator itr = m_objectsInRange.begin(); itr != m_objectsInRange.end(); ++itr)
	{
		if((*itr)->IsUnit())
			TO< Unit* >(*itr)->UpdateVisibility();
	}

	UpdateVisibility();
}

uint64 Unit::GetCurrentUnitForSingleTargetAura(SpellEntry* spell)
{
	UniqueAuraTargetMap::iterator itr;

	itr = m_singleTargetAura.find(spell->NameHash);

	if(itr != m_singleTargetAura.end())
		return itr->second;
	else
		return 0;
}

uint64 Unit::GetCurrentUnitForSingleTargetAura(uint32* name_hashes, uint32* index)
{
	UniqueAuraTargetMap::iterator itr;

	for(uint8 i = 0 ; ; i++)
	{
		if(! name_hashes[i])
			return 0;

		itr = m_singleTargetAura.find(name_hashes[i]);

		if(itr != m_singleTargetAura.end())
		{
			*index = i;
			return itr->second;
		}
	}
}

void Unit::SetCurrentUnitForSingleTargetAura(SpellEntry* spell, uint64 guid)
{
	UniqueAuraTargetMap::iterator itr;

	itr = m_singleTargetAura.find(spell->NameHash);

	if(itr != m_singleTargetAura.end())
		itr->second = guid;
	else
		m_singleTargetAura.insert(make_pair(spell->NameHash, guid));
}

void Unit::RemoveCurrentUnitForSingleTargetAura(SpellEntry* spell)
{
	UniqueAuraTargetMap::iterator itr;

	itr = m_singleTargetAura.find(spell->NameHash);

	if(itr != m_singleTargetAura.end())
		m_singleTargetAura.erase(itr);
}

void Unit::RemoveCurrentUnitForSingleTargetAura(uint32 name_hash)
{
	UniqueAuraTargetMap::iterator itr;

	itr = m_singleTargetAura.find(name_hash);

	if(itr != m_singleTargetAura.end())
		m_singleTargetAura.erase(itr);
}

bool Unit::InParty(Unit* u)
{
	if(u == NULL)
		return false;
	Player* p = TO< Player* >(GetPlayerOwner());
	Player* uFrom = TO< Player* >(u->GetPlayerOwner());

	if(p == NULL || uFrom == NULL)
		return false;

	if(p == uFrom)
		return true;

	if(p->GetGroup() != NULL && uFrom->GetGroup() != NULL && p->GetGroup() == uFrom->GetGroup() && p->GetSubGroup() == uFrom->GetSubGroup())
		return true;

	return false;
}

bool Unit::InRaid(Unit* u)
{
	if(u == NULL)
		return false;
	Player* p = TO< Player* >(GetPlayerOwner());
	Player* uFrom = TO< Player* >(u->GetPlayerOwner());

	if(p == NULL || uFrom == NULL)
		return false;

	if(p == uFrom)
		return true;

	if(p->GetGroup() != NULL && uFrom->GetGroup() != NULL && p->GetGroup() == uFrom->GetGroup())
		return true;

	return false;
}

bool Unit::IsCriticalDamageForSpell(Object* victim, SpellEntry* spell)
{
	bool result = false;
	float CritChance = 0.0f;
	uint32 resilience_type = 0;

	if(spell->is_ranged_spell)
	{
		if(IsPlayer())
		{
			CritChance = GetFloatValue(PLAYER_RANGED_CRIT_PERCENTAGE);
			if(victim->IsPlayer())
				CritChance += TO_PLAYER(victim)->res_R_crit_get();

			if(victim->IsUnit())
				CritChance += (float)(TO_UNIT(victim)->AttackerCritChanceMod[spell->NormalizedSchoolMask()]);
		}
		else
			CritChance = 5.0f; // static value for mobs.. not blizzlike, but an unfinished formula is not fatal :)

		if(victim->IsPlayer())
			resilience_type = PLAYER_RATING_MODIFIER_RANGED_CRIT_RESILIENCE;
	}
	else if(spell->is_melee_spell)
	{
		// Same shit with the melee spells, such as Judgement/Seal of Command
		if(IsPlayer())
			CritChance = GetFloatValue(PLAYER_CRIT_PERCENTAGE);

		if(victim->IsPlayer())
		{
			CritChance += TO_PLAYER(victim)->res_R_crit_get(); //this could be ability but in that case we overwrite the value
			resilience_type = PLAYER_RATING_MODIFIER_MELEE_CRIT_RESILIENCE;
		}

		// Victim's (!) crit chance mod for physical attacks?
		if(victim->IsUnit())
			CritChance += (float)(TO_UNIT(victim)->AttackerCritChanceMod[0]);
	}
	else
	{
		CritChance = spellcritperc + SpellCritChanceSchool[spell->SchoolMask];

		if(victim->IsUnit())
		{
			CritChance += TO_UNIT(victim)->AttackerCritChanceMod[spell->NormalizedSchoolMask()];

			if(IsPlayer() && (TO_UNIT(victim)->m_rooted - TO_UNIT(victim)->m_stunned))
				CritChance += TO_PLAYER(this)->m_RootedCritChanceBonus;
		}

		if(spell->SpellFamilyFlags)
		{
			if(Player * p = GetSpellModOwner())
				p->ApplySpellMod(spell->Id, SPELLMOD_CRITICAL_CHANCE, CritChance);
		}

		if(victim->IsPlayer())
			resilience_type = PLAYER_RATING_MODIFIER_SPELL_CRIT_RESILIENCE;
	}

	if(resilience_type)
		CritChance -= TO_PLAYER(victim)->CalcRating(resilience_type);

	if(CritChance < 0)
		CritChance = 0;
	else if(CritChance > 95)
		CritChance = 95;

	result = Rand(CritChance);
	if(spell->NameHash == SPELL_HASH_EXORCISM && victim->IsCreature())
	{
		uint32 type = TO_CREATURE(victim)->GetCreatureInfo()->Type;
		if(type == UNIT_TYPE_UNDEAD || type == UNIT_TYPE_DEMON)
			result = true;
	}
	// HACK!!!
	Aura* fs = NULL;
	if(victim->IsUnit() && spell->NameHash == SPELL_HASH_LAVA_BURST && (fs = TO_UNIT(victim)->FindAuraByNameHash(SPELL_HASH_FLAME_SHOCK)) != NULL)
	{
		result = true;
		if(! HasAura(55447))	// Glyph of Flame Shock
			fs->Remove();
	}

	return result;
}

float Unit::GetCriticalDamageBonusForSpell(Object* victim, SpellEntry* spell, float amount)
{
	int32 critical_bonus = 100;

	if(spell->SpellFamilyFlags)
	{
		if(Player * p = GetSpellModOwner())
			p->ApplySpellMod(spell->Id, SPELLMOD_CRIT_DAMAGE_BONUS, critical_bonus);
	}

	if(critical_bonus > 0)
	{
		// the bonuses are halved by 50% (funky blizzard math :S)
		float b;
		if(spell->NormalizedSchoolMask() == 0 || spell->is_melee_spell || spell->is_ranged_spell)		// physical || hackfix SoCommand/JoCommand
			b = critical_bonus / 100.0f + 1.0f;
		else
			b = critical_bonus / 200.0f + 1.0f;

		amount *= b;
	}

	if(victim->IsPlayer())
	{
		//res = res*(1.0f-2.0f*TO< Player* >(pVictim)->CalcRating(PLAYER_RATING_MODIFIER_MELEE_CRIT_RESISTANCE));
		//Resilience is a special new rating which was created to reduce the effects of critical hits against your character.
		//It has two components; it reduces the chance you will be critically hit by x%,
		//and it reduces the damage dealt to you by critical hits by 2x%. x is the percentage resilience granted by a given resilience rating.
		//It is believed that resilience also functions against spell crits,
		//though it's worth noting that NPC mobs cannot get critical hits with spells.

		float dmg_reduction_pct = 2 * TO_PLAYER(victim)->CalcRating(PLAYER_RATING_MODIFIER_MELEE_CRIT_RESILIENCE) / 100.0f;

		if(dmg_reduction_pct > 1.0f)
			dmg_reduction_pct = 1.0f; //we cannot resist more then he is criticalling us, there is no point of the critical then :P

		amount -= amount * dmg_reduction_pct;
	}

	if(victim->IsCreature() && TO_CREATURE(victim)->GetCreatureInfo()->Rank != ELITE_WORLDBOSS)
		TO_CREATURE(victim)->Emote(EMOTE_ONESHOT_WOUNDCRITICAL);

	return amount;
}

bool Unit::IsCriticalHealForSpell(Object* victim, SpellEntry* spell)
{
	int32 crit_chance = 0;

	crit_chance = float2int32(this->spellcritperc + this->SpellCritChanceSchool[spell->NormalizedSchoolMask()]);

	//Sacred Shield
	if(victim->IsUnit() && TO_UNIT(victim)->HasAurasWithNameHash(SPELL_HASH_SACRED_SHIELD) && spell->NameHash == SPELL_HASH_FLASH_OF_LIGHT)
		crit_chance += 50;

	if(spell->SpellFamilyFlags)
		if(Player * p = GetSpellModOwner())
			p->ApplySpellMod(spell->Id, SPELLMOD_CRITICAL_CHANCE, crit_chance);
	
	return Rand(crit_chance);
}

float Unit::GetCriticalHealBonusForSpell(Object* victim, SpellEntry* spell, float amount)
{
	int32 critical_bonus = 100;
	if(spell->SpellFamilyFlags)
		if(Player * p = GetSpellModOwner())
			p->ApplySpellMod(spell->Id, SPELLMOD_CRIT_DAMAGE_BONUS, critical_bonus);

	if(critical_bonus > 0)
	{
		// the bonuses are halved by 50% (funky blizzard math :S)
		float b = critical_bonus / 200.0f;
		amount += float2int32(amount * b);
	}

	return amount;
}

uint32 Unit::GetAuraCountWithDispel(uint32 dispel_type, uint64 guid)
{
	uint32 result = 0;

	for(uint32 x = MAX_TOTAL_AURAS_START; x < MAX_TOTAL_AURAS_END; ++x)
	{
		if(m_auras[x] == NULL)
			continue;

		if(m_auras[x]->GetSpellProto()->Dispel == dispel_type && (guid == 0 || m_auras[x]->GetCasterGUID() == guid))
			result++;
	}

	return result;
}

void Unit::HandleKnockback(Object* caster, float horizontal, float vertical)
{
	//This is in unit and not creature because players who are mind controlled must use this.
	if(caster == NULL)
		caster = this;
	if(GetCurrentSpell())
		GetCurrentSpell()->cancel();
	/* This seems to never go into the right direction ex: caster facing foward does knockback, victim goes backwards.
	float angle = calcRadAngle(caster->GetPositionX(), caster->GetPositionY(), GetPositionX(), GetPositionY());
	if(caster == this)
		angle = GetOrientation() + M_PI;*/
	float angle = caster->GetOrientation();

	float destx, desty, destz;
	if(GetPoint(angle, horizontal, destx, desty, destz, true))
		GetAIInterface()->MoveKnockback(destx, desty, destz, horizontal, vertical);
}


void Unit::BuildPetSpellList(WorldPacket & data)
{
	data << uint64(0);
}

void Unit::CastOnMeleeSpell(){
	SpellEntry *spellInfo = dbcSpell.LookupEntry( GetOnMeleeSpell() );
	Spell *spell = sSpellFactoryMgr.NewSpell( this, spellInfo, true, NULL );
	spell->extra_cast_number = GetOnMeleeSpellEcn();	
	SpellCastTargets targets;
	targets.m_unitTarget = GetTargetGUID();
	spell->prepare( &targets );
	SetOnMeleeSpell(0);
}

void Unit::SendHopOnVehicle( Unit *vehicleowner, uint32 seat ){
	WorldPacket data(SMSG_MONSTER_MOVE_TRANSPORT, 50);
	data << GetNewGUID();
	data << vehicleowner->GetNewGUID();
	data << uint8( seat );

	if( IsPlayer() )
		data << uint8( 1 );
	else
		data << uint8( 0 );

	data << float( GetPositionX() /* - vehicleowner->GetPositionX() */ );
	data << float( GetPositionY() /* - vehicleowner->GetPositionY() */ );
	data << float( GetPositionZ() /* - vehicleowner->GetPositionZ() */ );
	data << getMSTime();
	data << uint8( 4 ); // splinetype_facing_angle
	data << float( 0.0f ); // facing angle
	data << uint32( 0x00800000 ); // splineflag transport
	data << uint32( 0 ); // movetime
	data << uint32( 1 ); // wp count
	data << float( 0.0f ); // x
	data << float( 0.0f ); // y
	data << float( 0.0f ); // z

	SendMessageToSet( &data, true );
}

void Unit::SendHopOffVehicle( Unit *vehicleowner, LocationVector &landposition ){
	WorldPacket data(SMSG_MONSTER_MOVE, 1+12+4+1+4+4+4+12+8 );
	data << GetNewGUID();

	if( IsPlayer() )
		data << uint8( 1 );
	else
		data << uint8( 0 );

	data << float( GetPositionX() );
	data << float( GetPositionY() );
	data << float( GetPositionZ() );
	data << uint32( getMSTime() );
	data << uint8( 4 /* SPLINETYPE_FACING_ANGLE */ );
	data << float( GetOrientation() );                        // guess
	data << uint32( 0x01000000 /* SPLINEFLAG_EXIT_VEHICLE */ );
	data << uint32( 0 );                                      // Time in between points
	data << uint32( 1 );                                      // 1 single waypoint
	data << float( vehicleowner->GetPositionX() );
	data << float( vehicleowner->GetPositionY() );
	data << float( vehicleowner->GetPositionZ() );

    SendMessageToSet(&data, true);
}


void Unit::EnterVehicle( uint64 guid, uint32 delay, uint32 seat ){
	if( delay != 0 ){
		sEventMgr.AddEvent( this, &Unit::EnterVehicle, guid, uint32( 0 ), seat, 0, delay, 1, 0 );
		return;
	}

	Unit *u = m_mapMgr->GetUnit( guid );

	if( u == NULL )
		return;

	if( u->GetVehicleComponent() == NULL )
		return;

	if( currentvehicle != NULL )
		return;
	if(seat != 0)
		u->GetVehicleComponent()->AddPassengerToSeatIfCan(this, seat, true);
	else
		u->GetVehicleComponent()->AddPassenger( this );
}

Unit* Unit::GetVehicleBase(){
	if( currentvehicle != NULL )
		return currentvehicle->GetOwner();
	else
	if( vehicle != NULL )
		return this;

	return NULL;
}

void Unit::SendEnvironmentalDamageLog( uint64 guid, uint8 type, uint32 damage ){
	WorldPacket data( SMSG_ENVIRONMENTALDAMAGELOG, 20 );
	
	data << uint64( guid );
	data << uint8( type );
	data << uint32( damage );
	data << uint64( 0 );

	SendMessageToSet( &data, true, false );
}

bool Unit::IsTauntable()
{
	bool ret = true;
	if(IsPlayer())
		ret = false;
	if(GetAIInterface()->GetIsTaunted())
		ret = false;
	if(IsCreature() && TO< Creature* >(this)->GetProto()->modImmunities & 4096)
		ret = false;
	return ret;
}

const char* Unit::GetName()
{
	if(IsPet())
		return TO_PET(this)->GetName().c_str();
	if(IsCreature())
		return TO_CREATURE(this)->GetCreatureInfo()->Name;
	if(IsPlayer())
		return TO_PLAYER(this)->GetName();
	return "Unknown Being";
}

int32 Unit::GetTotalAuraModifer(uint32 AuraName, bool addone)
{
	int32 modifer = 0;
	for(uint32 i = MAX_TOTAL_AURAS_START; i < MAX_TOTAL_AURAS_END; ++i)
	{
		if(m_auras[ i ] != NULL && m_auras[ i ]->GetSpellProto()->AppliesAura(AuraName))
			modifer += m_auras[i]->GetModAmountByMod() + (addone ?  1 : 0);
	}
	return modifer;
}

int32 Unit::GetMaxPositiveAuraModifier(uint32 AuraName, uint32 ignorerspell)
{
	int32 modifer = 0;
	for(uint32 i = MAX_TOTAL_AURAS_START; i < MAX_TOTAL_AURAS_END; ++i)
	{
		if(m_auras[ i ] != NULL && m_auras[ i ]->GetSpellProto()->AppliesAura(AuraName) && !(m_auras[i]->GetSpellId() == ignorerspell))
		{
			for(uint32 x = 0; x < MAX_SPELL_EFFECTS; ++x)
			{
				if(m_auras[i]->GetSpellProto()->EffectApplyAuraName[x] == AuraName && m_auras[i]->GetModAmount(x) > modifer)
					modifer = m_auras[i]->GetModAmount(x);
			}
		}
	}
	return modifer;
}

float Unit::GetTotalAuraMultiplier(uint32 AuraName, uint32 ignorerspell)
{
	float multiplier = 1.0f;
	for(uint32 i = MAX_TOTAL_AURAS_START; i < MAX_TOTAL_AURAS_END; ++i)
	{
		if(m_auras[ i ] != NULL && m_auras[ i ]->GetSpellProto()->AppliesAura(AuraName) && !(m_auras[i]->GetSpellId() == ignorerspell))
		{
			for(uint32 x = 0; x < MAX_SPELL_EFFECTS; ++x)
			{
				if(m_auras[i]->GetSpellProto()->EffectApplyAuraName[x] == AuraName)
					AddPctN(multiplier, m_auras[i]->GetModAmount(x));
			}
		}
	}
	return multiplier;
}

int32 Unit::GetTotalAuraModifier(uint32 AuraName, uint32 ignorerspell)
{
	int32 modifer = 0;
	for(uint32 i = MAX_TOTAL_AURAS_START; i < MAX_TOTAL_AURAS_END; ++i)
	{
		if(m_auras[ i ] != NULL && m_auras[ i ]->GetSpellProto()->AppliesAura(AuraName) && !(m_auras[i]->GetSpellId() == ignorerspell))
		{
			for(uint32 x = 0; x < MAX_SPELL_EFFECTS; ++x)
			{
				if(m_auras[i]->GetSpellProto()->EffectApplyAuraName[x] == AuraName)
					modifer += m_auras[i]->GetModAmount(x);
			}
		}
	}
	return modifer;
}

int32 Unit::GetMaxNegativeAuraModifier(uint32 AuraName, uint32 ignorerspell)
{
	int32 modifer = 0;
	for(uint32 i = MAX_TOTAL_AURAS_START; i < MAX_TOTAL_AURAS_END; ++i)
	{
		if(m_auras[ i ] != NULL && m_auras[ i ]->GetSpellProto()->AppliesAura(AuraName) && !(m_auras[i]->GetSpellId() == ignorerspell))
		{
			for(uint32 x = 0; x < MAX_SPELL_EFFECTS; ++x)
			{
				if(m_auras[i]->GetSpellProto()->EffectApplyAuraName[x] == AuraName && m_auras[i]->GetModAmount(x) < modifer)
					modifer = m_auras[i]->GetModAmount(x);
			}
		}
	}
	return modifer;
}

int32 Unit::GetTotalAuraModifierByMiscMask(uint32 auratype, uint32 misc_mask)
{
	int32 modifer = 0;
	for(uint32 i = MAX_TOTAL_AURAS_START; i < MAX_TOTAL_AURAS_END; ++i)
	{
		if(m_auras[ i ] != NULL && m_auras[ i ]->GetSpellProto()->AppliesAura(auratype))
		{
			for(uint32 x = 0; x < MAX_SPELL_EFFECTS; ++x)
			{
				if(m_auras[i]->GetSpellProto()->EffectApplyAuraName[x] == auratype && m_auras[i]->GetMod(x).m_miscValue & misc_mask)
					modifer += m_auras[i]->GetModAmount(x);
			}
		}
	}
	return modifer;
}

bool Unit::CanFly(uint32 skipspell)
{
	if(GetCurrentVehicle())
		return true;

	if(IsPlayer())
	{
		Player * plr = TO_PLAYER(this);
		if(plr->GetSession()->HasGMPermissions() || plr->m_flycheckdelay || plr->FlyCheat || plr->m_setflycheat || plr->flying_aura || plr->GetTaxiState() || plr->m_CurrentTransporter)
			return true;
	}
	return HasFlyingAura(skipspell);
}

float Unit::CalcSpellDamageReduction(Unit* victim, SpellEntry* spell, float res)
{
	float reduced_damage = 0;
	reduced_damage += static_cast< float >( victim->DamageTakenMod[spell->NormalizedSchoolMask()] );
	reduced_damage += res * victim->DamageTakenPctMod[spell->NormalizedSchoolMask()];
	reduced_damage += res * victim->ModDamageTakenByMechPCT[spell->Mechanic];
	return reduced_damage;
}

bool Unit::ClassUsesSpellPower()
{
	switch( getClass() )
	{
		case PALADIN:
		case PRIEST:
		case SHAMAN:
		case MAGE:
		case WARLOCK:
		case DRUID:
		{
			return true;
		}break;
	}
	return false;
}

bool Unit::HasCreatureCustomFlag(uint32 flag)
{
	if(!IsCreature())
		return false;
	return TO< Creature *>(this)->HasCustomFlag(flag);
}

bool Unit::HasLoot()
{
	if(IsPlayer() && IsInBg())
		return true;
	if(!IsCreature())
		return false;
	return TO< Creature *>(this)->HasLoot();
}

Player* Unit::GetSpellModOwner()
{
    if (GetTypeId() == TYPEID_PLAYER)
        return TO_PLAYER(this);
    if (IsPet() || IsTotem())
    {
		if(GetPlayerOwner() != NULL)
			return TO_PLAYER(GetPlayerOwner());
    }
    return NULL;
}

void Unit::SendHover(bool apply)
{
	if(GetFloatValue(UNIT_FIELD_HOVERHEIGHT) <= 0)
		SetFloatValue(UNIT_FIELD_HOVERHEIGHT, 1.0f);
	WorldPacket data;
	if(apply)
	{
		data.Initialize(MSG_MOVE_HOVER, 64);
		data.append(GetNewGUID());
		BuildMovementPacket(&data);
		SendMessageToSet(&data, false);
	}
	data.Initialize(apply ? SMSG_MOVE_SET_HOVER : SMSG_MOVE_UNSET_HOVER);
	data << GetNewGUID();
	data << uint32(0);
	SendMessageToSet(&data, true);
}

void Unit::SendWaterWalk(bool apply) 
{
	WorldPacket data;
	if(apply)
	{
		data.Initialize(MSG_MOVE_WATER_WALK, 64);
		data.append(GetNewGUID());
		BuildMovementPacket(&data);
		SendMessageToSet(&data, false);
	}
	data.Initialize(apply ? SMSG_MOVE_WATER_WALK : SMSG_MOVE_LAND_WALK);
	data << GetNewGUID();
	data << uint32(apply ? 8 : 4);
	SendMessageToSet(&data, true);
}

void Unit::SendFeatherFall(bool apply)
{
    WorldPacket data;
	if(apply)
	{
		data.Initialize(MSG_MOVE_FEATHER_FALL, 64);
		data.append(GetNewGUID());
		BuildMovementPacket(&data);
		SendMessageToSet(&data, false);
	}
	data.Initialize(apply ? SMSG_MOVE_FEATHER_FALL : SMSG_MOVE_NORMAL_FALL);
	data << GetNewGUID();
	data << uint32(0);
	SendMessageToSet(&data, true);
}

bool Unit::SetHover(bool enable)
{
    if (enable == HasUnitMovementFlag(MOVEFLAG_LEVITATE))
        return false;

    if (enable)
    {
        //! No need to check height on ascent
        AddUnitMovementFlag(MOVEFLAG_LEVITATE);
       //if (float hh = GetFloatValue(UNIT_FIELD_HOVERHEIGHT))
            //UpdateHeight(GetPositionZ() + hh);
    }
    else
    {
        RemoveUnitMovementFlag(MOVEFLAG_LEVITATE);
        /*if (float hh = GetFloatValue(UNIT_FIELD_HOVERHEIGHT))
        {
            float newZ = GetPositionZ() - hh;
            UpdateAllowedPositionZ(GetPositionX(), GetPositionY(), newZ);
            UpdateHeight(newZ);
        }*/
    }
    return true;
}

void Unit::BuildMovementPacket(ByteBuffer *data)
{
    *data << uint32(GetUnitMovementFlags());            // movement flags
    *data << uint16(GetExtraUnitMovementFlags());       // 2.3.0
	*data << uint32(GetMovementInfo()->time);                       // time / counter
    *data << GetPositionX();
    *data << GetPositionY();
    *data << GetPositionZ();
    *data << GetOrientation();

    // 0x00000200
    if (GetUnitMovementFlags() & MOVEFLAG_TRANSPORT)
    {
		if(IsPlayer() && TO_PLAYER(this)->m_CurrentTransporter)
			transporter_info.guid = TO_PLAYER(this)->m_CurrentTransporter->GetGUID();
		if(Unit * u = GetVehicleBase())
			transporter_info.guid = u->GetGUID();
		*data << transporter_info.guid;
        *data << transporter_info.x;
        *data << transporter_info.y;
        *data << transporter_info.z;
        *data << transporter_info.o;
        *data << transporter_info.flags;
		*data << transporter_info.seat;

        if (GetExtraUnitMovementFlags() & MOVEFLAG2_ALLOW_PITCHING)
			*data << uint32(GetMovementInfo()->transTime2);
    }

    // 0x02200000
    if ((GetUnitMovementFlags() & (MOVEFLAG_SWIMMING | MOVEFLAG_AIR_SWIMMING))
		|| (GetExtraUnitMovementFlags() & MOVEFLAG2_ALLOW_PITCHING))
        *data << (float)GetMovementInfo()->pitch;

    *data << (uint32)GetMovementInfo()->fallTime;

    // 0x00001000
    if (GetUnitMovementFlags() & MOVEFLAG_JUMPING)
    {
        *data << (float)GetMovementInfo()->redirectVelocity;
        *data << (float)GetMovementInfo()->redirectSin;
        *data << (float)GetMovementInfo()->redirectCos;
        *data << (float)GetMovementInfo()->redirect2DSpeed;
    }

    // 0x04000000
    if (GetUnitMovementFlags() & MOVEFLAG_SPLINE_ELEVATION)
        *data << (float)GetMovementInfo()->splineElevation;
}


void Unit::BuildMovementPacket(ByteBuffer *data, float x, float y, float z, float o)
{
    *data << uint32(GetUnitMovementFlags());            // movement flags
    *data << uint16(GetExtraUnitMovementFlags());       // 2.3.0
    *data << uint32(GetMovementInfo()->time);                       // time / counter
    *data << x;
    *data << y;
    *data << z;
    *data << o;

    // 0x00000200
    if (GetUnitMovementFlags() & MOVEFLAG_TRANSPORT)
    {
		if(IsPlayer() && TO_PLAYER(this)->m_CurrentTransporter)
			transporter_info.guid = TO_PLAYER(this)->m_CurrentTransporter->GetGUID();
		if(Unit * u = GetVehicleBase())
			transporter_info.guid = u->GetGUID();
		*data << transporter_info.guid;
        *data << transporter_info.x;
        *data << transporter_info.y;
        *data << transporter_info.z;
        *data << transporter_info.o;
        *data << transporter_info.flags;
		*data << transporter_info.seat;

        if (GetExtraUnitMovementFlags() & MOVEFLAG2_ALLOW_PITCHING)
			*data << uint32(GetMovementInfo()->transTime2);
    }

    // 0x02200000
    if ((GetUnitMovementFlags() & (MOVEFLAG_SWIMMING | MOVEFLAG_AIR_SWIMMING))
		|| (GetExtraUnitMovementFlags() & MOVEFLAG2_ALLOW_PITCHING))
        *data << (float)GetMovementInfo()->pitch;

    *data << (uint32)GetMovementInfo()->fallTime;

    // 0x00001000
    if (GetUnitMovementFlags() & MOVEFLAG_JUMPING)
    {
        *data << (float)GetMovementInfo()->redirectVelocity;
        *data << (float)GetMovementInfo()->redirectSin;
        *data << (float)GetMovementInfo()->redirectCos;
        *data << (float)GetMovementInfo()->redirect2DSpeed;
    }

    // 0x04000000
    if (GetUnitMovementFlags() & MOVEFLAG_SPLINE_ELEVATION)
        *data << (float)GetMovementInfo()->splineElevation;
}

void Unit::SendMovementFlagUpdate()
{
    WorldPacket data;
    BuildHeartBeatMsg(&data);
    SendMessageToSet(&data, false);
}

void Unit::BuildHeartBeatMsg(WorldPacket* data)
{
    data->Initialize(MSG_MOVE_HEARTBEAT, 32);
    data->append(GetNewGUID());
    BuildMovementPacket(data);
}

void Unit::BroadcastAuras()
{
	if(HasAuraWithName(SPELL_AURA_HOVER))
		SendHover(true);
	if(HasAuraWithName(SPELL_AURA_FEATHER_FALL))
		SendFeatherFall(true);
	if(HasAuraWithName(SPELL_AURA_WATER_WALK))
		SendWaterWalk(true);
	WorldPacket data( SMSG_AURA_UPDATE_ALL, 200 );

	data << WoWGuid( GetNewGUID() );
	for ( uint32 i = MAX_TOTAL_AURAS_START; i < MAX_TOTAL_AURAS_END; ++i )
	{
		Aura * aur = m_auras[ i ];
		
		if( aur != NULL )
		{
			//if(aur->GetSpellProto()->Attributes & SPELL_ATTR0_HIDDEN_CLIENTSIDE)
				//continue;
			uint8 Flags = uint8( aur->GetAuraFlags() );

			Flags = ( AFLAG_EFFECT_1 | AFLAG_EFFECT_2 | AFLAG_EFFECT_3 );
		
			if( aur->IsPositive() )
				Flags |= AFLAG_CANCELLABLE;
			else
				Flags |= AFLAG_NEGATIVE;

			if( aur->GetDuration() != 0 && !(aur->GetSpellProto()->AttributesEx5 & SPELL_ATTR5_HIDE_DURATION))
				Flags |= AFLAG_DURATION;

			data << uint8( aur->m_visualSlot );
			data << uint32( aur->GetSpellId() );
			data << uint8( Flags );
			data << uint8( getLevel() );
			uint8 count = 1;
			
			std::map< uint32, struct SpellCharge >::iterator iter = m_chargeSpells.find(aur->GetSpellId());
			if(iter != m_chargeSpells.end())
				count = iter->second.count;
			else
				count = m_auraStackCount[ aur->m_visualSlot ];
			data << uint8(count);
			
			if( ( Flags & AFLAG_NOT_CASTER ) == 0 )
				data << WoWGuid(aur->GetCasterGUID());

 			if( Flags & AFLAG_DURATION )
			{
				data << uint32( aur->GetDuration() );
				data << uint32( aur->GetTimeLeft() );
			}
		}
	}
	SendMessageToSet(&data, false);
	if(IsPlayer())
		TO_PLAYER(this)->SendPacket(&data);
}

bool Unit::IsFlying()
{
	if(GetAIInterface()->Flying())
		return true;
	//if(CanFly())
		//return true;
	if(HasUnitMovementFlag(MOVEFLAG_AIR_SWIMMING))
		return true;
	if(HasUnitMovementFlag(MOVEFLAG_CAN_FLY))
		return true;
	if(HasUnitMovementFlag(MOVEFLAG_NO_COLLISION))
		return true;
	//This shouldn't be reached due to plays would have a flying movement flag when forced to fly
	if(IsPlayer() && TO_PLAYER(this)->FlyCheat)
		return true;
	return false;
}

void Unit::RestoreSpeed()
{
	UpdateSpeed();
	SetSpeeds(FLYBACK, 4.5f);
	SetSpeeds(SWIM, 4.722222f);
	SetSpeeds(SWIMBACK, 2.5f);
	SetSpeeds(TURN, M_PI_FLOAT);
	SetSpeeds(PITCH, M_PI_FLOAT);
}


uint32 Unit::GetModelForForm(uint32 form)
{
    switch (form)
    {
        case FORM_CAT:
            // Based on Hair color
            if (getRace() == RACE_NIGHTELF)
            {
				uint8 hairColor = GetByte(PLAYER_BYTES, 3);
                switch (hairColor)
                {
                    case 7: // Violet
                    case 8:
                        return 29405;
                    case 3: // Light Blue
                        return 29406;
                    case 0: // Green
                    case 1: // Light Green
                    case 2: // Dark Green
                        return 29407;
                    case 4: // White
                        return 29408;
                    default: // original - Dark Blue
                        return 892;
                }
            }
            // Based on Skin color
            else if (getRace() == RACE_TAUREN)
            {
                uint8 skinColor = GetByte(PLAYER_BYTES, 0);
                // Male
                if (getGender() == GENDER_MALE)
                {
                    switch (skinColor)
                    {
                        case 12: // White
                        case 13:
                        case 14:
                        case 18: // Completly White
                            return 29409;
                        case 9: // Light Brown
                        case 10:
                        case 11:
                            return 29410;
                        case 6: // Brown
                        case 7:
                        case 8:
                            return 29411;
                        case 0: // Dark
                        case 1:
                        case 2:
                        case 3: // Dark Grey
                        case 4:
                        case 5:
                            return 29412;
                        default: // original - Grey
                            return 8571;
                    }
                }
                // Female
                else switch (skinColor)
                {
                    case 10: // White
                        return 29409;
                    case 6: // Light Brown
                    case 7:
                        return 29410;
                    case 4: // Brown
                    case 5:
                        return 29411;
                    case 0: // Dark
                    case 1:
                    case 2:
                    case 3:
                        return 29412;
                    default: // original - Grey
                        return 8571;
                }
            }
			else if (GetTeam() == TEAM_ALLIANCE)
                return 892;
            else
                return 8571;
        case FORM_DIREBEAR:
        case FORM_BEAR:
            // Based on Hair color
            if (getRace() == RACE_NIGHTELF)
            {
                uint8 hairColor = GetByte(PLAYER_BYTES, 3);
                switch (hairColor)
                {
                    case 0: // Green
                    case 1: // Light Green
                    case 2: // Dark Green
                        return 29413; // 29415?
                    case 6: // Dark Blue
                        return 29414;
                    case 4: // White
                        return 29416;
                    case 3: // Light Blue
                        return 29417;
                    default: // original - Violet
                        return 2281;
                }
            }
            // Based on Skin color
            else if (getRace() == RACE_TAUREN)
            {
                uint8 skinColor = GetByte(PLAYER_BYTES, 0);
                // Male
                if (getGender() == GENDER_MALE)
                {
                    switch (skinColor)
                    {
                        case 0: // Dark (Black)
                        case 1:
                        case 2:
                            return 29418;
                        case 3: // White
                        case 4:
                        case 5:
                        case 12:
                        case 13:
                        case 14:
                            return 29419;
                        case 9: // Light Brown/Grey
                        case 10:
                        case 11:
                        case 15:
                        case 16:
                        case 17:
                            return 29420;
                        case 18: // Completly White
                            return 29421;
                        default: // original - Brown
                            return 2289;
                    }
                }
                // Female
                else switch (skinColor)
                {
                    case 0: // Dark (Black)
                    case 1:
                        return 29418;
                    case 2: // White
                    case 3:
                        return 29419;
                    case 6: // Light Brown/Grey
                    case 7:
                    case 8:
                    case 9:
                        return 29420;
                    case 10: // Completly White
                        return 29421;
                    default: // original - Brown
                        return 2289;
                }
            }
            else if (GetTeam() == TEAM_ALLIANCE)
                return 2281;
            else
                return 2289;
        case FORM_FLIGHT:
            if (GetTeam() == TEAM_ALLIANCE)
                return 20857;
            return 20872;
        case FORM_SWIFT:
            if (GetTeam() == TEAM_ALLIANCE)
                return 21243;
            return 21244;
        default:
            break;
    }

    uint32 modelid = 0;
    SpellShapeshiftForm * formEntry = dbcSpellShapeshiftForm.LookupEntry(form);
	if (formEntry && formEntry->modelId)
    {
        // Take the alliance modelid as default
        if (GetTypeId() != TYPEID_PLAYER)
            return formEntry->modelId;
        else
        {
            if (GetTeam() == TEAM_ALLIANCE)
                modelid = formEntry->modelId;
            else
                modelid = formEntry->modelId2;

            // If the player is horde but there are no values for the horde modelid - take the alliance modelid
            if (!modelid && GetTeam() == TEAM_HORDE)
                modelid = formEntry->modelId;
        }
    }

    return modelid;
}

uint32 Unit::GetCreatureIdForForm(uint32 form)
{
	uint32 id = 0;
    switch (form)
    {
        case FORM_TRAVEL:
			id = 6573;
        default:
            break;
    }
    return id;
}

bool Unit::IsControlledByPlayer()
{
	if(IS_PLAYER_GUID(GetCharmedByGUID()) || IsPlayer())
		return true;
	return false;
}

void Unit::UpdateAuraForGroup(uint8 slot)
{
    if (slot >= 64)                        // slot not found, return
        return;
    if (IsPlayer())
    {
		Player * player = TO_PLAYER(this);
        if (player->GetGroup())
        {
			player->AddGroupUpdateFlag(GROUP_UPDATE_FLAG_AURAS);
            player->SetAuraUpdateMaskForRaid(slot);
        }
    }
    else if (GetPlayerOwner())
    {
		if (GetPlayerOwner())
        {
            Player* owner = TO_PLAYER(GetPlayerOwner());
            if (owner->GetGroup())
            {
                owner->AddGroupUpdateFlag(GROUP_UPDATE_FLAG_PET_AURAS);
                SetAuraUpdateMaskForRaid(slot);
            }
        }
    }
}

void Unit::HandleUpdateFieldChange(uint32 Index)
{
	Player * player = NULL;
	bool pet = false;
	if(!IsInWorld())
		return;
	if(IsPlayer())
		player = TO_PLAYER(this);
	else if(GetPlayerOwner())
	{
		player = TO_PLAYER(GetPlayerOwner());
		pet = true;
	}
	if(player == NULL || !player->IsInWorld() || !player->GetGroup())
		return;
	uint32 Flags = 0;
	switch(Index)
	{
		case UNIT_FIELD_HEALTH:
			Flags = pet ? GROUP_UPDATE_FLAG_PET_CUR_HP : GROUP_UPDATE_FLAG_CUR_HP;
			break;

		case UNIT_FIELD_MAXHEALTH:
			Flags = pet ? GROUP_UPDATE_FLAG_PET_MAX_HP : GROUP_UPDATE_FLAG_MAX_HP;
			break;

		case UNIT_FIELD_POWER1:
		case UNIT_FIELD_POWER2:
		case UNIT_FIELD_POWER3:
		case UNIT_FIELD_POWER4:
		case UNIT_FIELD_POWER5:
		case UNIT_FIELD_POWER6:
		case UNIT_FIELD_POWER7:
			Flags = pet ? GROUP_UPDATE_FLAG_PET_CUR_POWER : GROUP_UPDATE_FLAG_CUR_POWER;
			break;

		case UNIT_FIELD_MAXPOWER1:
		case UNIT_FIELD_MAXPOWER2:
		case UNIT_FIELD_MAXPOWER3:
		case UNIT_FIELD_MAXPOWER4:
		case UNIT_FIELD_MAXPOWER5:
		case UNIT_FIELD_MAXPOWER6:
		case UNIT_FIELD_MAXPOWER7:
			Flags = pet ? GROUP_UPDATE_FLAG_PET_CUR_POWER : GROUP_UPDATE_FLAG_MAX_POWER;
			break;

		case UNIT_FIELD_DISPLAYID:
			Flags = pet ? GROUP_UPDATE_FLAG_PET_MODEL_ID : 0;
		case UNIT_FIELD_LEVEL:
			Flags = pet ? 0 : GROUP_UPDATE_FLAG_LEVEL;
			break;
		case UNIT_FIELD_BYTES_0:
			Flags = pet ? GROUP_UPDATE_FLAG_PET_POWER_TYPE : GROUP_UPDATE_FLAG_POWER_TYPE;
			break;
		case UNIT_FIELD_BYTES_2:
		case PLAYER_FLAGS:
			Flags = pet ? 0 : GROUP_UPDATE_FLAG_STATUS;
			break;
		default:
			break;
	}
	player->AddGroupUpdateFlag(Flags);
}

bool Unit::IsMoving() 
{ 
	return movement_info.HasMovementFlag(MOVEFLAG_MASK_MOVING); 
}

bool Unit::IsTurning() 
{ 
	return movement_info.HasMovementFlag(MOVEFLAG_MASK_TURNING); 
}

uint32 Unit::GetSpellCharges(uint32 spellid)
{
	std::map<uint32, struct SpellCharge>::iterator iter = m_chargeSpells.begin();

	while(iter != m_chargeSpells.end())
	{
		if(iter->first != spellid)
			continue;
		return int32(iter->second.count);
	}
	if(SpellEntry *s = dbcSpell.LookupEntry(spellid))
		return s->procCharges;

	return 0;
}

uint32 Unit::SpellDamageBonus(Unit* victim, SpellEntry* spellProto, uint32 pdamage, uint32 damagetype, uint32 stack)
{
    if (!spellProto || !victim || damagetype == 0)
        return pdamage;

    // small exception for Deep Wounds, can't find any general rule
    // should ignore ALL damage mods, they already calculated in trigger spell
    if (spellProto->Id == 12721) // Deep Wounds
        return pdamage;

	// For totems get damage bonus from owner
    if (GetTypeId() == TYPEID_UNIT && IsTotem())
        if (Unit* owner = TO<Summon*>(this)->GetOwner())
            return owner->SpellDamageBonus(victim, spellProto, pdamage, damagetype);

    // Taken/Done total percent damage auras
    float DoneTotalMod = 1.0f;
    float ApCoeffMod = 1.0f;
    int32 DoneTotal = 0;
    int32 TakenTotal = 0;

    // ..done
    // Pet damage?
    //if (GetTypeId() == TYPEID_UNIT && !ToCreature()->isPet())
       //DoneTotalMod *= ToCreature()->GetSpellDamageMod(ToCreature()->GetCreatureTemplate()->rank);


	DoneTotalMod = GetModPercentDamageDoneBonus(spellProto, DoneTotalMod);
    /*uint32 creatureTypeMask = victim->GetCreatureTypeMask();
    // Add flat bonus from spell damage versus
    DoneTotal += GetTotalAuraModifierByMiscMask(SPELL_AURA_MOD_FLAT_SPELL_DAMAGE_VERSUS, creatureTypeMask);
    AuraEffectList const& mDamageDoneVersus = GetAuraEffectsByType(SPELL_AURA_MOD_DAMAGE_DONE_VERSUS);
    for (AuraEffectList::const_iterator i = mDamageDoneVersus.begin(); i != mDamageDoneVersus.end(); ++i)
        if (creatureTypeMask & uint32((*i)->GetMiscValue()))
            AddPctN(DoneTotalMod, (*i)->GetAmount());

    // bonus against aurastate
    AuraEffectList const& mDamageDoneVersusAurastate = GetAuraEffectsByType(SPELL_AURA_MOD_DAMAGE_DONE_VERSUS_AURASTATE);
    for (AuraEffectList::const_iterator i = mDamageDoneVersusAurastate.begin(); i != mDamageDoneVersusAurastate.end(); ++i)
        if (victim->HasAuraState(AuraStateType((*i)->GetMiscValue())))
            AddPctN(DoneTotalMod, (*i)->GetAmount());

    // done scripted mod (take it from owner)
    Unit* owner = GetOwner() ? GetOwner() : this;
    AuraEffectList const& mOverrideClassScript= owner->GetAuraEffectsByType(SPELL_AURA_OVERRIDE_CLASS_SCRIPTS);
    for (AuraEffectList::const_iterator i = mOverrideClassScript.begin(); i != mOverrideClassScript.end(); ++i)
    {
        if (!(*i)->IsAffectedOnSpell(spellProto))
            continue;

        switch ((*i)->GetMiscValue())
        {
            case 4920: // Molten Fury
            case 4919:
            case 6917: // Death's Embrace
            case 6926:
            case 6928:
            {
                if (victim->HasAuraState(AURA_STATE_HEALTHLESS_35_PERCENT, spellProto, this))
                    AddPctN(DoneTotalMod, (*i)->GetAmount());
                break;
            }
            // Soul Siphon
            case 4992:
            case 4993:
            {
                // effect 1 m_amount
                int32 maxPercent = (*i)->GetAmount();
                // effect 0 m_amount
                int32 stepPercent = CalculateSpellDamage(this, (*i)->GetSpellInfo(), 0);
                // count affliction effects and calc additional damage in percentage
                int32 modPercent = 0;
                AuraApplicationMap const& victimAuras = victim->GetAppliedAuras();
                for (AuraApplicationMap::const_iterator itr = victimAuras.begin(); itr != victimAuras.end(); ++itr)
                {
                    Aura const* aura = itr->second->GetBase();
                    SpellInfo const* m_spell = aura->GetSpellInfo();
                    if (m_spell->SpellFamilyName != SPELLFAMILY_WARLOCK || !(m_spell->SpellFamilyFlags[1] & 0x0004071B || m_spell->SpellFamilyFlags[0] & 0x8044C402))
                        continue;
                    modPercent += stepPercent * aura->GetStackAmount();
                    if (modPercent >= maxPercent)
                    {
                        modPercent = maxPercent;
                        break;
                    }
                }
                AddPctN(DoneTotalMod, modPercent);
                break;
            }
            case 6916: // Death's Embrace
            case 6925:
            case 6927:
                if (HasAuraState(AURA_STATE_HEALTHLESS_20_PERCENT, spellProto, this))
                    AddPctN(DoneTotalMod, (*i)->GetAmount());
                break;
            case 5481: // Starfire Bonus
            {
                if (victim->GetAuraEffect(SPELL_AURA_PERIODIC_DAMAGE, SPELLFAMILY_DRUID, 0x200002, 0, 0))
                    AddPctN(DoneTotalMod, (*i)->GetAmount());
                break;
            }
            case 4418: // Increased Shock Damage
            case 4554: // Increased Lightning Damage
            case 4555: // Improved Moonfire
            case 5142: // Increased Lightning Damage
            case 5147: // Improved Consecration / Libram of Resurgence
            case 5148: // Idol of the Shooting Star
            case 6008: // Increased Lightning Damage
            case 8627: // Totem of Hex
            {
                DoneTotal += (*i)->GetAmount();
                break;
            }
            // Tundra Stalker
            // Merciless Combat
            case 7277:
            {
                // Merciless Combat
                if ((*i)->GetSpellInfo()->SpellIconID == 2656)
                {
                    if (!victim->HealthAbovePct(35))
                        AddPctN(DoneTotalMod, (*i)->GetAmount());
                }
                // Tundra Stalker
                else
                {
                    // Frost Fever (target debuff)
                    if (victim->HasAura(55095))
                        AddPctN(DoneTotalMod, (*i)->GetAmount());
                    break;
                }
                break;
            }
            // Rage of Rivendare
            case 7293:
            {
                if (victim->GetAuraEffect(SPELL_AURA_PERIODIC_DAMAGE, SPELLFAMILY_DEATHKNIGHT, 0, 0x02000000, 0))
                    AddPctF(DoneTotalMod, (*i)->GetSpellInfo()->GetRank() * 2.0f);
                break;
            }
            // Twisted Faith
            case 7377:
            {
                if (victim->GetAuraEffect(SPELL_AURA_PERIODIC_DAMAGE, SPELLFAMILY_PRIEST, 0x8000, 0, 0, GetGUID()))
                    AddPctN(DoneTotalMod, (*i)->GetAmount());
                break;
            }
            // Marked for Death
            case 7598:
            case 7599:
            case 7600:
            case 7601:
            case 7602:
            {
                if (victim->GetAuraEffect(SPELL_AURA_MOD_STALKED, SPELLFAMILY_HUNTER, 0x400, 0, 0))
                    AddPctN(DoneTotalMod, (*i)->GetAmount());
                break;
            }
            // Dirty Deeds
            case 6427:
            case 6428:
            case 6579:
            case 6580:
            {
                if (victim->HasAuraState(AURA_STATE_HEALTHLESS_35_PERCENT, spellProto, this))
                {
                    // effect 0 has expected value but in negative state
                    int32 bonus = -(*i)->GetBase()->GetEffect(0)->GetAmount();
                    AddPctN(DoneTotalMod, bonus);
                }
                break;
            }
        }
    }

    // Custom scripted damage
    switch (spellProto->SpellFamilyName)
    {
        case SPELLFAMILY_MAGE:
            // Ice Lance
            if (spellProto->SpellIconID == 186)
            {
                if (victim->HasAuraState(AURA_STATE_FROZEN, spellProto, this))
                {
                    // Glyph of Ice Lance
                    if (owner->HasAura(56377) && victim->getLevel() > owner->getLevel())
                        DoneTotalMod *= 4.0f;
                    else
                        DoneTotalMod *= 3.0f;
                }
            }

            // Torment the weak
            if (spellProto->SpellFamilyFlags[0] & 0x20600021 || spellProto->SpellFamilyFlags[1] & 0x9000)
                if (victim->HasAuraWithMechanic((1<<MECHANIC_SNARE)|(1<<MECHANIC_SLOW_ATTACK)))
                {
                    AuraEffectList const& mDumyAuras = GetAuraEffectsByType(SPELL_AURA_DUMMY);
                    for (AuraEffectList::const_iterator i = mDumyAuras.begin(); i != mDumyAuras.end(); ++i)
                        if ((*i)->GetSpellInfo()->SpellIconID == 3263)
                        {
                            AddPctN(DoneTotalMod, (*i)->GetAmount());
                            break;
                        }
                }
        break;
        case SPELLFAMILY_PRIEST:
            // Mind Flay
            if (spellProto->SpellFamilyFlags[0] & 0x800000)
            {
                // Glyph of Shadow Word: Pain
                if (AuraEffect* aurEff = GetAuraEffect(55687, 0))
                    // Increase Mind Flay damage if Shadow Word: Pain present on target
                    if (victim->GetAuraEffect(SPELL_AURA_PERIODIC_DAMAGE, SPELLFAMILY_PRIEST, 0x8000, 0, 0, GetGUID()))
                        AddPctN(DoneTotalMod, aurEff->GetAmount());

                // Twisted Faith - Mind Flay part
                if (AuraEffect* aurEff = GetAuraEffect(SPELL_AURA_OVERRIDE_CLASS_SCRIPTS, SPELLFAMILY_PRIEST, 2848, 1))
                    // Increase Mind Flay damage if Shadow Word: Pain present on target
                    if (victim->GetAuraEffect(SPELL_AURA_PERIODIC_DAMAGE, SPELLFAMILY_PRIEST, 0x8000, 0, 0, GetGUID()))
                        AddPctN(DoneTotalMod, aurEff->GetAmount());
            }
            // Smite
            else if (spellProto->SpellFamilyFlags[0] & 0x80)
            {
                // Glyph of Smite
                if (AuraEffect* aurEff = GetAuraEffect(55692, 0))
                    if (victim->GetAuraEffect(SPELL_AURA_PERIODIC_DAMAGE, SPELLFAMILY_PRIEST, 0x100000, 0, 0, GetGUID()))
                        AddPctN(DoneTotalMod, aurEff->GetAmount());
            }
            // Shadow Word: Death
            else if (spellProto->SpellFamilyFlags[1] & 0x2)
            {
                // Glyph of Shadow Word: Death
                if (AuraEffect* aurEff = GetAuraEffect(55682, 1))
                    if (victim->HasAuraState(AURA_STATE_HEALTHLESS_35_PERCENT))
                        AddPctN(DoneTotalMod, aurEff->GetAmount());
            }
        break;
        case SPELLFAMILY_PALADIN:
            // Judgement of Vengeance/Judgement of Corruption
            if ((spellProto->SpellFamilyFlags[1] & 0x400000) && spellProto->SpellIconID == 2292)
            {
                // Get stack of Holy Vengeance/Blood Corruption on the target added by caster
                uint32 stacks = 0;
                Unit::AuraEffectList const& auras = victim->GetAuraEffectsByType(SPELL_AURA_PERIODIC_DAMAGE);
                for (Unit::AuraEffectList::const_iterator itr = auras.begin(); itr != auras.end(); ++itr)
                    if (((*itr)->GetId() == 31803 || (*itr)->GetId() == 53742) && (*itr)->GetCasterGUID() == GetGUID())
                    {
                        stacks = (*itr)->GetBase()->GetStackAmount();
                        break;
                    }
                // + 10% for each application of Holy Vengeance/Blood Corruption on the target
                if (stacks)
                    AddPctU(DoneTotalMod, 10 * stacks);
            }
        break;
        case SPELLFAMILY_DRUID:
            // Thorns
            if (spellProto->SpellFamilyFlags[0] & 0x100)
            {
                // Brambles
                if (AuraEffect* aurEff = GetAuraEffectOfRankedSpell(16836, 0))
                    AddPctN(DoneTotalMod, aurEff->GetAmount());
            }
        break;
        case SPELLFAMILY_WARLOCK:
            // Fire and Brimstone
            if (spellProto->SpellFamilyFlags[1] & 0x00020040)
                if (victim->HasAuraState(AURA_STATE_CONFLAGRATE))
                {
                    AuraEffectList const& mDumyAuras = GetAuraEffectsByType(SPELL_AURA_DUMMY);
                    for (AuraEffectList::const_iterator i = mDumyAuras.begin(); i != mDumyAuras.end(); ++i)
                        if ((*i)->GetSpellInfo()->SpellIconID == 3173)
                        {
                            AddPctN(DoneTotalMod, (*i)->GetAmount());
                            break;
                        }
                }
            // Drain Soul - increased damage for targets under 25 % HP
            if (spellProto->SpellFamilyFlags[0] & 0x00004000)
                if (HasAura(100001))
                    DoneTotalMod *= 4;
            // Shadow Bite (15% increase from each dot)
            if (spellProto->SpellFamilyFlags[1] & 0x00400000 && isPet())
                if (uint8 count = victim->GetDoTsByCaster(GetOwnerGUID()))
                    AddPctN(DoneTotalMod, 15 * count);
        break;
        case SPELLFAMILY_HUNTER:
            // Steady Shot
            if (spellProto->SpellFamilyFlags[1] & 0x1)
                if (AuraEffect* aurEff = GetAuraEffect(56826, 0))  // Glyph of Steady Shot
                    if (victim->GetAuraEffect(SPELL_AURA_PERIODIC_DAMAGE, SPELLFAMILY_HUNTER, 0x00004000, 0, 0, GetGUID()))
                        AddPctN(DoneTotalMod, aurEff->GetAmount());
        break;
        case SPELLFAMILY_DEATHKNIGHT:
            // Improved Icy Touch
            if (spellProto->SpellFamilyFlags[0] & 0x2)
                if (AuraEffect* aurEff = GetDummyAuraEffect(SPELLFAMILY_DEATHKNIGHT, 2721, 0))
                    AddPctN(DoneTotalMod, aurEff->GetAmount());

            // Sigil of the Vengeful Heart
            if (spellProto->SpellFamilyFlags[0] & 0x2000)
                if (AuraEffect* aurEff = GetAuraEffect(64962, EFFECT_1))
                    AddPctN(DoneTotal, aurEff->GetAmount());

            // Glacier Rot
            if (spellProto->SpellFamilyFlags[0] & 0x2 || spellProto->SpellFamilyFlags[1] & 0x6)
                if (AuraEffect* aurEff = GetDummyAuraEffect(SPELLFAMILY_DEATHKNIGHT, 196, 0))
                    if (victim->GetDiseasesByCaster(owner->GetGUID()) > 0)
                        AddPctN(DoneTotalMod, aurEff->GetAmount());

            // Impurity (dummy effect)
            if (GetTypeId() == TYPEID_PLAYER)
            {
                PlayerSpellMap playerSpells = ToPlayer()->GetSpellMap();
                for (PlayerSpellMap::const_iterator itr = playerSpells.begin(); itr != playerSpells.end(); ++itr)
                {
                    if (itr->second->state == PLAYERSPELL_REMOVED || itr->second->disabled)
                        continue;
                    switch (itr->first)
                    {
                        case 49220:
                        case 49633:
                        case 49635:
                        case 49636:
                        case 49638:
                        {
                            if (SpellInfo const* proto = sSpellMgr->GetSpellInfo(itr->first))
                                AddPctN(ApCoeffMod, proto->Effects[0].CalcValue());
                        }
                        break;
                    }
                }
            }
        break;
    }*/

    // ..taken
    float TakenTotalMod = 1.0f;

    // from positive and negative SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN
    // multiplicative bonus, for example Dispersion + Shadowform (0.10*0.85=0.085)
    //TakenTotalMod *= victim->GetTotalAuraMultiplierByMiscMask(SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN, spellProto->GetSchoolMask());

    /*// .. taken pct: dummy auras
    AuraEffectList const& mDummyAuras = victim->GetAuraEffectsByType(SPELL_AURA_DUMMY);
    for (AuraEffectList::const_iterator i = mDummyAuras.begin(); i != mDummyAuras.end(); ++i)
    {
        switch ((*i)->GetSpellInfo()->SpellIconID)
        {
            // Cheat Death
            case 2109:
                if ((*i)->GetMiscValue() & SPELL_SCHOOL_MASK_NORMAL)
                {
                    if (victim->GetTypeId() != TYPEID_PLAYER)
                        continue;
                    float mod = victim->ToPlayer()->GetRatingBonusValue(CR_CRIT_TAKEN_MELEE) * (-8.0f);
                    AddPctF(TakenTotalMod, std::max(mod, float((*i)->GetAmount())));
                }
                break;
        }
    }*/

    // From caster spells
	TakenTotalMod = victim->GetModDamageFromCaster(GetGUID(), spellProto, TakenTotalMod);
    // Mod damage from spell mechanic
    TakenTotalMod = GetMechanicDamageTakenPct(spellProto, TakenTotalMod);

    // Taken/Done fixed damage bonus auras
	int32 DoneAdvertisedBenefit  = SpellBaseDamageBonus(spellProto->SchoolMask);
	int32 TakenAdvertisedBenefit = SpellBaseDamageBonusForVictim(spellProto->SchoolMask, victim);
    // Pets just add their bonus damage to their spell damage
    // note that their spell damage is just gain of their own auras
	if (IsPet())
        DoneAdvertisedBenefit += TO< Pet* >(this)->GetBonusDamage();

    // Check for table values
    float coeff = 0;
	//Impossibru for this to return NULL
	SpellEntry * bonusEntry = objmgr.GetRankOneSpell(spellProto->Id);
    if (bonusEntry->HasDBCoef())
    {
        if (damagetype == 2)
        {
			coeff = bonusEntry->OTspell_coef_override;
			if (bonusEntry->ap_dot_coef > 0)
            {
                uint8 attType = (spellProto->IsRangedWeaponSpell() && spellProto->DmgClass != 2) ? 2 : 0;
                float APbonus = (float) victim->GetTotalAuraModifier(attType == 0 ? SPELL_AURA_MELEE_ATTACK_POWER_ATTACKER_BONUS : SPELL_AURA_RANGED_ATTACK_POWER_ATTACKER_BONUS);
				APbonus += attType == 0 ? GetAP() : GetRAP();
                DoneTotal += int32(bonusEntry->ap_dot_coef * APbonus);
            }
        }
        else
        {
            coeff = bonusEntry->Dspell_coef_override;
			if (bonusEntry->ap_coef > 0)
            {
                uint8 attType = (spellProto->IsRangedWeaponSpell() && spellProto->DmgClass != 2) ? 2 : 0;
                float APbonus = (float) victim->GetTotalAuraModifier(attType == 0 ? SPELL_AURA_MELEE_ATTACK_POWER_ATTACKER_BONUS : SPELL_AURA_RANGED_ATTACK_POWER_ATTACKER_BONUS);
                APbonus += GetTotalAttackPowerValue(attType);
				DoneTotal += int32(bonusEntry->ap_coef * stack * ApCoeffMod * APbonus);
            }
        }
    }
    // Default calculation
    if (DoneAdvertisedBenefit || TakenAdvertisedBenefit)
    {
        if (!bonusEntry->HasDBCoef() || coeff < 0)
        {
            // Damage Done from spell damage bonus
            int32 CastingTime = spellProto->IsChanneled() ? GetDuration(dbcSpellDuration.LookupEntry(spellProto->DurationIndex)) : GetSpellCastTime(spellProto);
            // Damage over Time spells bonus calculation
            float DotFactor = 1.0f;
            if (damagetype == 2)
            {
				int32 DotDuration = GetDuration(dbcSpellDuration.LookupEntry(spellProto->DurationIndex));
                // 200% limit
                if (DotDuration > 0)
                {
                    if (DotDuration > 30000)
                        DotDuration = 30000;
                    if (!spellProto->IsChanneled())
                        DotFactor = DotDuration / 15000.0f;
                    uint8 x = 0;
                    for (uint8 j = 0; j < MAX_SPELL_EFFECTS; ++j)
                    {
                        if (spellProto->Effect[j] == SPELL_EFFECT_APPLY_AURA && (
                            spellProto->EffectApplyAuraName[j] == SPELL_AURA_PERIODIC_DAMAGE ||
                            spellProto->EffectApplyAuraName[j] == SPELL_AURA_PERIODIC_LEECH))
                        {
                            x = j;
                            break;
                        }
                    }
                    int32 DotTicks = 6;
                    if (spellProto->EffectAmplitude[x] != 0)
                        DotTicks = DotDuration / spellProto->EffectAmplitude[x];
                    if (DotTicks)
                    {
                        DoneAdvertisedBenefit /= DotTicks;
                        TakenAdvertisedBenefit /= DotTicks;
                    }
                }
            }
            // Distribute Damage over multiple effects, reduce by AoE
            CastingTime = GetCastingTimeForBonus(spellProto, damagetype, CastingTime);

            // 50% for damage and healing spells for leech spells from damage bonus and 0% from healing
            for (uint8 j = 0; j < MAX_SPELL_EFFECTS; ++j)
            {
                if (spellProto->Effect[j] == SPELL_EFFECT_HEALTH_LEECH ||
                    (spellProto->Effect[j] == SPELL_EFFECT_APPLY_AURA && spellProto->EffectApplyAuraName[j] == SPELL_AURA_PERIODIC_LEECH))
                {
                    CastingTime /= 2;
                    break;
                }
            }
            if (spellProto->NormalizedSchoolMask() != 1)
                coeff = (CastingTime / 3500.0f) * DotFactor;
            else
                coeff = DotFactor;
        }

        float factorMod = CalculateLevelPenalty(spellProto) * stack;
        // level penalty still applied on Taken bonus - is it blizzlike?
        TakenTotal+= int32(TakenAdvertisedBenefit * factorMod);
        if (Player* modOwner = GetSpellModOwner())
        {
            coeff *= 100.0f;
            modOwner->ApplySpellMod(spellProto->Id, SPELLMOD_BONUS_MULTIPLIER, coeff);
            coeff /= 100.0f;
        }
        DoneTotal += int32(DoneAdvertisedBenefit * coeff * factorMod);
    }

    // Some spells don't benefit from done mods
    if (spellProto->AttributesEx3 & SPELL_ATTR3_NO_DONE_BONUS)
    {
        DoneTotal = 0;
        DoneTotalMod = 1.0f;
    }

    // Some spells don't benefit from pct done mods
    // maybe should be implemented like SPELL_ATTR3_NO_DONE_BONUS,
    // but then it may break spell power coeffs work on spell 31117
    if (spellProto->AttributesEx6 & SPELL_ATTR6_NO_DONE_PCT_DAMAGE_MODS)
        DoneTotalMod = 1.0f;

    float tmpDamage = (int32(pdamage) + DoneTotal) * DoneTotalMod;
    // apply spellmod to Done damage (flat and pct)
    if (Player* modOwner = GetSpellModOwner())
        modOwner->ApplySpellMod(spellProto->Id, damagetype == 2 ? SPELLMOD_DOT : SPELLMOD_DAMAGE, tmpDamage);

    tmpDamage = (tmpDamage + TakenTotal) * TakenTotalMod;

    return uint32(std::max(tmpDamage, 0.0f));
}

float Unit::GetModPercentDamageDoneBonus(SpellEntry *proto, float DoneTotal)
{
	float DoneTotalMod = DoneTotal;
	for(uint32 i = MAX_TOTAL_AURAS_START; i < MAX_TOTAL_AURAS_END; ++i)
	{
		if(m_auras[ i ] != NULL && m_auras[ i ]->GetSpellProto()->AppliesAura(SPELL_AURA_MOD_DAMAGE_PERCENT_DONE))
		{
			if (proto->EquippedItemClass == -1 && m_auras[i]->GetSpellProto()->EquippedItemClass != -1)    //prevent apply mods from weapon specific case to non weapon specific spells (Example: thunder clap and two-handed weapon specialization)
				continue;
			for(uint32 x = 0; x < MAX_SPELL_EFFECTS; ++x)
			{
				if(m_auras[i]->GetSpellProto()->EffectApplyAuraName[x] == SPELL_AURA_MOD_DAMAGE_PERCENT_DONE)
				{
					Aura * aur = m_auras[i];
					// Something was crashing here so hackfix around it
					Modifier m;
					// Make sure this value will be null when we check if not valid i
					m.m_miscValue = NULL;
					// If valid size get the mod (i indexes an array of size 3)
					if (i >= 0 && i <= 2)
						m = aur->GetMod(i);
					// Check valid values
					if ((m.m_miscValue) && (proto->SchoolMask))
					{
						// Continue as normal
						if(m.m_miscValue & proto->SchoolMask)
						{
							if(aur->GetSpellProto()->EquippedItemClass == -1)
								AddPctN(DoneTotalMod, m_auras[i]->GetModAmount(x));
							else if (!(aur->GetSpellProto()->AttributesEx5 & SPELL_ATTR5_SPECIAL_ITEM_CLASS_CHECK) && (aur->GetSpellProto()->EquippedItemSubClassMask == 0))
								AddPctN(DoneTotalMod, m_auras[i]->GetModAmount(x));
							//else if (IsPlayer() && TO_PLAYER(this)->HasItemFitToSpellRequirements(aur->GetSpellProto()))
								//AddPctN(DoneTotalMod, m_auras[i]->GetModAmount(x));
						}
					}
				}
			}
		}
	}    
	return DoneTotalMod;
}

float Unit::GetTotalAttackPowerValue(uint8 attType)
{
    if (attType == 2)
		return GetRAP();
    else
		return GetAP();
	return 0.0f;
}

uint32 Unit::GetSpellCastTime(SpellEntry * sp)
{
	uint32 m_castTime = GetCastTime(dbcSpellCastTime.LookupEntry(sp->CastingTimeIndex));
	if(Player * p = GetSpellModOwner())
		p->ApplySpellMod(sp->Id, SPELLMOD_CASTING_TIME, m_castTime);
	// handle MOD_CAST_TIME
	if(m_castTime)
		m_castTime = float2int32(m_castTime * GetCastSpeedMod());
	return m_castTime;
}

uint32 Unit::GetCastingTimeForBonus(SpellEntry* spellProto, uint8 damagetype, uint32 CastingTime)
{
    // Not apply this to creature casted spells with casttime == 0
    if (CastingTime == 0 && GetTypeId() == TYPEID_UNIT && !IsPet())
        return 3500;

    if (CastingTime > 7000) CastingTime = 7000;
    if (CastingTime < 1500) CastingTime = 1500;

    if (damagetype == 2 && !spellProto->IsChanneled())
        CastingTime = 3500;

    int32 overTime    = 0;
    uint8 effects     = 0;
    bool DirectDamage = false;
    bool AreaEffect   = false;

    for (uint32 i = 0; i < MAX_SPELL_EFFECTS; i++)
    {
        switch (spellProto->Effect[i])
        {
            case SPELL_EFFECT_SCHOOL_DAMAGE:
            case SPELL_EFFECT_POWER_DRAIN:
            case SPELL_EFFECT_HEALTH_LEECH:
            case SPELL_EFFECT_ENVIRONMENTAL_DAMAGE:
            case SPELL_EFFECT_POWER_BURN:
            case SPELL_EFFECT_HEAL:
                DirectDamage = true;
                break;
            case SPELL_EFFECT_APPLY_AURA:
                switch (spellProto->EffectApplyAuraName[i])
                {
                    case SPELL_AURA_PERIODIC_DAMAGE:
                    case SPELL_AURA_PERIODIC_HEAL:
                    case SPELL_AURA_PERIODIC_LEECH:
                        if (GetDuration(dbcSpellDuration.LookupEntry(spellProto->DurationIndex)))
                            overTime = GetDuration(dbcSpellDuration.LookupEntry(spellProto->DurationIndex));
                        break;
                    default:
                        // -5% per additional effect
                        ++effects;
                        break;
                }
            default:
                break;
        }

        //if (spellProto->Effects[i].IsTargetingArea())
            //AreaEffect = true;
    }

    // Combined Spells with Both Over Time and Direct Damage
    if (overTime > 0 && CastingTime > 0 && DirectDamage)
    {
        // mainly for DoTs which are 3500 here otherwise
        uint32 OriginalCastTime = GetCastTime(dbcSpellCastTime.LookupEntry(spellProto->CastingTimeIndex));
        if (OriginalCastTime > 7000) OriginalCastTime = 7000;
        if (OriginalCastTime < 1500) OriginalCastTime = 1500;
        // Portion to Over Time
        float PtOT = (overTime / 15000.0f) / ((overTime / 15000.0f) + (OriginalCastTime / 3500.0f));

        if (damagetype == 2)
            CastingTime = uint32(CastingTime * PtOT);
        else if (PtOT < 1.0f)
            CastingTime  = uint32(CastingTime * (1 - PtOT));
        else
            CastingTime = 0;
    }

    // Area Effect Spells receive only half of bonus
    if (AreaEffect)
        CastingTime /= 2;

    // -5% of total per any additional effect
    for (uint8 i = 0; i < effects; ++i)
    {
        if (CastingTime > 175)
        {
            CastingTime -= 175;
        }
        else
        {
            CastingTime = 0;
            break;
        }
    }

    return CastingTime;
}

float Unit::CalculateLevelPenalty(SpellEntry* spellProto)
{
    if (spellProto->spellLevel <= 0 || spellProto->spellLevel >= spellProto->maxLevel)
        return 1.0f;

    float LvlPenalty = 0.0f;

    if (spellProto->spellLevel < 20)
        LvlPenalty = 20.0f - spellProto->spellLevel * 3.75f;
    float LvlFactor = (float(spellProto->spellLevel) + 6.0f) / float(getLevel());
    if (LvlFactor > 1.0f)
        LvlFactor = 1.0f;

    return AddPctF(LvlFactor, -LvlPenalty);
}

float Unit::GetModDamageFromCaster(uint64 casterguid, SpellEntry *proto, float ModTaken)
{
	float Mod = ModTaken;
	for(uint32 i = MAX_TOTAL_AURAS_START; i < MAX_TOTAL_AURAS_END; ++i)
	{
		if(m_auras[ i ] != NULL && m_auras[ i ]->GetSpellProto()->AppliesAura(271))
		{
			for(uint32 x = 0; x < MAX_SPELL_EFFECTS; ++x)
			{
				if(m_auras[i]->GetSpellProto()->EffectApplyAuraName[x] == 271)
				{
					Aura * aur = m_auras[i];
					if(aur->GetCasterGUID() != casterguid)
						continue;
					if (proto->SpellFamilyName != aur->GetSpellProto()->SpellFamilyName)
						return false;

					// Check EffectClassMask
					if (aur->GetSpellProto()->EffectSpellClassMask[i] & proto->SpellFamilyFlags)
						AddPctN(Mod, aur->GetModAmount(x));
				}
			}
		}
	}
    return Mod;
}

float Unit::GetMechanicDamageTakenPct(SpellEntry*proto, float ModTaken)
{
	float Mod = ModTaken;
	uint32 mechanicMask = proto->GetAllEffectsMechanicMask();
	for(uint32 i = MAX_TOTAL_AURAS_START; i < MAX_TOTAL_AURAS_END; ++i)
	{
		if(m_auras[ i ] != NULL && m_auras[ i ]->GetSpellProto()->AppliesAura(255))
		{
			for(uint32 x = 0; x < MAX_SPELL_EFFECTS; ++x)
			{
				if(m_auras[i]->GetSpellProto()->EffectApplyAuraName[x] == 255)
				{
					Aura * aur = m_auras[i];
					if(mechanicMask & uint32(1<<(aur->GetMod(i).m_miscValue)))
						AddPctN(Mod, aur->GetModAmount(x));
				}
			}
		}
	}
   return Mod;
}

int32 Unit::SpellBaseDamageBonus(uint32 schoolMask)
{
    int32 DoneAdvertisedBenefit = 0;

    // ..done
	for(uint32 i = MAX_TOTAL_AURAS_START; i < MAX_TOTAL_AURAS_END; ++i)
	{
		if(m_auras[ i ] != NULL)
		{
			Aura * aur = m_auras[ i ];
			for(uint32 x = 0; x < MAX_SPELL_EFFECTS; ++x)
			{
				if(aur->GetSpellProto()->EffectApplyAuraName[x] == SPELL_AURA_MOD_DAMAGE_DONE)
				{
					if(aur->GetMod(x).m_miscValue & schoolMask && aur->GetSpellProto()->EquippedItemClass == -1 
						&& aur->GetSpellProto()->EquippedItemInventoryTypeMask == 0)
						DoneAdvertisedBenefit += aur->GetModAmount(x);
				}
				if(IsPlayer())
				{
					if(aur->GetSpellProto()->EffectApplyAuraName[x] == 174)
					{
						if(aur->GetMod(x).m_miscValue & schoolMask)
						{
							Stats usedStat = Stats(aur->GetSpellProto()->EffectMiscValueB[x]);
							DoneAdvertisedBenefit += int32(CalculatePctN(GetStat(usedStat), aur->GetModAmount(x)));
						}
					}
					if(aur->GetSpellProto()->EffectApplyAuraName[x] == 237)
					{
						if(aur->GetMod(x).m_miscValue & schoolMask)
							DoneAdvertisedBenefit += int32(CalculatePctN(GetTotalAttackPowerValue(0), aur->GetModAmount(x)));
					}
				}
			}
		}
	}
	// Base value
    if (IsPlayer())
        DoneAdvertisedBenefit += TO_PLAYER(this)->GetPosDamageDoneMod(1);

    return DoneAdvertisedBenefit > 0 ? DoneAdvertisedBenefit : 0;
}

int32 Unit::SpellBaseDamageBonusForVictim(uint32 schoolMask, Unit* victim)
{
	int32 TakenAdvertisedBenefit = 0;
    /*uint32 creatureTypeMask = victim->GetCreatureTypeMask();

    
    // ..done (for creature type by mask) in taken
    AuraEffectList const& mDamageDoneCreature = GetAuraEffectsByType(SPELL_AURA_MOD_DAMAGE_DONE_CREATURE);
    for (AuraEffectList::const_iterator i = mDamageDoneCreature.begin(); i != mDamageDoneCreature.end(); ++i)
        if (creatureTypeMask & uint32((*i)->GetMiscValue()))
            TakenAdvertisedBenefit += (*i)->GetAmount();

    // ..taken
    AuraEffectList const& mDamageTaken = victim->GetAuraEffectsByType(SPELL_AURA_MOD_DAMAGE_TAKEN);
    for (AuraEffectList::const_iterator i = mDamageTaken.begin(); i != mDamageTaken.end(); ++i)
        if (((*i)->GetMiscValue() & schoolMask) != 0)
            TakenAdvertisedBenefit += (*i)->GetAmount();*/
	for(uint32 i = MAX_TOTAL_AURAS_START; i < MAX_TOTAL_AURAS_END; ++i)
	{
		if(m_auras[ i ] != NULL)
		{
			Aura * aur = m_auras[ i ];
			for(uint32 x = 0; x < MAX_SPELL_EFFECTS; ++x)
			{
				if(aur->GetSpellProto()->EffectApplyAuraName[x] == SPELL_AURA_MOD_DAMAGE_TAKEN)
				{
					if(aur->GetMod(x).m_miscValue & schoolMask)
						TakenAdvertisedBenefit += aur->GetModAmount(x);
				}
			}
		}
	}
    return TakenAdvertisedBenefit > 0 ? TakenAdvertisedBenefit : 0;
}
/*
uint32 Unit::CalculateSpellDamageTaken(Unit * victim, int32 damage, SpellEntry * spellInfo, uint8 attackType = BASE_ATTACK, bool crit = false)
{
    if (damage < 0)
        return;

    if (!victim || !victim->isAlive())
        return;

	uint32 damageSchoolMask = spellInfo->SchoolMask;
    //uint32 crTypeMask = victim->GetCreatureTypeMask();

    //if (IsDamageReducedByArmor(damageSchoolMask, spellInfo))
        //damage = CalcArmorReducedDamage(victim, damage, spellInfo, WeaponAttackType(attackType));

    /*bool blocked = false;
    // Per-school calc
    switch (spellInfo->DmgClass)
    {
        // Melee and Ranged Spells
        case SPELL_DAMAGE_CLASS_RANGED:
        case SPELL_DAMAGE_CLASS_MELEE:
        {
            // Physical Damage
            if (damageSchoolMask & SPELL_SCHOOL_MASK_NORMAL)
            {
                // Get blocked status
                blocked = isSpellBlocked(victim, spellInfo, attackType);
            }

            if (crit)
            {
                damageInfo->HitInfo |= SPELL_HIT_TYPE_CRIT;

                // Calculate crit bonus
                uint32 crit_bonus = damage;
                // Apply crit_damage bonus for melee spells
                if (Player* modOwner = GetSpellModOwner())
                    modOwner->ApplySpellMod(spellInfo->Id, SPELLMOD_CRIT_DAMAGE_BONUS, crit_bonus);
                damage += crit_bonus;

                // Apply SPELL_AURA_MOD_ATTACKER_RANGED_CRIT_DAMAGE or SPELL_AURA_MOD_ATTACKER_MELEE_CRIT_DAMAGE
                float critPctDamageMod = 0.0f;
                if (attackType == RANGED_ATTACK)
                    critPctDamageMod += victim->GetTotalAuraModifier(SPELL_AURA_MOD_ATTACKER_RANGED_CRIT_DAMAGE);
                else
                    critPctDamageMod += victim->GetTotalAuraModifier(SPELL_AURA_MOD_ATTACKER_MELEE_CRIT_DAMAGE);

                // Increase crit damage from SPELL_AURA_MOD_CRIT_DAMAGE_BONUS
                critPctDamageMod += (GetTotalAuraMultiplierByMiscMask(SPELL_AURA_MOD_CRIT_DAMAGE_BONUS, spellInfo->GetSchoolMask()) - 1.0f) * 100;

                // Increase crit damage from SPELL_AURA_MOD_CRIT_PERCENT_VERSUS
                critPctDamageMod += GetTotalAuraModifierByMiscMask(SPELL_AURA_MOD_CRIT_PERCENT_VERSUS, crTypeMask);

                if (critPctDamageMod != 0)
                    AddPctF(damage, critPctDamageMod);
            }

            // Spell weapon based damage CAN BE crit & blocked at same time
            if (blocked)
            {
                damageInfo->blocked = victim->GetShieldBlockValue();
                // double blocked amount if block is critical
                if (victim->isBlockCritical())
                    damageInfo->blocked += damageInfo->blocked;
                if (damage < int32(damageInfo->blocked))
                    damageInfo->blocked = uint32(damage);
                damage -= damageInfo->blocked;
            }

            if (attackType != RANGED_ATTACK)
                ApplyResilience(victim, NULL, &damage, crit, CR_CRIT_TAKEN_MELEE);
            else
                ApplyResilience(victim, NULL, &damage, crit, CR_CRIT_TAKEN_RANGED);
            break;
        }
        // Magical Attacks
        case SPELL_DAMAGE_CLASS_NONE:
        case SPELL_DAMAGE_CLASS_MAGIC:
        {
            // If crit add critical bonus
            if (crit)
            {
                damageInfo->HitInfo |= SPELL_HIT_TYPE_CRIT;
                damage = SpellCriticalDamageBonus(spellInfo, damage, victim);
            }

            ApplyResilience(victim, NULL, &damage, crit, CR_CRIT_TAKEN_SPELL);
            break;
        }
        default:
            break;
    }

    // Calculate absorb resist
    if (damage > 0)
    {
        CalcAbsorbResist(victim, damageSchoolMask, SPELL_DIRECT_DAMAGE, damage, &damageInfo->absorb, &damageInfo->resist, spellInfo);
        damage -= damageInfo->absorb + damageInfo->resist;
    }
    else
        damage = 0;

    return damage;
}*/
/*
bool Unit::IsDamageReducedByArmor(uint32 damageSchoolMask, SpellEntry* spellInfo = NULL, uint8 effIndex)
{
    // only physical spells damage gets reduced by armor
    if ((damageSchoolMask & SPELL_SCHOOL_MASK_NORMAL) == 0)
        return false;
    if (spellInfo)
    {
        // there are spells with no specific attribute but they have "ignores armor" in tooltip
        //if (spellInfo->AttributesCu & SPELL_ATTR0_CU_IGNORE_ARMOR)
            //return false;

        // bleeding effects are not reduced by armor
        if (effIndex != MAX_SPELL_EFFECTS)
        {
            if (spellInfo->EffectApplyAuraName[effIndex] == SPELL_AURA_PERIODIC_DAMAGE ||
                spellInfo->Effect[effIndex] == SPELL_EFFECT_SCHOOL_DAMAGE)
                if (spellInfo->GetEffectMechanicMask(effIndex) & (1<<15))
                    return false;
        }
    }
    return true;
}

uint32 Unit::CalcArmorReducedDamage(Unit* victim, const uint32 damage, SpellEntry* spellInfo, WeaponAttackType attackType)
{
/*    uint32 newdamage = 0;
    float armor = float(victim->GetArmor());

    // Ignore enemy armor by SPELL_AURA_MOD_TARGET_RESISTANCE aura
    armor += GetTotalAuraModifierByMiscMask(SPELL_AURA_MOD_TARGET_RESISTANCE, SPELL_SCHOOL_MASK_NORMAL);

    if (spellInfo)
        if (Player* modOwner = GetSpellModOwner())
            modOwner->ApplySpellMod(spellInfo->Id, SPELLMOD_IGNORE_ARMOR, armor);

    AuraEffectList const& ResIgnoreAurasAb = GetAuraEffectsByType(SPELL_AURA_MOD_ABILITY_IGNORE_TARGET_RESIST);
    for (AuraEffectList::const_iterator j = ResIgnoreAurasAb.begin(); j != ResIgnoreAurasAb.end(); ++j)
    {
        if ((*j)->GetMiscValue() & SPELL_SCHOOL_MASK_NORMAL
            && (*j)->IsAffectedOnSpell(spellInfo))
            armor = floor(AddPctN(armor, -(*j)->GetAmount()));
    }

    AuraEffectList const& ResIgnoreAuras = GetAuraEffectsByType(SPELL_AURA_MOD_IGNORE_TARGET_RESIST);
    for (AuraEffectList::const_iterator j = ResIgnoreAuras.begin(); j != ResIgnoreAuras.end(); ++j)
    {
        if ((*j)->GetMiscValue() & SPELL_SCHOOL_MASK_NORMAL)
            armor = floor(AddPctN(armor, -(*j)->GetAmount()));
    }

    // Apply Player CR_ARMOR_PENETRATION rating and buffs from stances\specializations etc.
    if (GetTypeId() == TYPEID_PLAYER)
    {
        float bonusPct = 0;
        AuraEffectList const& armorPenAuras = GetAuraEffectsByType(SPELL_AURA_MOD_ARMOR_PENETRATION_PCT);
        for (AuraEffectList::const_iterator itr = armorPenAuras.begin(); itr != armorPenAuras.end(); ++itr)
        {
            if ((*itr)->GetSpellInfo()->EquippedItemClass == -1)
            {
                if (!spellInfo || (*itr)->IsAffectedOnSpell(spellInfo) || (*itr)->GetMiscValue() & spellInfo->GetSchoolMask())
                    bonusPct += (*itr)->GetAmount();
                else if (!(*itr)->GetMiscValue() && !(*itr)->HasSpellClassMask())
                    bonusPct += (*itr)->GetAmount();
            }
            else
            {
                if (ToPlayer()->HasItemFitToSpellRequirements((*itr)->GetSpellInfo()))
                    bonusPct += (*itr)->GetAmount();
            }
        }

        float maxArmorPen = 0;
        if (victim->getLevel() < 60)
            maxArmorPen = float(400 + 85 * victim->getLevel());
        else
            maxArmorPen = 400 + 85 * victim->getLevel() + 4.5f * 85 * (victim->getLevel() - 59);

        // Cap armor penetration to this number
        maxArmorPen = std::min((armor + maxArmorPen) / 3, armor);
        // Figure out how much armor do we ignore
        float armorPen = CalculatePctF(maxArmorPen, bonusPct + ToPlayer()->GetRatingBonusValue(CR_ARMOR_PENETRATION));
        // Got the value, apply it
        armor -= std::min(armorPen, maxArmorPen);
    }

    if (armor < 0.0f)
        armor = 0.0f;

    float levelModifier = getLevel();
    if (levelModifier > 59)
        levelModifier = levelModifier + (4.5f * (levelModifier - 59));

    float tmpvalue = 0.1f * armor / (8.5f * levelModifier + 40);
    tmpvalue = tmpvalue / (1.0f + tmpvalue);

    if (tmpvalue < 0.0f)
        tmpvalue = 0.0f;
    if (tmpvalue > 0.75f)
        tmpvalue = 0.75f;

    newdamage = uint32(damage - (damage * tmpvalue));

    //return (newdamage > 1) ? newdamage : 1;
	return damage;
}
*/
uint32 Unit::SpellHealingBonus(Unit* victim, SpellEntry* spellProto, uint32 healamount, uint32 damagetype, uint32 stack)
{
    // For totems get healing bonus from owner (statue isn't totem in fact)
    if (GetTypeId() == TYPEID_UNIT && IsTotem())
		if (Unit* owner = TO<Summon*>(this)->GetOwner())
            return owner->SpellHealingBonus(victim, spellProto, healamount, damagetype, stack);

    // no bonus for heal potions/bandages
    if (spellProto->SpellFamilyName == 13)
        return healamount;

    // Healing Done
    // Taken/Done total percent damage auras
    float  DoneTotalMod = 1.0f;
    float  TakenTotalMod = 1.0f;
    int32  DoneTotal = 0;
    int32  TakenTotal = 0;

	for(uint32 i = MAX_TOTAL_AURAS_START; i < MAX_TOTAL_AURAS_END; ++i)
	{
		if(m_auras[ i ] != NULL)
		{
			Aura * aur = m_auras[ i ];
			for(uint32 x = 0; x < MAX_SPELL_EFFECTS; ++x)
			{
				if(aur->GetSpellProto()->EffectApplyAuraName[x] == SPELL_AURA_MOD_HEALING_DONE_PERCENT)
					AddPctN(DoneTotalMod, aur->GetModAmount(x));
			}
		}
	}
	/*
    // done scripted mod (take it from owner)
    Unit* owner = GetOwner() ? GetOwner() : this;
    AuraEffectList const& mOverrideClassScript= owner->GetAuraEffectsByType(SPELL_AURA_OVERRIDE_CLASS_SCRIPTS);
    for (AuraEffectList::const_iterator i = mOverrideClassScript.begin(); i != mOverrideClassScript.end(); ++i)
    {
        if (!(*i)->IsAffectedOnSpell(spellProto))
            continue;
        switch ((*i)->GetMiscValue())
        {
            case 4415: // Increased Rejuvenation Healing
            case 4953:
            case 3736: // Hateful Totem of the Third Wind / Increased Lesser Healing Wave / LK Arena (4/5/6) Totem of the Third Wind / Savage Totem of the Third Wind
                DoneTotal += (*i)->GetAmount();
                break;
            case   21: // Test of Faith
            case 6935:
            case 6918:
                if (victim->HealthBelowPct(50))
                    AddPctN(DoneTotalMod, (*i)->GetAmount());
                break;
            case 7798: // Glyph of Regrowth
            {
                if (victim->GetAuraEffect(SPELL_AURA_PERIODIC_HEAL, SPELLFAMILY_DRUID, 0x40, 0, 0))
                    AddPctN(DoneTotalMod, (*i)->GetAmount());
                break;
            }
            case 8477: // Nourish Heal Boost
            {
                int32 stepPercent = (*i)->GetAmount();
                int32 modPercent = 0;
                AuraApplicationMap const& victimAuras = victim->GetAppliedAuras();
                for (AuraApplicationMap::const_iterator itr = victimAuras.begin(); itr != victimAuras.end(); ++itr)
                {
                    Aura const* aura = itr->second->GetBase();
                    if (aura->GetCasterGUID() != GetGUID())
                        continue;
                    SpellInfo const* m_spell = aura->GetSpellInfo();
                    if (m_spell->SpellFamilyName != SPELLFAMILY_DRUID ||
                        !(m_spell->SpellFamilyFlags[1] & 0x00000010 || m_spell->SpellFamilyFlags[0] & 0x50))
                        continue;
                    modPercent += stepPercent * aura->GetStackAmount();
                }
                AddPctN(DoneTotalMod, modPercent);
                break;
            }
            case 7871: // Glyph of Lesser Healing Wave
            {
                if (victim->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_SHAMAN, 0, 0x00000400, 0, GetGUID()))
                    AddPctN(DoneTotalMod, (*i)->GetAmount());
                break;
            }
            default:
                break;
        }
    }
	*/
    // Taken/Done fixed damage bonus auras
	int32 DoneAdvertisedBenefit  = SpellBaseHealingBonus(spellProto->SchoolMask);
    int32 TakenAdvertisedBenefit = SpellBaseHealingBonusForVictim(spellProto->SchoolMask, victim);

    bool scripted = false;

    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
    {
        switch (spellProto->EffectApplyAuraName[i])
        {
            // These auras do not use healing coeff
            case SPELL_AURA_PERIODIC_LEECH:
            case SPELL_AURA_PERIODIC_HEALTH_FUNNEL:
                scripted = true;
                break;
        }
        if (spellProto->Effect[i] == SPELL_EFFECT_HEALTH_LEECH)
            scripted = true;
    }

    // Check for table values
	SpellEntry * bonusEntry = objmgr.GetRankOneSpell(spellProto->Id);
    float coeff = 0;
    float factorMod = 1.0f;
	if (bonusEntry->HasDBCoef())
    {
        if (damagetype == 2)
        {
			coeff = bonusEntry->OTspell_coef_override;
			if (bonusEntry->ap_dot_coef >= 0.0f)
				DoneTotal += int32(bonusEntry->ap_dot_coef * stack * GetTotalAttackPowerValue(
                    (spellProto->IsRangedWeaponSpell() && spellProto->DmgClass !=2)? RANGED_ATTACK : BASE_ATTACK));
        }
        else
        {
			coeff = bonusEntry->Dspell_coef_override;
			if (bonusEntry->ap_coef >= 0.0f)
				DoneTotal += int32(bonusEntry->ap_coef * stack * GetTotalAttackPowerValue(
                    (spellProto->IsRangedWeaponSpell() && spellProto->DmgClass !=2)? RANGED_ATTACK : BASE_ATTACK));
        }
    }
    else // scripted bonus
    {
        // Gift of the Naaru
        if (spellProto->SpellFamilyFlags[2] & 0x80000000 && spellProto->SpellIconID == 329)
        {
            scripted = true;
            int32 apBonus = int32(std::max(GetTotalAttackPowerValue(BASE_ATTACK), GetTotalAttackPowerValue(RANGED_ATTACK)));
            if (apBonus > DoneAdvertisedBenefit)
                DoneTotal += int32(apBonus * 0.22f); // 22% of AP per tick
            else
                DoneTotal += int32(DoneAdvertisedBenefit * 0.377f); // 37.7% of BH per tick
        }
        // Earthliving - 0.45% of normal hot coeff
        else if (spellProto->SpellFamilyName == 11 && spellProto->SpellFamilyFlags[1] & 0x80000)
            factorMod *= 0.45f;
        // Already set to scripted? so not uses healing bonus coefficient
        // No heal coeff for SPELL_DAMAGE_CLASS_NONE class spells by default
        else if (scripted || spellProto->DmgClass == 0)
        {
            scripted = true;
            coeff = 0.0f;
        }
    }

    // Default calculation
    if (DoneAdvertisedBenefit || TakenAdvertisedBenefit)
    {
		if ((!bonusEntry->HasDBCoef() && !scripted) || coeff < 0)
        {
            // Damage Done from spell damage bonus
			int32 CastingTime = !spellProto->IsChanneled() ? GetCastTime(dbcSpellCastTime.LookupEntry(spellProto->CastingTimeIndex)) : GetDuration(dbcSpellDuration.LookupEntry(spellProto->DurationIndex));
            // Damage over Time spells bonus calculation
            float DotFactor = 1.0f;
            if (damagetype == 2)
            {
                int32 DotDuration = GetDuration(dbcSpellDuration.LookupEntry(spellProto->DurationIndex));
                // 200% limit
                if (DotDuration > 0)
                {
                    if (DotDuration > 30000) DotDuration = 30000;
                    if (!spellProto->IsChanneled()) DotFactor = DotDuration / 15000.0f;
                    uint32 x = 0;
                    for (uint8 j = 0; j < MAX_SPELL_EFFECTS; j++)
                    {
                        if (spellProto->Effect[j] == SPELL_EFFECT_APPLY_AURA && (
                            spellProto->EffectApplyAuraName[j] == SPELL_AURA_PERIODIC_DAMAGE ||
                            spellProto->EffectApplyAuraName[j] == SPELL_AURA_PERIODIC_LEECH))
                        {
                            x = j;
                            break;
                        }
                    }
                    int32 DotTicks = 6;
					if (spellProto->EffectAmplitude[x] != 0)
                        DotTicks = DotDuration / spellProto->EffectAmplitude[x];
                    if (DotTicks)
                    {
                        DoneAdvertisedBenefit = DoneAdvertisedBenefit * int32(stack) / DotTicks;
                        TakenAdvertisedBenefit = TakenAdvertisedBenefit * int32(stack) / DotTicks;
                    }
                }
            }
            // Distribute Damage over multiple effects, reduce by AoE
            CastingTime = GetCastingTimeForBonus(spellProto, damagetype, CastingTime);
            // 50% for damage and healing spells for leech spells from damage bonus and 0% from healing
            for (uint8 j = 0; j < MAX_SPELL_EFFECTS; ++j)
            {
                if (spellProto->Effect[j] == SPELL_EFFECT_HEALTH_LEECH ||
                    (spellProto->Effect[j] == SPELL_EFFECT_APPLY_AURA && spellProto->EffectApplyAuraName[j] == SPELL_AURA_PERIODIC_LEECH))
                {
                    CastingTime /= 2;
                    break;
                }
            }
            // As wowwiki says: C = (Cast Time / 3.5) * 1.88 (for healing spells)
            coeff = (CastingTime / 3500.0f) * DotFactor * 1.88f;
        }

        factorMod *= CalculateLevelPenalty(spellProto) * stack;
        // level penalty still applied on Taken bonus - is it blizzlike?
        TakenTotal += int32(TakenAdvertisedBenefit * factorMod);
        if (Player* modOwner = GetSpellModOwner())
        {
            coeff *= 100.0f;
            modOwner->ApplySpellMod(spellProto->Id, SPELLMOD_BONUS_MULTIPLIER, coeff);
            coeff /= 100.0f;
        }
        DoneTotal += int32(DoneAdvertisedBenefit * coeff * factorMod);
    }

    // use float as more appropriate for negative values and percent applying
    float heal = (int32(healamount) + DoneTotal) * DoneTotalMod;
    // apply spellmod to Done amount
    if (Player* modOwner = GetSpellModOwner())
        modOwner->ApplySpellMod(spellProto->Id, damagetype == 2 ? SPELLMOD_DOT : SPELLMOD_DAMAGE, heal);

    // Nourish cast
    /*if (spellProto->SpellFamilyName == 7 && spellProto->SpellFamilyFlags[1] & 0x2000000)
    {
        // Rejuvenation, Regrowth, Lifebloom, or Wild Growth
        if (victim->GetAuraEffect(SPELL_AURA_PERIODIC_HEAL, 7, 0x50, 0x4000010, 0))
            // increase healing by 20%
            TakenTotalMod *= 1.2f;
    }*/

    // Taken mods

    // Tenacity increase healing % taken
	if (Aura * Tenacity = victim->FindAura(58549))
		AddPctN(TakenTotalMod, Tenacity->GetModAmount(0));

    // Healing taken percent
    float minval = (float)victim->GetMaxNegativeAuraModifier(SPELL_AURA_MOD_HEALING_PCT);
    if (minval)
        AddPctF(TakenTotalMod, minval);

    float maxval = (float)victim->GetMaxPositiveAuraModifier(SPELL_AURA_MOD_HEALING_PCT);
    if (maxval)
        AddPctF(TakenTotalMod, maxval);

    if (damagetype == 2)
    {
        // Healing over time taken percent
        float minval_hot = (float)victim->GetMaxNegativeAuraModifier(118);
        if (minval_hot)
            AddPctF(TakenTotalMod, minval_hot);

        float maxval_hot = (float)victim->GetMaxPositiveAuraModifier(118);
        if (maxval_hot)
            AddPctF(TakenTotalMod, maxval_hot);
    }
	for(uint32 i = MAX_TOTAL_AURAS_START; i < MAX_TOTAL_AURAS_END; ++i)
	{
		if(victim->m_auras[ i ] != NULL)
		{
			Aura * aur = victim->m_auras[ i ];
			for(uint32 x = 0; x < MAX_SPELL_EFFECTS; ++x)
			{
				if(aur->GetSpellProto()->EffectApplyAuraName[x] == 283)
				{
					if (spellProto->SpellFamilyName != aur->GetSpellProto()->SpellFamilyName)
						continue;

					// Check EffectClassMask
					if (aur->GetSpellProto()->EffectSpellClassMask[i] & spellProto->SpellFamilyFlags)
						AddPctN(TakenTotalMod, aur->GetModAmount(x));
				}
			}
		}
	}

    heal = (int32(heal) + TakenTotal) * TakenTotalMod;

    return uint32(std::max(heal, 0.0f));
}

int32 Unit::SpellBaseHealingBonus(uint32 schoolMask)
{
    int32 AdvertisedBenefit = 0;

 	for(uint32 i = MAX_TOTAL_AURAS_START; i < MAX_TOTAL_AURAS_END; ++i)
	{
		if(m_auras[ i ] != NULL)
		{
			Aura * aur = m_auras[ i ];
			for(uint32 x = 0; x < MAX_SPELL_EFFECTS; ++x)
			{
				if(aur->GetSpellProto()->EffectApplyAuraName[x] == SPELL_AURA_MOD_HEALING_DONE)
				{
					if (!aur->GetMod(x).m_miscValue || aur->GetMod(x).m_miscValue & schoolMask)
						AdvertisedBenefit += aur->GetModAmount(x);
				}
				if(IsPlayer())
				{
					if(aur->GetSpellProto()->EffectApplyAuraName[x] == 175)
					{
						Stats usedStat = Stats(aur->GetSpellProto()->EffectMiscValueB[x]);
						AdvertisedBenefit += int32(CalculatePctN(GetStat(usedStat), aur->GetModAmount(x)));
					}
					if(aur->GetSpellProto()->EffectApplyAuraName[x] == 238)
					{
						if(aur->GetMod(x).m_miscValue & schoolMask)
							AdvertisedBenefit += int32(CalculatePctN(GetTotalAttackPowerValue(0), aur->GetModAmount(x)));
					}
				}
			}
		}
	}
    if (IsPlayer())
        AdvertisedBenefit += TO_PLAYER(this)->GetPosDamageDoneMod(1);
    return AdvertisedBenefit;
}

int32 Unit::SpellBaseHealingBonusForVictim(uint32 schoolMask, Unit* victim)
{
    int32 AdvertisedBenefit = 0;
 	for(uint32 i = MAX_TOTAL_AURAS_START; i < MAX_TOTAL_AURAS_END; ++i)
	{
		if(m_auras[ i ] != NULL)
		{
			Aura * aur = m_auras[ i ];
			for(uint32 x = 0; x < MAX_SPELL_EFFECTS; ++x)
			{
				if(aur->GetSpellProto()->EffectApplyAuraName[x] == SPELL_AURA_MOD_HEALING)
				{
					if (aur->GetMod(x).m_miscValue & schoolMask)
						AdvertisedBenefit += aur->GetModAmount(x);
				}
			}
		}
	}
    return AdvertisedBenefit;
}

void Unit::Possess(Unit *pTarget, uint32 delay)
{
	Player * pThis = NULL;
	if(IsPlayer())
		pThis = TO_PLAYER(this);
	else // do not support creatures just yet
		return;
	if (!pThis)
		return;
	if(GetCharmedUnitGUID())
		return;

	Root();

	if(delay != 0)
	{
		sEventMgr.AddEvent(this, &Unit::Possess, pTarget, uint32(0), 0, delay, 1, 0);
		return;
	}
	if(pTarget == NULL)
	{
		Unroot();
		return;
	}

	pThis->m_CurrentCharm = pTarget->GetGUID();
	if(pTarget->IsCreature())
	{
		// unit-only stuff.
		pTarget->setAItoUse(false);
		pTarget->GetAIInterface()->StopMovement(0);
		pTarget->m_redirectSpellPackets = pThis;
	}

	m_noInterrupt++;
	SetCharmedUnitGUID(pTarget->GetGUID());
	pTarget->SetCharmedByGUID(GetGUID());
	pTarget->SetCharmTempVal(pTarget->GetFaction());
	pThis->SetFarsightTarget(pTarget->GetGUID());
	pTarget->SetFaction(GetFaction());
	pTarget->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED_CREATURE | UNIT_FLAG_PVP_ATTACKABLE);
	
	SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_LOCK_PLAYER);

	pThis->SetClientControl(pTarget, 1);
	// Below code does same as function above
	/* send "switch mover" packet */
	/*WorldPacket data1(SMSG_CLIENT_CONTROL_UPDATE, 10);
	data1 << pTarget->GetNewGUID() << uint8(1);
	pThis->GetSession()->SendPacket(&data1);*/

	/* update target faction set */
	pTarget->UpdateOppFactionSet();

	if(!(pTarget->IsPet() && TO< Pet* >(pTarget) == pThis->GetSummon()))
	{
		WorldPacket data(SMSG_PET_SPELLS, 4 * 4 + 20);
		pTarget->BuildPetSpellList(data);
		pThis->GetSession()->SendPacket(&data);
	}
}

void Unit::UnPossess()
{
	Player * pThis = NULL;
	if(IsPlayer())
		pThis = TO_PLAYER(this);
	else // creatures no support yet
		return;
	if (!pThis)
		return;
	if(!GetCharmedUnitGUID())
		return;

	Unit* pTarget = GetMapMgr()->GetUnit(GetCharmedUnitGUID());
	if(!pTarget)
		return;

	pThis->m_CurrentCharm = 0;

	pThis->SpeedCheatReset();

	if(pTarget->IsCreature())
	{
		// unit-only stuff.
		pTarget->setAItoUse(true);
		pTarget->m_redirectSpellPackets = 0;
	}

	m_noInterrupt--;
	pThis->SetFarsightTarget(0);
	SetCharmedUnitGUID(0);
	pTarget->SetCharmedByGUID(0);
	SetCharmedUnitGUID(0);

	RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_LOCK_PLAYER);
	pTarget->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED_CREATURE | UNIT_FLAG_PVP_ATTACKABLE);
	pTarget->SetFaction(pTarget->GetCharmTempVal());
	pTarget->UpdateOppFactionSet();

	pThis->SetClientControl(pTarget, 0);
	// Above function does same as below
	/* send "switch mover" packet */
	/*
	WorldPacket data(SMSG_CLIENT_CONTROL_UPDATE, 10);
	data << pTarget->GetNewGUID() << uint8(0);
	pThis->GetSession()->SendPacket(&data);*/

	if(!(pTarget->IsPet() && TO< Pet* >(pTarget) == pThis->GetSummon()))
		pThis->SendEmptyPetSpellList();

	Unroot();

	if(!pTarget->IsPet() && (pTarget->GetCreatedByGUID() == GetGUID()))
	{
		sEventMgr.AddEvent(TO< Object* >(pTarget), &Object::Delete, 0, 1, 1, 0);
		return;
	}
}

void Unit::SendBreakTarget()
{
	WorldPacket data(SMSG_BREAK_TARGET, sizeof(GetNewGUID()));
    data.append(GetNewGUID());
    SendMessageToSet(&data, false);
}

void Unit::setLevel(uint32 level)
{
	SetUInt32Value(UNIT_FIELD_LEVEL, level); 
	if(IsPlayer()) //I cheat
		TO< Player* >(this)->SetNextLevelXp(objmgr.GetXPToLevel(level));
};