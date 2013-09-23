
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

    //int32 WritePos { get; set; }

    template <T> Shift (T left, int32 right)
    {
        if (typeof (T).Name == "Int32")
            return Convert.ToInt32(left) >> right;

        if (typeof (T).Name == "UInt32")
            return (int) (Convert.ToUInt32(left) >> right);

        return 0;
    }

    void AlignToNextByte()
    {
        WritePos = (WritePos + 7) & ~7;
    }

    void WriteBytes( unsigned char * bytes )
    {
        AlignToNextByte();

        foreach (var b in bytes)
        {
            WriteBits((int)b, 8);
        }
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
    void WriteBits<T>(T valz, int32 numBits)
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
                var lShift = (char) (1 << unk);
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
                var firstHalf = (char) (~((lShift - 1) << pos7));

				// both 0
				// second run, both 10
				// 3rd run = 2797
				// 4th run = 60906
				// 5th run = 28503
                var shifted = (char) Shift(valz, numBits);
				// 3rd run = 237
				// 4th run = 234
				// 5th run = 7
                var secondHalf = (char) (((lShift - 1) & shifted) << pos7);

                Buffer[WritePos >> 3] = (byte) (Buffer[WritePos >> 3] & firstHalf | secondHalf);

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
        /*unsigned char* arr = Encoding.ASCII.GetBytes(fourCC);
        Array.Reverse(arr);

        if (arr.Length < 4)
        {
            byte[] backup = arr;
            arr = new byte[arr.Length + 1];
            backup.CopyTo(arr, 0);
        }
        int32 test = BitConverter.ToInt32(arr, 0);
        WriteInt32(BitConverter.ToInt32(arr,0));*/
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

};

#endif