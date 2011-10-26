/*
 * Sandshroud Hearthstone
 * Copyright (C) 2010 - 2011 Sandshroud <http://www.sandshroud.org/>
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

// gameobject faction
	static uint32 g_gameObjectFactions[IOC_NUM_CONTROL_POINTS] =
	{
		35,		// neutral
		2,		// alliance assault
		2,		// alliance	controlled
		1,		// horde assault
		1,		// horde controlled
	};

// Graveyard locations
	static float GraveyardLocations[IOC_NUM_CONTROL_POINTS][4] =
	{
		{ 0.0f, 0.0f, 0.0f },		// The Oil Derrick
		{ 0.0f, 0.0f, 0.0f },		// The Cobalt Mine
		{ 0.0f, 0.0f, 0.0f },		// The Docks
		{ 0.0f, 0.0f, 0.0f },		// The Airship Hangar
		{ 0.0f, 0.0f, 0.0f },		// The Siege Workshop
	};


	static float NoBaseGYLocations[2][4] =
	{
		{ 278.28f, -883.65f, 49.92f, 1.57f },	// ALLIANCE
		{ 1301.30f, -839.38f, 48.91f, 1.48f },	// HORDE
	};

	static const char * ControlPointNames[IOC_NUM_CONTROL_POINTS] =
	{
		"Oil Derrick",		// The Oil Derrick
		"Cobalt Mine",		// The Cobalt Mine
		"Docks",			// The Docks
		"Airship Hangar",	// The Airship Hangar
		"Siege Workshop",	// The Siege Workshop
		"Allaince Keep",
		"Horde Keep",
	};

	static uint32 ControlPointGoIds[IOC_NUM_CONTROL_POINTS][5] =
	{
		  // NEUTRAL    ALLIANCE-ATTACK    HORDE-ATTACK    ALLIANCE-CONTROLLED    HORDE_CONTROLLED
		{ 195343,       180085,            180086,         180076,                180078 },			// The Oil Derrick
		{ 195338,       180085,            180086,         180076,                180078 },			// The Cobalt Mine
		{ 195157,       180085,            180086,         180076,                180078 },			// The Docks
		{ 195158,       180085,            180086,         180076,                180078 },			// The Airship Hangar
		{ 195133,       180085,            180086,         180076,                180078 },			// The Siege Workshop
		{ 195132,       180085,            180086,         180076,                180078 },			// Alliance Keep
		{ 195130,       180085,            180086,         180076,                180078 },			// Horde Keep
	};

	static float ControlPointCoordinates[IOC_NUM_CONTROL_POINTS][4] =
	{
		{ 1266.01f, -400.78f, 37.62f, 0.16f },		// The Oil Derrick
		{ 225.29f, -1189.01f, 8.05f, 0.86f },		// The Cobalt Mine
		{ 782.88f, -371.84f, 12.37f, 5.45f },		// The Docks
		{ 691.70f, -1121.04f, 133.70f, 2.147f },	// The Airship Hangar
		{ 751.29f, -818.18f, 7.40f, 0.75f },		// The Siege Workshop
		{ 301.04f, -780.49f, 48.91f, 6.03f},		// Alliance Keep
		{ 1278.59f, -704.18f, 48.91f, 3.19f},		// Horde Keep
	};

	static float demolisherSalesmen[2][5] =
	{
		{35345, 763.660f, -880.25f , 18.55f, 3.14f},	// Gnomish Mechanic (A)
		{35346, 763.660f, -880.25f , 18.55f, 3.14f},	// Goblin Mechanic	(H)
	};

	static float iocTransporterDestination[12][4] =
	{
		{429.79f, -800.825f, 49.03f, 3.23f},	// Alliance front gate out
		{399.66f, -798.63f, 49.06f, 4.01f},		// Alliance front gate in
		{313.64f, -775.43f, 49.04f, 4.93f},		// Alliance west gate in
		{324.68f, -748.73f, 49.38f, 1.76f},		// Alliance west gate out
		{323.01f, -888.61f, 48.91f, 4.66f},		// Allaince east gate in
		{316.22f, -914.65f, 48.87f, 1.69f},		// Allaince east gate out
		{1234.51f, -684.55f, 49.32f, 5.01f},	// Horde west gate in
		{1196.72f, -664.84f, 48.57f, 1.71f},	// Horde west gate out
		{1161.82f, -748.87f, 48.62f, 0.34f},	// Horde front gate in
		{1140.19f, -780.74f, 48.69f, 2.93f},	// Horde front gate out
		{1196.47f, -861.29f, 49.17f, 4.04f},	// Horde east gate out
		{1196.06f, -842.70f, 49.13f, 0.30f},	// Horde east gate in
	};

	static float iocTransporterLocation[12][4] =
	{
		{429.79f, -800.825f, 49.03f, 3.23f},	// Alliance front gate out
		{399.66f, -798.63f, 49.06f, 4.01f},		// Alliance front gate in
		{313.64f, -775.43f, 49.04f, 4.93f},		// Alliance west gate in
		{324.68f, -748.73f, 49.38f, 1.76f},		// Alliance west gate out
		{323.01f, -888.61f, 48.91f, 4.66f},		// Allaince east gate in
		{316.22f, -914.65f, 48.87f, 1.69f},		// Allaince east gate out
		{1234.51f, -684.55f, 49.32f, 5.01f},	// Horde west gate in
		{1196.72f, -664.84f, 48.57f, 1.71f},	// Horde west gate out
		{1161.82f, -748.87f, 48.62f, 0.34f},	// Horde front gate in
		{1140.19f, -780.74f, 48.69f, 2.93f},	// Horde front gate out
		{1196.47f, -861.29f, 49.17f, 4.04f},	// Horde east gate out
		{1196.06f, -842.70f, 49.13f, 0.30f},	// Horde east gate in
	};

	static float iocGatesLocation[6][4] =
	{
		{352.70269f, -762.66369f, 48.91628f, 4.6866f},		// Alliance West gate
		{412.41436f, - 833.83011f, 48.5479f, 3.11868f},		// Alliance Front gate
		{352.54592f, -904.92181f, 48.92093f, 1.57336f},		// Alliance East gate
		{1151.51562f, -763.4730f, 48.62429f, 3.17145f},		// Horde Front gate
		{1218.54126f, -676.44390f, 48.68709f, 1.53727f},	// Horde West gate
		{1218.35607f, -850.55456f, 48.91478f, 4.77781f},	// Horde East gate
	};

	static uint32 gatesIds[6] =
	{
		195698,
		195699,
		195700,
		195494,
		195495,
		195496,
	};

	static uint32 AssaultFields[IOC_NUM_CONTROL_POINTS][2] =
	{
		{ WORLDSTATE_IOC_REFINERY_ALLIANCE_ASSAULTED, WORLDSTATE_IOC_REFINERY_HORDE_ASSAULTED },
		{ WORLDSTATE_IOC_QUARRY_ALLIANCE_ASSAULTED, WORLDSTATE_IOC_QUARRY_HORDE_ASSAULTED },
		{ WORLDSTATE_IOC_DOCKS_ALLIANCE_ASSAULTED, WORLDSTATE_IOC_DOCKS_HORDE_ASSAULTED },					// The Docks
		{ WORLDSTATE_IOC_HANGAR_ALLIANCE_ASSAULTED, WORLDSTATE_IOC_HANGAR_HORDE_ASSAULTED },
		{ WORLDSTATE_IOC_WORKSHOP_ALLIANCE_ASSAULTED, WORLDSTATE_IOC_WORKSHOP_HORDE_ASSAULTED },			// The Siege Workshop
		{ WORLDSTATE_IOC_ALLIANCE_KEEP_ALLIANCE_ASSAULTED, WORLDSTATE_IOC_ALLIANCE_KEEP_HORDE_ASSAULTED },	// Alliance Keep
		{ WORLDSTATE_IOC_HORDE_KEEP_ALLIANCE_ASSAULTED, WORLDSTATE_IOC_HORDE_KEEP_HORDE_ASSAULTED },		// Horde Keep
	};

	static uint32 OwnedFields[IOC_NUM_CONTROL_POINTS][2] =
	{
		{ WORLDSTATE_IOC_REFINERY_ALLIANCE_CONTROLLED, WORLDSTATE_IOC_REFINERY_HORDE_CONTROLLED },
		{ WORLDSTATE_IOC_QUARRY_ALLIANCE_CONTROLLED, WORLDSTATE_IOC_QUARRY_HORDE_CONTROLLED },
		{ WORLDSTATE_IOC_DOCKS_ALLIANCE_CONTROLLED, WORLDSTATE_IOC_DOCKS_HORDE_CONTROLLED },					// The Docks
		{ WORLDSTATE_IOC_HANGAR_ALLIANCE_CONTROLLED, WORLDSTATE_IOC_HANGAR_HORDE_CONTROLLED },
		{ WORLDSTATE_IOC_WORKSHOP_ALLIANCE_CONTROLLED, WORLDSTATE_IOC_WORKSHOP_HORDE_CONTROLLED },				// The Siege Workshop
		{ WORLDSTATE_IOC_ALLIANCE_KEEP_ALLIANCE_CONTROLLED, WORLDSTATE_IOC_ALLIANCE_KEEP_HORDE_CONTROLLED },	// Alliance Keep
		{ WORLDSTATE_IOC_HORDE_KEEP_ALLIANCE_CONTROLLED, WORLDSTATE_IOC_HORDE_KEEP_HORDE_CONTROLLED },			// Horde Keep
	};

	static uint32 NeutralFields[IOC_NUM_CONTROL_POINTS] =
	{
		WORLDSTATE_IOC_REFINERY_NETURAL,
		WORLDSTATE_IOC_QUARRY_NETURAL,
		WORLDSTATE_IOC_DOCKS_NETURAL,
		WORLDSTATE_IOC_HANGAR_NETURAL,
		WORLDSTATE_IOC_WORKSHOP_NETURAL,
		WORLDSTATE_IOC_ALLIANCE_KEEP_NETURAL,
		WORLDSTATE_IOC_HORDE_KEEP_NETURAL,
	};

	static uint32 ResourceUpdateIntervals[6] =
	{
		0,
		12000,
		9000,
		6000,
		3000,
		1000,
	};

float CalcDistance(float x1, float y1, float z1, float x2, float y2, float z2)
{
	float dx = x1 - x2;
	float dy = y1 - y2;
	float dz = z1 - z2;
	return sqrt(dx*dx + dy*dy + dz*dz);
}

IsleOfConquest::IsleOfConquest(MapMgr * mgr, uint32 id, uint32 lgroup, uint32 t) : CBattleground(mgr, id, lgroup, t)
{
	for(uint32 i = 0; i < IOC_NUM_CONTROL_POINTS; i++)
	{
		m_ioccontrolPointAuras[i] = NULL;
		m_ioccontrolPoints[i] = NULL;
		m_spiritGuides[i] = NULL;
		m_basesAssaultedBy[i] = -1;
		m_basesOwnedBy[i] = -1;
		m_basesLastOwnedBy[i] = -1;
		m_flagIsVirgin[i] = true;
	}

	for(uint32 i = 0; i < 2; i++)
	{
		m_capturedBases[i] = 0;
	}

	m_playerCountPerTeam = 40;
	m_reinforcements[0] = IOC_NUM_REINFORCEMENTS;
	m_reinforcements[1] = IOC_NUM_REINFORCEMENTS;
	m_LiveCaptain[0] = true;
	m_LiveCaptain[1] = true;
	m_vehicles.clear();
	//m_bonusHonor = HonorHandler::CalculateHonorPointsFormula(lgroup*10,lgroup*10);

	/*memset(m_nodes, 0, sizeof(m_nodes));*/
	m_zoneid = 4710;
	for(int i = 0; i < 6; i++)
	{
		ActiveBonuses[0][i] = false;
		ActiveBonuses[1][i] = false;
	}
}

IsleOfConquest::~IsleOfConquest()
{
	for(uint32 i = 0; i < IOC_NUM_CONTROL_POINTS; i++)
	{
		if(m_ioccontrolPoints[i] != NULL)
		{
			if( !m_ioccontrolPoints[i]->IsInWorld() )
			{
				delete m_ioccontrolPoints[i];
			}
		}

		if(m_ioccontrolPointAuras[i])
		{
			if( !m_ioccontrolPointAuras[i]->IsInWorld() )
			{
				delete m_ioccontrolPointAuras[i];
			}
		}
	}
}

bool IsleOfConquest::HookHandleRepop(Player* plr)
{
	LocationVector dest_pos;
	if( plr->GetTeam() == 1 )
		dest_pos.ChangeCoords(NoBaseGYLocations[1][0], NoBaseGYLocations[1][1], NoBaseGYLocations[1][2], NoBaseGYLocations[1][3]);
	else
		dest_pos.ChangeCoords(NoBaseGYLocations[0][0], NoBaseGYLocations[0][1], NoBaseGYLocations[0][2], NoBaseGYLocations[0][3]);

	// port to it
	plr->SafeTeleport(plr->GetMapId(), plr->GetInstanceID(), dest_pos);
	return false;
}

void IsleOfConquest::OnPlatformTeleport(Player* plr)
{
	LocationVector dest;
	uint32 closest_platform = 0;

	if(plr->GetTeam() == TEAM_ALLIANCE)
	{
		for (uint32 i = 0; i < 6; i++)
		{
			float distance = CalcDistance(plr->GetPositionX(),
				plr->GetPositionY(), plr->GetPositionZ(),
				iocTransporterDestination[i][0],
				iocTransporterDestination[i][1],
				iocTransporterDestination[i][2]);
			if (distance < 75 && distance > 10)
			{
				closest_platform = i;
				break;
			}
		}
		dest.ChangeCoords(iocTransporterDestination[closest_platform][0],
			iocTransporterDestination[closest_platform][1],
			iocTransporterDestination[closest_platform][2],
			iocTransporterDestination[closest_platform][3]);
	}
	else		// HORDE
	{
		for (uint32 i = 6; i < 12; i++)
		{
			float distance = CalcDistance(plr->GetPositionX(),
				plr->GetPositionY(), plr->GetPositionZ(),
				iocTransporterDestination[i][0],
				iocTransporterDestination[i][1],
				iocTransporterDestination[i][2]);
			if (distance < 75 && distance > 10)
			{
				closest_platform = i;
				break;
			}
		}
		dest.ChangeCoords(iocTransporterDestination[closest_platform][0],
			iocTransporterDestination[closest_platform][1],
			iocTransporterDestination[closest_platform][2],
			iocTransporterDestination[closest_platform][3]);
	}
	plr->SafeTeleport(plr->GetMapId(), plr->GetInstanceID(), dest);
}

void IsleOfConquest::SpawnControlPoint(uint32 Id, uint32 Type)
{
	GameObjectInfo * gi, * gi_aura;
	gi = GameObjectNameStorage.LookupEntry(ControlPointGoIds[Id][Type]);
	if(gi == NULL)
		return;

	gi_aura = gi->sound3 ? GameObjectNameStorage.LookupEntry(gi->sound3) : NULL;
	if(m_ioccontrolPoints[Id] == NULL)
	{
		m_ioccontrolPoints[Id] = SpawnGameObject(gi->ID, ControlPointCoordinates[Id][0], ControlPointCoordinates[Id][1],
			ControlPointCoordinates[Id][2], ControlPointCoordinates[Id][3], 0, 35, 1.0f);

		m_ioccontrolPoints[Id]->SetState(1);
		m_ioccontrolPoints[Id]->SetType(gi->Type);
		m_ioccontrolPoints[Id]->SetAnimProgress(100);
		m_ioccontrolPoints[Id]->SetUInt32Value(GAMEOBJECT_DYNAMIC, 1);
		m_ioccontrolPoints[Id]->SetDisplayId(gi->DisplayID);

		switch(Type)
		{
		case IOC_SPAWN_TYPE_ALLIANCE_ASSAULT:
		case IOC_SPAWN_TYPE_ALLIANCE_CONTROLLED:
			m_ioccontrolPoints[Id]->SetFaction(2);
			break;

		case IOC_SPAWN_TYPE_HORDE_ASSAULT:
		case IOC_SPAWN_TYPE_HORDE_CONTROLLED:
			m_ioccontrolPoints[Id]->SetFaction(1);
			break;

		default:
			m_ioccontrolPoints[Id]->SetFaction(35);		// neutral
			break;
		}

		m_ioccontrolPoints[Id]->bannerslot = Id;
		m_ioccontrolPoints[Id]->PushToWorld(m_mapMgr);
	}
	else
	{
		if(m_ioccontrolPoints[Id]->IsInWorld())
			m_ioccontrolPoints[Id]->RemoveFromWorld(false);

		// assign it a new guid (client needs this to see the entry change?)
		m_ioccontrolPoints[Id]->SetNewGuid(m_mapMgr->GenerateGameobjectGuid());
		m_ioccontrolPoints[Id]->SetEntry(gi->ID);
		m_ioccontrolPoints[Id]->SetDisplayId(gi->DisplayID);
		m_ioccontrolPoints[Id]->SetType(gi->Type);

		switch(Type)
		{
		case IOC_SPAWN_TYPE_ALLIANCE_ASSAULT:
		case IOC_SPAWN_TYPE_ALLIANCE_CONTROLLED:
			m_ioccontrolPoints[Id]->SetUInt32Value(GAMEOBJECT_FACTION, 2);
			break;

		case IOC_SPAWN_TYPE_HORDE_ASSAULT:
		case IOC_SPAWN_TYPE_HORDE_CONTROLLED:
			m_ioccontrolPoints[Id]->SetUInt32Value(GAMEOBJECT_FACTION, 1);
			break;

		default:
			m_ioccontrolPoints[Id]->SetUInt32Value(GAMEOBJECT_FACTION, 35);		// neutral
			break;
		}

		m_ioccontrolPoints[Id]->SetInfo(gi);
		m_ioccontrolPoints[Id]->PushToWorld(m_mapMgr);
	}

	if(gi_aura == NULL)
	{
		// remove it if it exists
		if(m_ioccontrolPointAuras[Id]!=NULL && m_ioccontrolPointAuras[Id]->IsInWorld())
			m_ioccontrolPointAuras[Id]->RemoveFromWorld(false);

		return;
	}

	if(m_ioccontrolPointAuras[Id] == NULL)
	{
		m_ioccontrolPointAuras[Id] = SpawnGameObject(gi_aura->ID, ControlPointCoordinates[Id][0], ControlPointCoordinates[Id][1],
			ControlPointCoordinates[Id][2], ControlPointCoordinates[Id][3], 0, 35, 5.0f);

		m_ioccontrolPointAuras[Id]->SetByte(GAMEOBJECT_BYTES_1,GAMEOBJECT_BYTES_STATE, 1);
		m_ioccontrolPointAuras[Id]->SetByte(GAMEOBJECT_BYTES_1,GAMEOBJECT_BYTES_TYPE_ID, 6);
		m_ioccontrolPointAuras[Id]->SetByte(GAMEOBJECT_BYTES_1,GAMEOBJECT_BYTES_ANIMPROGRESS, 100);
		m_ioccontrolPointAuras[Id]->bannerauraslot = Id;
		m_ioccontrolPointAuras[Id]->PushToWorld(m_mapMgr);
	}
	else
	{
		if(m_ioccontrolPointAuras[Id]->IsInWorld())
			m_ioccontrolPointAuras[Id]->RemoveFromWorld(false);

		// re-spawn the aura
		m_ioccontrolPointAuras[Id]->SetNewGuid(m_mapMgr->GenerateGameobjectGuid());
		m_ioccontrolPointAuras[Id]->SetUInt32Value(OBJECT_FIELD_ENTRY, gi_aura->ID);
		m_ioccontrolPointAuras[Id]->SetUInt32Value(GAMEOBJECT_DISPLAYID, gi_aura->DisplayID);
		m_ioccontrolPointAuras[Id]->SetInfo(gi_aura);
		m_ioccontrolPointAuras[Id]->PushToWorld(m_mapMgr);
	}
}

void IsleOfConquest::CaptureControlPoint(uint32 Id, uint32 Team)
{
	if(m_basesOwnedBy[Id] != -1)
	{
		// there is a very slim chance of this happening, 2 teams evnets could clash..
		// just in case...
		return;
	}

	// anticheat, not really necessary because this is a server method but anyway
	if(m_basesAssaultedBy[Id] != (int32)Team)
		return;


	m_basesLastOwnedBy[Id] = Team;

	m_flagIsVirgin[Id] = false;

	m_basesOwnedBy[Id] = Team;
	m_basesAssaultedBy[Id]=-1;

	// remove the other spirit guide (if it exists) // burlex: shouldnt' happen
	if(m_spiritGuides[Id] != NULL)
	{
		RemoveSpiritGuide(m_spiritGuides[Id]);
		m_spiritGuides[Id]->Despawn(0,0);
	}

	// spawn the spirit guide for our faction
	m_spiritGuides[Id] = SpawnSpiritGuide(GraveyardLocations[Id][0], GraveyardLocations[Id][1], GraveyardLocations[Id][2], 0.0f, Team);
	AddSpiritGuide(m_spiritGuides[Id]);

	// send the chat message/sounds out
	PlaySoundToAll(Team ? SOUND_HORDE_SCORES : SOUND_ALLIANCE_SCORES);
	SendChatMessage(Team ? CHAT_MSG_BG_EVENT_HORDE : CHAT_MSG_BG_EVENT_ALLIANCE, 0, "The %s has taken the %s!", Team ? "Horde" : "Alliance", ControlPointNames[Id]);

	// update the overhead display on the clients (world states)
	m_capturedBases[Team]++;
	// respawn the control point with the correct aura
	SpawnControlPoint(Id, Team ? IOC_SPAWN_TYPE_HORDE_CONTROLLED : IOC_SPAWN_TYPE_ALLIANCE_CONTROLLED);

	// update the map
	SetWorldState(AssaultFields[Id][Team], 0);
	SetWorldState(OwnedFields[Id][Team], 1);
	AddHonorToTeam(5, Team);
	if(Id == 5)
		Updateworkshop(Team);
}

void IsleOfConquest::Updateworkshop(uint32 Team)
{
	if(m_salesman != NULL)
		m_salesman->Despawn(0,0);

	m_salesman = SpawnCreature(demolisherSalesmen[Team][0], demolisherSalesmen[Team][1], demolisherSalesmen[Team][2], demolisherSalesmen[Team][3], demolisherSalesmen[Team][4]);

	m_salesman->PushToWorld(m_mapMgr);
}

void IsleOfConquest::AssaultControlPoint(Player* pPlayer, uint32 Id)
{
	if(!m_started)
	{
		SendChatMessage(CHAT_MSG_BG_EVENT_NEUTRAL, pPlayer->GetGUID(), "%s has been removed from the game for cheating.", pPlayer->GetName());
		pPlayer->SoftDisconnect();
		return;
	}

	bool isVirgin = false;

	uint32 Team = pPlayer->m_bgTeam;
	uint32 Owner;

	if(m_basesOwnedBy[Id]==-1 && m_basesAssaultedBy[Id]==-1)
	{
		isVirgin = true;
		// omgwtfbbq our flag is a virgin?
		SetWorldState(NeutralFields[Id], 0);
	}

	if(m_basesOwnedBy[Id] != -1)
	{
		Owner = m_basesOwnedBy[Id];

		// set it to uncontrolled for now
		m_basesOwnedBy[Id] = -1;

		// this control point just got taken over by someone! oh noes!
		if( m_spiritGuides[Id] != NULL )
		{
			map<Creature*,set<uint32> >::iterator itr = m_resurrectMap.find(m_spiritGuides[Id]);
			if( itr != m_resurrectMap.end() )
			{
				for( set<uint32>::iterator it2 = itr->second.begin(); it2 != itr->second.end(); it2++ )
				{
					Player* r_plr = m_mapMgr->GetPlayer( *it2 );
					if( r_plr != NULL && r_plr->IsDead())
					{
						HookHandleRepop( r_plr );
						QueueAtNearestSpiritGuide(r_plr, itr->first);
					}
				}
			}
			m_resurrectMap.erase( itr );
			if(m_spiritGuides[Id] && m_spiritGuides[Id]->IsInWorld())
			{
				m_spiritGuides[Id]->Despawn( 0, 0 );
				m_spiritGuides[Id] = NULL;
			}
		}

		// reset the world states
		SetWorldState(OwnedFields[Id][Owner], 0);

		// modify the resource update time period
		if(m_capturedBases[Owner]==0)
			event_RemoveEvents(EVENT_IOC_RESOURCES_UPDATE_TEAM_0+Owner);
		else
			event_ModifyTime(EVENT_IOC_RESOURCES_UPDATE_TEAM_0 + Owner, ResourceUpdateIntervals[m_capturedBases[Owner]]);
	}
	pPlayer->AddHonor(25);
	// Contested Flag, not ours, and is not virgin
	if( !isVirgin && m_basesLastOwnedBy[Id] == int32(Team) && m_basesOwnedBy[Id] == -1 )
	{
		SetWorldState(AssaultFields[Id][Team ? 0 : 1], 0);
		event_RemoveEvents(EVENT_IOC_CAPTURE_CP_1 + Id);
		SendChatMessage(Team ?  CHAT_MSG_BG_EVENT_HORDE :  CHAT_MSG_BG_EVENT_ALLIANCE, pPlayer->GetGUID(), "$N has defended the %s!", ControlPointNames[Id]);
		m_basesAssaultedBy[Id] = Team;
		CaptureControlPoint( Id, Team );
		pPlayer->m_bgScore.MiscData[BG_SCORE_IOC_BASE_DEFENDED]++;
		return;
	}

	// nigga stole my flag!
	if(m_basesAssaultedBy[Id] != -1)
	{
		Owner = m_basesAssaultedBy[Id];
		m_basesAssaultedBy[Id] = Team;
		SetWorldState(AssaultFields[Id][Owner], 0);
		sEventMgr.RemoveEvents(this, EVENT_IOC_CAPTURE_CP_1 + Id);
	}

	m_basesAssaultedBy[Id] = Team;

	// spawn the new control point gameobject
	SpawnControlPoint(Id, Team ? IOC_SPAWN_TYPE_HORDE_ASSAULT : IOC_SPAWN_TYPE_ALLIANCE_ASSAULT);

	// send out the chat message and sound
	SendChatMessage(Team ?  CHAT_MSG_BG_EVENT_HORDE :  CHAT_MSG_BG_EVENT_ALLIANCE, pPlayer->GetGUID(), "$N claims the %s! If left unchallenged, the %s will control it in 1 minute!", ControlPointNames[Id],
		Team ? "Horde" : "Alliance");
	// guessed
	PlaySoundToAll(Team ? SOUND_ALLIANCE_CAPTURE : SOUND_HORDE_CAPTURE);

	// update the client's map with the new assaulting field
	SetWorldState(AssaultFields[Id][Team], 1);

	// create the 60 second event.
	sEventMgr.AddEvent(this, &IsleOfConquest::CaptureControlPoint, Id, Team, EVENT_IOC_CAPTURE_CP_1 + Id, 60000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);

	// update players info
	pPlayer->m_bgScore.MiscData[BG_SCORE_IOC_BASE_ASSAULTED]++;
	UpdatePvPData();
	ApplyCaptureBonus(Id, Team);
	if(Id == 5)
	{
		if(m_salesman != NULL)
			m_salesman->Despawn(0,0);
	}
}

void IsleOfConquest::HookOnAreaTrigger(Player* plr, uint32 id)
{

}

void IsleOfConquest::HookOnPlayerDeath(Player* plr)
{
	plr->m_bgScore.Deaths++;
	UpdatePvPData();
	RemoveReinforcements(plr->GetTeam(), IOC_POINTS_ON_KILL);
}
// we don't have flag in ioc
void IsleOfConquest::HookFlagDrop(Player* plr, GameObject* obj)
{
}

void IsleOfConquest::HookFlagStand(Player* plr, GameObject* obj)
{
}

bool IsleOfConquest::HookSlowLockOpen(GameObject* pGo, Player* pPlayer, Spell* pSpell)
{
	if(pGo->bannerslot >= 0 && pGo->bannerslot < IOC_NUM_CONTROL_POINTS)
	{
		// TODO: anticheat here
		AssaultControlPoint(pPlayer,pGo->bannerslot);
		return true;
	}
	return false;
}

void IsleOfConquest::HookOnMount(Player* plr)
{
}

void IsleOfConquest::OnAddPlayer(Player* plr)
{
	if(!m_started)
		plr->CastSpell(plr, BG_PREPARATION, true);
	plr->m_bgScore.MiscData[BG_SCORE_IOC_BASE_DEFENDED] = 0;
	plr->m_bgScore.MiscData[BG_SCORE_IOC_BASE_ASSAULTED] = 0;
	UpdatePvPData();
}

void IsleOfConquest::OnRemovePlayer(Player* plr)
{
  plr->RemoveAura(BG_PREPARATION);
}

void IsleOfConquest::OnCreate()
{
	// generals/leaders!
	SpawnCreature(34924, 214.77f, -830.73f, 60.81f, 0.07f);	// High Commander Halford Wyrmbane (ALLIANCE)
	SpawnCreature(34922, 1296.57f, -765.78f, 69.98f, 6.22f);	// Overlord Agmar (HORDE)

	// Spawn const spiritguides
	AddSpiritGuide(SpawnSpiritGuide(NoBaseGYLocations[0][0], NoBaseGYLocations[0][1], NoBaseGYLocations[0][2], NoBaseGYLocations[0][3], 0));
	AddSpiritGuide(SpawnSpiritGuide(NoBaseGYLocations[1][0], NoBaseGYLocations[1][1], NoBaseGYLocations[1][2], NoBaseGYLocations[1][3], 1));


	// Spawn Teleporters
	for(uint32 i = 0; i < 6; i++)	// Alliance
	{
		m_teleporters[i] = SpawnGameObject(IOC_TRANSPORTER, iocTransporterLocation[i][0], iocTransporterLocation[i][1], iocTransporterLocation[i][2], iocTransporterLocation[i][3], 0, 1, 1.0f);
		m_teleporters[i]->PushToWorld(m_mapMgr);
		m_teleeffect[i] = SpawnGameObject(TELEPORTER_EFFECT_A, iocTransporterLocation[i][0], iocTransporterLocation[i][1], iocTransporterLocation[i][2], iocTransporterLocation[i][3], 0, 1, 1.0f);
		m_teleeffect[i]->PushToWorld(m_mapMgr);
	}
	for(uint32 i = 6; i < 12; i++)	// Horde
	{
		m_teleporters[i] = SpawnGameObject(IOC_TRANSPORTER, iocTransporterLocation[i][0], iocTransporterLocation[i][1], iocTransporterLocation[i][2], iocTransporterLocation[i][3], 0, 2, 1.0f);
		m_teleporters[i]->PushToWorld(m_mapMgr);
		m_teleeffect[i] = SpawnGameObject(TELEPORTER_EFFECT_H, iocTransporterLocation[i][0], iocTransporterLocation[i][1], iocTransporterLocation[i][2], iocTransporterLocation[i][3], 0, 1, 1.0f);
		m_teleeffect[i]->PushToWorld(m_mapMgr);
	}

	// Spawn Gates
	for(uint32 x = 0; x < 3; x++)
	{
		m_desgates[x] = SpawnGameObject(gatesIds[x], iocGatesLocation[x][0],  iocGatesLocation[x][1], iocGatesLocation[x][2], iocGatesLocation[x][3], 0, 1, 1.0f);
		m_desgates[x]->PushToWorld(m_mapMgr);
		m_desgates[x]->bannerslot = x;
		m_ogates[x] = SpawnGameObject(IOC_DYNAMIC_DOOR_A, iocGatesLocation[x][0],  iocGatesLocation[x][1], iocGatesLocation[x][2], iocGatesLocation[x][3], 0, 1, 1.0f);
		m_ogates[x]->SetUInt32Value(GAMEOBJECT_FLAGS, 32);
		m_ogates[x]->SetUInt32Value(GAMEOBJECT_DYNAMIC, 4294901760);
		m_ogates[x]->SetUInt32Value(GAMEOBJECT_FACTION, 1375);
		m_ogates[x]->SetUInt32Value(GAMEOBJECT_BYTES_1, 4278190081);
		m_ogates[x]->PushToWorld(m_mapMgr);
	}

	for(uint32 x = 3; x < 6; x++)
	{
		m_desgates[x] = SpawnGameObject(gatesIds[x], iocGatesLocation[x][0],  iocGatesLocation[x][1], iocGatesLocation[x][2], iocGatesLocation[x][3], 0, 2, 1.0f);
		m_desgates[x]->PushToWorld(m_mapMgr);
		m_desgates[x]->bannerslot = x;
		m_ogates[x] = SpawnGameObject(IOC_DYNAMIC_DOOR_H, iocGatesLocation[x][0],  iocGatesLocation[x][1], iocGatesLocation[x][2], iocGatesLocation[x][3], 0, 2, 1.0f);
		m_ogates[x]->SetUInt32Value(GAMEOBJECT_FLAGS, 32);
		m_ogates[x]->SetUInt32Value(GAMEOBJECT_DYNAMIC, 4294901760);
		m_ogates[x]->SetUInt32Value(GAMEOBJECT_FACTION, 1375);
		m_ogates[x]->SetUInt32Value(GAMEOBJECT_BYTES_1, 4278190081);
		m_ogates[x]->PushToWorld(m_mapMgr);
	}

	// Flagpole
	for(uint32 i = 0; i < IOC_NUM_CONTROL_POINTS; i++)
	{
		m_flagpole[i] = SpawnGameObject(IOC_FLAGPOLE, ControlPointCoordinates[i][0], ControlPointCoordinates[i][1], ControlPointCoordinates[i][2], ControlPointCoordinates[i][3], 0, 35, 1.0f);
		m_flagpole[i]->PushToWorld(m_mapMgr);
	}

	SpawnControlPoint(IOC_CONTROL_POINT_OILDERRICK,		IOC_SPAWN_TYPE_NEUTRAL);
	SpawnControlPoint(IOC_CONTROL_POINT_COBALTMINE,		IOC_SPAWN_TYPE_NEUTRAL);
	SpawnControlPoint(IOC_CONTROL_POINT_DOCKS,			IOC_SPAWN_TYPE_NEUTRAL);
	SpawnControlPoint(IOC_CONTROL_POINT_AIRSHIPHANGAR,	IOC_SPAWN_TYPE_NEUTRAL);
	SpawnControlPoint(IOC_CONTROL_POINT_SIEGEWORKSHOP,	IOC_SPAWN_TYPE_NEUTRAL);
	SpawnControlPoint(IOC_CONTROL_POINT_ALLIANCE_KEEP,	IOC_SPAWN_TYPE_ALLIANCE_CONTROLLED);
	SpawnControlPoint(IOC_CONTROL_POINT_HORDE_KEEP,		IOC_SPAWN_TYPE_HORDE_CONTROLLED);
}

void IsleOfConquest::HookOnPlayerKill(Player* plr, Player* pVictim)
{
	plr->AddHonor(20);
	plr->m_bgScore.KillingBlows++;
	UpdatePvPData();
}

void IsleOfConquest::HookOnHK(Player* plr)
{
	plr->AddHonor(10);
    plr->m_bgScore.HonorableKills++;
	UpdatePvPData();
}

void IsleOfConquest::AddReinforcements(uint32 teamId, uint32 amt)
{
	if( ((int32)( m_reinforcements[teamId] + amt )) > IOC_NUM_REINFORCEMENTS )
		m_reinforcements[teamId] = IOC_NUM_REINFORCEMENTS;
	else
		m_reinforcements[teamId] += amt;

	SetWorldState(WORLDSTATE_IOC_ALLIANCE_SCORE + teamId, m_reinforcements[teamId]);
}

void IsleOfConquest::RemoveReinforcements(uint32 teamId, uint32 amt)
{
	if( ((int32)( m_reinforcements[teamId] - amt )) < 0 )
		m_reinforcements[teamId] = 0;
	else
		m_reinforcements[teamId] -= amt;

	SetWorldState(WORLDSTATE_IOC_ALLIANCE_SCORE + teamId, m_reinforcements[teamId]);

	/*
	No resources just means no vehicles.
	if( m_reinforcements[teamId] == 0 )
	{
		Finish( teamId );
	}*/
}

LocationVector IsleOfConquest::GetStartingCoords(uint32 Team)
{
	if(Team)		// Horde
		return LocationVector(1264.06f, -736.73f, 48.91f, 3.07f);
	else			// Alliance
		return LocationVector(303.22f, -857.02f, 48.91f, 5.99f);
}

void IsleOfConquest::OnStart()
{
	for(uint32 i = 0; i < 2; i++) {
		for(set<Player*  >::iterator itr = m_players[i].begin(); itr != m_players[i].end(); itr++) {
			(*itr)->RemoveAura(BG_PREPARATION);
		}
	}

	PlaySoundToAll(SOUND_BATTLEGROUND_BEGIN);

	m_started = true;
	sEventMgr.AddEvent(this, &IsleOfConquest::AddReinforcements, (uint32)0, (uint32)200, EVENT_IOC_RESOURCES_UPDATE_TEAM_0, 60000, 0, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT); 
	sEventMgr.AddEvent(this, &IsleOfConquest::AddReinforcements, (uint32)1, (uint32)200, EVENT_IOC_RESOURCES_UPDATE_TEAM_1, 60000, 0, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT); 
}

void IsleOfConquest::HookGenerateLoot(Player* plr, Object* pCorpse)
{
	if(pCorpse->IsCorpse())
	{
		// add some money
		float gold = ((float(plr->getLevel()) / 2.5f)+1) * 100.0f;			// fix this later
		gold *= sWorld.getRate(RATE_MONEY);
		TO< Corpse* >(pCorpse)->loot.gold = float2int32(gold);
	}
}

void IsleOfConquest::HookOnShadowSight()
{
}

void IsleOfConquest::SetIsWeekend(bool isweekend)
{
}

void IsleOfConquest::HookOnUnitKill(Player* plr, Unit* pVictim)
{
	if(pVictim->IsPlayer())
		return;

	if(pVictim->GetEntry() == 34924)	// High Commander Halford Wyrmbane
	{
		Herald("The 7th Legion General is dead!");
		RemoveReinforcements( 0, IOC_NUM_REINFORCEMENTS );	// Horde Win
		Finish(0);
	}
	else if(pVictim->GetEntry() == 34922)	// Overlord Agmar
	{
		Herald("The Scarshield Legion General is dead!");
		RemoveReinforcements( 1, IOC_NUM_REINFORCEMENTS );	// Alliance Win
		Finish(1);
	}
}

void IsleOfConquest::Herald(const char *format, ...)
{
	char msgbuf[200];
	va_list ap;
	size_t msglen;
	WorldPacket data(SMSG_MESSAGECHAT, 500);

	va_start(ap, format);
	vsnprintf(msgbuf, 100, format, ap);
	va_end(ap);
	msglen = strlen(msgbuf);

	data << uint8(CHAT_MSG_MONSTER_YELL);
	data << uint32(LANG_UNIVERSAL);
	data << uint64(0);
	data << uint32(0);			// new in 2.1.0
	data << uint32(7);			// Herald
	data << "Herald";			// Herald
	data << uint64(0);
	data << uint32(msglen+1);
	data << msgbuf;
	data << uint8(0x00);
	DistributePacketToAll(&data);
}

void IsleOfConquest::Finish(uint32 losingTeam)
{
	if(m_ended)
		return;

	m_ended = true;
	sEventMgr.RemoveEvents(this);
	sEventMgr.AddEvent(TO< CBattleground* >(this), &CBattleground::Close, EVENT_BATTLEGROUND_CLOSE, 120000, 1,0);

	for(uint32 i = 0; i < 2; i++)
	{
		for(set<Player*  >::iterator itr = m_players[i].begin(); itr != m_players[i].end(); itr++)
		{
			(*itr)->Root();
			(*itr)->BroadcastMessage("The battle for the Isle of Conquest has ended, %s has won!", losingTeam ? "Alliance" : "Horde");
			if(i == losingTeam)
				(*itr)->AddHonor(75);	
			else
				(*itr)->AddHonor(200);
		}
	}

	UpdatePvPData();
}

void IsleOfConquest::HookOnFlagDrop(Player * plr)
{
}

void IsleOfConquest::HookGameObjectDamage(GameObject*go)
{
	switch(go->bannerslot)
	{
		case 1: // alliance west
		{
			if(go->HasFlags(GAMEOBJECT_FLAG_DESTROYED))
			{
				SendChatMessage(CHAT_MSG_BG_EVENT_NEUTRAL, 0, "Alliance Keep's West Gate has been destroyed!");
				SetWorldState(4327, 0);
				SetWorldState(4325, 1);
				AddHonorToTeam(10, 1);
			}
		}break;

		case 2: // alliance front
		{
			if(go->HasFlags(GAMEOBJECT_FLAG_DESTROYED))
			{
				SendChatMessage(CHAT_MSG_BG_EVENT_NEUTRAL, 0, "Alliance Keep's Front Gate has been destroyed!");
				SetWorldState(4328, 0);
				SetWorldState(4324, 1);
				AddHonorToTeam(10, 1);
			}
		}break;

		case 3: // alliance east
		{
			if(go->HasFlags(GAMEOBJECT_FLAG_DESTROYED))
			{
				SendChatMessage(CHAT_MSG_BG_EVENT_NEUTRAL, 0, "Alliance Keep's East Gate has been destroyed!");
				SetWorldState(4326, 0);
				SetWorldState(4323, 1);
				AddHonorToTeam(10, 1);
			}
		}break;

		case 4: // horde front
		{
			if(go->HasFlags(GAMEOBJECT_FLAG_DESTROYED))
			{
				SendChatMessage(CHAT_MSG_BG_EVENT_NEUTRAL, 0, "Horde Keep's Front Gate has been destroyed!");
				SetWorldState(4317, 0);
				SetWorldState(4322, 1);
				AddHonorToTeam(10, 0);
			}
		}break;

		case 5: // horde west
		{
			if(go->HasFlags(GAMEOBJECT_FLAG_DESTROYED))
			{
				SendChatMessage(CHAT_MSG_BG_EVENT_NEUTRAL, 0, "Horde Keep's West Gate has been destroyed!");
				SetWorldState(4318, 0);
				SetWorldState(4321, 1);
				AddHonorToTeam(10, 0);
			}
		}break;

		case 6: // horde east
		{
			if(go->HasFlags(GAMEOBJECT_FLAG_DESTROYED))
			{
				SendChatMessage(CHAT_MSG_BG_EVENT_NEUTRAL, 0, "Alliance Keep's West Gate has been destroyed!");
				SetWorldState(4319, 0);
				SetWorldState(4320, 1);
				AddHonorToTeam(10, 0);
			}
		}break;
	}
}

void IsleOfConquest::ApplyCaptureBonus(uint32 Id, uint32 team) //todo make this loop and apply bonuses that haven't been aplied.
{
	ActiveBonuses[team][Id] = true;
	switch(Id)
	{
		case 5:
		{
			SendChatMessage(CHAT_MSG_BG_EVENT_NEUTRAL, 0, "%s's resources now come by air, reinforcement gain time cut in half!", team ? "Horde" : "Alliance");
			sEventMgr.ModifyEventTime(this, EVENT_IOC_RESOURCES_UPDATE_TEAM_0 + team, 30000);
		}break;
		case 3:
		{
			SendChatMessage(CHAT_MSG_BG_EVENT_NEUTRAL, 0, "The %s have broken through the dock blockade! Demolisher's rams have been repaired!", team ? "Horde" : "Alliance");
			sEventMgr.ModifyEventTime(this, EVENT_IOC_RESOURCES_UPDATE_TEAM_0 + team, 60000);
		}break;
	}
}

void IsleOfConquest::RemoveCaptureBonus(uint32 Id, uint32 team)
{
	ActiveBonuses[team][Id] = false;
	switch(Id)
	{
		case 4:
		{
			SendChatMessage(CHAT_MSG_BG_EVENT_NEUTRAL, 0, "%s's resources no longer come by air, reinforcement gain time is now normal!", team ? "Horde" : "Alliance");
			sEventMgr.ModifyEventTime(this, EVENT_IOC_RESOURCES_UPDATE_TEAM_0 + team, 60000);
		}break;
		case 3:
		{
			SendChatMessage(CHAT_MSG_BG_EVENT_NEUTRAL, 0, "The dock has been blocked by %s demolishers rams no longer function!", team ? "Horde" : "Alliance");
			sEventMgr.ModifyEventTime(this, EVENT_IOC_RESOURCES_UPDATE_TEAM_0 + team, 60000);
		}break;

	}
}

void IsleOfConquest::CreateVehicle(uint8 team, uint32 entry, float x, float y, float z, float o)
{
	Creature * c = SpawnCreature(entry, x, y, z, o);
	if(c)
	{
		m_vehicles.insert(make_pair(c, team));
	}
}

void IsleOfConquest::AddHonorToTeam(uint32 amount, uint8 team)
{
	for(set<Player*  >::iterator itr = m_players[team].begin(); itr != m_players[team].end(); itr++)
	{
		(*itr)->AddHonor(amount);
	}
}

void IsleOfConquest::BuildVehicleSpellList(Creature *c, WorldPacket & data)
{
	#define MAKE_ACTION_BUTTON(A,T) uint32(uint32(A) | (uint32(T) << 24))
	if(c == NULL || !c->IsInWorld())
	{
		sLog.outError("IOC attempted to build a vehicle spell list for a nonexistant/not in world creature.");
		return;
	}
	uint32 spellcount = 0;
	Unit * controller = c->GetMapMgrUnit(c->GetCharmedByGUID());
	if(controller == NULL || !controller->IsInWorld())
	{
		sLog.outError("IOC attempted to build a vehicle spell list for a nonexistant/not in world controller.");
		return;
	}
	c->SetFaction(controller->GetFaction());
	switch(c->GetEntry())
	{
		case KEEP_CANNON:
		case CATAPULT:
		{
			spellcount = 2;
		}break;

		case DEMOLISHER:
		{
			spellcount = ActiveBonuses[c->GetTeam()][5] ? 1 : 2;
		}break;

		case FLAME_TURRET_A:
		case FLAME_TURRET_H:
		{
			spellcount = 1;
		}break;

		case SIEGE_ENGINE_A:
		case SIEGE_ENGINE_H:
		{
			spellcount = 2;
		}break;

		case SIEGE_TURRET_A:
		case SIEGE_TURRET_H:
		{
			spellcount = 2;
		}break;
		default:
		{
			sLog.outError("Unhandled vehicle attempting to build spell list. Entry: %u");
			return;
		}
	}
	data << uint64(c->GetGUID());
	data << uint16(c->GetCreatureInfo()->Family);
	data << uint32(0);
	data << uint32( 0x8000101 );
	uint8 count = 0;
	for (uint32 i = 0; i < 10; i++)
	{
		uint32 spellId = c->GetProto()->AISpells[i];

		SpellEntry const *spellInfo = dbcSpell.LookupEntryForced( spellId );
		if (!spellInfo || spellInfo->Id == 1 || i > spellcount)
		{
			data << uint16(0) << uint8(0) << uint8(i+8);
		}
		else
		{
			data << uint32(MAKE_ACTION_BUTTON(spellId,i+8));
			++count;
		}
	}
	data << count; // spells count
	data << uint8(0);
}

