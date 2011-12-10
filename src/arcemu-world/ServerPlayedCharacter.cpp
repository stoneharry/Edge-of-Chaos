#include "StdAfx.h"

// Table format
const char* gServerPlayedCreatureFormat = "uccccccccuuuuuuuuuuuuuu";
// Table storage
SERVER_DECL SQLStorage< ServerPlayedCharacter, HashMapStorageContainer<ServerPlayedCharacter> > ServerPlayedNpcStorage;
stdext::hash_set<uint32> mirrorImagePacketHookSet;

static uint32 RaceDisplayMap[P_NUM_RACES * 2 + 2] =
{
	0U, 0U, 49U, 50U, 51U, 52U, 53U, 54U, 55U, 56U, 57U, 58U, 59U,
	60U, 1563U, 1564U, 1478U, 1479U, 6894U, 6895U, 15476U, 15475U,
	16125U, 16126U, 16981U, 16980U, 17402U, 17403U, 17576U,
	17577U, 17578U, 17579U, 21685U, 21686U, 21780U,21780U,21963U,
	21964U, 26316U, 26317U, 26871U, 26872U, 26873U, 26874U
}; // maps the race index/gender in the DB to the actual display ID

void LoadServerPlayedNPCFromDB(TaskList& tl)
{
	tl.AddTask( new Task( new CallbackP2<SQLStorage< ServerPlayedCharacter, HashMapStorageContainer<ServerPlayedCharacter> >, const char *, const char *>(&ServerPlayedNpcStorage, &SQLStorage<ServerPlayedCharacter, HashMapStorageContainer<ServerPlayedCharacter> >::Load,  "server_played_character", gServerPlayedCreatureFormat) ) );
}

void UnitLoadMiDisplayInfo(Unit* pUnit)
{
	ServerPlayedCharacter* infoSpc = ServerPlayedNpcStorage.LookupEntry(pUnit->GetEntry());
	if (!infoSpc)
		return;

	if (infoSpc->raceId > (uint8)P_NUM_RACES)
	{
		std::cout << "Server-Player NPC with entry ID " << infoSpc->entry
				  << " used an invalid race id: " << infoSpc->raceId << std::endl;
		infoSpc->raceId = 0;
	}
	infoSpc->gender &= 0x1;
	pUnit->SetDisplayId( RaceDisplayMap[(infoSpc->raceId << 1) | infoSpc->gender] );
	pUnit->setRace(infoSpc->raceId);
	pUnit->setGender(infoSpc->gender);
	mirrorImagePacketHookSet.insert(pUnit->GetEntry());
	pUnit->SetUInt32Value(UNIT_FIELD_FLAGS_2, pUnit->GetUInt32Value(UNIT_FIELD_FLAGS_2) | UNIT_FLAG2_MIRROR_IMAGE);
}

WorldPacket MirrorImagePacketHook(Unit* pUnit)
{
	ServerPlayedCharacter* infoSpc = ServerPlayedNpcStorage.LookupEntry(pUnit->GetEntry());
	Arcemu::Util::ARCEMU_ASSERT(infoSpc != 0);

	WorldPacket data(SMSG_MIRRORIMAGE_DATA, 68);
	data << pUnit->GetGUID();
	data << RaceDisplayMap[(infoSpc->raceId << 1) | infoSpc->gender];
	data << infoSpc->raceId;
	data << infoSpc->gender;
	if (infoSpc->classId == 10 || infoSpc->classId > 11)
	{
		std::cout << "Server-Played NPC with entry ID " << infoSpc->entry
				  << " used an invalid class id: " << infoSpc->classId << std::endl;
		infoSpc->classId = 0;
	}
	data << infoSpc->classId;
	data << infoSpc->skinId;
	data << infoSpc->faceId;
	data << infoSpc->hairStyleId;
	data << infoSpc->hairColorId;
	data << infoSpc->facialHairId;
	data << static_cast<uint32>(0);

	for (uint8 i = 0; i < NUM_ITEM_SLOTS - 3; i++)
	{
		data << infoSpc->itemId[i];
	}

	pUnit->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, infoSpc->itemId[ITEM_SLOT_MAINHAND]);
	pUnit->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 0x1, infoSpc->itemId[ITEM_SLOT_OFFHAND]);
	pUnit->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 0x2, infoSpc->itemId[ITEM_SLOT_RANGED]);

	return data;
}

void ServerPlayedNPCCleanup(void)
{
	ServerPlayedNpcStorage.Cleanup();
}