
#include "StdAfx.h"

/*
	To Do:
		- Spawn mobs at start of BG
		- Add waypoints to mobs (a way to automate this through DB?)
		- Player removing gear etc on enter, reset on leave (Terror was working on this)
		- Mob AI
		- Scenarios
		...
*/

HungerGames::HungerGames(MapMgr * mgr, uint32 id, uint32 lgroup, uint32 t) : CBattleground(mgr, id, lgroup, t)
{
	SpawnPoint = 0;
	ReaminingPlayers = 0;
	winningPlayer = "";
	m_started = false;

	for (int i = 0; i < 10; i++)
	{
		m_bubbles[i] = SpawnGameObject(184719, HG_SPAWN_POINTS[SpawnPoint][0], HG_SPAWN_POINTS[SpawnPoint][1], HG_SPAWN_POINTS[SpawnPoint][2], 0, 0, 35, 0.1f);
		m_bubbles[i]->SetScale(0.1f);
		m_bubbles[i]->SetByte(GAMEOBJECT_BYTES_1, 0, 1);
		m_bubbles[i]->SetUInt32Value(GAMEOBJECT_FLAGS, 32);
		m_bubbles[i]->SetFaction(114);
		m_bubbles[i]->SetByte(GAMEOBJECT_BYTES_1, 3, 100);
		m_bubbles[i]->PushToWorld(m_mapMgr);
	}

	sEventMgr.AddEvent(this, &HungerGames::CheckForWin, EVENT_HUNGER_GAMES_CHECK_FOR_WIN, 1000, 0, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
}

HungerGames::~HungerGames()
{
	for(uint32 i = 0; i < 2; ++i)
	{
		if(m_bubbles[i] != NULL)
		{
			if(!m_bubbles[i]->IsInWorld())
				delete m_bubbles[i];
		}
	}
}

void HungerGames::CheckForWin()
{
	if (m_started && ReaminingPlayers < 2)
	{
		for (int i = 0; i < 2; i++)
		{
			for (set<Player*  >::iterator itr = m_players[i].begin(); itr != m_players[i].end(); itr++)
			{
				if ((*itr)->isAlive())
				{
					winningPlayer = (*itr)->GetName();
					break;
				}
			}
		}

		Finish(0);
	}
}

bool HungerGames::HookHandleRepop(Player* plr)
{
	LocationVector dest_pos;
	
	dest_pos.ChangeCoords(HG_SPAWN_POINTS[SpawnPoint][0], HG_SPAWN_POINTS[SpawnPoint][1], HG_SPAWN_POINTS[SpawnPoint][2]);
	ReaminingPlayers++;
	SpawnPoint++;

	plr->SetFFAPvPFlag();

	if (!m_started)
		plr->CastSpell(plr, BG_PREPARATION, true);

	// port to it
	plr->SafeTeleport(plr->GetMapId(), plr->GetInstanceID(), dest_pos);
	return false;
}

void HungerGames::HookOnAreaTrigger(Player* plr, uint32 id)
{
}

void HungerGames::HookOnPlayerDeath(Player* plr)
{
	ReaminingPlayers--;
	plr->m_bgScore.Deaths++;
	UpdatePvPData();

	// Apparently you cannot loot your own factions corpse so we spawn a chest instead
	GameObject * chest = SpawnGameObject(6038333, plr->GetPositionX(), plr->GetPositionY(), plr->GetPositionZ(), 0, 0, 35, 1.0f);
	if(!chest)
	{
		delete chest;
		return;
	}
	chest->SetState(1);
	chest->PushToWorld(m_mapMgr);
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
	// players should not join during a game of hunger games
	UpdatePvPData();
	plr->SetFFAPvPFlag();
	ReaminingPlayers++;
}

void HungerGames::OnRemovePlayer(Player* plr)
{
	plr->RemoveAura(BG_PREPARATION);
	if (!plr->isAlive())
		ReaminingPlayers--;
	plr->RemoveFFAPvPFlag();
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
	m_started = true;

	for(uint32 i = 0; i < 2; i++) {
		for(set<Player*  >::iterator itr = m_players[i].begin(); itr != m_players[i].end(); itr++) {
			(*itr)->RemoveAura(BG_PREPARATION);
		}
	}

	for (int i = 0; i < 10; i++)
	{
		m_bubbles[i]->RemoveFromWorld(false);
		delete m_bubbles[i];
		m_bubbles[i] = NULL;
	}

	PlaySoundToAll(SOUND_BATTLEGROUND_BEGIN);
}

void HungerGames::HookGenerateLoot(Player* plr, Object* pCorpse)
{
}

void HungerGames::HookOnShadowSight()
{
}

void HungerGames::SetIsWeekend(bool isweekend)
{
}

void HungerGames::HookOnUnitKill(Player* plr, Unit* pVictim)
{
	// Can hook on special unit deaths here
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
	
	for (int i = 0; i < 2; i++)
	{
		for (set<Player*  >::iterator itr = m_players[i].begin(); itr != m_players[i].end(); itr++)
		{
			(*itr)->Root();

			if (winningPlayer == "")
				winningPlayer = "<No Winner>";

			(*itr)->BroadcastMessage("The Hunger Games has ended, %s has won!", winningPlayer.c_str());
			if ((*itr)->GetName() == winningPlayer) // not sure if this will work
				(*itr)->AddHonor(200);	
			else
				(*itr)->AddHonor(75);
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

void HungerGames::AddHonorToTeam(uint32 amount, uint8 team)
{
}
