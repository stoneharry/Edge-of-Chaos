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
	if (readBuffer.GetContiguiousBytes() < 11)
	{
		printf( "[InformationRequest] Packet has no header. Refusing to handle." );
		return;
	}

	InformationRequestStruct infoR;

	unsigned char data[1024];
	uint32 size = readBuffer.GetSize();
	readBuffer.Read(&data, size);

	BitReader test(data, size);
	int32 test2 = test.ReadInt32(32);

	//readBuffer.Read(&infoR, sizeof(infoR));

	/*int32 count;

	readBuffer.Read(&infoR.Program, sizeof(infoR.Program));
	readBuffer.Read(&infoR.Platform, sizeof(infoR.Platform));
	readBuffer.Read(&infoR.Locale, sizeof(infoR.Locale));
	readBuffer.Read(&count, infoR.componentCount);

	for (int32 i = 0; i < count; ++i)
	{
		InfRequestComponents temp;
		readBuffer.Read(&temp, sizeof(temp));
		infoR.components.push_back(temp);
	}*/
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
	readBuffer.Read(&header, sizeof(header));
	BN_Channel channel;
	if (header.hasChannel != -1)
		readBuffer.Read(&channel, sizeof(channel));

	printf("Got packet ID: %d\n",header.id);
	last_recv = UNIXTIME;
	if(header.id < MAX_BATTLENET_CMD && Handlers[header.id] != NULL)
		(this->*Handlers[header.id])();
	else
		printf("Unknown cmd %u\n", header.id);
}
