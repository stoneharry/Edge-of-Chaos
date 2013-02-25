
#include "StdAfx.h"

/*
	To Do:
		- Make player leave shortly after death
		- Spawn mobs at start of BG
		- Add waypoints to mobs (a way to automate this through DB?)
		- Player removing gear etc on enter, reset on leave (Terror was working on this)
		- Mob AI
		- Scenarios
		- Events
		- Reward for killing players
		...
*/

HungerGames::HungerGames(MapMgr * mgr, uint32 id, uint32 lgroup, uint32 t) : CBattleground(mgr, id, lgroup, t)
{
	SpawnPoint = 0;
}

HungerGames::~HungerGames()
{
}

bool HungerGames::HookHandleRepop(Player* plr)
{
	LocationVector dest_pos;
	
	dest_pos.ChangeCoords(HG_SPAWN_POINTS[SpawnPoint][0], HG_SPAWN_POINTS[SpawnPoint][1], HG_SPAWN_POINTS[SpawnPoint][2]);
	SpawnPoint++;

	// port to it
	plr->SafeTeleport(plr->GetMapId(), plr->GetInstanceID(), dest_pos);
	return false;
}

void HungerGames::HookOnAreaTrigger(Player* plr, uint32 id)
{
}

void HungerGames::HookOnPlayerDeath(Player* plr)
{
	plr->m_bgScore.Deaths++;
	UpdatePvPData();
}

void HungerGames::HookFlagDrop(Player* plr, GameObject* obj)
{
}

void HungerGames::HookFlagStand(Player* plr, GameObject* obj)
{
}

bool HungerGames::HookSlowLockOpen(GameObject* pGo, Player* pPlayer, Spell* pSpell)
{
	return false;
}

void HungerGames::HookOnMount(Player* plr)
{
}

void HungerGames::OnAddPlayer(Player* plr)
{
	if(!m_started)
		plr->CastSpell(plr, BG_PREPARATION, true);
	UpdatePvPData();
}

void HungerGames::OnRemovePlayer(Player* plr)
{
	plr->RemoveAura(BG_PREPARATION);
}

void HungerGames::OnCreate()
{
	// Spawn creatures
}

void HungerGames::HookOnPlayerKill(Player* plr, Player* pVictim)
{
	plr->AddHonor(20);
	plr->m_bgScore.KillingBlows++;
	UpdatePvPData();
}

void HungerGames::HookOnHK(Player* plr)
{
	plr->AddHonor(10);
    plr->m_bgScore.HonorableKills++;
	UpdatePvPData();
}

void HungerGames::AddReinforcements(uint32 teamId, uint32 amt)
{
}

void HungerGames::RemoveReinforcements(uint32 teamId, uint32 amt)
{
}

LocationVector HungerGames::GetStartingCoords(uint32 Team)
{
	return LocationVector(HG_SPAWN_POINTS[SpawnPoint][0], HG_SPAWN_POINTS[SpawnPoint][1], HG_SPAWN_POINTS[SpawnPoint][2], HG_SPAWN_POINTS[SpawnPoint][3]);
}

void HungerGames::OnStart()
{
	for(uint32 i = 0; i < 2; i++) {
		for(set<Player*  >::iterator itr = m_players[i].begin(); itr != m_players[i].end(); itr++) {
			(*itr)->RemoveAura(BG_PREPARATION);
		}
	}

	PlaySoundToAll(SOUND_BATTLEGROUND_BEGIN);

	m_started = true;
}

void HungerGames::HookGenerateLoot(Player* plr, Object* pCorpse)
{
	if(pCorpse->IsCorpse())
	{
		// add some money
		float gold = ((float(plr->getLevel()) / 2.5f)+1) * 100.0f;
		gold *= sWorld.getRate(RATE_MONEY);
		TO< Corpse* >(pCorpse)->loot.gold = float2int32(gold);
	}
}

void HungerGames::HookOnShadowSight()
{
}

void HungerGames::SetIsWeekend(bool isweekend)
{
}

void HungerGames::HookOnUnitKill(Player* plr, Unit* pVictim)
{
}

void HungerGames::Herald(const char *format, ...)
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

void HungerGames::Finish(uint32 losingTeam)
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
			(*itr)->BroadcastMessage("The Hunger Games has ended, %s has won!", losingTeam ? "Alliance" : "Horde");
			if(i == losingTeam)
				(*itr)->AddHonor(75);	
			else
				(*itr)->AddHonor(200);
		}
	}

	UpdatePvPData();
}

void HungerGames::HookOnFlagDrop(Player * plr)
{
}

void HungerGames::HookGameObjectDamage(GameObject*go)
{
}

void HungerGames::CreateVehicle(uint8 team, uint32 entry, float x, float y, float z, float o)
{
	Creature * c = SpawnCreature(entry, x, y, z, o);
	if(c)
	{
		m_vehicles.insert(make_pair(c, team));
	}
}

void HungerGames::AddHonorToTeam(uint32 amount, uint8 team)
{
	for(set<Player*  >::iterator itr = m_players[team].begin(); itr != m_players[team].end(); itr++)
	{
		(*itr)->AddHonor(amount);
	}
}
