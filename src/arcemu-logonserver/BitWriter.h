
#ifndef BITWRITER_H_BN
#define BITWRITER_H_BN

class BitWriter_BN
{
private:
    unsigned char * _buffer;
    int32 _numBits;

public:
    BitWriter_BN(int32 capacity)
    {
        _buffer = new unsigned char[capacity];
    }

    unsigned char * Buffer()
    {
        return _buffer;
    }

    int32 NumBits()
    {
       return _numBits;
    }

    int32 Length()
    {
        int32 pos7 = (WritePos & 7);
        int32 bitsLeft = 8 - pos7;

        if (bitsLeft == 0)
            return NumBits() / 8;
        return (_numBits + bitsLeft)/8;
    }

	template<typename T>
	T Shift (T left, int32 right) {
		return (T)0;
	}

	template<>
	uint32 Shift<uint32>(uint32 left, int32 right) {
		return left >> right;
	}

	template<>
	int32 Shift<int32>(int32 left, int32 right) {
		return static_cast<int32>(static_cast<uint32>(left) >> right);
	}

    void AlignToNextByte()
    {
        WritePos = (WritePos + 7) & ~7;
    }

    void WriteBytes( unsigned char * bytes )
    {
        AlignToNextByte();
		printf("NOT HANDLED\n");
        /*foreach (var b in bytes)
        {
            WriteBits((int)b, 8);
        }*/
    }

    void WriteBytes( unsigned char * bytes, int32 length )
    {
        unsigned char* buf = new unsigned char[length];
        //Array.Copy(bytes, 0, buf, 0, length);
		memcpy(buf, bytes, length);
        WriteBytes(buf);
    }

    void WriteBuffer(unsigned char * bytes, int32 byteLength, int32 sizeBitCount)
    {
        WriteBits(byteLength, sizeBitCount);
        WriteBytes(bytes, byteLength);
    }

    void WriteInt32( int32 intVal )
    {
        WriteBits(intVal, 32);
    }

    // passing 5730135 into function, which is equal to 'WoW' (WoW + chr(0) to make 4 chars)
    template<typename T> void WriteBits(T valz, int numBits)
    {
        if (numBits > 0)
        {
			// becomes 43 (+ 32 to old result)
            _numBits += numBits;
            while (true)
            {
				// WritePos = 11, pos7 becomes 3
				// second run, WritePos = 16, pos7 = 0
				// 3rd run, WritePos = 32, pos7 = 0
				// 4th run, WritePos = 40, pos7 = 0
				// 5th run, WritePos = 40, pos7 = 0
                int32 pos7 = (WritePos & 7);
				// unk = 5
				// second run, unk = 8
				// 3rd + 4th + 5th, unk = 8
                int32 unk = 8 - pos7;
				// lShift = 32
				// second run, 256
				// 3rd, 4th, 5th = 256
                char lShift = (char) (1 << unk);
                int32 subNum;

                if (unk < numBits)
					// = 5
					// second run, 8
					// 3rd = 8
					// 4th = 8
                    subNum = unk;
                else
                {
					// 5th run
					// lshift = 8
                    lShift = (char) (1 << numBits);
					// subnum = 3
                    subNum = numBits;
                }
				// numbits = 27 now
				// second run, 19
				// 4th = 3
				// 5th = 0
                numBits -= subNum;
					
				// 65287
				// 65280 second run & 3rd & 4th
				// 65528 = 5th
                char firstHalf = (char) (~((lShift - 1) << pos7));

				// both 0
				// second run, both 10
				// 3rd run = 2797
				// 4th run = 60906
				// 5th run = 28503
                char shifted = (char) Shift(valz, numBits);
				// 3rd run = 237
				// 4th run = 234
				// 5th run = 7
                char secondHalf = (char) (((lShift - 1) & shifted) << pos7);

                Buffer()[WritePos >> 3] = (Byte) (Buffer()[WritePos >> 3] & firstHalf | secondHalf);

				// writepos = 16
				// second run, writepos = 24
				// 3rd run, = 32
				// 4th run = 40
				// 5th run = 43
                WritePos += subNum;

				// 5th run = 0
                if (numBits == 0)
                    return;
            }
        }
    }

    void WriteFourCC(string fourCC)
    {
		string temp = fourCC;
		for (uint32 i = 0; i < fourCC.length(); ++i)
		{
			fourCC[fourCC.length() - 1 - i] = temp[i];
		}
		if (fourCC.length() < 4)
			fourCC.push_back('\0');
		int32 value = atoi(fourCC.c_str());
        WriteInt32(value);
    }

    void WriteHeader( int32 packetId, int32 channelId )
    {
        WriteBits(packetId, 6);
        WriteBits(1, 1);
        WriteBits(channelId, 4);
    }

    string ToString()
    {
        string str = "";
        int32 numBytes = _numBits/8;

        if (_numBits % 8 > 0)
            numBytes++;

        for( int32 i = 0; i < numBytes; i++)
        {
            if (i > 0 && i % 16 == 0)
                str += "\r\n";

            //str += string.Format("{0:x2} ", Buffer[i]); // wut
        }
        return str;
    }

	int32 WritePos;
};

#endif