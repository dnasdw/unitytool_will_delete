#ifndef VERSION_H_
#define VERSION_H_

#include <sdw.h>

class CVersion
{
public:
	CVersion();
	~CVersion();
	bool Init(const string& a_sVersionString);
	n32 Compare(const CVersion& a_Other) const;
private:
	static const string s_sVersionString;
	n32 m_nVersion[5];
};

#endif	// VERSION_H_
