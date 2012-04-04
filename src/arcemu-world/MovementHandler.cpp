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
#define SWIMMING_TOLERANCE_LEVEL -0.08f
#define MOVEMENT_PACKET_TIME_DELAY 500

#ifdef WIN32

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#define DELTA_EPOCH_IN_USEC  11644473600000000ULL
uint32 TimeStamp()
{
	//return timeGetTime();

	FILETIME ft;
	uint64 t;
	GetSystemTimeAsFileTime(&ft);

	t = (uint64)ft.dwHighDateTime << 32;
	t |= ft.dwLowDateTime;
	t /= 10;
	t -= DELTA_EPOCH_IN_USEC;

	return uint32(((t / 1000000L) * 1000) + ((t % 1000000L) / 1000));
}

uint32 mTimeStamp()
{
	return timeGetTime();
}

#else

uint32 TimeStamp()
{
	struct timeval tp;
	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1000) + (tp.tv_usec / 1000);
}

uint32 mTimeStamp()
{
	struct timeval tp;
	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1000) + (tp.tv_usec / 1000);
}

#endif

void WorldSession::HandleMoveWorldportAckOpcode(WorldPacket & recv_data)
{
	GetPlayer()->SetPlayerStatus(NONE);
	if(_player->IsInWorld())
	{
		// get outta here
		return;
	}
	LOG_DEBUG("WORLD: got MSG_MOVE_WORLDPORT_ACK.");

	if(_player->m_CurrentTransporter && _player->GetMapId() != _player->m_CurrentTransporter->GetMapId())
	{
		/* wow, our pc must really suck. */
		Transporter* pTrans = _player->m_CurrentTransporter;

		float c_tposx = pTrans->GetPositionX() + _player->transporter_info.x;
		float c_tposy = pTrans->GetPositionY() + _player->transporter_info.y;
		float c_tposz = pTrans->GetPositionZ() + _player->transporter_info.z;


		_player->SetMapId(pTrans->GetMapId());
		_player->SetPosition(c_tposx, c_tposy, c_tposz, _player->GetOrientation());

		WorldPacket dataw(SMSG_NEW_WORLD, 20);

		dataw << pTrans->GetMapId();
		dataw << c_tposx;
		dataw << c_tposy;
		dataw << c_tposz;
		dataw << _player->GetOrientation();

		SendPacket(&dataw);
	}
	else
	{
		_player->m_TeleportState = 2;
		_player->AddToWorld();
	}
}

void WorldSession::HandleMoveTeleportAckOpcode(WorldPacket & recv_data)
{
	WoWGuid guid;
	recv_data >> guid;
    uint32 flags, time;
    recv_data >> flags >> time;
	if(m_MoverWoWGuid.GetOldGuid() == _player->GetGUID())
	{
		if(sWorld.antihack_teleport && !(HasGMPermissions() && sWorld.no_antihack_on_gm) && _player->GetPlayerStatus() != TRANSFER_PENDING)
		{
			/* we're obviously cheating */
			sCheatLog.writefromsession(this, "Used teleport hack, disconnecting.");
			Disconnect();
			return;
		}

		if(sWorld.antihack_teleport && !(HasGMPermissions() && sWorld.no_antihack_on_gm) && _player->m_position.Distance2DSq(_player->m_sentTeleportPosition) > 625.0f)	/* 25.0f*25.0f */
		{
			/* cheating.... :( */
			sCheatLog.writefromsession(this, "Used teleport hack {2}, disconnecting.");
			Disconnect();
			return;
		}

		LOG_DEBUG("WORLD: got MSG_MOVE_TELEPORT_ACK.");
		GetPlayer()->SetPlayerStatus(NONE);
		_player->SpeedCheatReset();

		std::list<Pet*> summons = _player->GetSummons();
		for(std::list<Pet*>::iterator itr = summons.begin(); itr != summons.end(); ++itr)
		{
			// move pet too
			(*itr)->SetPosition((GetPlayer()->GetPositionX() + 2), (GetPlayer()->GetPositionY() + 2), GetPlayer()->GetPositionZ(), M_PI_FLOAT);
		}
		if(_player->m_sentTeleportPosition.x != 999999.0f)
		{
			_player->m_position = _player->m_sentTeleportPosition;
			_player->m_sentTeleportPosition.ChangeCoords(999999.0f, 999999.0f, 999999.0f);
		}
	}

}

void _HandleBreathing(MovementInfo & movement_info, Player* _player, WorldSession* pSession)
{
	// no water breathing is required
	if(!sWorld.BreathingEnabled || _player->FlyCheat || _player->m_bUnlimitedBreath || !_player->isAlive() || _player->GodModeCheat)
	{
		// player is flagged as in water
		if(_player->m_UnderwaterState & UNDERWATERSTATE_SWIMMING)
			_player->m_UnderwaterState &= ~UNDERWATERSTATE_SWIMMING;

		// player is flagged as under water
		if(_player->m_UnderwaterState & UNDERWATERSTATE_UNDERWATER)
		{
			_player->m_UnderwaterState &= ~UNDERWATERSTATE_UNDERWATER;
			WorldPacket data(SMSG_START_MIRROR_TIMER, 20);
			data << uint32(TIMER_BREATH) << _player->m_UnderwaterTime << _player->m_UnderwaterMaxTime << int32(-1) << uint32(0);

			pSession->SendPacket(&data);
		}
		if(pSession->m_bIsWLevelSet)
		{
			if(movement_info.z + _player->m_noseLevel <= _player->GetMapMgr()->GetLiquidHeight(movement_info.x, movement_info.y))
			{
				_player->m_UnderwaterTime = 0;
				_player->m_UnderwaterMaxTime = 0;
				_player->m_UnderwaterState = UNDERWATERSTATE_NONE;
				_player->StopMirrorTimer(TIMER_BREATH);
				_player->RemoveAurasByInterruptFlag(AURA_INTERRUPT_ON_LEAVE_WATER);
				// unset swim session water level
				pSession->m_bIsWLevelSet = false;
			}
		}
		return;
	}

	//player is swimming and not flagged as in the water
	if(movement_info.flags & MOVEFLAG_SWIMMING && !(_player->m_UnderwaterState & UNDERWATERSTATE_SWIMMING))
	{
		if( ( _player->GetZoneId() == 46 )&& !(_player->m_UnderwaterState & UNDERWATERSTATE_LAVA))
			_player->m_UnderwaterState |= UNDERWATERSTATE_LAVA;

		_player->RemoveAurasByInterruptFlag(AURA_INTERRUPT_ON_ENTER_WATER);

		// get water level only if it was not set before
		if(!pSession->m_bIsWLevelSet)
		{
			// water level is somewhere below the nose of the character when entering water
			pSession->m_wLevel = movement_info.z + _player->m_noseLevel * 0.95f;
			pSession->m_bIsWLevelSet = true;
		}

		_player->m_UnderwaterState |= UNDERWATERSTATE_SWIMMING;
	}

	// player is not swimming and is not stationary and is flagged as in the water
	if(!(movement_info.flags & MOVEFLAG_SWIMMING) && (movement_info.flags != MOVEFLAG_MOVE_STOP) && (_player->m_UnderwaterState & UNDERWATERSTATE_SWIMMING))
	{
		if(movement_info.z + _player->m_noseLevel <= _player->GetMapMgr()->GetLiquidHeight(movement_info.x, movement_info.y))
		{
			_player->m_UnderwaterTime = 0;
			_player->m_UnderwaterMaxTime = 0;
			_player->m_UnderwaterState = UNDERWATERSTATE_NONE;
			_player->StopMirrorTimer(TIMER_BREATH);
			_player->RemoveAurasByInterruptFlag(AURA_INTERRUPT_ON_LEAVE_WATER);
			pSession->m_bIsWLevelSet = false;
			return;
		}
		// player is above water level
		if((movement_info.z + _player->m_noseLevel) > pSession->m_wLevel)
		{
			if( ( _player->GetZoneId() == 46 ) && (_player->m_UnderwaterState & UNDERWATERSTATE_LAVA))
				_player->m_UnderwaterState &= ~UNDERWATERSTATE_LAVA;

			_player->RemoveAurasByInterruptFlag(AURA_INTERRUPT_ON_LEAVE_WATER);

			// unset swim session water level
			pSession->m_bIsWLevelSet = false;

			_player->m_UnderwaterState &= ~UNDERWATERSTATE_SWIMMING;
		}
	}

	// player is flagged as in the water and is not flagged as under the water
	if(_player->m_UnderwaterState & UNDERWATERSTATE_SWIMMING && !(_player->m_UnderwaterState & UNDERWATERSTATE_UNDERWATER))
	{
		//the player is in the water and has gone under water, requires breath bar.
		if(movement_info.z + _player->m_noseLevel < _player->GetMapMgr()->GetLiquidHeight(movement_info.x, movement_info.y))
		{
			_player->m_UnderwaterState |= UNDERWATERSTATE_UNDERWATER;
			if( ( _player->GetZoneId() == 46 ) && !(_player->m_UnderwaterState & UNDERWATERSTATE_LAVA))
				_player->m_UnderwaterState |= UNDERWATERSTATE_LAVA;
			else
			{
				WorldPacket data(SMSG_START_MIRROR_TIMER, 20);
				data << uint32( TIMER_BREATH ) << _player->m_UnderwaterTime << _player->m_UnderwaterMaxTime << int32(-1) << uint32(0);
				pSession->SendPacket(&data);
			}
		}
	}

	// player is flagged as in the water and is flagged as under the water
	if(_player->m_UnderwaterState & UNDERWATERSTATE_SWIMMING && _player->m_UnderwaterState & UNDERWATERSTATE_UNDERWATER)
	{
		//the player is in the water but their face is above water, no breath bar needed.
		if(movement_info.z + _player->m_noseLevel > _player->GetMapMgr()->GetLiquidHeight(movement_info.x, movement_info.y))
		{
			_player->m_UnderwaterState &= ~UNDERWATERSTATE_UNDERWATER;
			if( ( _player->GetZoneId() == 46) && (_player->m_UnderwaterState & UNDERWATERSTATE_LAVA))
				_player->m_UnderwaterState &= ~UNDERWATERSTATE_LAVA;
			else
			{
				WorldPacket data(SMSG_START_MIRROR_TIMER, 20);
				data << uint32( TIMER_BREATH ) << _player->m_UnderwaterTime << _player->m_UnderwaterMaxTime << int32(10) << uint32(0);
				pSession->SendPacket(&data);
			}
		}
	}

	// player is flagged as not in the water and is flagged as under the water
	if(!(_player->m_UnderwaterState & UNDERWATERSTATE_SWIMMING) && _player->m_UnderwaterState & UNDERWATERSTATE_UNDERWATER)
	{
		//the player is out of the water, no breath bar needed.
		if(movement_info.z + _player->m_noseLevel > _player->GetMapMgr()->GetLiquidHeight(movement_info.x, movement_info.y))
		{
			if( ( _player->GetZoneId() == 46 ) && (_player->m_UnderwaterState & UNDERWATERSTATE_LAVA))
				_player->m_UnderwaterState &= ~UNDERWATERSTATE_LAVA;
			else
			{
				WorldPacket data(SMSG_START_MIRROR_TIMER, 20);
				data << uint32( TIMER_BREATH ) << _player->m_UnderwaterTime << _player->m_UnderwaterMaxTime << int32(10) << uint32(0);
				pSession->SendPacket(&data);
			}
		}
	}

}

struct MovementFlagName
{
	uint32 flag;
	const char* name;
};

static MovementFlagName MoveFlagsToNames[] =
{
	{ MOVEFLAG_MOVE_STOP, "MOVEFLAG_MOVE_STOP" },
	{ MOVEFLAG_MOVE_FORWARD, "MOVEFLAG_MOVE_FORWARD" },
	{ MOVEFLAG_MOVE_BACKWARD, "MOVEFLAG_MOVE_BACKWARD" },
	{ MOVEFLAG_STRAFE_LEFT, "MOVEFLAG_STRAFE_LEFT" },
	{ MOVEFLAG_STRAFE_RIGHT, "MOVEFLAG_STRAFE_RIGHT" },
	{ MOVEFLAG_TURN_LEFT, "MOVEFLAG_TURN_LEFT" },
	{ MOVEFLAG_TURN_RIGHT, "MOVEFLAG_TURN_RIGHT" },
	{ MOVEFLAG_PITCH_DOWN, "MOVEFLAG_PITCH_DOWN" },
	{ MOVEFLAG_PITCH_UP, "MOVEFLAG_PITCH_UP" },
	{ MOVEFLAG_WALK, "MOVEFLAG_WALK" },
	{ MOVEFLAG_TRANSPORT, "MOVEFLAG_TRANSPORT" },
	{ MOVEFLAG_NO_COLLISION, "MOVEFLAG_NO_COLLISION" },
	{ MOVEFLAG_ROOTED, "MOVEFLAG_FLYING" },
	{ MOVEFLAG_JUMPING, "MOVEFLAG_JUMPING" },
	{ MOVEFLAG_FALLING, "MOVEFLAG_FALLING" },
	{ MOVEFLAG_FALLING_FAR, "MOVEFLAG_FALLING_FAR" },
	{ MOVEFLAG_FREE_FALLING, "MOVEFLAG_FREE_FALLING" },
	{ MOVEFLAG_TB_PENDING_STOP, "MOVEFLAG_TB_PENDING_STOP" },
	{ MOVEFLAG_TB_PENDING_UNSTRAFE, "MOVEFLAG_TB_PENDING_UNSTRAFE" },
	{ MOVEFLAG_TB_PENDING_FALL, "MOVEFLAG_TB_PENDING_FALL" },
	{ MOVEFLAG_TB_PENDING_FORWARD, "MOVEFLAG_TB_PENDING_FORWARD" },
	{ MOVEFLAG_TB_PENDING_BACKWARD, "MOVEFLAG_TB_PENDING_BACKWARD" },
	{ MOVEFLAG_SWIMMING, "MOVEFLAG_SWIMMING" },
	{ MOVEFLAG_ASCENDING, "MOVEFLAG_ASCENDING" },
	{ MOVEFLAG_CAN_FLY, "MOVEFLAG_CAN_FLY" },
	{ MOVEFLAG_AIR_SWIMMING, "MOVEFLAG_AIR_SWIMMING" },
	{ MOVEFLAG_SPLINE_ENABLED, "MOVEFLAG_SPLINE_ENABLED" },
	{ MOVEFLAG_WATER_WALK, "MOVEFLAG_WATER_WALK" },
	{ MOVEFLAG_FEATHER_FALL, "MOVEFLAG_FEATHER_FALL" },
	{ MOVEFLAG_LEVITATE, "MOVEFLAG_LEVITATE" },
	{ MOVEFLAG_LOCAL, "MOVEFLAG_LOCAL" },
};

static const uint32 nmovementflags = sizeof(MoveFlagsToNames) / sizeof(MovementFlagName);

void WorldSession::HandleMovementOpcodes(WorldPacket & recv_data)
{
	CHECK_INWORLD_RETURN
	// spell cancel on movement, for now only fishing is added
	Object* t_go = _player->m_SummonedObject;
	if(t_go)
	{
		if(t_go->GetEntry() == GO_FISHING_BOBBER)
			TO_GAMEOBJECT(t_go)->EndFishing(GetPlayer(), true);
	}

	/************************************************************************/
	/* Clear standing state to stand.				                        */
	/************************************************************************/
	if(recv_data.GetOpcode() == MSG_MOVE_START_FORWARD)
		_player->SetStandState(STANDSTATE_STAND);
	/************************************************************************/
	/* Make sure the packet is the correct size range.                      */
	/************************************************************************/
	//if(recv_data.size() > 80) { Disconnect(); return; }

	/************************************************************************/
	/* Read Movement Data Packet                                            */
	/************************************************************************/
    uint64 guid;

    recv_data.readPackGUID(guid);

    MovementInfo movementInfo;
    movementInfo.guid = guid;
    ReadMovementInfo(recv_data, &movementInfo);

    recv_data.rfinish();                   // prevent warnings spam

	if(guid != m_MoverWoWGuid.GetOldGuid())
		return;

	// Player is in control of some entity, so we move that instead of the player
	Unit *mover = _player->GetMapMgr()->GetUnit( m_MoverWoWGuid.GetOldGuid() );
	if( mover == NULL )
		return;

	/************************************************************************/
	/* Update player movement state                                         */
	/************************************************************************/

	/*Anti Multi-Jump Check*/
	if(recv_data.GetOpcode() == MSG_MOVE_JUMP && _player->HasUnitMovementFlag(MOVEFLAG_JUMPING) && !GetPermissionCount())
	{
		sCheatLog.writefromsession(this, "Detected jump hacking");
		Disconnect();
		return;
	}

	if(!(HasGMPermissions() && sWorld.no_antihack_on_gm) && !_player->GetCharmedUnitGUID())
	{
		/************************************************************************/
		/* Anti-Teleport                                                        */
		/************************************************************************/
		if(sWorld.antihack_teleport && _player->m_position.Distance2DSq(movementInfo.x, movementInfo.y) > 3025.0f
		        && _player->m_runSpeed < 50.0f && !_player->transporter_info.guid)
		{
			sCheatLog.writefromsession(this, "Disconnected for teleport hacking. Player speed: %f, Distance traveled: %f", _player->m_runSpeed, sqrt(_player->m_position.Distance2DSq(movementInfo.x, movementInfo.y)));
			Disconnect();
			return;
		}
	}

	//update the detector
	if(sWorld.antihack_speed && !_player->GetTaxiState() && _player->transporter_info.guid == 0 && !_player->GetSession()->GetPermissionCount())
	{
		// simplified: just take the fastest speed. less chance of fuckups too
		float speed = (_player->flying_aura) ? _player->m_flySpeed : (_player->m_swimSpeed > _player-> m_runSpeed) ? _player->m_swimSpeed : _player->m_runSpeed;

		_player->SDetector->AddSample(movementInfo.x, movementInfo.y, getMSTime(), speed);

		if(_player->SDetector->IsCheatDetected())
			_player->SDetector->ReportCheater(_player);
	}

	/************************************************************************/
	/* Remove Emote State                                                   */
	/************************************************************************/
	if(_player->GetEmoteState())
		_player->SetEmoteState(0);

	/************************************************************************/
	/* Make sure the co-ordinates are valid.                                */
	/************************************************************************/
	if(!((movementInfo.y >= _minY) && (movementInfo.y <= _maxY)) || !((movementInfo.x >= _minX) && (movementInfo.x <= _maxX)))
	{
		Disconnect();
		return;
	}

	uint32 mstime = mTimeStamp();
	if(m_clientTimeDelay == 0)
		m_clientTimeDelay = mstime - movementInfo.time;
	WorldPacket data(recv_data.GetOpcode(), recv_data.size());
    movementInfo.time = getMSTime();
    movementInfo.guid = mover->GetGUID();
    WriteMovementInfo(&data, &movementInfo);
    mover->SendMessageToSet(&data, _player);

    mover->movement_info = movementInfo;

	if(recv_data.GetOpcode() == MSG_MOVE_FALL_LAND)
	{
		// player has finished falling
		//if _player->z_axisposition contains no data then set to current position
		if(!_player->z_axisposition)
			_player->z_axisposition = movementInfo.z;
		// calculate distance fallen
		uint32 falldistance = float2int32(_player->z_axisposition - movementInfo.z);
		if(_player->z_axisposition <= movementInfo.z)
			falldistance = 1;
		/*Safe Fall*/
		if((int)falldistance > _player->m_safeFall)
			falldistance -= _player->m_safeFall;
		else
			falldistance = 1;
		mover->RemoveAurasByInterruptFlag(AURA_INTERRUPT_ON_LANDING);
		//checks that player has fallen more than 12 units, otherwise no damage will be dealt
		//falltime check is also needed here, otherwise sudden changes in Z axis position, such as using !recall, may result in death
		if(_player->isAlive() && !_player->bInvincible && !_player->GodModeCheat && falldistance > 12 && (UNIXTIME >= _player->m_fallDisabledUntil) /*&& movement_info.FallTime > 1000*/ && !_player->m_noFallDamage && !_player->IsFlying() && !_player->HasAuraWithName(SPELL_AURA_FEATHER_FALL))
		{
			// 1.7% damage for each unit fallen on Z axis over 13
			uint32 health_loss = float2int32(_player->GetUInt32Value(UNIT_FIELD_MAXHEALTH) * (falldistance - 12) * 0.017f);

			if(health_loss >= _player->GetUInt32Value(UNIT_FIELD_HEALTH))
				health_loss = _player->GetUInt32Value(UNIT_FIELD_HEALTH);
			#ifdef ENABLE_ACHIEVEMENTS
			else if(falldistance >= 65)
			{
				// Rather than Updating achievement progress every time fall damage is taken, all criteria currently have 65 yard requirement...
				// Achievement 964: Fall 65 yards without dying.
				// Achievement 1260: Fall 65 yards without dying while completely smashed during the Brewfest Holiday.
				_player->GetAchievementMgr().UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_FALL_WITHOUT_DYING, falldistance, Player::GetDrunkenstateByValue(_player->GetDrunkValue()), 0);
			}
			#endif
			_player->SendEnvironmentalDamageLog(_player->GetGUID(), DAMAGE_FALL, health_loss);
			_player->DealDamage(_player, health_loss, 0, 0, 0);
			//_player->RemoveStealth(); // cebernic : why again? lost stealth by AURA_INTERRUPT_ON_ANY_DAMAGE_TAKEN already.
		}
		_player->z_axisposition = 0.0f;
	}
	else
		//whilst player is not falling, continuously update Z axis position.
		//once player lands this will be used to determine how far he fell.
		if(!(movementInfo.flags & MOVEFLAG_FALLING))
			_player->z_axisposition = movementInfo.z;

	/************************************************************************/
	/* Transporter Setup                                                    */
	/************************************************************************/
	if( ( mover->transporter_info.guid != 0 ) && ( movementInfo.transGuid.GetOldGuid() == 0 ) )
	{
		/* we left the transporter we were on */

		Transporter *transporter = objmgr.GetTransporter( Arcemu::Util::GUID_LOPART( mover->transporter_info.guid ) );
		if( transporter != NULL )
			transporter->RemovePassenger( mover );

		mover->transporter_info.guid = 0;
		_player->SpeedCheatReset();

	}
	else
	{
		if( movementInfo.transGuid.GetOldGuid() != 0 ){

			if( mover->transporter_info.guid == 0 ){
				Transporter *transporter = objmgr.GetTransporter( Arcemu::Util::GUID_LOPART( movementInfo.transGuid ) );
				if( transporter != NULL )
					transporter->AddPassenger( mover );
				
				/* set variables */
				mover->transporter_info.guid = movementInfo.transGuid;
				mover->transporter_info.flags = movementInfo.transTime;
				mover->transporter_info.x = movementInfo.transX;
				mover->transporter_info.y = movementInfo.transY;
				mover->transporter_info.z = movementInfo.transZ;
				mover->transporter_info.o = movementInfo.transO;
				mover->transporter_info.seat = movementInfo.transSeat;
			}else{
				/* no changes */
				mover->transporter_info.flags = movementInfo.transTime;
				mover->transporter_info.x = movementInfo.transX;
				mover->transporter_info.y = movementInfo.transY;
				mover->transporter_info.z = movementInfo.transZ;
				mover->transporter_info.o = movementInfo.transO;
				mover->transporter_info.seat = movementInfo.transSeat;
			}
		}
	}

	/************************************************************************/
	/* Breathing System                                                     */
	/************************************************************************/
	_HandleBreathing(movementInfo, _player, this);

	/************************************************************************/
	/* Remove Spells                                                        */
	/************************************************************************/
	if((movementInfo.flags & MOVEFLAG_MASK_MOVING) != 0)
		mover->RemoveAurasByInterruptFlag(AURA_INTERRUPT_ON_MOVEMENT);

	if(!(movementInfo.flags & MOVEFLAG_SWIMMING || movementInfo.flags & MOVEFLAG_FALLING))
		mover->RemoveAurasByInterruptFlag(AURA_INTERRUPT_ON_LEAVE_WATER);
	if(movementInfo.flags & MOVEFLAG_SWIMMING)
		mover->RemoveAurasByInterruptFlag(AURA_INTERRUPT_ON_ENTER_WATER);
	if(movementInfo.flags & (MOVEFLAG_TURN_LEFT | MOVEFLAG_TURN_RIGHT))
		mover->RemoveAurasByInterruptFlag(AURA_INTERRUPT_ON_TURNING);

	/************************************************************************/
	/* Update our position in the server.                                   */
	/************************************************************************/

	// Player is the active mover
	if(m_MoverWoWGuid.GetOldGuid() == _player->GetGUID())
	{

		if(_player->m_CurrentTransporter == NULL)
		{
			if(!_player->SetPosition(movementInfo.x, movementInfo.y, movementInfo.z, movementInfo.orientation))
				_player->EjectFromInstance();
		}
	}
	else
	{
		if( !mover->isRooted() )
			mover->SetPosition(movementInfo.x, movementInfo.y, movementInfo.z, movementInfo.orientation);
	}
}

void WorldSession::HandleMoveTimeSkippedOpcode(WorldPacket & recv_data)
{

}

void WorldSession::HandleMoveNotActiveMoverOpcode(WorldPacket & recv_data)
{
	CHECK_INWORLD_RETURN
	WoWGuid old_mover_guid;
	recv_data >> old_mover_guid;
	if(old_mover_guid == m_MoverWoWGuid)
		return;
    MovementInfo mi;
	mi.guid = old_mover_guid.GetOldGuid();
	ReadMovementInfo(recv_data, &mi);
	_player->movement_info = mi;
}


void WorldSession::HandleSetActiveMoverOpcode(WorldPacket & recv_data)
{
	CHECK_INWORLD_RETURN

	// set current movement object
	uint64 guid;
	recv_data >> guid;
	// make sure the guid is valid and we aren't cheating
	/* todo: fix these checks, right now it can cause a crash if a player is entering a vehicle and doesn't have the vehicle set yet.
	if(!(_player->m_CurrentCharm == guid) &&
	        !(_player->GetGUID() == guid))
	{
		if( _player->GetCurrentVehicle() && _player->GetCurrentVehicle()->GetOwner() && 
			_player->GetCurrentVehicle()->GetOwner()->GetGUID() != guid )
			return;
	}*/
	// ^ till is fixed
	if(_player->GetMapMgr()->GetUnit(guid) || guid == 0)
	{
		// generate wowguid
		if(guid != 0)
			m_MoverWoWGuid.Init(guid);
		else
			m_MoverWoWGuid.Init(_player->GetGUID());
	}
}

void WorldSession::HandleMoveSplineCompleteOpcode(WorldPacket & recvPacket)
{
    uint64 guid; // used only for proper packet read
    recvPacket.readPackGUID(guid);

    MovementInfo movementInfo;                              // used only for proper packet read
    ReadMovementInfo(recvPacket, &movementInfo);

    recvPacket.read_skip<uint32>();                          // unk
}

void WorldSession::HandleMountSpecialAnimOpcode(WorldPacket & recvdata)
{
	CHECK_INWORLD_RETURN

	WorldPacket data(SMSG_MOUNTSPECIAL_ANIM, 8);
	data << _player->GetGUID();
	_player->SendMessageToSet(&data, true);
}

void WorldSession::HandleWorldportOpcode(WorldPacket & recv_data)
{
	CHECK_INWORLD_RETURN

	uint32 unk;
	uint32 mapid;
	float x, y, z, o;
	recv_data >> unk >> mapid >> x >> y >> z >> o;

	//printf("\nTEST: %u %f %f %f %f", mapid, x, y, z, o);

	if(!HasGMPermissions())
	{
		SendNotification("You do not have permission to use this function.");
		return;
	}

	LocationVector vec(x, y, z, o);
	_player->SafeTeleport(mapid, 0, vec);
}

void WorldSession::HandleTeleportToUnitOpcode(WorldPacket & recv_data)
{
	CHECK_INWORLD_RETURN

	uint8 unk;
	Unit* target;
	recv_data >> unk;

	if(!HasGMPermissions())
	{
		SendNotification("You do not have permission to use this function.");
		return;
	}

	if((target = _player->GetMapMgr()->GetUnit(_player->GetSelection())) == NULL)
		return;

	_player->SafeTeleport(_player->GetMapId(), _player->GetInstanceID(), target->GetPosition());
}

void WorldSession::HandleTeleportCheatOpcode(WorldPacket & recv_data)
{

	CHECK_INWORLD_RETURN

	float x, y, z, o;
	LocationVector vec;

	if(!HasGMPermissions())
	{
		SendNotification("You do not have permission to use this function.");
		return;
	}

	recv_data >> x >> y >> z >> o;
	vec.ChangeCoords(x, y, z, o);
	_player->SafeTeleport(_player->GetMapId(), _player->GetInstanceID(), vec);
}

void WorldSession::HandleMoveKnockBackAck(WorldPacket & recv_data)
{
    uint64 guid;
    recv_data.readPackGUID(guid);
	if(guid != m_MoverWoWGuid.GetOldGuid())
		return;
    recv_data.read_skip<uint32>();                          // unk

    MovementInfo movementInfo;
    ReadMovementInfo(recv_data, &movementInfo);
    _player->movement_info = movementInfo;

    WorldPacket data(MSG_MOVE_KNOCK_BACK, 66);
    data.appendPackGUID(guid);
    _player->BuildMovementPacket(&data);
	data << movementInfo.redirectSin;
	data << movementInfo.redirectCos;
	data << movementInfo.redirectVelocity;
	data << movementInfo.redirect2DSpeed;
	_player->SendMessageToSet(&data, false);
}

void WorldSession::ReadMovementInfo(WorldPacket &data, MovementInfo* mi)
{
	data >> mi->flags;
	data >> mi->flags2;
	data >> mi->time;
	data >> mi->x;
	data >> mi->y;
	data >> mi->z;
	data >> mi->orientation;

	if(mi->HasMovementFlag(MOVEFLAG_TRANSPORT))
	{
		data >> mi->transGuid;
		data >> mi->transX;
		data >> mi->transY;
		data >> mi->transZ;
		data >> mi->transO;
		data >> mi->transTime;
		data >> mi->transSeat;
		if(mi->HasExtraMovementFlag(MOVEFLAG2_INTERPOLATED_MOVEMENT))
			data >> mi->transTime2;
	}
	if(mi->HasMovementFlag(MovementFlags(MOVEFLAG_SWIMMING | MOVEFLAG_AIR_SWIMMING)) || mi->HasExtraMovementFlag(MOVEFLAG2_ALLOW_PITCHING))
		data >> mi->pitch;

	data >> mi->fallTime;

	if(mi->HasMovementFlag(MOVEFLAG_JUMPING))
	{
		data >> mi->redirectVelocity;
		data >> mi->redirectSin;
		data >> mi->redirectCos;
		data >> mi->redirect2DSpeed;
	}
	if(mi->HasMovementFlag(MOVEFLAG_SPLINE_ELEVATION))
		data >> mi->splineElevation;
	/*
    // This must be a packet spoofing attempt. MOVEMENTFLAG_ROOT sent from the client is not valid,
    // and when used in conjunction with any of the moving movement flags such as MOVEMENTFLAG_FORWARD
    // it will freeze clients that receive this player's movement info.
    if (mi->HasMovementFlag(MOVEFLAG_ROOTED))
        mi->flags &= ~MOVEFLAG_ROOTED;

    // Cannot hover and jump at the same time
    if (mi->HasMovementFlag(MOVEFLAG_LEVITATE) && mi->HasMovementFlag(MOVEFLAG_JUMPING))
        mi->flags &= ~MOVEFLAG_JUMPING;

    // Cannot ascend and descend at the same time
    if (mi->HasMovementFlag(MOVEFLAG_ASCENDING) && mi->HasMovementFlag(MOVEFLAG_DESCENDING))
        mi->flags &= ~(MOVEFLAG_ASCENDING | MOVEFLAG_DESCENDING);

    // Cannot move left and right at the same time
    if (mi->HasMovementFlag(MOVEFLAG_TURN_LEFT) && mi->HasMovementFlag(MOVEFLAG_TURN_RIGHT))
        mi->flags &= ~(MOVEFLAG_TURN_LEFT | MOVEFLAG_TURN_RIGHT);

    // Cannot strafe left and right at the same time
    if (mi->HasMovementFlag(MOVEFLAG_STRAFE_LEFT) && mi->HasMovementFlag(MOVEFLAG_STRAFE_RIGHT))
        mi->flags &= ~(MOVEFLAG_STRAFE_LEFT | MOVEFLAG_STRAFE_RIGHT);

    // Cannot pitch up and down at the same time
    if (mi->HasMovementFlag(MOVEFLAG_PITCH_UP) && mi->HasMovementFlag(MOVEFLAG_PITCH_DOWN))
        mi->flags &= ~(MOVEFLAG_PITCH_UP | MOVEFLAG_PITCH_DOWN);

    // Cannot move forwards and backwards at the same time
    if (mi->HasMovementFlag(MOVEFLAG_MOVE_FORWARD) && mi->HasMovementFlag(MOVEFLAG_MOVE_BACKWARD))
        mi->flags &= ~(MOVEFLAG_MOVE_FORWARD | MOVEFLAG_MOVE_BACKWARD);*/
}

void WorldSession::WriteMovementInfo(WorldPacket* data, MovementInfo* mi)
{
    data->appendPackGUID(mi->guid);
	*data << mi->flags;
	*data << mi->flags2;
	*data << mi->time;

	*data << mi->x;
	*data << mi->y;
	*data << mi->z;
	*data << mi->orientation;

	if(mi->HasMovementFlag(MOVEFLAG_TRANSPORT))
	{
		*data << mi->transGuid;
		*data << mi->transX;
		*data << mi->transY;
		*data << mi->transZ;
		*data << mi->transO;
		*data << mi->transTime;
		*data << mi->transSeat;
	}
	if(mi->HasMovementFlag(MovementFlags(MOVEFLAG_SWIMMING | MOVEFLAG_AIR_SWIMMING)) || mi->HasExtraMovementFlag(MOVEFLAG2_ALLOW_PITCHING))
		*data << mi->pitch;

    *data << mi->fallTime;

	if(mi->HasMovementFlag(MOVEFLAG_FALLING))
	{
		*data << mi->redirectVelocity;
		*data << mi->redirectSin;
		*data << mi->redirectCos;
		*data << mi->redirect2DSpeed;
	}
	if(mi->HasMovementFlag(MOVEFLAG_SPLINE_ELEVATION))
		*data << mi->splineElevation;
}

void WorldSession::HandleMoveHoverAck(WorldPacket & recv_data)
{
    uint64 guid;                                            // guid - unused
    recv_data.readPackGUID(guid);

    recv_data.read_skip<uint32>();                          // unk

    MovementInfo movementInfo;
    ReadMovementInfo(recv_data, &movementInfo);

    recv_data.read_skip<uint32>();                          // unk2
}

void WorldSession::HandleMoveWaterWalkAck(WorldPacket & recv_data)
{
    uint64 guid;                                            // guid - unused
    recv_data.readPackGUID(guid);

    recv_data.read_skip<uint32>();                          // unk

    MovementInfo movementInfo;
    ReadMovementInfo(recv_data, &movementInfo);

    recv_data.read_skip<uint32>();                          // unk2
}

void WorldSession::HandleFeatherFallAck(WorldPacket & recv_data)
{
	recv_data.rfinish();
}