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
		delete reader;
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
		delete reader;
		printf("WARNING: Account tried to connect with no account name.\n");
		SendError(AUTH_BAD_CREDENTIALS);
		Disconnect();
		return;
	}
	infoR.accountName = reader->ReadAsciiString(9, 3);

	delete reader;

	if (infoR.accountName.length() == 0)
	{
		SendError(AUTH_BAD_CREDENTIALS);
		Disconnect();
		return;
	}

	if (infoR.program != "WoW")
	{
		printf("Someone tried to connect who is not using WoW! They use: %s.\n", infoR.program);
		SendError(AUTH_INVALID_PROGRAM);
		Disconnect();
		return;
	}

	// Check for a possible IP ban on this client.
	BAN_STATUS ipb = IPBanner::getSingleton().CalculateBanStatus(GetRemoteAddress());
	if( ipb != BAN_STATUS_NOT_BANNED )
	{
		printf("Battle.net detected ban person logging in. Refusing.", GetRemoteIP().c_str());
		SendError(LOGIN_BANNED);
		Disconnect();
		return;
	}

	// Make account name uppercase
	transform(infoR.accountName.begin(), infoR.accountName.end(),infoR.accountName.begin(), ::toupper);
	m_account = AccountMgr::getSingleton().GetAccount(infoR.accountName);
	if(m_account == 0)
	{
		SendError(AUTH_BAD_CREDENTIALS);
		printf("[Battlenet] Invalid account name: %s.", infoR.accountName.c_str());
		Disconnect();
		return;
	}
	if(m_account->Banned != 0)
	{
		SendError(LOGIN_BANNED);
		Disconnect();
		return;
	}

	////////////////////////////////////////////////////////////////////////////////////
	// We need to check the build which is sent in the components
	// Build is loaded from component-locale-wow.txt which is located in the highest priority MPQ
	// Changing the build causes WoW to crash when logging in with Battle.net 2 protocol
	// So instead we will hackfix by parsing build in with username, yay!
	////////////////////////////////////////////////////////////////////////////////
	// TO DO //////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	// Now for proof response
	// Header
	writer = new BitWriter_BN(206+321+1024); // (( (4*8) + (4*8) + 32 ) * 2) + 3 + 11 = 206
	writer->WriteHeader(2, 0);
	int32 Zero = 0;
	// Some stuff
	writer->WriteBits(Zero, 1); // HasError must equal 0
	int32 moduleCount = 2;
	writer->WriteBits(moduleCount, 3);
	// Passwords.dll
	writer->WriteFourCC("auth");
	writer->WriteFourCC(infoR.locale);
	const char * moduleID = "8f52906a2c85b416a595702251570f96d3522f39237603115f2f1ab24962043c";
	writer->WriteBits(moduleID, 32);
	// Size of module data this must be
	int32 blobSize = 0;
	writer->WriteBits(blobSize, 10);
	// Module Data, starts with 0
	// usersalt (offset 1, size 0x20)
	// passsalt (offset 21, size 0x20)
	// publicB  (offset 41, size 0x80)
	// Eh, hex to binary of something, maybe password.dll data (offset 0xc1, size 0x80)
	// 1 + 0x20 + 0x20 + 0x80 + 0x80 = 321
	unsigned char * moduleData = new unsigned char[321];
	writer->WriteBytes(moduleData, 321);
	/*
	        this.authState = 1;
            byte[] dst = new byte[0x141];
            dst[0] = 0;
            Buffer.BlockCopy(this.handler.User.UserSalt, 0, dst, 1, 0x20);
            Buffer.BlockCopy(this.handler.User.PassSalt, 0, dst, 0x21, 0x20);
            Buffer.BlockCopy(this.crypto._PublicB, 0, dst, 0x41, 0x80);
            Buffer.BlockCopy(Utilities.HexToBin("0EA3375900A3F7CA981C3F61B6CA728BA25126959240EE93DB398AFCA28FAE9501B3853EB11E2E37C02078F9C8E31EA079F1ED5E65964BB853DAEB58C7DDEDBD880E66554C9C039AAE78AA78309AAD8442DB29ABD4C59222FD9FF7C3AA65638D78494FBBEA6A5EF66A9DBA58BB79F9A0B5352ECF1F9E6BBE724A8EC571517C74"), 0, dst, 0xc1, 0x80);
            return dst;
	*/
	// Thumbnails.dll
	writer->WriteFourCC("auth");
	writer->WriteFourCC(infoR.locale);
	const char * moduleID2 = "36b27cd911b33c61730a8b82c8b2495fd16e8024fc3b2dde08861c77a852941c";
	writer->WriteBits(moduleID2, 32);
	// Size of module data
	int32 blobSize2 = 0;
	writer->WriteBits(blobSize2, 10);
	// Module Data, starts with 0
	//  return Utilities.HexToBin("23DE12E08B3CEF5C2BB5DF2BC82D9F0D2F55ECD47C7616B3122ED1ED0C1C75B0CEDADC9DAB44815AD7C1D551A8437954D2FFAB5E5F34379298F08BF98A907821348CAF24D4F18B6EBEE951CB3B08154792D74E41A04657E038777648425AA26053C3F5C6882B7A794C042CECD529C8B7D0C41921EB9A75C9D75FCB468F95B12B4E62FF6C60EC9704BAFFEF33578DFE0745624FADA2FCEE67D4DEEEAF451875601FFB90B3EEC5484CE76888C540A0AC480F6CB5BC6D77F971A52937D6AD482186E5692F14E7212EBC744FD57D55AF6C294F4E184A32855110D08E418DD2D491CF480230CA1CE3BCE8ADE148B66D986F1B37DF7977D7E747F3172DA60F2189013EE653BE163A501E81C84CBFE138EAFDEEEBD9365C7756670256A2CD804ADE31E44480A59AD98B182A41AD45FE7BC858912D466B07FFB61B707325E2853B79ABC21CD9897706689B943AE3BF2704EFB987F5A437F2C79F6F16C838A05DB56CF00EAC4BBDC438D7171148E69AFF67A72E87BF44938A7408EF3562656201874C4BB09533ABE919A67B66B0432607FD8300C9836A1377CF00C93DD63287C637594E5AAEF24F788DBC9A87C3C1C85744336A8511F4BD2F73F801E6A4A0FAD34C95FF84192D7FFE4CDD1319CAB1533C903A1DF8CA33775FECF48B0DC8C1223A8324C6EF06AF490745FCCA476AD0D8DA5EEABE778C80EDF21B15B6C092277ABDB1C33E71");
	// convert above to bin, put that below
	unsigned char * moduleData2 = new unsigned char[1024];
	writer->WriteBytes(moduleData2, 1024);
	// We will need to disable RSA check (which is what this module is) in the client
	// Send
	Send(writer->Buffer(), 206+321+1024);
	delete writer;
}

void BattleNetSocket::SendError(int32 ErrorCode)
{
	BitWriter_BN * writer = new BitWriter_BN(63); // 6 + 1 + 4 + 1 + 1 + 2 + 0x10 + 0x20

	int32 Zero = 0;
	int32 One = 1;
	// Header
	writer->WriteBits(Zero, 6);
	writer->WriteBits(One, 1);
	writer->WriteBits(Zero, 4);
	// Contents
	writer->WriteBits(One, 1); // bool HasError
	writer->WriteBits(Zero, 1); // bool ???
	writer->WriteBits(One, 2); // ???
	writer->WriteBits(ErrorCode, 0x10);
    writer->WriteBits(Zero, 0x20); // ???

	Send(writer->Buffer(), 63);

	delete writer;
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
