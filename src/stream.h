#ifndef STREAM_H_
#define STREAM_H_

#include <sdw.h>

class CEndiannessTester
{
public:
	CEndiannessTester();
	virtual ~CEndiannessTester();
	static bool IsSizeSafe(n64 a_nSize);
protected:
	static bool s_bLittleEndian;
private:
	static bool s_bInitEndian;
};

template<typename IStreamType>
class CStream
	: virtual public IStreamType
	, public CEndiannessTester
{
public:
	CStream<IStreamType>& Read(void* a_pValue, ptrdiff_t a_nValueSize)
	{
		IStreamType::read(reinterpret_cast<char*>(a_pValue), a_nValueSize);
		return *this;
	}
	CStream<IStreamType>& ReadN8(n8& a_nValue)
	{
		IStreamType::read(reinterpret_cast<char*>(&a_nValue), sizeof(n8));
		return *this;
	}
	CStream<IStreamType>& ReadN16(n16& a_nValue, bool a_bLittleEndian)
	{
		IStreamType::read(reinterpret_cast<char*>(&a_nValue), sizeof(n16));
		if (a_bLittleEndian != s_bLittleEndian)
		{
			a_nValue = SDW_CONVERT_ENDIAN16(a_nValue);
		}
		return *this;
	}
	CStream<IStreamType>& ReadN32(n32& a_nValue, bool a_bLittleEndian)
	{
		IStreamType::read(reinterpret_cast<char*>(&a_nValue), sizeof(n32));
		if (a_bLittleEndian != s_bLittleEndian)
		{
			a_nValue = SDW_CONVERT_ENDIAN32(a_nValue);
		}
		return *this;
	}
	CStream<IStreamType>& ReadN64(n64& a_nValue, bool a_bLittleEndian)
	{
		IStreamType::read(reinterpret_cast<char*>(&a_nValue), sizeof(n64));
		if (a_bLittleEndian != s_bLittleEndian)
		{
			a_nValue = SDW_CONVERT_ENDIAN64(a_nValue);
		}
		return *this;
	}
	CStream<IStreamType>& ReadU8(u8& a_uValue)
	{
		IStreamType::read(reinterpret_cast<char*>(&a_uValue), sizeof(u8));
		return *this;
	}
	CStream<IStreamType>& ReadU16(u16& a_uValue, bool a_bLittleEndian)
	{
		IStreamType::read(reinterpret_cast<char*>(&a_uValue), sizeof(u16));
		if (a_bLittleEndian != s_bLittleEndian)
		{
			a_uValue = SDW_CONVERT_ENDIAN16(a_uValue);
		}
		return *this;
	}
	CStream<IStreamType>& ReadU32(u32& a_uValue, bool a_bLittleEndian)
	{
		IStreamType::read(reinterpret_cast<char*>(&a_uValue), sizeof(u32));
		if (a_bLittleEndian != s_bLittleEndian)
		{
			a_uValue = SDW_CONVERT_ENDIAN32(a_uValue);
		}
		return *this;
	}
	CStream<IStreamType>& ReadU64(u64& a_uValue, bool a_bLittleEndian)
	{
		IStreamType::read(reinterpret_cast<char*>(&a_uValue), sizeof(u64));
		if (a_bLittleEndian != s_bLittleEndian)
		{
			a_uValue = SDW_CONVERT_ENDIAN64(a_uValue);
		}
		return *this;
	}
	CStream<IStreamType>& ReadString(string& a_sValue)
	{
		std::getline(*this, a_sValue, '\0');
		return *this;
	}
	bool IsPaddingValid(ptrdiff_t a_nSize, u8 a_uPaddingValue = 0)
	{
		if (a_nSize < 0)
		{
			return false;
		}
		if (a_nSize > 0)
		{
			vector<u8> vPadding(a_nSize);
			if (!Read(&*vPadding.begin(), a_nSize).good())
			{
				return false;
			}
			if (count(vPadding.begin(), vPadding.end(), a_uPaddingValue) != a_nSize)
			{
				return false;
			}
		}
		return IStreamType::good();
	}
};

class CTestIFStream : public CStream<ifstream>
{
private:
	CTestIFStream();
	void test();
};

class CTestIStringStream : public CStream<istringstream>
{
private:
	CTestIStringStream();
	void test();
};

#endif	// STREAM_H_
