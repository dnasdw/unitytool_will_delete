#ifndef LZ4_H_
#define LZ4_H_

#include <sdw.h>

class CLz4
{
public:
	static n32 GetCompressBoundSize(n32 a_nUncompressedSize);
	static bool Uncompress(const char* a_pCompressed, n32 a_nCompressedSize, char* a_pUncompressed, n32& a_nUncompressedSize);
	static bool Compress(const char* a_pUncompressed, n32 a_nUncompressedSize, char* a_pCompressed, n32& a_nCompressedSize);
private:
	CLz4();
};

#endif	// LZ4_H_
