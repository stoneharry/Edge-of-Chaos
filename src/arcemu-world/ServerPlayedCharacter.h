#ifndef __SERVER_PLAYED_CHARACTER_H_
#define __SERVER_PLAYED_CHARACTER_H_

class TaskList;
class Unit;

enum PlayerRace
{
	P_RACE_HUMAN				= 1,
    P_RACE_ORC					= 2,
    P_RACE_DWARF				= 3,
    P_RACE_NIGHTELF				= 4,
    P_RACE_UNDEAD				= 5,
    P_RACE_TAUREN				= 6,
    P_RACE_GNOME				= 7,
    P_RACE_TROLL				= 8,
	P_RACE_GOBLIN				= 9,
    P_RACE_BLOODELF				= 10,
    P_RACE_DRAENEI				= 11,
	P_RACE_FELORC				= 12,
	P_RACE_NAGA					= 13,
	P_RACE_BROKEN				= 14,
	P_RACE_SKELETON				= 15,
	P_RACE_VRYKUL				= 16,
	P_RACE_TUSKARR				= 17,
	P_RACE_FORESTTROLL			= 18,
	P_RACE_TAUNKA				= 19,
	P_RACE_NORTHRENDSKELETON	= 20,
	P_RACE_ICETROLL				= 21,
	P_NUM_RACES					= 21

};

enum PlayerGender
{
	GENDER_MALE					= 0,
	GENDER_FEMALE				= 1
};

enum PlayerClass
{
	CLASS_WARRIOR				= 1,
    CLASS_PALADIN				= 2,
    CLASS_HUNTER				= 3,
    CLASS_ROGUE					= 4,
    CLASS_PRIEST				= 5,
    CLASS_DEATHKNIGHT			= 6,
    CLASS_SHAMAN				= 7,
    CLASS_MAGE					= 8,
    CLASS_WARLOCK				= 9,
    CLASS_DRUID					= 11
};

enum UnitItemSlot
{
	ITEM_SLOT_HEAD				= 0,
	ITEM_SLOT_SHOULDER			= 1,
	ITEM_SLOT_BODY				= 2,
	ITEM_SLOT_CHEST				= 3,
	ITEM_SLOT_WAIST				= 4,
	ITEM_SLOT_LEGS				= 5,
	ITEM_SLOT_FEET				= 6,
	ITEM_SLOT_WRITST			= 7,
	ITEM_SLOT_HAND				= 8,
	ITEM_SlOT_BACK				= 9,
	ITEM_SLOT_TABARD			= 10,
	ITEM_SLOT_MAINHAND			= 11,
	ITEM_SLOT_OFFHAND			= 12,
	ITEM_SLOT_RANGED			= 13,
	NUM_ITEM_SLOTS				= 14
};

struct ServerPlayedCharacter
{
	uint32 entry;
	uint8 raceId;		// also serves as the character's display index
	uint8 gender;
	uint8 classId;
	uint8 skinId;
	uint8 faceId;
	uint8 hairStyleId;
	uint8 hairColorId;
	uint8 facialHairId;
	uint32 itemId[14];
};

void LoadServerPlayedNPCFromDB(TaskList&);
void UnitLoadMiDisplayInfo(Unit* pUnit);
WorldPacket MirrorImagePacketHook(Unit* pUnit);
void ServerPlayedNPCCleanup(void);

#endif