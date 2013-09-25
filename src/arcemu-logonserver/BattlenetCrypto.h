
#ifndef BN_CRYPTO_H
#define BN_CRYPTO_H

#include "Common.h"
#include <algorithm>
#include <iterator>
#include <iomanip>

#define SALT_LENGTH 42

const static string passSaltString = "2cfc79a2b55761326805a0cdde4bbd734c686724bd6add9b630ddf0b8f7059e9";
const static string userSaltString = "01e324110608e8ebfdfa24af33d79d9c60c5076e6e87c7ea07b106b635b5123e";
const static string somethingHex = "0EA3375900A3F7CA981C3F61B6CA728BA25126959240EE93DB398AFCA28FAE9501B3853EB11E2E37C02078F9C8E31EA079F1ED5E65964BB853DAEB58C7DDEDBD880E66554C9C039AAE78AA78309AAD8442DB29ABD4C59222FD9FF7C3AA65638D78494FBBEA6A5EF66A9DBA58BB79F9A0B5352ECF1F9E6BBE724A8EC571517C74";

class BN_Crypto
{
public:
	BN_Crypto(string _password)
	{
		password = _password;
		arcemu_TOUPPER(password);
		vector<unsigned char> user_bin;
		vector<unsigned char> pass_bin;
		vector<unsigned char> something_bin;
		HexadecimalToBinary(userSaltString, user_bin);
		HexadecimalToBinary(passSaltString, pass_bin);
		HexadecimalToBinary(somethingHex, something_bin);
		userSalt = reinterpret_cast<unsigned char*>(user_bin.data());
		passSalt = reinterpret_cast<unsigned char*>(user_bin.data());
		Something = reinterpret_cast<unsigned char*>(something_bin.data());

		publicB = new unsigned char[0x80]; // TEMP

		Generate_b();
		_I = BinaryToHexadecimal(userSalt);
		Calculate_x();
		Calculate_v();
        Calculate_k();
        Calculate_PublicB();
	}

	~BN_Crypto()
	{
		delete _b;
		delete userSalt;
		delete passSalt;
		delete publicB;
		delete Something;
	}

	void Generate_b()
	{
		_b = new unsigned char[0x80];
		srand(time(NULL));
		for(int32 i = 0; i < 0x80; i++)
			_b[i] = rand() % 256;
	}

	void Calculate_x()
	{
		//this._x = this.Sha256(this.Join(new byte[][] { this._s, this.Sha256(this._I + ":" + this._P) }));
	}

	void Calculate_v()
	{
		/*
		    BigInteger bigIntAbs = this.GetBigIntAbs(this._g);
            BigInteger exponent = this.GetBigIntAbs(this._x);
            BigInteger modulus = this.GetBigIntAbs(this._N);
            this._v = this.BigIntToByteArray(BigInteger.ModPow(bigIntAbs, exponent, modulus));
		*/
	}

	void Calculate_k()
	{
		//this._k = this.Sha256(this.Join(new byte[][] { this._N, this._g }));
	}

	void Calculate_PublicB()
	{
		/*
		    BigInteger bigIntAbs = this.GetBigIntAbs(this._k);
            BigInteger integer2 = this.GetBigIntAbs(this._v);
            BigInteger integer3 = this.GetBigIntAbs(this._g);
            BigInteger exponent = this.GetBigIntAbs(this._b);
            BigInteger divisor = this.GetBigIntAbs(this._N);
            this._PublicB = this.BigIntToByteArray((bigIntAbs * integer2) + BigInteger.ModPow(integer3, exponent, divisor) % divisor);
		*/
	}

	string BinaryToHexadecimal(unsigned char* userSalt)
	{
		string ret("");

		ostringstream ss;

		vector<unsigned char> v;
		v.resize(SALT_LENGTH);
		for (int32 i = 0; i < SALT_LENGTH; i++)
			v[i] = userSalt[i];

		ss << std::hex << std::uppercase << std::setfill( '0' );
		std::for_each( v.cbegin(), v.cend(), [&]( int c ) { ss << std::setw( 2 ) << c; } );

		ret = ss.str();

		return ret;
	}

	void HexadecimalToBinary(const string & hex, vector<unsigned char> & bin)
	{
		for(uint32 i = 0; i < hex.length() / 2; ++i)
		{
			stringstream strm;
			strm << hex.substr(i * 2, 2);
			unsigned int cur = 0;
			strm >> std::hex >> cur;
			bin.push_back((unsigned char)cur);
		}
	}

	unsigned char* userSalt;
	unsigned char* passSalt;
	unsigned char* publicB;
	unsigned char* Something;
private:
	string password;
	unsigned char* _b;
	string _I;
};

#endif