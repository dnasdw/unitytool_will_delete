#ifndef STRINGSTREAM_H_
#define STRINGSTREAM_H_

#include "stream.h"

class CStringStream : public CStream<istringstream>
{
public:
	CStringStream();
	CStringStream(const string& a_sStr);
	virtual ~CStringStream();
};

#endif	// STRINGSTREAM_H_
