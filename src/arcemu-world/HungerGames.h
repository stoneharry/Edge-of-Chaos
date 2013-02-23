
#ifndef _HUNG_H
#define _HUNG_H

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

	void OnStart();

	bool SupportsPlayerLoot() { return true; }
	bool HookSlowLockOpen(GameObject* pGo, Player* pPlayer, Spell* pSpell);

	void HookGenerateLoot(Player* plr, Object* pCorpse);

	void SetIsWeekend(bool isweekend);
	void HookOnUnitKill(Player* plr, Unit* pVictim);
	void Herald(const char *format, ...);
	void Finish(uint32 losingTeam);
	uint32 GetNameID() { return -1; }

	void CreateVehicle(uint8 team, uint32 entry, float x, float y, float z, float o);
	void AddHonorToTeam(uint32 amount, uint8 team);
protected:
	int m_bonusHonor;
	uint32 m_lastHonorGainResources[2];
	std::map<Creature*, uint8> m_vehicles;
	bool ActiveBonuses[1][6];
};

#endif
