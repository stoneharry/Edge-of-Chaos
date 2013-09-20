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
}

BattleNetSocket::~BattleNetSocket()
{
}

void BattleNetSocket::InformationRequest()
{
}

void BattleNetSocket::OnRead()
{
	if(readBuffer.GetContiguiousBytes() < 1)
		return;

	uint8 Command = *(uint8*)readBuffer.GetBufferStart();
	last_recv = UNIXTIME;
	if(Command < MAX_BATTLENET_CMD && Handlers[Command] != NULL)
		(this->*Handlers[Command])();
	else
		printf("Unknown cmd %u\n", Command);
}