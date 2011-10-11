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

#ifndef _TIOC_H
#define _TIOC_H

enum IOCControlPoints
{
	IOC_CONTROL_POINT_OILDERRICK				= 0,
	IOC_CONTROL_POINT_COBALTMINE				= 1,
	IOC_CONTROL_POINT_DOCKS						= 2,
	IOC_CONTROL_POINT_AIRSHIPHANGAR				= 3,
	IOC_CONTROL_POINT_SIEGEWORKSHOP				= 4,
	IOC_CONTROL_POINT_ALLIANCE_KEEP				= 5,
	IOC_CONTROL_POINT_HORDE_KEEP				= 6,
	IOC_NUM_CONTROL_POINTS						= 7,
};

enum IOCSpawnTypes
{
	IOC_SPAWN_TYPE_NEUTRAL				= 0,
	IOC_SPAWN_TYPE_ALLIANCE_ASSAULT		= 1,
	IOC_SPAWN_TYPE_HORDE_ASSAULT		= 2,
	IOC_SPAWN_TYPE_ALLIANCE_CONTROLLED	= 3,
	IOC_SPAWN_TYPE_HORDE_CONTROLLED		= 4,
	IOC_NODE_STATE_COUNT				= 5,
};

enum IOCvehicles
{
	KEEP_CANNON					= 34944,
	CATAPULT					= 34793,
	DEMOLISHER					= 34775,
	FLAME_TURRET_A				= 34778,
	FLAME_TURRET_H				= 36356,
	GLAIVE_THROWER_A			= 34802,
	GLAIVE_THROWER_H			= 35273,
	ALLIANCE_GUNSHIP_CANNON		= 34929,
	HORDE_GUNSHIP_CANNON		= 34935,
	SIEGE_ENGINE_A				= 34776,
	SIEGE_ENGINE_H				= 35069,
	SIEGE_TURRET_A				= 34777,
	SIEGE_TURRET_H				= 36355,
};

#define IOC_TRANSPORTER		195313
#define TELEPORTER_EFFECT_A		195701
#define TELEPORTER_EFFECT_H		195702
#define IOC_FLAGPOLE 	191311
#define IOC_DYNAMIC_DOOR_A		195703
#define IOC_DYNAMIC_DOOR_H		195491

#define BG_SCORE_IOC_BASE_ASSAULTED			0
#define BG_SCORE_IOC_BASE_DEFENDED			1

#define WORLDSTATE_IOC_ALLIANCE_SCORE						4221
#define WORLDSTATE_IOC_HORDE_SCORE							4222
#define WORLDSTATE_IOC_ALLIANCE_EAST_GATE					4326
#define WORLDSTATE_IOC_ALLIANCE_GATE_DESTROYED_1			4323		// east
#define WORLDSTATE_IOC_ALLIANCE_GATE_DESTROYED_2			4325		// west
#define WORLDSTATE_IOC_ALLIANCE_GATE_DESTROYED_3			4324		// front
#define WORLDSTATE_IOC_ALLIANCE_WEST_GATE					4327
#define WORLDSTATE_IOC_ALLIANCE_FRONT_GATE					4328
#define WORLDSTATE_IOC_ALLIANCE_KEEP_ALLIANCE_CONTROLLED	4339
#define WORLDSTATE_IOC_ALLIANCE_KEEP_HORDE_CONTROLLED		4340
#define WORLDSTATE_IOC_ALLIANCE_KEEP_ALLIANCE_ASSAULTED		4342
#define WORLDSTATE_IOC_ALLIANCE_KEEP_HORDE_ASSAULTED		4343
#define WORLDSTATE_IOC_ALLIANCE_KEEP_NETURAL				4341
#define WORLDSTATE_IOC_HORDE_KEEP_ALLIANCE_CONTROLLED		4344
#define WORLDSTATE_IOC_HORDE_KEEP_HORDE_CONTROLLED			4345
#define WORLDSTATE_IOC_HORDE_KEEP_ALLIANCE_ASSAULTED		4347
#define WORLDSTATE_IOC_HORDE_KEEP_HORDE_ASSAULTED			4348
#define WORLDSTATE_IOC_HORDE_KEEP_NETURAL					4346
#define WORLDSTATE_IOC_DOCKS_ALLIANCE_CONTROLLED			4304
#define WORLDSTATE_IOC_DOCKS_HORDE_CONTROLLED				4303
#define WORLDSTATE_IOC_DOCKS_ALLIANCE_ASSAULTED				4305
#define WORLDSTATE_IOC_DOCKS_HORDE_ASSAULTED				4302
#define WORLDSTATE_IOC_DOCKS_NETURAL						4301
#define WORLDSTATE_IOC_HANGAR_ALLIANCE_CONTROLLED			4299
#define WORLDSTATE_IOC_HANGAR_HORDE_CONTROLLED				4298
#define WORLDSTATE_IOC_HANGAR_ALLIANCE_ASSAULTED			4300
#define WORLDSTATE_IOC_HANGAR_HORDE_ASSAULTED				4297
#define WORLDSTATE_IOC_HANGAR_NETURAL						4296
#define WORLDSTATE_IOC_QUARRY_ALLIANCE_CONTROLLED			4309
#define WORLDSTATE_IOC_QUARRY_HORDE_CONTROLLED				4308
#define WORLDSTATE_IOC_QUARRY_ALLIANCE_ASSAULTED			4310
#define WORLDSTATE_IOC_QUARRY_HORDE_ASSAULTED				4307
#define WORLDSTATE_IOC_QUARRY_NETURAL						4306
#define WORLDSTATE_IOC_REFINERY_ALLIANCE_CONTROLLED			4314
#define WORLDSTATE_IOC_REFINERY_HORDE_CONTROLLED			4313
#define WORLDSTATE_IOC_REFINERY_ALLIANCE_ASSAULTED			4315
#define WORLDSTATE_IOC_REFINERY_HORDE_ASSAULTED				4312
#define WORLDSTATE_IOC_REFINERY_NETURAL						4311
#define WORLDSTATE_IOC_WORKSHOP_ALLIANCE_CONTROLLED			4229
#define WORLDSTATE_IOC_WORKSHOP_HORDE_CONTROLLED			4230
#define WORLDSTATE_IOC_WORKSHOP_ALLIANCE_ASSAULTED			4228
#define WORLDSTATE_IOC_WORKSHOP_HORDE_ASSAULTED				4293
#define WORLDSTATE_IOC_WORKSHOP_NETURAL						4294
#define WORLDSTATE_IOC_HORDE_EAST_GATE						4319
#define WORLDSTATE_IOC_HORDE_GATE_DESTROYED_1				4322		// front
#define WORLDSTATE_IOC_HORDE_GATE_DESTROYED_2				4320		// east
#define WORLDSTATE_IOC_HORDE_GATE_DESTROYED_3				4321		// west
#define WORLDSTATE_IOC_HORDE_WEST_GATE						4318
#define WORLDSTATE_IOC_HORDE_FRONT_GATE						4317

struct IOCLocation { float x; float y; float z; };
struct IOCSpawnLocation { float x; float y; float z; float o; };
struct IOCGameObject { uint32 id[IOC_NODE_STATE_COUNT]; float x; float y; float z; float o; float rot1; float rot2; };
struct IOCNodeTemplate
{
	const char *m_name;										// Stormpike Aid Station
	const bool m_isGraveyard;								// Is this a graveyard?
	const bool m_capturable;								// Is this capturable?
	const IOCLocation m_graveyardLocation;					// Revive location, also location of spirit guide
	const IOCGameObject m_flagLocation;						// Flag location (need to add GO id/properties here)
	const IOCGameObject m_auraLocation;						// Aura location
	const IOCGameObject m_glowLocation;						// Aura glow location
	const uint32 m_guardId[3];								// Horde/alliance guard ids
	const uint32 m_guardCount;								// Count of guards to spawn
	const uint32 m_bossId[3];								// Boss ID (e.g. Balinda), 0 = A, 1 = H, 2 = Neutral
	const IOCLocation *m_peonLocations;						// Used by mines.
	const IOCLocation m_bossLocation;						// Location of boss if there is one
	const uint32 m_initialSpawnId;							// Initial spawn (Bowmen) ID
	const uint32 m_worldStateFields[IOC_NODE_STATE_COUNT];	// State fields
	const uint32 m_defaultState;							// State of the node when battleground is spawned
};


class IsleOfConquest : public CBattleground
{
public:
	IsleOfConquest(MapMgr* mgr, uint32 id, uint32 lgroup, uint32 t);
	~IsleOfConquest();

	void HookOnPlayerDeath(Player* plr);
	void HookFlagDrop(Player* plr, GameObject* obj);
	void HookFlagStand(Player* plr, GameObject* obj);
	void HookOnMount(Player* plr);
	void SpawnControlPoint(uint32 Id, uint32 Type);
	void CaptureControlPoint(uint32 Id, uint32 Team);
	void Updateworkshop(uint32 Team);
	void AssaultControlPoint(Player* pPlayer, uint32 Id);
	void HookOnAreaTrigger(Player* plr, uint32 id);
	bool HookHandleRepop(Player* plr);
	void OnPlatformTeleport(Player* plr);
	void OnAddPlayer(Player* plr);
	void OnRemovePlayer(Player* plr);
	void OnCreate();
	void HookOnPlayerKill(Player* plr, Player* pVictim);
	void HookOnHK(Player* plr);
	void HookOnShadowSight();
	void HookOnFlagDrop(Player* plr);
	void Respawn();
	void AddReinforcements(uint32 teamId, uint32 amt);
	void RemoveReinforcements(uint32 teamId, uint32 amt);
	void HookGameObjectDamage(GameObject* go);
	LocationVector GetStartingCoords(uint32 Team);

	static CBattleground* Create(MapMgr* m, uint32 i, uint32 l, uint32 t) { return new IsleOfConquest(m, i, l, t); }

	const char * GetName() { return "Isle of Conquest"; }

	void OnStart();

	bool SupportsPlayerLoot() { return true; }
	bool HookSlowLockOpen(GameObject* pGo, Player* pPlayer, Spell* pSpell);

	void HookGenerateLoot(Player* plr, Object* pCorpse);

	void SetIsWeekend(bool isweekend);
	void HookOnUnitKill(Player* plr, Unit* pVictim);
	void Herald(const char *format, ...);
	void Finish(uint32 losingTeam);
	uint32 GetNameID() { return 83; }
	GameObject* m_ioccontrolPoints[IOC_NUM_CONTROL_POINTS];
	GameObject* m_ioccontrolPointAuras[IOC_NUM_CONTROL_POINTS];
protected:
	list< GameObject* > m_gates;
	uint32 m_reinforcements[2];
	bool m_nearingVictory[2];
	bool m_LiveCaptain[2];
	int m_bonusHonor;
	Creature* cannons[8];
	GameObject* m_flagpole[IOC_NUM_CONTROL_POINTS];
	GameObject* m_teleporters[12];
	GameObject* m_teleeffect[12];
	GameObject* m_desgates[6];
	GameObject* m_ogates[6];
	Creature* m_spiritGuides[IOC_NUM_CONTROL_POINTS];
	Creature* m_salesman;
	uint32 m_resources[2];
	uint32 m_capturedBases[2];
	uint32 m_lastHonorGainResources[2];
	int32 m_basesLastOwnedBy[IOC_NUM_CONTROL_POINTS];
	int32 m_basesOwnedBy[IOC_NUM_CONTROL_POINTS];
	int32 m_basesAssaultedBy[IOC_NUM_CONTROL_POINTS];
	bool m_flagIsVirgin[IOC_NUM_CONTROL_POINTS];
};

enum GENERAL_IOC_DEFINES
{
	IOC_NUM_REINFORCEMENTS				= 600,		// Amount of reinforcements we start off with
	IOC_SCORE_WARNING					= 530,		// Dunno what this should be ;p
	IOC_ADD_POINTS_ON_CONTROLLED_MINE	= 1,		// Points to give the team who controls (a) mine(s)
	IOC_REINFORCEMENT_ADD_INTERVAL		= 45000,	// The interval (in milliseconds) that points from mines are awarded
	IOC_POINTS_ON_DESTROY_BUNKER		= 75,		// Points to remove for destroying a team's bunker
	IOC_POINTS_ON_KILL					= 1,		// Points to remove when killing a member of the opposite team
	IOC_POINTS_ON_KILL_CAPTAIN			= 100,		// Points  to remove for killing a team's captain
	IOC_NUM_CONTESTED_AREAS				= 9,		// Total contested areas (graveyards/mines)
	IOC_NUM_DESTROYABLE_AREAS			= 8,		// Total destroyable areas (towers/bunkers)
	IOC_NUM_BOSS_UNITS					= 14,		// Boss units (generals/captains/wing commanders etc)
	IOC_NUM_COLDTOOTH_UNITS				= 5,		// Coldtooth mine NPC types
	IOC_NUM_IRONDEEP_UNITS				= 4,		// Irondeep mine NPC types
	IOC_NUM_SNOWFALL_FLAGS				= 2,		// Count of Snowfall flags (used when changing them on a team's acquiration of the CP
	IOC_CONTESTED_AREAS_START			= 0,		// ID at which contested points start (for loops/ifs)
	IOC_CONTESTED_AREAS_END				= 8,		// ID at which contested points end (for loops/ifs)
	IOC_DESTROYABLE_AREAS_START			= 9,		// ID at which destroyable points start (for loops/ifs)
	IOC_DESTROYABLE_AREAS_END			= 16,		// ID at which contested points finish (for loops/ifs)
	IOC_PER_KILL_HONOR					= 21,
};

#endif		// _TIOC_H
