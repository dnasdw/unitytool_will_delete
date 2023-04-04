#ifndef NAMEGETTER_H_
#define NAMEGETTER_H_

#include "stringstream.h"

class CNameGetter : public CStringStream
{
public:
	CNameGetter();
	~CNameGetter();
	void SetLittleEndian(bool a_bLittleEndian);
	const string& GetName() const;
	bool ReadName();
private:
	bool m_bLittleEndian;
	string m_sName;
};

#endif	// NAMEGETTER_H_
