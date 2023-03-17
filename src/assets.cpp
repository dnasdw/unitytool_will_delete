#include "assets.h"
#include "filestream.h"

CAssets::SAssetsHeader::SAssetsHeader()
	: AssetsVersion(0)
	, MetadataSize(0)
	, FileSize(0)
	, DataOffset(0)
	, LittleEndian(true)
{
}

CAssets::CAssets()
	: m_nFileSize(0)
	, m_bVerbose(false)
	, m_nDataOffsetMin(0)
	, m_nDataOffsetMax(0)
{
}

CAssets::~CAssets()
{
}

void CAssets::SetFileSize(n64 a_nFileSize)
{
	m_nFileSize = a_nFileSize;
}

void CAssets::SetPathRes(const map<string, string>& a_mPathRes)
{
	m_mPathRes.clear();
	m_mPathRes.insert(a_mPathRes.begin(), a_mPathRes.end());
}

void CAssets::SetFileName(const UString& a_sFileName)
{
	m_sFileName = a_sFileName;
}

void CAssets::SetResFileName(const vector<UString>& a_vResFileName)
{
	m_vResFileName.assign(a_vResFileName.begin(), a_vResFileName.end());
}

void CAssets::SetDirName(const UString& a_sDirName)
{
	m_sDirName = a_sDirName;
}

void CAssets::SetObjectFileName(const UString& a_sObjectFileName)
{
	m_sObjectFileName = a_sObjectFileName;
}

void CAssets::SetBackupFileName(const UString& a_sBackupFileName)
{
	m_sBackupFileName = a_sBackupFileName;
}

void CAssets::SetVerbose(bool a_bVerbose)
{
	m_bVerbose = a_bVerbose;
}

bool CAssets::ExtractFile()
{
	if (m_nFileSize == 0)
	{
		FILE* fpAssets = UFopen(m_sFileName, USTR("rb"));
		if (fpAssets == nullptr)
		{
			return false;
		}
		Fseek(fpAssets, 0, SEEK_END);
		m_nFileSize = Ftell(fpAssets);
		if (m_nFileSize <= 0)
		{
			fclose(fpAssets);
			return false;
		}
		if (!CStream::IsSizeSafe(m_nFileSize))
		{
			fclose(fpAssets);
			return false;
		}
		Fseek(fpAssets, 0, SEEK_SET);
		string sFileData;
		sFileData.resize(static_cast<string::size_type>(m_nFileSize));
		fread(&*sFileData.begin(), 1, static_cast<size_t>(m_nFileSize), fpAssets);
		fclose(fpAssets);
		istringstream::str(sFileData);
		sFileData.clear();
		ShrinkToFit(sFileData);
		for (vector<UString>::const_iterator it = m_vResFileName.begin(); it != m_vResFileName.end(); ++it)
		{
			const UString& sResFileName = *it;
			string sPath = UToU8(sResFileName);
			string::size_type uPos = sPath.find_last_of("/\\");
			if (uPos != string::npos)
			{
				sPath.erase(0, uPos + 1);
			}
			FILE* fpAssetsRes = UFopen(sResFileName, USTR("rb"));
			if (fpAssetsRes == nullptr)
			{
				return false;
			}
			Fseek(fpAssetsRes, 0, SEEK_END);
			n64 nResFileSize = Ftell(fpAssetsRes);
			if (nResFileSize < 0)
			{
				fclose(fpAssetsRes);
				return false;
			}
			if (nResFileSize != 0)
			{
				if (!CStream::IsSizeSafe(nResFileSize))
				{
					fclose(fpAssetsRes);
					return false;
				}
				Fseek(fpAssetsRes, 0, SEEK_SET);
				sFileData.resize(static_cast<string::size_type>(nResFileSize));
				fread(&*sFileData.begin(), 1, static_cast<size_t>(nResFileSize), fpAssetsRes);
			}
			fclose(fpAssetsRes);
			map<string, string>::const_iterator itPathRes = m_mPathRes.find(sPath);
			if (itPathRes != m_mPathRes.end())
			{
				return false;
			}
			m_mPathRes[sPath].swap(sFileData);
		}
	}
	if (!readAssetsHeader(*this, m_AssetsHeader))
	{
		return false;
	}
	if (m_AssetsHeader.AssetsVersion >= 9)
	{
		m_nDataOffsetMin = m_AssetsHeader.DataOffset;
		m_nDataOffsetMax = m_AssetsHeader.FileSize;
	}
	else
	{
		m_nDataOffsetMin = 0x10;
		m_nDataOffsetMax = m_AssetsHeader.FileSize - m_AssetsHeader.MetadataSize;
		if (m_nDataOffsetMax < m_nDataOffsetMin)
		{
			return false;
		}
	}
	// TODO
	return true;
}

bool CAssets::IsAssetsFile(const UString& a_sFileName)
{
	CFileStream fs(a_sFileName);
	if (!fs.good())
	{
		return false;
	}
	SAssetsHeader assetsHeader;
	if (!readAssetsHeader(fs, assetsHeader))
	{
		return false;
	}
	return true;
}

template<typename IStreamType>
bool CAssets::readAssetsHeader(IStreamType& a_Stream, SAssetsHeader& a_AssetsHeader)
{
	if (!a_Stream.seekg(0, ios_base::end).good())
	{
		return false;
	}
	n64 nFileSize = a_Stream.tellg();
	if (nFileSize <= 0)
	{
		return false;
	}
	if (!CStream::IsSizeSafe(nFileSize))
	{
		return false;
	}
	if (!a_Stream.seekg(0).good())
	{
		return false;
	}
	u32 uMetadataSize = 0;
	u32 uFileSize = 0;
	u32 uDataOffset = 0;
	if (!a_Stream.ReadU32(uMetadataSize, false)
		.ReadU32(uFileSize, false)
		.ReadN32(a_AssetsHeader.AssetsVersion, false)
		.ReadU32(uDataOffset, false)
		.good())
	{
		return false;
	}
	a_AssetsHeader.MetadataSize = uMetadataSize;
	a_AssetsHeader.FileSize = uFileSize;
	a_AssetsHeader.DataOffset = uDataOffset;
	if (a_AssetsHeader.AssetsVersion < 2)
	{
		return false;
	}
	if (a_AssetsHeader.AssetsVersion > 22)
	{
		return false;
	}
	u8 uBigEndian = 0;
	if (a_AssetsHeader.AssetsVersion >= 22)
	{
		if (a_AssetsHeader.MetadataSize != 0)
		{
			return false;
		}
		if (a_AssetsHeader.FileSize != 0)
		{
			return false;
		}
		if (a_AssetsHeader.DataOffset != 0)
		{
			return false;
		}
		if (!a_Stream.ReadN64(a_AssetsHeader.MetadataSize, false)
			.ReadN64(a_AssetsHeader.FileSize, false)
			.ReadN64(a_AssetsHeader.DataOffset, false)
			.IsPaddingValid(8))
		{
			return false;
		}
	}
	else
	{
		if (a_AssetsHeader.AssetsVersion >= 9)
		{
			if (!a_Stream.ReadU8(uBigEndian)
				.IsPaddingValid(3))
			{
				return false;
			}
		}
		else
		{
			typename IStreamType::pos_type posAfterAssetsHeader = a_Stream.tellg();
			if (!a_Stream.seekg(static_cast<ptrdiff_t>(a_AssetsHeader.FileSize - a_AssetsHeader.MetadataSize)).good())
			{
				return false;
			}
			if (!a_Stream.ReadU8(uBigEndian).good())
			{
				return false;
			}
			if (!a_Stream.seekg(posAfterAssetsHeader).good())
			{
				return false;
			}
		}
	}
	a_AssetsHeader.LittleEndian = uBigEndian == 0;
	if (a_AssetsHeader.FileSize != nFileSize)
	{
		return false;
	}
	if (a_AssetsHeader.MetadataSize <= 0)
	{
		return false;
	}
	if (a_AssetsHeader.MetadataSize >= a_AssetsHeader.FileSize)
	{
		return false;
	}
	if (a_AssetsHeader.DataOffset < 0)
	{
		return false;
	}
	if (a_AssetsHeader.DataOffset >= a_AssetsHeader.FileSize)
	{
		return false;
	}
	if (uBigEndian != 0 && uBigEndian != 1)
	{
		return false;
	}
	return true;
}
