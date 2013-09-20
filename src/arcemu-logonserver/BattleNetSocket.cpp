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
	printf("CREATED SOCKET!\n");
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
	if (readBuffer.GetContiguiousBytes() < 4)
	{
		printf( "[InformationRequest] Packet has no header. Refusing to handle." );
		return;
	}

	// Check the rest of the packet is complete.
	uint8 * ReceiveBuffer = (uint8*)readBuffer.GetBufferStart();

	uint16 full_size = *(uint16*)&ReceiveBuffer[2];

	printf("[InformationRequest] got header, body is %u bytes", full_size );

	if(readBuffer.GetSize() < uint32(full_size+4)){
		printf( "[InformationRequest] Packet is smaller than expected, refusing to handle" );
		return;
	}

	// Copy the data into our cached challenge structure
	if(full_size > sizeof(sAuthLogonChallenge_C))
	{
		printf( "[InformationRequest] Packet is larger than expected, refusing to handle!" );
		Disconnect();
		return;
	}

	printf("[InformationRequest] got a complete packet.");

	//memcpy(&m_challenge, ReceiveBuffer, full_size + 4);
	//RemoveReadBufferBytes(full_size + 4, true);
	readBuffer.Read(&m_challenge, full_size + 4);
}

void BattleNetSocket::OnRead()
{
	printf("Called!\n");
	if(readBuffer.GetContiguiousBytes() < 1)
		return;

	int32 Command = *(int32*)readBuffer.GetBufferStart();
	printf("%d\n",Command);
	last_recv = UNIXTIME;
	if(Command < MAX_BATTLENET_CMD && Handlers[Command] != NULL)
		(this->*Handlers[Command])();
	else
		printf("Unknown cmd %u\n", Command);
}