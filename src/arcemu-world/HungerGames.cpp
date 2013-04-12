
#include "StdAfx.h"

/*
	To Do:
		- Spawn mobs at start of BG
		- Add waypoints to mobs (a way to automate this through DB?)
		- Mob AI
		- Scenarios
		- If a player dies then leaves, it will count as 2 players getting killed at the moment
		- Player cannot speak when exiting the BG
		- Talent points are not fully restored when exiting the BG - player gets 5 new talent points still
		- Server froze up with no crash dump when entering the BG a second time
		...
*/

HungerGames::HungerGames(MapMgr * mgr, uint32 id, uint32 lgroup, uint32 t) : CBattleground(mgr, id, lgroup, t)
{
	SpawnPoint = 0;
	ReaminingPlayers = 0;
	winningPlayer = 0;
	m_started = false;

	for (int i = 0; i < 10; i++) // Pushing this object to world is causing a crash for some reason. Tried using mgr passed in function and pushing later on. Still crashes.
	{
		m_bubbles[i] = SpawnGameObject(184719, HG_SPAWN_POINTS[i][0], HG_SPAWN_POINTS[i][1], HG_SPAWN_POINTS[i][2], 0, 35, 0, 0.1f);
		if(!m_bubbles[i])
		{
			delete m_bubbles[i];
			continue;
		}
		m_bubbles[i]->SetByte(GAMEOBJECT_BYTES_1, 0, 1);
		m_bubbles[i]->SetByte(GAMEOBJECT_BYTES_1, 3, 100);
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
					winningPlayer = (*itr)->GetGUID();
					break;
				}
			}
		}

		Finish(0);
	}
}

bool HungerGames::HookHandleRepop(Player* plr)
{
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
	if (m_started && plr->GetSession()->GetPermissionCount() != 0) // If a GM and game has started do not count
	{
		UpdatePvPData();
		plr->SetFFAPvPFlag();
		plr->SaveBlock(true);
		return;
	}

	LocationVector dest_pos;
	dest_pos.ChangeCoords(HG_SPAWN_POINTS[SpawnPoint][0], HG_SPAWN_POINTS[SpawnPoint][1], HG_SPAWN_POINTS[SpawnPoint][2]);
	plr->SafeTeleport(plr->GetMapId(), plr->GetInstanceID(), dest_pos);

	if(!m_started)
		plr->CastSpell(plr, BG_PREPARATION, true);
	// players should not join during a game of hunger games
	UpdatePvPData();
	plr->SetFFAPvPFlag();
	ReaminingPlayers++;
	plr->SaveBlock(true);
	SpawnPoint++;
	plr->BroadcastMessage("[EoC-Addon] HungerGamesOpen");
}

void HungerGames::OnRemovePlayer(Player* plr)
{
	Herald("%s has left the game!", plr->GetName());
	plr->RemoveAura(BG_PREPARATION);
	ReaminingPlayers--;
	plr->RemoveFFAPvPFlag();
	plr->SaveBlock(false);
}

void HungerGames::OnCreate()
{
	int i;
	// Push bubbles to world
	for (i = 0; i < 10; i++)
	{
		if(m_bubbles[i] && !m_bubbles[i]->IsInWorld())
			m_bubbles[i]->PushToWorld(m_mapMgr);
	}
	// Push average chests to world (does one of two random location generations)
	bool spawn = false;
	if (rand() % 2 == 1)
		spawn = true;
	for (i = 0; i < HG_AVERAGE_CHEST_COUNT; i++)
	{
		if (spawn)
		{
			GameObject * temp = SpawnGameObject(2855, HG_AVERAGE_CHESTS[i][0], HG_AVERAGE_CHESTS[i][1], HG_AVERAGE_CHESTS[i][2], 0, 35, 0, 1.0f);
			if(!temp)
			{
				delete temp;
				continue;
			}
			temp->SetState(1);
			temp->PushToWorld(m_mapMgr);
		}
		spawn = !spawn;
	}
	// Spawn creatures
	// ...
}

void HungerGames::HookOnPlayerKill(Player* plr, Player* pVictim)
{
	plr->AddHonor(20);
	plr->m_bgScore.KillingBlows++;
	UpdatePvPData();
	Herald("%s has killed %s!", plr->GetName(), pVictim->GetName());
	if (ReaminingPlayers > 1)
		Herald("There are just %d players remaining!", ReaminingPlayers);
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
		if(m_bubbles[i] && m_bubbles[i]->IsInWorld())
			m_bubbles[i]->RemoveFromWorld(false);
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
	const char* winnername = "no one";
	sEventMgr.AddEvent(TO< CBattleground* >(this), &CBattleground::Close, EVENT_BATTLEGROUND_CLOSE, 120000, 1,0);
	for (int i = 0; i < 2; i++)
	{
		for (set<Player*  >::iterator itr = m_players[i].begin(); itr != m_players[i].end(); itr++)
		{
			Player * plr = (*itr);
			plr->Root();

			if (plr->GetGUID() == winningPlayer)
			{
				plr->AddHonor(200);
				winnername = (*itr)->GetName();
			}
			else
				plr->AddHonor(75);
		}
	}

	Herald("The Divide has ended, %s has won!", winnername);

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
