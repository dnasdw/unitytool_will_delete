#include "assetbundle.h"

CAssetBundle::CAssetBundle()
	: m_bVerbose(false)
	, m_fpAssetBundle(nullptr)
	, m_uAssetBundleOffset(0)
{
	memset(&m_AssetBundleHeader, 0, sizeof(SAssetBundleHeader));
}

CAssetBundle::~CAssetBundle()
{
	if (m_fpAssetBundle != nullptr)
	{
		fclose(m_fpAssetBundle);
		m_fpAssetBundle = nullptr;
	}
}

void CAssetBundle::SetFileName(const UString& a_sFileName)
{
	m_sFileName = a_sFileName;
}

void CAssetBundle::SetDirName(const UString& a_sDirName)
{
	m_sDirName = a_sDirName;
}

void CAssetBundle::SetLuaFileName(const UString& a_sLuaFileName)
{
	m_sLuaFileName = a_sLuaFileName;
}

void CAssetBundle::SetBackupFileName(const UString& a_sBackupFileName)
{
	m_sBackupFileName = a_sBackupFileName;
}

void CAssetBundle::SetVerbose(bool a_bVerbose)
{
	m_bVerbose = a_bVerbose;
}

bool CAssetBundle::ExtractFile()
{
	bool bResult = true;
	m_fpAssetBundle = UFopen(m_sFileName.c_str(), USTR("rb"));
	if (m_fpAssetBundle == nullptr)
	{
		return false;
	}
	Fseek(m_fpAssetBundle, 0, SEEK_END);
	u32 uAssetBundleSize = static_cast<u32>(Ftell(m_fpAssetBundle));
	Fseek(m_fpAssetBundle, 0, SEEK_SET);
	u8* pTemp = new u8[uAssetBundleSize];
	if (pTemp == nullptr)
	{
		fclose(m_fpAssetBundle);
		m_fpAssetBundle = nullptr;
		return false;
	}
	fread(pTemp, 1, uAssetBundleSize, m_fpAssetBundle);
	fclose(m_fpAssetBundle);
	m_fpAssetBundle = nullptr;
	m_vAssetBundle.assign(pTemp, pTemp + uAssetBundleSize);
	delete[] pTemp;
	if (!readAssetBundleHeader())
	{
		return false;
	}
	return bResult;
}

bool CAssetBundle::readAssetBundleHeader()
{
	if (!readString(m_AssetBundleHeader.Signature))
	{
		return false;
	}
	if (!readU32(m_AssetBundleHeader.Unknown1, false))
	{
		return false;
	}
	if (m_AssetBundleHeader.Unknown1 != 3)
	{
		return false;
	}
	if (!readString(m_AssetBundleHeader.Version1))
	{
		return false;
	}
	if (!readString(m_AssetBundleHeader.Version2))
	{
		return false;
	}
	if (!readU32(m_AssetBundleHeader.FileSize1, false))
	{
		return false;
	}
	if (m_AssetBundleHeader.FileSize1 != static_cast<u32>(m_vAssetBundle.size()))
	{
		return false;
	}
	if (!readU32(m_AssetBundleHeader.DataOffset, false))
	{
		return false;
	}
	if (m_AssetBundleHeader.DataOffset > m_AssetBundleHeader.FileSize1)
	{
		return false;
	}
	if (m_AssetBundleHeader.DataOffset % 4 != 0)
	{
		return false;
	}
	if (!readU32(m_AssetBundleHeader.Unknown6, false))
	{
		return false;
	}
	if (m_AssetBundleHeader.Unknown6 != 1)
	{
		return false;
	}
	if (!readU32(m_AssetBundleHeader.Unknown7, false))
	{
		return false;
	}
	if (m_AssetBundleHeader.Unknown7 != 1)
	{
		return false;
	}
	if (!readU32(m_AssetBundleHeader.CompressedSize, false))
	{
		return false;
	}
	if (m_AssetBundleHeader.DataOffset + m_AssetBundleHeader.CompressedSize != m_AssetBundleHeader.FileSize1)
	{
		return false;
	}
	if (!readU32(m_AssetBundleHeader.UncompressedSize, false))
	{
		return false;
	}
	if (!readU32(m_AssetBundleHeader.FileSize2, false))
	{
		return false;
	}
	if (m_AssetBundleHeader.FileSize2 != m_AssetBundleHeader.FileSize1)
	{
		return false;
	}
	if (!readU32(m_AssetBundleHeader.AssetsOffset, false))
	{
		return false;
	}
	if (m_AssetBundleHeader.AssetsOffset > m_AssetBundleHeader.UncompressedSize)
	{
		return false;
	}
	if (m_uAssetBundleOffset > m_AssetBundleHeader.DataOffset)
	{
		return false;
	}
	if (m_uAssetBundleOffset < m_AssetBundleHeader.DataOffset)
	{
		if (m_AssetBundleHeader.DataOffset != static_cast<u32>(Align(m_uAssetBundleOffset, 4)))
		{
			return false;
		}
		for (u32 i = m_uAssetBundleOffset; i < m_AssetBundleHeader.DataOffset; i++)
		{
			if (m_vAssetBundle[i] != 0)
			{
				return false;
			}
		}
	}
	return true;
}

bool CAssetBundle::readU32(u32& a_uValue, bool a_bLittleEndian /* = true */)
{
	if (m_uAssetBundleOffset + 4 > static_cast<u32>(m_vAssetBundle.size()))
	{
		return false;
	}
	a_uValue = *reinterpret_cast<u32*>(&*m_vAssetBundle.begin() + m_uAssetBundleOffset);
	m_uAssetBundleOffset += 4;
	if (!a_bLittleEndian)
	{
		a_uValue = SDW_CONVERT_ENDIAN32(a_uValue);
	}
	return true;
}

bool CAssetBundle::readString(string& a_sValue)
{
	if (m_uAssetBundleOffset + strlen(reinterpret_cast<char*>(&m_vAssetBundle.begin() + m_uAssetBundleOffset)) > static_cast<u32>(m_vAssetBundle.size()))
	{
		return false;
	}
	a_sValue = reinterpret_cast<char*>(&*m_vAssetBundle.begin() + m_uAssetBundleOffset);
	m_uAssetBundleOffset += a_sValue.size() + 1;
	return true;
}
