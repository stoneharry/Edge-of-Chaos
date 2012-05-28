/*
* arcemu MMORPG Server
* Copyright (C) 2005-2007 arcemu Team <http://www.arcemuemu.com/>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*/

#include "StdAfx.h"

uint32 g_spellImplicitTargetFlags[MAX_IMPLICIT_TARGET_VALUE];

void InitImplicitTargetFlags()
{
	memset(g_spellImplicitTargetFlags, 0, sizeof(uint32) * MAX_IMPLICIT_TARGET_VALUE);

#define SET_TARGET_TYPE(ind, val) g_spellImplicitTargetFlags[ind] = val;

	SET_TARGET_TYPE(0, SPELL_TARGET_REQUIRE_ITEM | SPELL_TARGET_REQUIRE_GAMEOBJECT);
	SET_TARGET_TYPE(1, SPELL_TARGET_OBJECT_SELF);
	SET_TARGET_TYPE(2, SPELL_TARGET_AREA_SELF | SPELL_TARGET_REQUIRE_ATTACKABLE);
	SET_TARGET_TYPE(3, SPELL_TARGET_AREA_SELF | SPELL_TARGET_AREA_PARTY);
	SET_TARGET_TYPE(4, SPELL_TARGET_AREA_SELF | SPELL_TARGET_REQUIRE_FRIENDLY);
	SET_TARGET_TYPE(5, SPELL_TARGET_OBJECT_CURPET);
	SET_TARGET_TYPE(6, SPELL_TARGET_REQUIRE_ATTACKABLE);
	SET_TARGET_TYPE(7, SPELL_TARGET_OBJECT_SCRIPTED);
	SET_TARGET_TYPE(8, SPELL_TARGET_AREA | SPELL_TARGET_REQUIRE_ATTACKABLE);
	SET_TARGET_TYPE(15, SPELL_TARGET_AREA_SELF | SPELL_TARGET_REQUIRE_ATTACKABLE);
	SET_TARGET_TYPE(16, SPELL_TARGET_AREA | SPELL_TARGET_REQUIRE_ATTACKABLE);
	SET_TARGET_TYPE(17, SPELL_TARGET_AREA_SELF);
	SET_TARGET_TYPE(18, SPELL_TARGET_AREA_SELF | SPELL_TARGET_NO_OBJECT);
	SET_TARGET_TYPE(20, SPELL_TARGET_AREA_SELF | SPELL_TARGET_AREA_PARTY);
	SET_TARGET_TYPE(21, SPELL_TARGET_REQUIRE_FRIENDLY);
	SET_TARGET_TYPE(22, SPELL_TARGET_AREA_SELF);
	SET_TARGET_TYPE(23, SPELL_TARGET_REQUIRE_GAMEOBJECT);
	SET_TARGET_TYPE(24, SPELL_TARGET_AREA_CONE | SPELL_TARGET_REQUIRE_ATTACKABLE);
	SET_TARGET_TYPE(25, SPELL_TARGET_ANY_OBJECT);
	SET_TARGET_TYPE(26, SPELL_TARGET_REQUIRE_GAMEOBJECT | SPELL_TARGET_REQUIRE_ITEM);
	SET_TARGET_TYPE(27, SPELL_TARGET_OBJECT_PETOWNER);
	SET_TARGET_TYPE(28, SPELL_TARGET_AREA | SPELL_TARGET_REQUIRE_ATTACKABLE);
	SET_TARGET_TYPE(29, SPELL_TARGET_OBJECT_SELF | SPELL_TARGET_AREA_PARTY | SPELL_TARGET_AREA_SELF);
	SET_TARGET_TYPE(30, SPELL_TARGET_REQUIRE_FRIENDLY);
	SET_TARGET_TYPE(31, SPELL_TARGET_REQUIRE_FRIENDLY | SPELL_TARGET_AREA);
	//SET_TARGET_TYPE(32, SPELL_TARGET_OBJECT_SELF | SPELL_TARGET_AREA);
	SET_TARGET_TYPE(33, SPELL_TARGET_AREA_SELF | SPELL_TARGET_AREA_PARTY);
	SET_TARGET_TYPE(34, SPELL_TARGET_AREA_SELF | SPELL_TARGET_AREA_PARTY);
	SET_TARGET_TYPE(35, SPELL_TARGET_AREA_PARTY);
	SET_TARGET_TYPE(36, SPELL_TARGET_OBJECT_SCRIPTED);
	SET_TARGET_TYPE(37, SPELL_TARGET_AREA_SELF | SPELL_TARGET_AREA_PARTY | SPELL_TARGET_AREA_RAID);
	SET_TARGET_TYPE(39, SPELL_TARGET_OBJECT_SELF);
	SET_TARGET_TYPE(40, SPELL_TARGET_OBJECT_SCRIPTED);
	SET_TARGET_TYPE(41, SPELL_TARGET_AREA_SELF | SPELL_TARGET_FRONT_RIGHT);
	SET_TARGET_TYPE(42, SPELL_TARGET_AREA_SELF | SPELL_TARGET_BACK_RIGHT);
	SET_TARGET_TYPE(43, SPELL_TARGET_AREA_SELF | SPELL_TARGET_BACK_LEFT);
	SET_TARGET_TYPE(44, SPELL_TARGET_AREA_SELF | SPELL_TARGET_FRONT_LEFT);
	SET_TARGET_TYPE(45, SPELL_TARGET_AREA_CHAIN | SPELL_TARGET_REQUIRE_FRIENDLY);
	SET_TARGET_TYPE(46, SPELL_TARGET_OBJECT_SELF);
	SET_TARGET_TYPE(47, SPELL_TARGET_AREA_SELF | SPELL_TARGET_NO_OBJECT); //dont fill target map for this (fucks up some spell visuals)
	SET_TARGET_TYPE(48, SPELL_TARGET_AREA_SELF | SPELL_TARGET_BACK);
	SET_TARGET_TYPE(49, SPELL_TARGET_AREA_SELF | SPELL_TARGET_RIGHT);
	SET_TARGET_TYPE(50, SPELL_TARGET_AREA_SELF | SPELL_TARGET_LEFT);
	SET_TARGET_TYPE(51, SPELL_TARGET_AREA | SPELL_TARGET_REQUIRE_GAMEOBJECT | SPELL_TARGET_REQUIRE_ATTACKABLE );
	SET_TARGET_TYPE(52, SPELL_TARGET_AREA | SPELL_TARGET_REQUIRE_GAMEOBJECT | SPELL_TARGET_REQUIRE_ATTACKABLE );
	SET_TARGET_TYPE(53, SPELL_TARGET_AREA_CURTARGET | SPELL_TARGET_REQUIRE_ATTACKABLE | SPELL_TARGET_AREA);
	SET_TARGET_TYPE(54, SPELL_TARGET_AREA_CONE | SPELL_TARGET_REQUIRE_ATTACKABLE);
	SET_TARGET_TYPE(55, SPELL_TARGET_AREA);
	SET_TARGET_TYPE(56, SPELL_TARGET_AREA_SELF | SPELL_TARGET_AREA_RAID); //used by commanding shout, targets raid now
	SET_TARGET_TYPE(57, SPELL_TARGET_REQUIRE_FRIENDLY | SPELL_TARGET_AREA_RAID);
	SET_TARGET_TYPE(58, SPELL_TARGET_AREA_SELF | SPELL_TARGET_REQUIRE_FRIENDLY | SPELL_TARGET_AREA_RAID);
	SET_TARGET_TYPE(59, SPELL_TARGET_AREA_CONE | SPELL_TARGET_REQUIRE_FRIENDLY);
	SET_TARGET_TYPE(61, SPELL_TARGET_AREA_SELF | SPELL_TARGET_AREA_RAID | SPELL_TARGET_OBJECT_TARCLASS | SPELL_TARGET_REQUIRE_FRIENDLY);
	SET_TARGET_TYPE(63, SPELL_TARGET_AREA | SPELL_TARGET_ANY_OBJECT);
	SET_TARGET_TYPE(64, SPELL_TARGET_AREA_CURTARGET | SPELL_TARGET_AREA);
	SET_TARGET_TYPE(65, SPELL_TARGET_AREA_CURTARGET | SPELL_TARGET_BACK);
	SET_TARGET_TYPE(66, SPELL_TARGET_AREA_CURTARGET | SPELL_TARGET_RIGHT);
	SET_TARGET_TYPE(67, SPELL_TARGET_AREA_CURTARGET | SPELL_TARGET_LEFT);
	SET_TARGET_TYPE(68, SPELL_TARGET_AREA_CURTARGET | SPELL_TARGET_FRONT_RIGHT);
	SET_TARGET_TYPE(69, SPELL_TARGET_AREA_CURTARGET | SPELL_TARGET_BACK_RIGHT);
	SET_TARGET_TYPE(70, SPELL_TARGET_AREA_CURTARGET | SPELL_TARGET_BACK_LEFT);
	SET_TARGET_TYPE(71, SPELL_TARGET_AREA_CURTARGET | SPELL_TARGET_FRONT_LEFT);
	SET_TARGET_TYPE(72, SPELL_TARGET_AREA_SELF | SPELL_TARGET_AREA_RANDOM);
	SET_TARGET_TYPE(73, SPELL_TARGET_AREA_RANDOM);
	SET_TARGET_TYPE(74, SPELL_TARGET_AREA_CURTARGET | SPELL_TARGET_AREA_RANDOM);
	SET_TARGET_TYPE(75, SPELL_TARGET_AREA_CURTARGET | SPELL_TARGET_AREA_RANDOM);
	SET_TARGET_TYPE(76, SPELL_TARGET_ANY_OBJECT);
	SET_TARGET_TYPE(77, SPELL_TARGET_ANY_OBJECT);
	SET_TARGET_TYPE(78, SPELL_TARGET_AREA);
	SET_TARGET_TYPE(79, SPELL_TARGET_AREA | SPELL_TARGET_BACK);
	SET_TARGET_TYPE(80, SPELL_TARGET_AREA | SPELL_TARGET_RIGHT);
	SET_TARGET_TYPE(81, SPELL_TARGET_AREA | SPELL_TARGET_LEFT);
	SET_TARGET_TYPE(82, SPELL_TARGET_AREA | SPELL_TARGET_FRONT_RIGHT);
	SET_TARGET_TYPE(83, SPELL_TARGET_AREA | SPELL_TARGET_BACK_RIGHT);
	SET_TARGET_TYPE(84, SPELL_TARGET_AREA | SPELL_TARGET_BACK_LEFT);
	SET_TARGET_TYPE(85, SPELL_TARGET_AREA | SPELL_TARGET_FRONT_LEFT);
	SET_TARGET_TYPE(86, SPELL_TARGET_AREA_RANDOM);
	SET_TARGET_TYPE(87, SPELL_TARGET_AREA);
	SET_TARGET_TYPE(88, SPELL_TARGET_AREA);
	SET_TARGET_TYPE(89, SPELL_TARGET_AREA);
	SET_TARGET_TYPE(90, SPELL_TARGET_OBJECT_CURCRITTER);
	SET_TARGET_TYPE(91, SPELL_TARGET_AREA);
	SET_TARGET_TYPE(92, SPELL_TARGET_OBJECT_PETOWNER);
	SET_TARGET_TYPE(93, SPELL_TARGET_AREA_CURTARGET);
	SET_TARGET_TYPE(94, SPELL_TARGET_OBJECT_SELF);
	SET_TARGET_TYPE(95, SPELL_TARGET_OBJECT_SELF);
	SET_TARGET_TYPE(96, SPELL_TARGET_OBJECT_SELF);
	SET_TARGET_TYPE(97, SPELL_TARGET_OBJECT_SELF);
	SET_TARGET_TYPE(98, SPELL_TARGET_OBJECT_SELF);
	SET_TARGET_TYPE(99, SPELL_TARGET_OBJECT_SELF);
	SET_TARGET_TYPE(100, SPELL_TARGET_OBJECT_SELF);
	SET_TARGET_TYPE(101, SPELL_TARGET_OBJECT_SELF);
	SET_TARGET_TYPE(102, SPELL_TARGET_OBJECT_SELF);
	SET_TARGET_TYPE(103, SPELL_TARGET_OBJECT_SELF);
	SET_TARGET_TYPE(104, SPELL_TARGET_REQUIRE_ATTACKABLE | SPELL_TARGET_AREA_CONE);
	SET_TARGET_TYPE(106, SPELL_TARGET_AREA_SELF);
	SET_TARGET_TYPE(108, SPELL_TARGET_REQUIRE_GAMEOBJECT | SPELL_TARGET_AREA_CONE);
	SET_TARGET_TYPE(110, SPELL_TARGET_AREA);

#undef SET_TARGET_TYPE
}

void Spell::FillTargetMap(uint32 i)
{
	//Spell::prepare() has already a m_caster->IsInWorld() check so if now the caster is no more in world something bad happened.
	ARCEMU_ASSERT(m_caster->IsInWorld());

	uint32 TargetType = 0;
	TargetType |= GetTargetType(m_spellInfo->EffectImplicitTargetA[i], i);

	//never get info from B if it is 0 :P
	if(m_spellInfo->EffectImplicitTargetB[i] != 0)
		TargetType |= GetTargetType(m_spellInfo->EffectImplicitTargetB[i], i);

	if(TargetType & SPELL_TARGET_NOT_IMPLEMENTED)
		return;
	if(TargetType & SPELL_TARGET_NO_OBJECT)  //summon spells that appear infront of caster
	{
		HandleTargetNoObject();
		return;
	}
	if(m_targets.HasTraj())
		SelectTrajectoryTargets();

	//always add this guy :P
	if(!(TargetType & (SPELL_TARGET_AREA | SPELL_TARGET_AREA_SELF | SPELL_TARGET_AREA_CURTARGET | SPELL_TARGET_AREA_CONE | SPELL_TARGET_OBJECT_SELF | SPELL_TARGET_OBJECT_PETOWNER)))
	{
		Object* target = m_caster->GetMapMgr()->_GetObject(m_targets.m_unitTarget);
		AddTarget(i, TargetType, target);
	}

	if(TargetType & SPELL_TARGET_OBJECT_SELF)
		AddTarget(i, TargetType, m_caster);
	if(TargetType & (SPELL_TARGET_AREA | SPELL_TARGET_AREA_SELF))  //targetted aoe
		AddAOETargets(i, TargetType, GetRadius(i), m_spellInfo->MaxAffectedTargets);
	//TODO: arcemu, doesn't support summon slots?
	/*if (TargetType & SPELL_TARGET_OBJECT_CURTOTEMS && u_caster != NULL)
		for (uint32 i=1; i<5; ++i) //totem slots are 1, 2, 3, 4
			AddTarget(i, TargetType, u_caster->m_summonslot[i]);*/
	if(TargetType & SPELL_TARGET_OBJECT_CURPET && p_caster != NULL)
		AddTarget(i, TargetType, p_caster->GetSummon());
	if(TargetType & SPELL_TARGET_OBJECT_PETOWNER)
	{
		uint64 guid = m_targets.m_unitTarget;
		if(GET_TYPE_FROM_GUID(guid) == HIGHGUID_TYPE_PET)
		{
			Pet* p = m_caster->GetMapMgr()->GetPet(GET_LOWGUID_PART(guid));

			if(p != NULL)
				AddTarget(i, TargetType, p->GetPetOwner());
		}
		else
		{
			Object * tarp = m_caster->GetMapMgrObject(guid);
			if(Object * owner = tarp->GetPlayerOwner())
				AddTarget(i, TargetType, owner);
		}
	}
	//targets party, not raid
	if((TargetType & SPELL_TARGET_AREA_PARTY) && !(TargetType & SPELL_TARGET_AREA_RAID))
	{
		if(p_caster == NULL && !m_caster->IsPet() && (!m_caster->IsCreature() || !m_caster->IsTotem()))
			AddAOETargets(i, TargetType, GetRadius(i), m_spellInfo->MaxAffectedTargets); //npcs
		else
			AddPartyTargets(i, TargetType, GetRadius(i), m_spellInfo->MaxAffectedTargets); //players/pets/totems
	}
	if(TargetType & SPELL_TARGET_AREA_RAID)
	{
		if(p_caster == NULL && !m_caster->IsPet() && (!m_caster->IsCreature() || !m_caster->IsTotem()))
			AddAOETargets(i, TargetType, GetRadius(i), m_spellInfo->MaxAffectedTargets); //npcs
		else
			AddRaidTargets(i, TargetType, GetRadius(i), m_spellInfo->MaxAffectedTargets, (TargetType & SPELL_TARGET_AREA_PARTY) ? true : false); //players/pets/totems
	}
	if(TargetType & SPELL_TARGET_AREA_CHAIN)
		AddChainTargets(i, TargetType, GetRadius(i), m_spellInfo->MaxAffectedTargets);
	//target cone
	if(TargetType & SPELL_TARGET_AREA_CONE)
		AddConeTargets(i, TargetType, GetRadius(i), m_spellInfo->MaxAffectedTargets);

	if(TargetType & SPELL_TARGET_OBJECT_SCRIPTED)
		AddScriptedOrSpellFocusTargets(i, TargetType, GetRadius(i), m_spellInfo->MaxAffectedTargets);
}

void Spell::AddScriptedOrSpellFocusTargets(uint32 i, uint32 TargetType, float r, uint32 maxtargets)
{
	for(std::set< Object* >::iterator itr = m_caster->GetInRangeSetBegin(); itr != m_caster->GetInRangeSetEnd(); ++itr)
	{
		Object* o = *itr;

		if(!o->IsGameObject())
			continue;

		GameObject* go = TO_GAMEOBJECT(o);

		if(go->GetInfo()->SpellFocus == m_spellInfo->RequiresSpellFocus)
		{

			if(!m_caster->isInRange(go, r))
				continue;

			bool success = AddTarget(i, TargetType, go);

			if(success)
				return;
		}
	}
}

void Spell::AddConeTargets(uint32 i, uint32 TargetType, float r, uint32 maxtargets)
{
	TargetsList* list = &m_targetUnits[i];
	ObjectSet::iterator itr;
	for(itr = m_caster->GetInRangeSetBegin(); itr != m_caster->GetInRangeSetEnd(); itr++)
	{
		if(!((*itr)->IsUnit()) || !TO_UNIT((*itr))->isAlive())
			continue;
		//is Creature in range
		if(m_caster->isInRange(TO_UNIT(*itr), GetRadius(i)))
		{
			if(m_spellInfo->cone_width ? m_caster->isInArc(TO_UNIT(*itr), m_spellInfo->cone_width) : m_caster->isInFront(TO_UNIT(*itr)))  // !!! is the target within our cone ?
			{
				AddTarget(i, TargetType, (*itr));
			}
		}
		if(maxtargets != 0 && list->size() >= maxtargets)
			return;
	}
}

void Spell::AddChainTargets(uint32 i, uint32 TargetType, float r, uint32 maxtargets)
{
	if(!m_caster->IsInWorld())
		return;

	Object* targ = m_caster->GetMapMgr()->_GetObject(m_targets.m_unitTarget);

	if(targ == NULL)
		return;

	TargetsList* list = &m_targetUnits[i];

	//if selected target is party member, then jumps on party
	Unit* firstTarget = NULL;

	if(targ->IsUnit())
		firstTarget = TO_UNIT(targ);
	else
		firstTarget = u_caster;

	bool RaidOnly = false;
	float range = GetMaxRange(dbcSpellRange.LookupEntry(m_spellInfo->rangeIndex));//this is probably wrong,
	Player* casterFrom = TO< Player* >(u_caster->GetPlayerOwner());
	if(casterFrom)
		casterFrom->ApplySpellMod(m_spellInfo->Id, SPELLMOD_RANGE, range, NULL);
	//this is cast distance, not searching distance
	range *= range;

	//is this party only?
	Player* pfirstTargetFrom = TO< Player* >(firstTarget->GetPlayerOwner());

	if(casterFrom != NULL && pfirstTargetFrom != NULL && casterFrom->GetGroup() == pfirstTargetFrom->GetGroup())
		RaidOnly = true;

	uint32 jumps = m_spellInfo->EffectChainTarget[i];

	//range
	range /= jumps; //hacky, needs better implementation!

	if(m_spellInfo->SpellFamilyFlags && u_caster != NULL)
	{
		if(Player * p = u_caster->GetSpellModOwner())
			p->ApplySpellMod(m_spellInfo->Id, SPELLMOD_JUMP_TARGETS, jumps);
	}

	AddTarget(i, TargetType, firstTarget);

	if(jumps <= 1 || list->size() == 0) //1 because we've added the first target, 0 size if spell is resisted
		return;

	ObjectSet::iterator itr;
	for(itr = firstTarget->GetInRangeSetBegin(); itr != firstTarget->GetInRangeSetEnd(); itr++)
	{
		if(!(*itr)->IsUnit() || !TO_UNIT((*itr))->isAlive())
			continue;

		if(RaidOnly && !pfirstTargetFrom->InRaid(TO_UNIT(*itr)))
			continue;

		//healing spell, full health target = NONO
		if(IsHealingSpell(m_spellInfo) && TO_UNIT(*itr)->GetHealthPct() == 100)
			continue;

		size_t oldsize;

		if(IsInrange(firstTarget->GetPositionX(), firstTarget->GetPositionY(), firstTarget->GetPositionZ(), (*itr), range))
		{
			oldsize = list->size();
			AddTarget(i, TargetType, (*itr));
			if(list->size() == oldsize || list->size() >= jumps) //either out of jumps or a resist
				return;
		}
	}
}

void Spell::AddPartyTargets(uint32 i, uint32 TargetType, float r, uint32 maxtargets)
{
	Object* u = m_caster->GetMapMgr()->_GetObject(m_targets.m_unitTarget);
	if(u == NULL)
		u = m_caster;
	Player* p = TO< Player* >(u->GetPlayerOwner());

	if(p == NULL || u_caster == NULL)
		return;

	AddTarget(i, TargetType, p);

	ObjectSet::iterator itr;
	for(itr = u->GetInRangeSetBegin(); itr != u->GetInRangeSetEnd(); itr++)
	{
		if(!(*itr)->IsUnit() || !TO_UNIT(*itr)->isAlive())
			continue;

		//only affect players and pets
		if(!(*itr)->IsPlayer() && !(*itr)->IsPet())
			continue;

		if(!p->InParty(TO_UNIT(*itr)))
			continue;

		if(u->CalcDistance(*itr) > r)
			continue;

		AddTarget(i, TargetType, (*itr));
	}
}

void Spell::AddRaidTargets(uint32 i, uint32 TargetType, float r, uint32 maxtargets, bool partylimit)
{
	Object* u = m_caster->GetMapMgr()->_GetObject(m_targets.m_unitTarget);
	if(u == NULL)
		u = m_caster;
	Player* p = TO< Player* >(u->GetPlayerOwner());

	if(p == NULL || u_caster == NULL)
		return;

	AddTarget(i, TargetType, p);

	ObjectSet::iterator itr;
	for(itr = u->GetInRangeSetBegin(); itr != u->GetInRangeSetEnd(); itr++)
	{
		if(!(*itr)->IsUnit() || !TO_UNIT(*itr)->isAlive())
			continue;

		//only affect players and pets
		if(!(*itr)->IsPlayer() && !(*itr)->IsPet())
			continue;

		if(!p->InRaid(TO_UNIT(*itr)))
			continue;

		if(u->CalcDistance(*itr) > r)
			continue;

		AddTarget(i, TargetType, (*itr));
	}
}

void Spell::AddAOETargets(uint32 i, uint32 TargetType, float r, uint32 maxtargets)
{
	LocationVector source;

	//cant do raid/party stuff here, seperate functions for it
	if(TargetType & (SPELL_TARGET_AREA_PARTY | SPELL_TARGET_AREA_RAID) && !(p_caster == NULL && !m_caster->IsPet() && (!m_caster->IsCreature() || !m_caster->IsTotem())))
		return;

	Object* tarobj = m_caster->GetMapMgr()->_GetObject(m_targets.m_unitTarget);

	if(TargetType & SPELL_TARGET_AREA_SELF)
		source = m_caster->GetPosition();
	else if(TargetType & SPELL_TARGET_AREA_CURTARGET && tarobj != NULL)
		source = tarobj->GetPosition();
	else
	{
		m_targets.m_targetMask |= TARGET_FLAG_DEST_LOCATION;
		source.x = m_targets.m_destX;
		source.y = m_targets.m_destY;
		source.z = m_targets.m_destZ;
	}

	//caster might be in the aoe LOL
	if(m_caster->CalcDistance(source) <= r)
		AddTarget(i, TargetType, m_caster);

	TargetsList* t = &m_targetUnits[i];

	for(ObjectSet::iterator itr = m_caster->GetInRangeSetBegin(); itr != m_caster->GetInRangeSetEnd(); ++itr)
	{
		if(maxtargets != 0 && t->size() >= maxtargets)
			break;

		float dist = (*itr)->CalcDistance(source);
		if(dist <= r)
			AddTarget(i, TargetType, (*itr));
	}
}

bool Spell::AddTarget(uint32 i, uint32 TargetType, Object* obj)
{
	TargetsList* t = &m_targetUnits[i];

	if(obj == NULL || !obj->IsInWorld())
		return false;

	//GO target, not item
	if((TargetType & SPELL_TARGET_REQUIRE_GAMEOBJECT) && !(TargetType & SPELL_TARGET_REQUIRE_ITEM) && !obj->IsGameObject())
		return false;

	//target go, not able to target go
	if(obj->IsGameObject() && !(TargetType & SPELL_TARGET_OBJECT_SCRIPTED) && !(TargetType & SPELL_TARGET_REQUIRE_GAMEOBJECT) && !m_triggeredSpell)
		return false;
	//target item, not able to target item
	if(obj->IsItem() && !(TargetType & SPELL_TARGET_REQUIRE_ITEM) && !m_triggeredSpell)
		return false;

	if(u_caster != NULL && u_caster->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_9) && ((obj->IsPlayer() || obj->IsPet()) || (p_caster != NULL || m_caster->IsPet())))
		return false;

	if(TargetType & SPELL_TARGET_REQUIRE_FRIENDLY && !isFriendly(m_caster, obj))
		return false;
	if(TargetType & SPELL_TARGET_REQUIRE_ATTACKABLE && !isAttackable(m_caster, obj, false))
		return false;
	if(TargetType & SPELL_TARGET_OBJECT_TARCLASS)
	{
		Object* originaltarget = m_caster->GetMapMgr()->_GetObject(m_targets.m_unitTarget);

		if(originaltarget == NULL || (originaltarget->IsPlayer() && obj->IsPlayer() && TO_PLAYER(originaltarget)->getClass() != TO_PLAYER(obj)->getClass()) || (originaltarget->IsPlayer() && !obj->IsPlayer()) || (!originaltarget->IsPlayer() && obj->IsPlayer()))
			return false;
	}
	if(TargetType & SPELL_TARGET_OBJECT_CURPET && !obj->IsPet())
		return false;
	if(TargetType & (SPELL_TARGET_AREA | SPELL_TARGET_AREA_SELF | SPELL_TARGET_AREA_CURTARGET | SPELL_TARGET_AREA_CONE | SPELL_TARGET_AREA_PARTY | SPELL_TARGET_AREA_RAID) && ((obj->IsUnit() && !TO_UNIT(obj)->isAlive()) || (obj->IsCreature() && obj->IsTotem())))
		return false;

	uint8 hitresult = (TargetType & SPELL_TARGET_REQUIRE_ATTACKABLE && obj->IsUnit()) ? DidHit(i, TO_UNIT(obj)) : SPELL_DID_HIT_SUCCESS;
	if(hitresult != SPELL_DID_HIT_SUCCESS)
	{
		uint8 extended = 0;
		if(hitresult == SPELL_DID_HIT_REFLECT && u_caster != NULL)
		{
			//for checks
			Unit* tmp = u_caster;
			u_caster = TO_UNIT(obj);
			extended = DidHit(i, tmp);
			u_caster = tmp;
		}
		ModeratedTargets.push_back(SpellTargetMod(obj->GetGUID(), hitresult));
		return false;
	}
	else
	{
		//check target isnt already in
		for(TargetsList::iterator itr = m_targetUnits[i].begin(); itr != m_targetUnits[i].end(); ++itr)
		{
			if(obj->GetGUID() == *itr)
				return false;
		}
		t->push_back(obj->GetGUID());
	}

	//final checks, require line of sight unless range/radius is 50000 yards
	SpellRange* r = dbcSpellRange.LookupEntry(m_spellInfo->rangeIndex);
	if(sWorld.Collision && r->maxRange < 50000 && GetRadius(i) < 50000 && !obj->IsItem())
	{
		float x = m_caster->GetPositionX(), y = m_caster->GetPositionY(), z = m_caster->GetPositionZ() + 0.5f;

		//are we using a different location?
		if(TargetType & SPELL_TARGET_AREA)
		{
			x = m_targets.m_destX;
			y = m_targets.m_destY;
			z = m_targets.m_destZ;
		}
		else if(TargetType & SPELL_TARGET_AREA_CHAIN)
		{
			//TODO: Add support for this in arcemu
			/*Object* lasttarget = NULL;
			if (m_orderedObjects.size() > 0)
			{
				lasttarget = m_caster->GetMapMgr()->_GetObject(m_orderedObjects[m_orderedObjects.size() - 1]);
				if (lasttarget != NULL)
				{
					x = lasttarget->GetPositionX();
					y = lasttarget->GetPositionY();
					z = lasttarget->GetPositionZ();
				}
			}*/
		}

		if(!(GetProto()->AttributesEx2 & SPELL_ATTR2_CAN_TARGET_NOT_IN_LOS) && !CollideInterface.CheckLOS(m_caster->GetMapId(), x, y, z + 2, obj->GetPositionX(), obj->GetPositionY(), obj->GetPositionZ() + 2))
			return false;
	}



	return true;
}

bool Spell::GenerateTargets(SpellCastTargets* t)
{
	if(u_caster == NULL || u_caster->GetAIInterface() == NULL || !u_caster->IsInWorld())
		return false;

	bool result = false;

	for(uint32 i = 0; i < 3; ++i)
	{
		if(m_spellInfo->Effect[i] == 0)
			continue;
		uint32 TargetType = 0;
		TargetType |= GetTargetType(m_spellInfo->EffectImplicitTargetA[i], i);

		//never get info from B if it is 0 :P
		if(m_spellInfo->EffectImplicitTargetB[i] != 0)
			TargetType |= GetTargetType(m_spellInfo->EffectImplicitTargetB[i], i);

		if(TargetType & (SPELL_TARGET_OBJECT_SELF | SPELL_TARGET_AREA_PARTY | SPELL_TARGET_AREA_RAID))
		{
			t->m_targetMask |= TARGET_FLAG_UNIT;
			t->m_unitTarget = u_caster->GetGUID();
			result = true;
		}

		if(TargetType & SPELL_TARGET_NO_OBJECT)
		{
			t->m_targetMask = 0;
			result = true;
		}

		if(!(TargetType & (SPELL_TARGET_AREA | SPELL_TARGET_AREA_SELF | SPELL_TARGET_AREA_CURTARGET | SPELL_TARGET_AREA_CONE)))
		{

			if(TargetType & SPELL_TARGET_ANY_OBJECT)
			{
				if(u_caster->GetUInt64Value(UNIT_FIELD_TARGET))
				{
					//generate targets for things like arcane missiles trigger, tame pet, etc
					Object* target = u_caster->GetMapMgr()->_GetObject(u_caster->GetUInt64Value(UNIT_FIELD_TARGET));
					if(target != NULL)
					{
						if(target->IsUnit())
						{
							t->m_targetMask |= TARGET_FLAG_UNIT;
							t->m_unitTarget = target->GetGUID();
							result = true;
						}
						else if(target->IsGameObject())
						{
							t->m_targetMask |= TARGET_FLAG_GAMEOBJECT;
							t->m_unitTarget = target->GetGUID();
							result = true;
						}
					}
					result = true;
				}
			}

			if(TargetType & SPELL_TARGET_REQUIRE_ATTACKABLE)
			{
				if(u_caster->GetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT))
				{
					//generate targets for things like arcane missiles trigger, tame pet, etc
					Object* target = u_caster->GetMapMgr()->_GetObject(u_caster->GetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT));
					if(target != NULL)
					{
						if(target->IsUnit())
						{
							t->m_targetMask |= TARGET_FLAG_UNIT;
							t->m_unitTarget = target->GetGUID();
							result = true;
						}
						else if(target->IsGameObject())
						{
							t->m_targetMask |= TARGET_FLAG_GAMEOBJECT;
							t->m_unitTarget = target->GetGUID();
							result = true;
						}
					}
				}
				else if(u_caster->GetUInt64Value(UNIT_FIELD_TARGET))
				{
					//generate targets for things like arcane missiles trigger, tame pet, etc
					Object* target = u_caster->GetMapMgr()->_GetObject(u_caster->GetUInt64Value(UNIT_FIELD_TARGET));
					if(target != NULL)
					{
						if(target->IsUnit())
						{
							t->m_targetMask |= TARGET_FLAG_UNIT;
							t->m_unitTarget = target->GetGUID();
							result = true;
						}
						else if(target->IsGameObject())
						{
							t->m_targetMask |= TARGET_FLAG_GAMEOBJECT;
							t->m_unitTarget = target->GetGUID();
							result = true;
						}
					}
					result = true;
				}
				else if(u_caster->IsCreature() && u_caster->IsTotem())
				{
					Unit* target = u_caster->GetMapMgr()->GetUnit(GetSinglePossibleEnemy(i));
					if(target != NULL)
					{
						t->m_targetMask |= TARGET_FLAG_UNIT;
						t->m_unitTarget = target->GetGUID();
					}
				}
			}

			if(TargetType & SPELL_TARGET_REQUIRE_FRIENDLY)
			{
				Unit* target = u_caster->GetMapMgr()->GetUnit(GetSinglePossibleFriend(i));
				if(target != NULL)
				{
					t->m_targetMask |= TARGET_FLAG_UNIT;
					t->m_unitTarget = target->GetGUID();
					result = true;
				}
				else
				{
					t->m_targetMask |= TARGET_FLAG_UNIT;
					t->m_unitTarget = u_caster->GetGUID();
					result = true;
				}
			}
		}
		float dist = GetRadius(i);
		float angle = GetDirectionAngle(TargetType);
		float objSize = m_caster->GetObjectSize();

		if (dist < objSize)
			dist = objSize;
		if(TargetType & SPELL_TARGET_AREA_RANDOM)
		{
			//we always use radius(0) for some reason
			uint8 attempts = 0;
			do
			{
				//prevent deadlock
				++attempts;
				if(attempts > 10)
					return false;
				if(t->m_targetMask & TARGET_FLAG_DEST_LOCATION)
				{
					t->m_destX = t->m_destX + (cosf(angle) * dist);
					t->m_destY = t->m_destY + (sinf(angle) * dist);
					t->m_destZ = m_caster->GetMapMgr()->GetLandHeight(t->m_destX, t->m_destY, t->m_destX + 2.0f);
					t->m_targetMask = TARGET_FLAG_DEST_LOCATION;
				}
				else
				{
					t->m_destX = m_caster->GetPositionX() + (cosf(angle) * dist);
					t->m_destY = m_caster->GetPositionY() + (sinf(angle) * dist);
					t->m_destZ = m_caster->GetMapMgr()->GetLandHeight(t->m_destX, t->m_destY, m_caster->GetPositionZ() + 2.0f);
					t->m_targetMask = TARGET_FLAG_DEST_LOCATION;
				}
			}
			while(sWorld.Collision && !(GetProto()->AttributesEx2 & SPELL_ATTR2_CAN_TARGET_NOT_IN_LOS) && !CollideInterface.CheckLOS(m_caster->GetMapId(), m_caster->GetPositionX(), m_caster->GetPositionY(), m_caster->GetPositionZ(), t->m_destX, t->m_destY, t->m_destZ));
			result = true;
		}
		else if(TargetType & SPELL_TARGET_AREA)  //targetted aoe
		{
			//spells like blizzard, rain of fire
			if(u_caster->GetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT))
			{
				Object* target = u_caster->GetMapMgr()->_GetObject(u_caster->GetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT));
				if(target != NULL)
				{
					t->m_targetMask |= TARGET_FLAG_DEST_LOCATION | TARGET_FLAG_UNIT;
					t->m_destX = target->GetPositionX() + (cosf(angle) * dist);
					t->m_destY = target->GetPositionY() + (sinf(angle) * dist);
					t->m_destZ = target->GetPositionZ();
				}
				result = true;
			}
			else
			{
				if(u_caster->GetAIInterface()->getNextTarget() != NULL && TargetType & SPELL_TARGET_REQUIRE_ATTACKABLE)
				{
					t->m_targetMask |= TARGET_FLAG_DEST_LOCATION | TARGET_FLAG_UNIT;
					t->m_destX = u_caster->GetAIInterface()->getNextTarget()->GetPositionX() + (cosf(angle) * dist);
					t->m_destY = u_caster->GetAIInterface()->getNextTarget()->GetPositionY() + (sinf(angle) * dist);
					t->m_destZ = u_caster->GetAIInterface()->getNextTarget()->GetPositionZ();
					result = true;
				}
				else if(TargetType & SPELL_TARGET_REQUIRE_FRIENDLY)
				{
					t->m_targetMask |= TARGET_FLAG_DEST_LOCATION | TARGET_FLAG_UNIT;
					t->m_destX = u_caster->GetPositionX() + (cosf(angle) * dist);
					t->m_destY = u_caster->GetPositionY() + (sinf(angle) * dist);
					t->m_destZ = u_caster->GetPositionZ();
					result = true;
				}
				else
				{
					t->m_destX = t->m_destX + (cosf(angle) * dist);
					t->m_destY = t->m_destY + (sinf(angle) * dist);
					result = true;
				}
			}
		}
		else if(TargetType & SPELL_TARGET_AREA_SELF)
		{
			t->m_targetMask |= TARGET_FLAG_SOURCE_LOCATION | TARGET_FLAG_UNIT;
			t->m_unitTarget = u_caster->GetGUID();
			t->m_srcX = u_caster->GetPositionX();
			t->m_srcY = u_caster->GetPositionY();
			t->m_srcZ = u_caster->GetPositionZ();
			t->m_destX = u_caster->GetPositionX() + (cosf(angle) * dist);
			t->m_destY = u_caster->GetPositionY() + (sinf(angle) * dist);
			t->m_destZ = u_caster->GetPositionZ();
			result = true;
		}

		if(TargetType & SPELL_TARGET_AREA_CHAIN)
		{
			if(TargetType & SPELL_TARGET_REQUIRE_ATTACKABLE)
			{
				if(u_caster->GetAIInterface()->getNextTarget() != NULL)
				{
					t->m_targetMask |= TARGET_FLAG_UNIT;
					t->m_unitTarget = u_caster->GetAIInterface()->getNextTarget()->GetGUID();
					result = true;
				}
			}
			else
			{
				t->m_targetMask |= TARGET_FLAG_UNIT;
				t->m_unitTarget = u_caster->GetGUID();
				result = true;
			}
		}
		//target cone
		if(TargetType & SPELL_TARGET_AREA_CONE)
		{
			if(u_caster->GetAIInterface()->getNextTarget() != NULL)
			{
				t->m_targetMask |= TARGET_FLAG_DEST_LOCATION;
				t->m_destX = u_caster->GetAIInterface()->getNextTarget()->GetPositionX();
				t->m_destY = u_caster->GetAIInterface()->getNextTarget()->GetPositionY();
				t->m_destZ = u_caster->GetAIInterface()->getNextTarget()->GetPositionZ();
				result = true;
			}
		}
	}
	return result;
}

float Spell::GetDirectionAngle(uint32 TargetType)
{
	if(TargetType & SPELL_TARGET_BACK)
		return static_cast<float>(M_PI);
	if(TargetType & SPELL_TARGET_RIGHT)
		return static_cast<float>(-M_PI/2);
	if(TargetType & SPELL_TARGET_LEFT)
		return static_cast<float>(M_PI/2);
	if(TargetType & SPELL_TARGET_FRONT_RIGHT)
		return static_cast<float>(-M_PI/4);
	if(TargetType & SPELL_TARGET_BACK_RIGHT)
		return static_cast<float>(-3*M_PI/4);
	if(TargetType & SPELL_TARGET_BACK_LEFT)
		return static_cast<float>(3*M_PI/4);
	if(TargetType & SPELL_TARGET_FRONT_LEFT)
		return static_cast<float>(M_PI/4);
	if(TargetType & SPELL_TARGET_AREA_RANDOM)
		return RandomFloat()*static_cast<float>(2*M_PI);
	return 0.0f;
}

float tangent(float x)
{
    x = tan(x);
    //if (x < std::numeric_limits<float>::max() && x > -std::numeric_limits<float>::max()) return x;
    //if (x >= std::numeric_limits<float>::max()) return std::numeric_limits<float>::max();
    //if (x <= -std::numeric_limits<float>::max()) return -std::numeric_limits<float>::max();
    if (x < 100000.0f && x > -100000.0f) return x;
    if (x >= 100000.0f) return 100000.0f;
    if (x <= 100000.0f) return -100000.0f;
    return 0.0f;
}

void Spell::SelectTrajectoryTargets()
{
    if (!m_targets.HasTraj())
        return;

    float dist2d = m_targets.GetDist2d();
    if (!dist2d)
        return;

	float srcToDestDelta = m_targets.m_destZ - m_targets.m_srcZ;
    float b = tangent(m_targets.GetElevation());
    float a = (srcToDestDelta - dist2d * b) / (dist2d * dist2d);
    if (a > -0.0001f)
        a = 0;

    float bestDist = GetMaxRange(dbcSpellRange.LookupEntry(m_spellInfo->rangeIndex));
	LocationVector src(m_targets.m_srcX, m_targets.m_srcY, m_targets.m_srcZ, m_caster->GetOrientation());
	ObjectSet::iterator itr = m_caster->GetInRangeSetBegin();
	for(; itr != m_caster->GetInRangeSetEnd(); ++itr)
	{
		Object * target = (*itr);
		if(!m_caster->HasInLine(target, 0))
			continue;
		if(m_caster->GetGUID() == target->GetGUID())
			continue;
		if(target->IsUnit())
			if(TO_UNIT(target)->GetCurrentVehicle())
				continue;
        const float size = std::max((*itr)->GetObjectSize() * 0.7f, 1.0f); // 1/sqrt(3)
		
        // TODO: all calculation should be based on src instead of m_caster
		float objDist2d = src.GetExactDist2d(target->GetPositionX(), target->GetPositionY()) * cos(src.GetRelativeAngle(target->GetPositionX(), target->GetPositionY()));
		float dz = (*itr)->GetPositionZ() - m_targets.m_srcZ;
        float dist = objDist2d - size;
        float height = dist * (a * dist + b);
        if (dist < bestDist && height < dz + size && height > dz - size)
        {
            bestDist = dist > 0 ? dist : 0;
            break;
        }
#define CHECK_DIST {\
            sLog.outDebug("Spell::SelectTrajTargets: dist %f, height %f.", dist, height);\
            if (dist > bestDist)\
                continue;\
            if (dist < objDist2d + size && dist > objDist2d - size)\
            {\
                bestDist = dist;\
                break;\
            }\
        }
        if (!a)
        {
            height = dz - size;
            dist = height / b;
            CHECK_DIST;

            height = dz + size;
            dist = height / b;
            CHECK_DIST;

            continue;
        }

        height = dz - size;
        float sqrt1 = b * b + 4 * a * height;
        if (sqrt1 > 0)
        {
            sqrt1 = sqrt(sqrt1);
            dist = (sqrt1 - b) / (2 * a);
            CHECK_DIST;
        }

        height = dz + size;
        float sqrt2 = b * b + 4 * a * height;
        if (sqrt2 > 0)
        {
            sqrt2 = sqrt(sqrt2);
            dist = (sqrt2 - b) / (2 * a);
            CHECK_DIST;

            dist = (-sqrt2 - b) / (2 * a);
            CHECK_DIST;
        }

        if (sqrt1 > 0)
        {
            dist = (-sqrt1 - b) / (2 * a);
            CHECK_DIST;
        }
	}


	if (src.GetExactDist2d(m_targets.m_destX, m_targets.m_destY) > bestDist)
    {
		float x = src.x + cos(m_caster->GetOrientation()) * bestDist;
        float y = src.y + sin(m_caster->GetOrientation()) * bestDist;
        float z = src.z + bestDist * (a * bestDist + b);

        if (itr != m_caster->GetInRangeSetEnd())
        {
            float distSq = (*itr)->GetExactDistSq(x, y, z);
            float sizeSq = (*itr)->GetObjectSize();
            sizeSq *= sizeSq;
            if (distSq > sizeSq)
            {
                float factor = 1 - sqrt(sizeSq / distSq);
                x += factor * ((*itr)->GetPositionX() - x);
                y += factor * ((*itr)->GetPositionY() - y);
                z += factor * ((*itr)->GetPositionZ() - z);

                distSq = (*itr)->GetExactDistSq(x, y, z);
            }
        }
		m_targets.m_destX = x;
		m_targets.m_destY = y;
		m_targets.m_destZ = z;
    }
}