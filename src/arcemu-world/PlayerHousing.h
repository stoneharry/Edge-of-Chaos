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

#pragma once

#define RE_BUILD_REV	4

class PlayerRealEstate
{
public:
	uint32 accountid;
	uint32 ownerguid;
	uint32 guildid;
	uint32 mapid;
	float positionX;
	float positionY;
	float positionZ;
	float lenghtX;
	float lenghtY;
	uint32 lease_start;
	uint32 lease_exp;
	uint32 pvp;
	uint32 earned;
	bool dirty;
};

int32 RealEstate_GetOwner(uint32 mapid, float x, float y);
//int32 RealEstate_GetAcct(uint32 owner);

PlayerRealEstate *RealEstate_GetRealEstate(uint32 mapid, float x, float y);

bool RealEstate_AsOwnerRights(Player *player, Object *object);
bool RealEstate_AsOwnerRights2(Player *player);

bool RealEstate_CanUseCommand(WorldSession *m_session, Object *object = NULL);
//bool RealEstate_CanGetReward(Player *player);

int32 RealEstate_LandCount(Player *player);

void RealEstate_Update(Player *player);
void RealEstate_Payup(Player *player);
void RealEstate_Save();

void GW_CheckPlayerCpu(Player *player);
