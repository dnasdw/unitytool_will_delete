#include "filestream.h"

CFileStream::CFileStream()
	: ifstream()
{
}

CFileStream::CFileStream(const UString& a_sFileName)
	: ifstream(a_sFileName.c_str(), ios_base::in | ios_base::binary)
{
}

CFileStream::~CFileStream()
{
}

CFileStream& CFileStream::Open(const UString& a_sFileName)
{
	ifstream::open(a_sFileName.c_str(), ios_base::in | ios_base::binary);
	return *this;
}

CFileStream& CFileStream::Close()
{
	if (ifstream::is_open())
	{
		ifstream::close();
	}
	return *this;
}
