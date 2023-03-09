#include "stream.h"

bool CEndiannessTester::s_bLittleEndian = true;
bool CEndiannessTester::s_bInitEndian = false;

CEndiannessTester::CEndiannessTester()
{
	if (!s_bInitEndian)
	{
		u32 uBOM = 0xFEFF;
		u32 uBOMLow = *reinterpret_cast<u8*>(&uBOM);
		s_bLittleEndian = uBOMLow == 0xFF;
		s_bInitEndian = true;
	}
}

CEndiannessTester::~CEndiannessTester()
{
}

bool CEndiannessTester::IsSizeSafe(n64 a_nSize)
{
	if (sizeof(ptrdiff_t) == 4)
	{
		return a_nSize <= INT32_MAX;
	}
	else if (sizeof(ptrdiff_t) == 8)
	{
		return a_nSize <= INT64_MAX;
	}
	return false;
}

CTestIFStream::CTestIFStream()
{
}

void CTestIFStream::test()
{
	u64 uTest;
	string sTest;
	CStream::Read(&uTest, sizeof(u64));
	CStream::ReadN8(*reinterpret_cast<n8*>(&uTest));
	CStream::ReadN16(*reinterpret_cast<n16*>(&uTest), true);
	CStream::ReadN32(*reinterpret_cast<n32*>(&uTest), true);
	CStream::ReadN64(*reinterpret_cast<n64*>(&uTest), true);
	CStream::ReadU8(*reinterpret_cast<u8*>(&uTest));
	CStream::ReadU16(*reinterpret_cast<u16*>(&uTest), true);
	CStream::ReadU32(*reinterpret_cast<u32*>(&uTest), true);
	CStream::ReadU64(*reinterpret_cast<u64*>(&uTest), true);
	CStream::ReadString(sTest);
	CStream::IsPaddingValid(1);
}

CTestIStringStream::CTestIStringStream()
{
}

void CTestIStringStream::test()
{
	u64 uTest;
	string sTest;
	CStream::Read(&uTest, sizeof(u64));
	CStream::ReadN8(*reinterpret_cast<n8*>(&uTest));
	CStream::ReadN16(*reinterpret_cast<n16*>(&uTest), true);
	CStream::ReadN32(*reinterpret_cast<n32*>(&uTest), true);
	CStream::ReadN64(*reinterpret_cast<n64*>(&uTest), true);
	CStream::ReadU8(*reinterpret_cast<u8*>(&uTest));
	CStream::ReadU16(*reinterpret_cast<u16*>(&uTest), true);
	CStream::ReadU32(*reinterpret_cast<u32*>(&uTest), true);
	CStream::ReadU64(*reinterpret_cast<u64*>(&uTest), true);
	CStream::ReadString(sTest);
	CStream::IsPaddingValid(1);
}
