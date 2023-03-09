#include "stringstream.h"

CStringStream::CStringStream()
	: istringstream(ios_base::in | ios_base::binary)
{
}

CStringStream::CStringStream(const string& a_sStr)
	: istringstream(a_sStr, ios_base::in | ios_base::binary)
{
}

CStringStream::~CStringStream()
{
}
