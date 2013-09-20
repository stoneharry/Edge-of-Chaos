
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

	ARCEMU_INLINE sAuthLogonChallenge_C_BattleNet * GetChallenge() { return &m_challenge; }
	ARCEMU_INLINE void SendPacket(const uint8* data, const uint16 len) { Send(data, len); }
	void OnDisconnect();
	ARCEMU_INLINE time_t GetLastRecv() { return last_recv; }
	bool removedFromSet;
	ARCEMU_INLINE uint32 GetAccountID() { return m_account ? m_account->AccountId : 0; }

	time_t last_recv;
protected:
	sAuthLogonChallenge_C_BattleNet m_challenge;
	Account * m_account;
	bool m_authenticated;
};

#endif