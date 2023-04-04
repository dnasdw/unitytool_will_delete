#include "namegetter.h"

CNameGetter::CNameGetter()
	: m_bLittleEndian(true)
{
}

CNameGetter::~CNameGetter()
{
}

void CNameGetter::SetLittleEndian(bool a_bLittleEndian)
{
	m_bLittleEndian = a_bLittleEndian;
}

const string& CNameGetter::GetName() const
{
	return m_sName;
}

bool CNameGetter::ReadName()
{
	n32 nStringSize = 0;
	if (!CStream::ReadN32(nStringSize, m_bLittleEndian).good())
	{
		return false;
	}
	if (nStringSize < 0)
	{
		return false;
	}
	if (nStringSize != 0)
	{
		m_sName.resize(nStringSize);
		if (!CStream::Read(&*m_sName.begin(), nStringSize).good())
		{
			return false;
		}
		if (strlen(m_sName.c_str()) != nStringSize)
		{
			return false;
		}
	}
	n64 nPos = istringstream::tellg();
	n32 nPaddingSize = static_cast<n32>(Align(nPos, 4) - nPos);
	if (!CStream::IsPaddingValid(nPaddingSize))
	{
		return false;
	}
	return true;
}
