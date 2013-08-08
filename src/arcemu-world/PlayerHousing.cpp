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
#include <svn_revision.h>
#define GWN_GPPERCYCLE	14

void ObjectMgr::LoadPlayerHousing()
{
	QueryResult * result = CharacterDatabase.Query("SELECT * FROM player_player_housing");
	if(result)
	{
		do 
		{
			PlayerRealEstate *re = new PlayerRealEstate;

			re->accountid = result->Fetch()[0].GetUInt32();
			re->ownerguid = result->Fetch()[1].GetUInt32();
			re->mapid = result->Fetch()[2].GetUInt32();
			re->positionX = result->Fetch()[3].GetFloat();
			re->positionY = result->Fetch()[4].GetFloat();
			re->positionZ = result->Fetch()[5].GetFloat();
			re->lenghtX = result->Fetch()[6].GetFloat();
			re->lenghtY = result->Fetch()[7].GetFloat();
			m_real_estate.insert(re);
		} while(result->NextRow());
		delete result;
	}

	Log.Notice("ObjectMgr", "%u real estate.", m_real_estate.size());
}

void ObjectMgr::ReloadPlayerHousing()
{
	m_real_estate.clear();
	LoadPlayerHousing();
}

bool RealEstate_AsOwnerRights(Player *player, Object *object)
{
	if(!player) 
		return false;

	if(!object) 
		object = player;

	PlayerRealEstate *re = RealEstate_GetRealEstate(object->GetMapId(), object->GetPositionX(), object->GetPositionY());

	if(!re) 
		return false;

	if(re->accountid == player->getPlayerInfo()->acct)
		return true;

	return false;
}

bool RealEstate_CanBuild(WorldSession *m_session, Object *object)
{
	Player *player = m_session->GetPlayer();

	if(!player) 
		return false;

	if(m_session->CanUseCommand('a'))
		return true;

	if(RealEstate_AsOwnerRights(player, object))
		return true;

	sChatHandler.RedSystemMessage(m_session, "You can only build at your house.");
	return false;
}

int32 RealEstate_GetOwner(uint32 mapid, float x, float y)
{
	objmgr.m_real_estate_lock.Acquire();
	for(std::set<PlayerRealEstate *>::iterator itr = objmgr.m_real_estate.begin(); 
		itr != objmgr.m_real_estate.end(); itr++)
	{
		PlayerRealEstate *re = (*itr);
		if(	mapid == re->mapid &&
			x > re->positionX - re->lenghtX &&
			x < re->positionX + re->lenghtX &&
			y > re->positionY - re->lenghtY &&
			y < re->positionY + re->lenghtY)
		{
			objmgr.m_real_estate_lock.Release();
			return re->ownerguid;
		}
	}

	objmgr.m_real_estate_lock.Release();
	return 0;
}


PlayerRealEstate *RealEstate_GetRealEstate(uint32 mapid, float x, float y)
{
	objmgr.m_real_estate_lock.Acquire();
	for(std::set<PlayerRealEstate *>::iterator itr = objmgr.m_real_estate.begin(); 
		itr != objmgr.m_real_estate.end(); itr++)
	{
		PlayerRealEstate *re = (*itr);
		if(	mapid == re->mapid &&
			x > re->positionX - re->lenghtX &&
			x < re->positionX + re->lenghtX &&
			y > re->positionY - re->lenghtY &&
			y < re->positionY + re->lenghtY)
		{
			objmgr.m_real_estate_lock.Release();
			return re;
		}
	}

	objmgr.m_real_estate_lock.Release();
	return NULL;
}

bool ChatHandler::RealEstate_LandBuy(const char* args, WorldSession *m_session)
{
	Player *player = m_session->GetPlayer();

	if(RealEstate_LandCount(player) >= (int32)sWorld.MaxLandStaff && m_session->CanUseCommand('a'))
	{
		sChatHandler.RedSystemMessage(m_session, "You have reached the maximum number of lands for staff you can buy.");
		return true;
	}
	else if(RealEstate_LandCount(player) >= (int32)sWorld.MaxLand)
	{
		sChatHandler.RedSystemMessage(m_session, "You have reached the maximum number of lands you can buy.");
		return true;
	}

	if(IS_INSTANCE(player->GetMapId()))
	{
		sChatHandler.RedSystemMessage(m_session, "You can't buy a land here since it's an instance.");
		return true;
	}

	AreaTable *at = dbcArea.LookupEntry(player->GetAreaID());
	if(!at)
		return true;

	if(	at->category == AREAC_SANCTUARY || at->AreaFlags & AREA_SANCTUARY)
	{
		sChatHandler.RedSystemMessage(m_session, "You can't buy a land here since it's a sanctuary.");
		return true;
	}

	uint32 lenght = sWorld.LandSize;

	if(at->AreaFlags & AREA_CITY_AREA || at->AreaFlags & AREA_CITY)
		lenght = sWorld.LandSizeCity;

	// check out if already owned
	objmgr.m_real_estate_lock.Acquire();

	uint32 o0 = RealEstate_GetOwner(player->GetMapId(), player->GetPositionX(), player->GetPositionY());

	uint32 o1 = RealEstate_GetOwner(player->GetMapId(), player->GetPositionX() - lenght, player->GetPositionY() - lenght);
	uint32 o2 = RealEstate_GetOwner(player->GetMapId(), player->GetPositionX() + lenght, player->GetPositionY() - lenght);
	uint32 o3 = RealEstate_GetOwner(player->GetMapId(), player->GetPositionX() - lenght, player->GetPositionY() + lenght);
	uint32 o4 = RealEstate_GetOwner(player->GetMapId(), player->GetPositionX() + lenght, player->GetPositionY() + lenght);

	uint32 o5 = RealEstate_GetOwner(player->GetMapId(), player->GetPositionX() - lenght, player->GetPositionY());
	uint32 o6 = RealEstate_GetOwner(player->GetMapId(), player->GetPositionX() + lenght, player->GetPositionY());
	uint32 o7 = RealEstate_GetOwner(player->GetMapId(), player->GetPositionX(), player->GetPositionY() + lenght);
	uint32 o8 = RealEstate_GetOwner(player->GetMapId(), player->GetPositionX(), player->GetPositionY() - lenght);

	if(	(o0 && o0 != player->GetLowGUID()) || 
		(o1 && o1 != player->GetLowGUID()) || (o2 && o2 != player->GetLowGUID()) || 
		(o3 && o3 != player->GetLowGUID()) || (o4 && o4 != player->GetLowGUID()) ||
		(o5 && o5 != player->GetLowGUID()) || (o6 && o6 != player->GetLowGUID()) || 
		(o7 && o7 != player->GetLowGUID()) || (o8 && o8 != player->GetLowGUID()))
	{
		sChatHandler.RedSystemMessage(m_session, "There is not enough place here to buy.");
		objmgr.m_real_estate_lock.Release();
		return true;
	}

	CharacterDatabase.Execute(
		"insert into player_real_estate values(%d, %d, %d, %f, %f, %f, %d, %d)",
		player->getPlayerInfo()->acct, player->GetLowGUID(), player->GetMapId(), 
		player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), 
		lenght, lenght);

	PlayerRealEstate *re = new PlayerRealEstate;

	re->accountid = player->getPlayerInfo()->acct;
	re->ownerguid = player->GetLowGUID();
	re->guildid = 0;
	re->mapid = player->GetMapId();
	re->positionX = player->GetPositionX();
	re->positionY = player->GetPositionY();
	re->positionZ = player->GetPositionZ();
	re->lenghtX = (float)lenght;
	re->lenghtY = (float)lenght;

	objmgr.m_real_estate.insert(re);
	objmgr.m_real_estate_lock.Release();
	sChatHandler.GreenSystemMessage(m_session, "You now own your very own house!");

	return true;
}

bool ChatHandler::RealEstate_LandSell(const char* args, WorldSession *m_session)
{
	Player *player = m_session->GetPlayer();
	if(!player) return true;

	uint32 count = 0;
	if(*args)
	{
		char *pcount = strtok((char*)args, " ");
		if(pcount)
			count = atoi(pcount);
	}

	if(!count)
	{
		PlayerRealEstate *re = RealEstate_GetRealEstate(player->GetMapId(),
			player->GetPositionX(), player->GetPositionY());
		if(re && re->accountid == player->getPlayerInfo()->acct)
		{
			CharacterDatabase.Execute(
				"delete from player_real_estate where ownerguid=%d and mapid=%d and "\
				"positionX>%f and positionX<%f and positionY>%f and positionY<%f",
				re->ownerguid, re->mapid, re->positionX-1, re->positionX+1,
				re->positionY-1, re->positionY+1);

			objmgr.m_real_estate.erase(re);
			delete re;

			player->m_owneracct = 0;
			player->m_ownerguid = 0;
			player->m_ownerguild = 0;

			sChatHandler.GreenSystemMessage(m_session, "You have sold the land at your current location.");
		}
		else
			sChatHandler.RedSystemMessage(m_session, "This is not your land.");

		return true;
	}

	uint32 i = 0;
	objmgr.m_real_estate_lock.Acquire();

	for(std::set<PlayerRealEstate *>::iterator itr = objmgr.m_real_estate.begin(); 
		itr != objmgr.m_real_estate.end(); itr++)
	{
		PlayerRealEstate *re = (*itr);
		if(re->accountid == player->getPlayerInfo()->acct)
		{
			i++;
			if(i == count)
			{
				//Uncomment for spawns deleted.

				/*WorldDatabase.Execute(
					"delete from gameobject_spawns where map=%d and "\
					"position_x>%f and position_x<%f and position_y>%f and position_y<%f", 
					player->GetMapId(), 
					player->GetPositionX()-sWorld.LandSize, player->GetPositionX()+sWorld.LandSize,
					player->GetPositionY()-sWorld.LandSize, player->GetPositionY()+sWorld.LandSize);

				WorldDatabase.Execute(
					"delete from creature_spawns where map=%d and "\
					"position_x>%f and position_x<%f and position_y>%f and position_y<%f", 
					player->GetMapId(), 
					player->GetPositionX()-sWorld.LandSize, player->GetPositionX()+sWorld.LandSize,
					player->GetPositionY()-sWorld.LandSize, player->GetPositionY()+sWorld.LandSize);*/

	            CharacterDatabase.Execute(
					"delete from player_real_estate where ownerguid=%d and mapid=%d and "\
					"positionX>%f and positionX<%f and positionY>%f and positionY<%f",
					re->ownerguid, re->mapid, re->positionX-1, re->positionX+1,
					re->positionY-1, re->positionY+1);

				objmgr.m_real_estate.erase(re);
				delete re;

				objmgr.m_real_estate_lock.Release();

				sChatHandler.GreenSystemMessage(m_session, "You have sold your land number %d", count);
				return true;
			}
		}
	}

	objmgr.m_real_estate_lock.Release();

	sChatHandler.RedSystemMessage(m_session, "You don't have a land with that number.");
	return true;
}

bool ChatHandler::RealEstate_LandInfo(const char* args, WorldSession *m_session)
{
	Player *player = m_session->GetPlayer();
	if(!player) return true;

	PlayerRealEstate *re = RealEstate_GetRealEstate(player->GetMapId(), player->GetPositionX(),
		player->GetPositionY());
	if(!re)
	{
		sChatHandler.GreenSystemMessage(m_session, "This land is free to buy.");
		return true;
	}

	PlayerInfo *pinfo = objmgr.GetPlayerInfo(re->ownerguid);
	if(!pinfo)
	{
		sChatHandler.GreenSystemMessage(m_session, "This land got an unknown owner.");
		return true;
	}

	sChatHandler.GreenSystemMessage(m_session, 
		"This land is owned by %s, set to %s and expires in %d day(s) %s.",
		pinfo->name, re->pvp == 0? "pve": re->pvp == 1? "pvp": "arena", 
		(re->lease_exp - int(time(NULL)))/(24*60*60)+1, re->guildid? "- guild": "");

	return true;
}
