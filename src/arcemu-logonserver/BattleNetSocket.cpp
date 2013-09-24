#include "LogonStdAfx.h"
#include <openssl/md5.h>
#include <sha.h>

typedef void (BattleNetSocket::*BattleNetHandler)();
static BattleNetHandler Handlers[MAX_BATTLENET_CMD] = {
		&BattleNetSocket::InformationRequest,			// 0
		NULL,
		NULL,
		NULL,
};

BattleNetSocket::BattleNetSocket(SOCKET fd) : Socket(fd, 32768, 4096)
{
	last_recv = time(NULL);
	_authSocketLock.Acquire();
	_authSockets_BN.insert(this);
	_authSocketLock.Release();
}

BattleNetSocket::~BattleNetSocket()
{
}

void BattleNetSocket::OnDisconnect()
{
	if(!removedFromSet)
	{
		_authSocketLock.Acquire();
		_authSockets_BN.erase(this);
		_authSocketLock.Release();
	}
}

void BattleNetSocket::InformationRequest()
{
	/*if (reader->ReadBuffer() < 11)
	{
		delete reader;
		printf( "[InformationRequest] Packet has no header. Refusing to handle." );
		return;
	}*/

	InformationRequestStruct infoR;

	int32 n = reader->ReadInt32(32);
	char chars[5] = { 0 };
	memcpy(chars, &n, 4 * sizeof(char));

	infoR.program = ReverseString(chars);

	n = reader->ReadInt32(32);
	memcpy(chars, &n, 4 * sizeof(char));

	infoR.platform = ReverseString(chars);

	n = reader->ReadInt32(32);
	memcpy(chars, &n, 4 * sizeof(char));

	infoR.locale = ReverseString(chars);

	infoR.componentCount = reader->ReadInt32(6);
	infoR.components.resize(infoR.componentCount);
	for (int32 i = 0; i < infoR.componentCount; ++i)
	{
		InfRequestComponents comp;
		n = reader->ReadInt32(32);
		memcpy(chars, &n, 4 * sizeof(char));
		comp.program = ReverseString(chars);
		n = reader->ReadInt32(32);
		memcpy(chars, &n, 4 * sizeof(char));
		comp.platform = ReverseString(chars);
		comp.Build = reader->ReadInt32(32);
		infoR.components.at(i) = comp;
	}

	infoR.hasAccountName = reader->ReadInt32(1);
	if (!infoR.hasAccountName)
	{
		delete reader;
		printf("WARNING: Account tried to connect with no account name.\n");
		SendError(AUTH_BAD_CREDENTIALS);
		Disconnect();
		return;
	}
	infoR.accountName = reader->ReadAsciiString(9, 3);

	delete reader;

	if (infoR.accountName.length() == 0)
	{
		SendError(AUTH_BAD_CREDENTIALS);
		Disconnect();
		return;
	}

	if (infoR.program != "WoW")
	{
		printf("Someone tried to connect who is not using WoW! They use: %s.\n", infoR.program);
		SendError(AUTH_INVALID_PROGRAM);
		Disconnect();
		return;
	}

	// Check for a possible IP ban on this client.
	BAN_STATUS ipb = IPBanner::getSingleton().CalculateBanStatus(GetRemoteAddress());
	if( ipb != BAN_STATUS_NOT_BANNED )
	{
		printf("Battle.net detected ban person logging in. Refusing.", GetRemoteIP().c_str());
		SendError(LOGIN_BANNED);
		Disconnect();
		return;
	}

	// Make account name uppercase
	transform(infoR.accountName.begin(), infoR.accountName.end(),infoR.accountName.begin(), ::toupper);
	m_account = AccountMgr::getSingleton().GetAccount(infoR.accountName);
	if(m_account == 0)
	{
		SendError(AUTH_BAD_CREDENTIALS);
		printf("[Battlenet] Invalid account name: %s.", infoR.accountName.c_str());
		Disconnect();
		return;
	}
	if(m_account->Banned != 0)
	{
		SendError(LOGIN_BANNED);
		Disconnect();
		return;
	}

	// Now for proof response
	writer = new BitWriter_BN(206); // (( (4*8) + (4*8) + 32 ) * 2) + 3 + 11
	writer->WriteHeader(2, 0);
	int32 moduleCount = 2;
	writer->WriteBits(moduleCount, 3);
	// Passwords.dll
	writer->WriteFourCC("auth");
	writer->WriteFourCC(infoR.locale);
	const char * moduleID = "TEMP";
	writer->WriteBits(moduleID, 32);
	int32 blobSize = 0;
	writer->WriteBits(blobSize, 10);
	const char * moduleData = "BlaBlaBla";
	// Thumbnails.dll

	// Send
	Send(writer->Buffer(), 206);
	delete writer;
	/*
	int:3 moduleCount
	for (moduleCount)
	{
 		{ // Battlenet::Cache::Handle
		aligntobb	char[4] "auth"
				char[4] locale
				byte[32] ModuleId
		}
		int:10 blobSize
		byte[blobSize] moduleData
	}
	*/
}

void BattleNetSocket::SendError(int32 ErrorCode)
{
	BitWriter_BN * writer = new BitWriter_BN(63); // 6 + 1 + 4 + 1 + 1 + 2 + 0x10 + 0x20

	int32 Zero = 0;
	int32 One = 1;
	// Header
	writer->WriteBits(Zero, 6);
	writer->WriteBits(One, 1);
	writer->WriteBits(Zero, 4);
	// Contents
	writer->WriteBits(One, 1); // bool isError???
	writer->WriteBits(Zero, 1); // bool ???
	writer->WriteBits(One, 2);
	writer->WriteBits(ErrorCode, 0x10);
    writer->WriteBits(Zero, 0x20);

	Send(writer->Buffer(), 63);

	delete writer;
}

string BattleNetSocket::ReverseString(string str)
{
	string ret;
	uint32 size = str.size();
	ret.resize(size);
	for (uint32 i = 0; i < size; ++i)
		ret[i] = str[size - i - 1];
	return ret;
}

#ifdef DEBUG_STONE
// Debug
struct TESTING
{
	char str[1024];
};

#include <fstream>
#include <iostream>
// End debug
#endif

void BattleNetSocket::OnRead()
{
	if(readBuffer.GetContiguiousBytes() < 11)
		return;

#ifdef DEBUG_STONE
	// Debug, dump packet
	TESTING temp;
	uint32 size = readBuffer.GetSize();
	readBuffer.Read(&temp, size);

	fstream write;
	write.open("C:\\Users\\Harry_\\Desktop\\packets.dump", ios::out | ios::binary);
	write.write(temp.str, size);
	write.close();

	return;
	// End Debug
#endif
	BN_PacketHeader header;

	unsigned char data[1024];
	uint32 size = readBuffer.GetSize();
	readBuffer.Read(&data, size);

	reader = new BitReader_BN(data, size);

	header.id = reader->ReadInt32(6);
	header.hasChannel = reader->ReadInt32(1);
	if (header.hasChannel)
		header.Channel = reader->ReadInt32(4);

	printf("Got packet ID: %d\n", header.id);
	last_recv = UNIXTIME;
	if(header.id < MAX_BATTLENET_CMD && Handlers[header.id] != NULL)
		(this->*Handlers[header.id])();
	else
		printf("Unknown cmd %u\n", header.id);
}
