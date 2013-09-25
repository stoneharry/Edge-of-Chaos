
#ifndef _BATTLENETSOCKET
#define _BATTLENETSOCKET

#define MAX_BATTLENET_CMD 5

#include "AccountCache.h"
#include "AuthStructs.h"
#include "BattlenetCrypto.h"
#include "BitReader.h"
#include "BitWriter.h"

enum BnetAuthErrors : int32
{
    AUTH_BAD_CREDENTIALS = 0x68,
    AUTH_BAD_SERVER = 0x67,
    AUTH_CLOSED = 0x69,
    AUTH_DUPLICATE_LOGON = 0x73,
    AUTH_FAILED = -1,
    AUTH_INVALID_PROGRAM = 0x6d,
    AUTH_LOGON_TOO_FAST = 0x7b,
    AUTH_NO_GAME_ACCOUNTS = 0x6b,
    AUTH_OK = 0,
    AUTH_TEMP_OUTAGE = 0x71,
    AUTH_USE_GRUNT_LOGON = 0x7c,
    LOGIN_ANTI_INDULGENCE = 0xd3,
    LOGIN_BANNED = 0xca,
    LOGIN_CHARGEBACK = 0xd5,
    LOGIN_EXPIRED = 0xcf,
    LOGIN_GAME_ACCOUNT_LOCKED = 0xcc,
    LOGIN_IGR_WITHOUT_BNET = 0xd6,
    LOGIN_LOCKED_ENFORCED = 0xd7,
    LOGIN_NOTIME = 0xce,
    LOGIN_PARENTALCONTROL = 0xd1,
    LOGIN_SUSPENDED = 0xcb,
    LOGIN_TRIAL_EXPIRED = 210,
    LOGIN_UNLOCKABLE_LOCK = 0xd8
};

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
	void SendError(int32 ErrorCode);

	time_t last_recv;
protected:
	string ReverseString(string str);
	BitReader_BN * reader;
	BitWriter_BN * writer;
	sAuthLogonChallenge_C_BattleNet m_challenge;
	Account * m_account;
	bool m_authenticated;
	const static int32 Zero = 0;
	const static int32 One = 1;
};

#endif