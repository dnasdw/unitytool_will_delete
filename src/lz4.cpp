#include "lz4.h"
#include <lz4.h>

n32 CLz4::GetCompressBoundSize(n32 a_nUncompressedSize)
{
	return LZ4_compressBound(a_nUncompressedSize);
}

bool CLz4::Uncompress(const char* a_pCompressed, n32 a_nCompressedSize, char* a_pUncompressed, n32& a_nUncompressedSize)
{
	bool bResult = true;
	n32 nUncompressedSize = LZ4_decompress_safe(a_pCompressed, a_pUncompressed, a_nCompressedSize, a_nUncompressedSize);
	if (nUncompressedSize < 0)
	{
		bResult = false;
	}
	else
	{
		a_nUncompressedSize = nUncompressedSize;
	}
	return bResult;
}

bool CLz4::Compress(const char* a_pUncompressed, n32 a_nUncompressedSize, char* a_pCompressed, n32& a_nCompressedSize)
{
	bool bResult = true;
	n32 nCompressedSize = LZ4_compressBound(a_nUncompressedSize);
	if (nCompressedSize == 0)
	{
		bResult = false;
	}
	else
	{
		nCompressedSize = LZ4_compress_default(a_pUncompressed, a_pCompressed, a_nUncompressedSize, a_nCompressedSize);
		if (nCompressedSize == 0)
		{
			bResult = false;
		}
		else
		{
			a_nCompressedSize = nCompressedSize;
		}
	}
	return bResult;
}

CLz4::CLz4()
{
}
