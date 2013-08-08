/*
 * Copyright (C) 2012-2013 <Derek Anarchy>
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
 */

#include "Setup.h"
#include "Instance_RubySanctum.h"

class RubySanctumScript : public MoonInstanceScript
{
public:
	MOONSCRIPT_INSTANCE_FACTORY_FUNCTION( RubySanctumScript, MoonInstanceScript );
	RubySanctumScript( MapMgr* pMapMgr ) : MoonInstanceScript( pMapMgr )
	{
		InstanceData[RUBY_STATUS][0] = RUBY_NOT_STARTED;
	}

	void SetInstanceData( uint32 pType, uint32 pIndex, uint32 pData )
	{
		if(pType == RUBY_EVENT)
		{
			switch(pIndex)
			{
				case RUBY_EVENT_FARSIGHT:
				{
					SetAllPlayersFarSight(pData);
				}break;
				case RUBY_EVENT_PHASE_PLAYERS:
				{
					PhaseAllPlayers(pData);
				}break;
			}
		}
		InstanceData[pType][pIndex] = pData;
	}

	uint32 GetInstanceData( uint32 pType, uint32 pIndex )
	{
		return InstanceData[pType][pIndex];
	}

	void OnPlayerEnter(Player* pPlayer)
	{
		pPlayer->SetDisplayId(29121);
		pPlayer->SetNativeDisplayId(29121);
		if(GetInstanceData(RUBY_STATUS, RUBY_ACTIVE) == 0)
			pPlayer->Phase(PHASE_SET, 2);
	}

private:
	uint32 InstanceData[RUBY_TYPE_MAX][RUBY_MAX]; 
};
class ScoutActivatorGossip : public Arcemu::Gossip::Script
{
public:
    void OnHello(Object* pObject, Player* Plr);
    void OnSelectOption(Object* pObject, Player* Plr, uint32 Id, const char * Code);
	void Destroy() { delete this; }
};

void ScoutActivatorGossip::OnHello(Object* pObject, Player* Plr)
{
	Arcemu::Gossip::Menu menu(pObject->GetGUID(), 2, 0);
	menu.AddItem(Arcemu::Gossip::ICON_CHAT, "We are ready, send the scout out.", 1); 
	menu.AddItem(Arcemu::Gossip::ICON_CHAT, "We need more time to prepare.", 2); 
	if(Plr->HasItemCount(18206, 1))
		menu.AddItem(Arcemu::Gossip::ICON_CHAT, "<Show dwarf spine>", 3); 
	menu.Send(Plr);
}

void ScoutActivatorGossip::OnSelectOption(Object* pObject, Player* Plr, uint32 Id, const char * Code)
{
	Creature* c = TO_CREATURE(pObject);
	if(Id == 1)
	{
		//Creature * a = c->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(c->GetPositionX(), c->GetPositionY(), c->GetPositionZ(), NPC_SCOUTTER);
		Creature * a = c->GetCreatureWithEntry(NPC_SCOUTTER);
		if(a)
		{
			c->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Scouter, you are needed.");
			a->ReceiveAction(RUBY_ACTION_CALL_SCOUTER);
			c->SetUInt32Value(UNIT_NPC_FLAGS, 0);
			Plr->CloseGossip();
		}
		else
			c->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "We has no scouter, go fuck yourself emulator.");
	}
	if(Id == 2)
	{
		c->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Very well then, we need you ready as soon as possible, the enemy draws closer with each second.");
		Plr->CloseGossip();
	}
	if(Id == 3)
	{
		//Creature * a = c->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(c->GetPositionX(), c->GetPositionY(), c->GetPositionZ(), NPC_ENERAGED_DWARF);
		Creature * a = c->GetCreatureWithEntry(NPC_ENERAGED_DWARF);
		if(a)
		{
			c->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Why are you showing me this dwarf spine?");
			a->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "You must die now.");
			a->ReceiveAction(RUBY_ACTION_DWARF_SPINE);
		}
		else
			c->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "We has no angry dwarf, go fuck yourself emulator.");
	}
	Arcemu::Gossip::Menu::Complete(Plr);
}

struct Location ScouterPos[]=
{
	{  },
	{ 3256.832520f, 539.685608f, 96.145943f, 4.829193f },
	{ 3197.444092f, 613.681946f, 143.439362f, 3.632246f },
	{ 3159.257813f, 451.506317f, 148.159531f, 4.016284f }
};

class ScouterAI : public MoonScriptCreatureAI
{
public:
	MOONSCRIPT_FACTORY_FUNCTION(ScouterAI, MoonScriptCreatureAI);
	ScouterAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
	{
		_unit->GetAIInterface()->SetFly();
	}

	void ReceiveAction(uint32 action)
	{
		switch(action)
		{
			case RUBY_ACTION_CALL_SCOUTER:
			{
				_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Just a second sir.");
				_unit->AddUnitMovementFlag(MOVEFLAG_NO_COLLISION);
				_unit->SendMovementFlagUpdate();
				AddWaypoint(CreateWaypoint(1, 2000, 512, ScouterPos[1]));
				ForceWaypointMove(1);
				GetInstanceScript()->SetInstanceData(RUBY_STATUS, RUBY_SCOUTING_REPORT, 1);
			}break;
		}
	}

	void OnReachWP(uint32 iWaypointId, bool bForwards)
    {
		switch(iWaypointId)
		{
			case 1:
			{
				StopWaypointMovement();
				Creature * c = FindCreature(NPC_SCOUT_ACTIVATOR);
				if(c == NULL || GetInstanceScript() == NULL)
				{
					_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Unable to find caller or instance script, script aborting.");
					return;
				}
				c->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Scout the area for any anomalies whatever is coming, shall be here soon...");
				_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Yes, sir.", 1000);
				SetPlayerFarsight(_unit->GetGUID());
				AddWaypoint(CreateWaypoint(2, 1000, 512, ScouterPos[2]));
				ForceWaypointMove(2);
			}break;
			case 2:
			{
				_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Scanning area...");
				_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "No anomalies detected, searching another area.", 3000);
				AddWaypoint(CreateWaypoint(3, 1, 512, ScouterPos[3]));
				ForceWaypointMove(3);
			}break;
			case 3:
			{
				_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Scanning area...");
				_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "WARNING!", 2000);
				_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "WARNING!", 4000);
				_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Spatial rift detected, it's ripping through time itself,", 5000);
				_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Recommend evac...", 6000);
				_unit->SendChatMessage(CHAT_MSG_MONSTER_EMOTE, LANG_UNIVERSAL, "Scoutting machine explodes from a huge energy influx.", 7000);
				sEventMgr.AddEvent(TO_UNIT(_unit), &Unit::EventCastSpell, TO_UNIT(_unit), dbcSpell.LookupEntry(74550), EVENT_UNK, 7000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
				sEventMgr.AddEvent(TO_UNIT(_unit), &Unit::Die, TO_UNIT(_unit), uint32(_unit->GetHealth()), uint32(74550), EVENT_UNK, 7200, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);				
				sEventMgr.AddEvent(_unit->GetMapMgr(), &MapMgr::SetInstanceData, uint32(RUBY_EVENT), uint32(RUBY_EVENT_FARSIGHT), uint32(0), EVENT_UNK, 9000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);				
				sEventMgr.AddEvent(_unit->GetMapMgr(), &MapMgr::SetInstanceData, uint32(RUBY_EVENT), uint32(RUBY_EVENT_PHASE_PLAYERS), uint32(1), EVENT_UNK, 9000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);				
				sEventMgr.AddEvent(_unit->GetMapMgr(), &MapMgr::SetInstanceData, uint32(RUBY_STATUS), uint32(RUBY_ACTIVE), uint32(1), EVENT_UNK, 9000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);				
			}break;
		}
	}

	void SetPlayerFarsight(uint64 guid)
	{
		for(std::set<Object*>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); itr++)
		{
			if((*itr) == NULL || !(*itr)->IsPlayer())
				continue;
			TO_PLAYER((*itr))->SetFarsightTarget(guid);
		}
	}
};

void SetupRubySanctum(ScriptMgr * mgr)
{
	Arcemu::Gossip::Script * gs = new ScoutActivatorGossip();
	mgr->register_instance_script(RUBY_SANCTUM, &RubySanctumScript::Create );
	mgr->register_creature_gossip(NPC_SCOUT_ACTIVATOR, gs);
	mgr->register_creature_script(NPC_SCOUTTER, &ScouterAI::Create);
}