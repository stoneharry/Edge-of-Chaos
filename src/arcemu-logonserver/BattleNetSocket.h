
#ifndef _BATTLENETSOCKET
#define _BATTLENETSOCKET

#define MAX_BATTLENET_CMD 5

#include "AccountCache.h"
#include "AuthStructs.h"
#include "BitReader.h"

struct InfRequestComponents
{
	string program;
	string platform;
	int32 Build;
};

struct InformationRequestStruct
{
	string program;
	string platform;
	string locale;
	int32 componentCount;
	vector<InfRequestComponents> components;
	int32 hasAccountName;
	int32 accountLength; // then add 3 to this
	string accountName;
};

struct BN_PacketHeader
{
	int32 id;
	bool hasChannel;
	int32 Channel;
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
	string ReverseString(string str);
	BitReader_BN * reader;
	sAuthLogonChallenge_C_BattleNet m_challenge;
	Account * m_account;
	bool m_authenticated;
};

#endif