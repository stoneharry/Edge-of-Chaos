
#ifndef _BATTLENETSOCKET
#define _BATTLENETSOCKET

#define MAX_BATTLENET_CMD 5

#include "AccountCache.h"
#include "AuthStructs.h"

struct InfRequestComponents
{
	char Program[4];
	char Platform[4];
	int Build:32;
};

struct InformationRequestStruct
{
	//char Program[4];
	//char Platform[4];
	//char Locale[4];
	int32 Program:4; // I have no clue how to read this data, http://pastebin.com/rDPmNumD it is sent from the client like this
	int32 Platform:4; // Until this data can be read we cannot get any further
	int32 Locale:4;
	int componentCount:6;
	vector<InfRequestComponents> components;
	int hasAccountName:1;
	int accountLength:9; // then add 3 to this
	vector<char> accountName;
};

struct BN_PacketHeader
{
	int id:6;
	int hasChannel:1;
};

struct BN_Channel
{
	int Channel:4;
};

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