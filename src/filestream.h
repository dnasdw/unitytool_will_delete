#ifndef FILESTREAM_H_
#define FILESTREAM_H_

#include "stream.h"

class CFileStream : public CStream<ifstream>
{
public:
	CFileStream();
	CFileStream(const UString& a_sFileName);
	virtual ~CFileStream();
	CFileStream& Open(const UString& a_sFileName);
	CFileStream& Close();
};

#endif	// FILESTREAM_H_
