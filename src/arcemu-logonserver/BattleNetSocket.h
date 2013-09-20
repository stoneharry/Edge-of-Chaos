
#ifndef _BATTLENETSOCKET
#define _BATTLENETSOCKET

#define MAX_BATTLENET_CMD 5

#include "AccountCache.h"
#include "AuthStructs.h"

class LogonCommServerSocket;

class BattleNetSocket : public Socket
{
	friend class LogonCommServerSocket;
public:
	BattleNetSocket(SOCKET fd);
	~BattleNetSocket();

	void OnRead();
	void InformationRequest();

	time_t last_recv;
protected:
	sAuthLogonChallenge_C_BattleNet m_challenge;
};

#endif