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
		printf("WARNING: Account tried to connect with no account name.\n");
		return;
	}
	infoR.accountName = reader->ReadAsciiString(9, 3);
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
