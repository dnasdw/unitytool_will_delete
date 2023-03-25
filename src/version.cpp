#include "version.h"

const string CVersion::s_sVersionString = "abfpx";

CVersion::CVersion()
{
	memset(m_nVersion, 0, sizeof(m_nVersion));
}

CVersion::~CVersion()
{
}

bool CVersion::Init(const string& a_sVersionString)
{
	string::size_type uPos0 = 0;
	for (n32 i = 0; i < SDW_ARRAY_COUNT(m_nVersion); i++)
	{
		if (i == 1 || i == 2)
		{
			if (uPos0 != a_sVersionString.size())
			{
				if (a_sVersionString[uPos0] != '.')
				{
					return false;
				}
				uPos0++;
			}
		}
		if (i != 3)
		{
			string::size_type uPos1 = a_sVersionString.find_first_not_of("0123456789", uPos0);
			if (uPos1 != string::npos)
			{
				if (uPos1 == uPos0)
				{
					return false;
				}
				m_nVersion[i] = SToN32(a_sVersionString.substr(uPos0, uPos1 - uPos0));
				uPos0 = uPos1;
			}
			else
			{
				m_nVersion[i] = SToN32(a_sVersionString.substr(uPos0));
				uPos0 = a_sVersionString.size();
			}
		}
		else
		{
			string::size_type uPos1 = string::npos;
			if (uPos0 == a_sVersionString.size())
			{
				uPos1 = s_sVersionString.find('f');
				if (uPos1 == string::npos)
				{
					return false;
				}
			}
			else
			{
				uPos1 = s_sVersionString.find(a_sVersionString[uPos0]);
				if (uPos1 == string::npos)
				{
					return false;
				}
				uPos0++;
			}
			m_nVersion[i] = static_cast<n32>(uPos1);
			if (m_nVersion[i] == 4)
			{
				break;
			}
		}
	}
	return true;
}

n32 CVersion::Compare(const CVersion& a_Other) const
{
	for (n32 i = 0; i < SDW_ARRAY_COUNT(m_nVersion); i++)
	{
		if (m_nVersion[i] != a_Other.m_nVersion[i])
		{
			return m_nVersion[i] - a_Other.m_nVersion[i];
		}
	}
	return 0;
}
