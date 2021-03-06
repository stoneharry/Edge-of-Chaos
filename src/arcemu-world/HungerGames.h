
#ifndef _HUNG_H
#define _HUNG_Hb

const float HG_SPAWN_POINTS[10][3] = {
	{15747.00f, 15687.00f, 1.00f},
	{15730.00f, 15798.00f, 1.00f},
	{16260.00f, 15843.00f, 0.00f},
	{15911.00f, 16060.00f, 0.00f},
	{15997.00f, 15901.00f, 1.00f},
	{15927.00f, 15752.00f, 1.00f},
	{15688.00f, 16023.00f, 1.00f},
	{16245.00f, 16095.00f, 0.00f},
	{16014.00f, 16307.00f, 0.00f},
	{15999.00f, 15639.00f, 0.00f}
};

#define HG_AVERAGE_CHEST_COUNT 35
const float HG_AVERAGE_CHESTS[HG_AVERAGE_CHEST_COUNT][4] = {
	{15684.00f, 15819.00f, 0.00f, 0.00f}, 
	{15704.00f, 15710.00f, 0.00f, 0.00f}, 
	{15739.00f, 15648.00f, 0.00f, 0.00f}, 
	{15816.00f, 15642.00f, 1.00f, 0.00f}, 
	{15805.00f, 15713.00f, 8.00f, 0.00f}, 
	{15837.00f, 15682.00f, 0.00f, 0.00f}, 
	{15874.00f, 15729.00f, 0.00f, 0.00f}, 
	{15918.00f, 15675.00f, 0.00f, 0.00f}, 
	{16034.00f, 15678.00f, -2.00f, 0.00f}, 
	{16142.00f, 15714.00f, 5.00f, 0.00f}, 
	{16178.00f, 15748.00f, 8.00f, 0.00f}, 
	{16202.00f, 15734.00f, 0.00f, 0.00f}, 
	{16266.00f, 15826.00f, 0.00f, 0.00f}, 
	{16261.00f, 15866.00f, 0.00f, 0.00f}, 
	{16329.00f, 15942.00f, 0.00f, 0.00f}, 
	{16279.00f, 16022.00f, 0.00f, 0.00f}, 
	{16311.00f, 16088.00f, 0.00f, 0.00f}, 
	{16325.00f, 16061.00f, 0.00f, 0.00f}, 
	{16281.00f, 16150.00f, 0.00f, 0.00f}, 
	{16244.00f, 16156.00f, 0.00f, 0.00f}, 
	{16147.00f, 16202.00f, 0.00f, 0.00f}, 
	{16152.00f, 16296.00f, 1.00f, 0.00f}, 
	{16077.00f, 16339.00f, 0.00f, 0.00f}, 
	{15946.00f, 16358.00f, 0.00f, 0.00f}, 
	{15897.00f, 16346.00f, -15.00f, 0.00f}, 
	{15782.00f, 16298.00f, 0.00f, 0.00f}, 
	{15745.00f, 16222.00f, -2.00f, 0.00f}, 
	{15850.00f, 16096.00f, -3.00f, 0.00f}, 
	{15897.00f, 15985.00f, 0.00f, 0.00f}, 
	{15905.00f, 15895.00f, 0.00f, 0.00f}, 
	{15903.00f, 15895.00f, 0.00f, 0.00f}, 
	{15943.00f, 15892.00f, -2.00f, 0.00f}, 
	{15729.00f, 15909.00f, 1.00f, 0.00f}, 
	{15768.00f, 15842.00f, 0.00f, 0.00f}, 
	{15670.00f, 15775.00f, 6.00f, 0.00f}
};

#define HG_MURLOC_COUNT 14
const float HG_MURLOC_SPAWNS[HG_MURLOC_COUNT][4] = {
	{15832.00f, 16265.00f, 0.00f, 0.00f},
	{15848.00f, 16179.00f, 0.00f, 0.00f},
	{15854.00f, 16134.00f, 0.00f, 0.00f},
	{15944.00f, 15951.00f, 0.00f, 0.00f},
	{16096.00f, 15868.00f, 0.00f, 0.00f},
	{16106.00f, 15799.00f, 0.00f, 0.00f},
	{16195.00f, 15813.00f, 0.00f, 0.00f},
	{16233.00f, 15930.00f, 0.00f, 0.00f},
	{16180.00f, 15978.00f, 0.00f, 0.00f},
	{16112.00f, 16015.00f, 0.00f, 0.00f},
	{16064.00f, 16068.00f, 0.00f, 0.00f},
	{16054.00f, 16113.00f, 0.00f, 0.00f},
	{16058.00f, 16184.00f, 0.00f, 0.00f},
	{16055.00f, 16233.00f, 0.00f, 0.00f}
};

#define HG_GOBLIN_COUNT 15
const float HG_GOBLIN_SPAWNS[HG_GOBLIN_COUNT][2] = {
	{16229.00f, 16196.00f},
	{16264.00f, 16106.00f},
	{16304.00f, 16010.00f},
	{16245.00f, 15954.00f},
	{16094.00f, 15813.00f},
	{16017.00f, 15818.00f},
	{15995.00f, 15809.00f},
	{15929.00f, 15779.00f},
	{15938.00f, 15743.00f},
	{15937.00f, 15709.00f},
	{15971.00f, 15636.00f},
	{16017.00f, 15646.00f},
	{16155.00f, 16166.00f},
	{16122.00f, 16273.00f},
	{16115.00f, 16268.00f}
};

class HungerGames : public CBattleground
{
public:
	HungerGames(MapMgr* mgr, uint32 id, uint32 lgroup, uint32 t);
	~HungerGames();

	void HookOnPlayerDeath(Player* plr);
	void HookFlagDrop(Player* plr, GameObject* obj);
	void HookFlagStand(Player* plr, GameObject* obj);
	void HookOnMount(Player* plr);
	void HookOnAreaTrigger(Player* plr, uint32 id);
	bool HookHandleRepop(Player* plr);
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

	static CBattleground* Create(MapMgr* m, uint32 i, uint32 l, uint32 t) { return new HungerGames(m, i, l, t); }

	const char * GetName() { return "Hunger Games"; }
	uint32 GetNameID() { return 84; }

	void OnStart();

	bool SupportsPlayerLoot() { return true; }
	bool HookSlowLockOpen(GameObject* pGo, Player* pPlayer, Spell* pSpell);

	void HookGenerateLoot(Player* plr, Object* pCorpse);

	void SetIsWeekend(bool isweekend);
	void HookOnUnitKill(Player* plr, Unit* pVictim);
	void Herald(const char *format, ...);
	void Finish(uint32 losingTeam);

	void AddHonorToTeam(uint32 amount, uint8 team);

	void CheckForWin();
protected:
	int m_bonusHonor;
	uint32 m_lastHonorGainResources[2];
	bool ActiveBonuses[1][6];
	int SpawnPoint;
	int ReaminingPlayers;
	uint64 winningPlayer;
	GameObject * m_bubbles[10];
	enum EventList {
		EVENT_HUNGER_GAMES_CHECK_FOR_WIN = 0
	};
};

#endif