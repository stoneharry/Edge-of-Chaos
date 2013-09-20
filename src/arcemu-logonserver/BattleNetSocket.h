
#ifndef _BATTLENETSOCKET
#define _BATTLENETSOCKET

#define MAX_BATTLENET_CMD 5

#include "AccountCache.h"
#include "AuthStructs.h"

class BattleNetSocket : public Socket
{
public:
	BattleNetSocket(SOCKET fd);
	~BattleNetSocket();

	void OnRead();
	void InformationRequest();

	time_t last_recv;
};

#endif