
#ifndef BITREADER_BN_C
#define BITREADER_BN_C

class BitReader_BN
{
private:
    unsigned char * _buffer;
    int32 _numBits;
	int32 _readPos;

public:
    BitReader_BN::BitReader_BN(unsigned char buffer[], uint32 Length)
    {
        _buffer = buffer;
        _numBits = Length*8;
        _readPos = 0;
    }

    unsigned char * Buffer()
    {
        return _buffer;
    }

    int32 NumBits()
    {
        return _numBits;
    }

    int32 ByteLength()
    {
        return NumBits()/8;
    }

    int32 ReadPos()
    {
        return _readPos;
    }

    void AlignToNextByte()
    {
        _readPos = (ReadPos() + 7) & ~7;
    }

    unsigned char * ReadBytes(int32 count)
    {
        AlignToNextByte();
        unsigned char * buf = new unsigned char[count];
		memcpy(buf, _buffer + (ReadPos() >> 3), count);
        _readPos = ReadPos() + count*8;
        return buf;
    }

    unsigned char * ReadBuffer(int32 sizeBitCount)
    {
        int32 blobSize = ReadInt32(sizeBitCount);
        return ReadBytes(blobSize);
    }

    bool ReadBoolean()
    {
        return ReadInt32(1) != 0;
    }

    bool ReadOptional()
    {
        return ReadBoolean();
    }

    float ReadFloat()
    {
        //return BitConverter.ToSingle(BitConverter.GetBytes(ReadInt32(32)), 0);
		return float(ReadInt32(32));
    }

    string ReadAsciiString(int32 bitCount)
    {
        int32 len = ReadInt32(bitCount);
        //return Encoding.ASCII.GetString(ReadBytes(len));;
		return reinterpret_cast<char*>(ReadBytes(len));
    }

    string ReadAsciiString(int32 bitCount, int32 min)
    {
        int32 len = ReadInt32(bitCount, min);
		if (len > 100)
			return "";
		string ret;
		ret.resize(len);
		ret.assign(reinterpret_cast<char*>(ReadBytes(len)), len);
		return ret;
    }

    string ReadUTFString(int32 bitCount)
    {
        int32 len = ReadInt32(bitCount + 2);
        //return Encoding.UTF8.GetString(ReadBytes(len));
		return reinterpret_cast<char*>(ReadBytes(len));
    }

	uint32 ReadUInt32(int32 numBits)
    {
        if (numBits <= 0)
            return 0;
        uint32 ret = 0;
        while (true)
        {
            if (ReadPos() >= _numBits)
            {
                return ret;
            }

            int32 pos7 = (ReadPos() & 7);
            int32 bitsLeftInByte = 8 - pos7;

            int32 subNum = bitsLeftInByte;
            if (bitsLeftInByte >= numBits)
                subNum = numBits;

            Byte lShift = (Byte)(1 << subNum);

            int32 v10 = _buffer[ReadPos() >> 3] >> (ReadPos() & 7);
            numBits -= subNum;

            ret |= (uint32) (((lShift - 1) & v10) << numBits);
            _readPos = ReadPos() + subNum;

            if (numBits == 0)
                return ret;
        }
    }

    int32 ReadInt32(int32 numBits)
    {
        if (numBits <= 0)
            return 0;
        int32 ret = 0;
        while (true)
        {
            if (ReadPos() >= _numBits)
            {
                return ret;
            }

            int32 pos7 = (ReadPos() & 7);
            int32 bitsLeftInByte = 8 - pos7;

            int32 subNum = bitsLeftInByte;
            if (bitsLeftInByte >= numBits)
                subNum = numBits;

            Byte lShift = (Byte) (1 << subNum);

            int32 v10 = _buffer[ReadPos() >> 3] >> (ReadPos() & 7);
            numBits -= subNum;

            ret |= ((lShift - 1) & v10) << numBits;
            _readPos = ReadPos() + subNum;

            if (numBits == 0)
                return ret;
        }
    }


    int32 ReadInt32(int32 numBits, int32 min)
    {
        return ReadInt32(numBits) + min;
    }


    long ReadInt64(int32 numBits)
    {
        if (numBits <= 0)
            return 0;
        long ret = 0;
        while (true)
        {
            if (ReadPos() >= _numBits)
            {
                return ret;
            }

            int32 pos7 = (ReadPos() & 7);
            int32 bitsLeftInByte = 8 - pos7;

            int32 subNum = bitsLeftInByte;
            if (bitsLeftInByte >= numBits)
                subNum = numBits;

            Byte lShift = (Byte)(1 << subNum);

            int32 v10 = _buffer[ReadPos() >> 3] >> (ReadPos() & 7);
            numBits -= subNum;

            ret |= ((lShift - 1) & v10) << numBits;
            _readPos = ReadPos() + subNum;

            if (numBits == 0)
                return ret;
        }
    }
};

#endif