#include "assetbundle.h"
#include "filestream.h"

const string CAssetBundle::s_sSignatureUnityRaw = "UnityRaw";
const string CAssetBundle::s_sSignatureUnityWeb = "UnityWeb";
const string CAssetBundle::s_sSignatureUnityArchive = "UnityArchive";
const string CAssetBundle::s_sSignatureUnityFS = "UnityFS";
const n32 CAssetBundle::s_nAssetBundleVersionMin = 1;
const n32 CAssetBundle::s_nAssetBundleVersionMax = 8;

CAssetBundle::SSize::SSize()
	: Compressed(0)
	, Uncompressed(0)
{
}

CAssetBundle::SAssetBundleHeader::SAssetBundleHeader()
	: Offset(0)
	, AssetBundleVersion(0)
	, CRC(0)
	, MinimumStreamedBytes(0)
	, HeaderSize(0)
	, NumberOfLevelsToDownload(0)
	, BlockCount(0)
	, CompleteFileSize(0)
	, Flags(0)
{
	memset(Hash, 0, sizeof(Hash));
}

CAssetBundle::CAssetBundle()
	: m_bVerbose(false)
	, m_nFileSize(0)
	, m_bUnityFS(false)
{
}

CAssetBundle::~CAssetBundle()
{
}

void CAssetBundle::SetFileName(const UString& a_sFileName)
{
	m_sFileName = a_sFileName;
}

void CAssetBundle::SetDirName(const UString& a_sDirName)
{
	m_sDirName = a_sDirName;
}

void CAssetBundle::SetObjectFileName(const UString& a_sObjectFileName)
{
	m_sObjectFileName = a_sObjectFileName;
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
	FILE* fpAssetBundle = UFopen(m_sFileName, USTR("rb"));
	if (fpAssetBundle == nullptr)
	{
		return false;
	}
	Fseek(fpAssetBundle, 0, SEEK_END);
	m_nFileSize = Ftell(fpAssetBundle);
	if (m_nFileSize <= 0)
	{
		fclose(fpAssetBundle);
		return false;
	}
	if (!CStream::IsSizeSafe(m_nFileSize))
	{
		fclose(fpAssetBundle);
		return false;
	}
	Fseek(fpAssetBundle, 0, SEEK_SET);
	string sFileData;
	sFileData.resize(static_cast<string::size_type>(m_nFileSize));
	fread(&*sFileData.begin(), 1, static_cast<size_t>(m_nFileSize), fpAssetBundle);
	fclose(fpAssetBundle);
	istringstream::str(sFileData);
	sFileData.clear();
	ShrinkToFit(sFileData);
	if (!readAssetBundleHeader())
	{
		return false;
	}
	// TODO
	return true;
}

bool CAssetBundle::IsAssetBundleFile(const UString& a_sFileName)
{
	CFileStream fs(a_sFileName);
	if (!fs.good())
	{
		return false;
	}
	string sSignature;
	if (!fs.ReadString(sSignature).good())
	{
		return false;
	}
	return sSignature == s_sSignatureUnityFS
		|| sSignature == s_sSignatureUnityArchive
		|| sSignature == s_sSignatureUnityWeb
		|| sSignature == s_sSignatureUnityRaw;
}

bool CAssetBundle::readAssetBundleHeader()
{
	if (!CStream::ReadString(m_AssetBundleHeader.Signature).good())
	{
		return false;
	}
	if (m_AssetBundleHeader.Signature == s_sSignatureUnityFS)
	{
		m_bUnityFS = true;
	}
	else if (m_AssetBundleHeader.Signature == s_sSignatureUnityWeb)
	{
		if (!CStream::ReadN32(m_AssetBundleHeader.AssetBundleVersion, false).good())
		{
			return false;
		}
		m_bUnityFS = m_AssetBundleHeader.AssetBundleVersion == 6;
		if (!istringstream::seekg(-4, ios_base::cur).good())
		{
			return false;
		}
	}
	else
	{
		// unofficial
		if (m_AssetBundleHeader.Signature == s_sSignatureUnityRaw)
		{
			if (!CStream::ReadN32(m_AssetBundleHeader.AssetBundleVersion, false).good())
			{
				return false;
			}
			m_bUnityFS = m_AssetBundleHeader.AssetBundleVersion == 6;
			if (!istringstream::seekg(-4, ios_base::cur).good())
			{
				return false;
			}
		}
	}
	if (m_bUnityFS)
	{
		if (!CStream::ReadN32(m_AssetBundleHeader.AssetBundleVersion, false)
			.ReadString(m_AssetBundleHeader.UnityVersion)
			.ReadString(m_AssetBundleHeader.UnityRevision)
			.ReadN64(m_AssetBundleHeader.CompleteFileSize, false)
			.ReadU32(m_AssetBundleHeader.DataHeaderSize.Compressed, false)
			.ReadU32(m_AssetBundleHeader.DataHeaderSize.Uncompressed, false)
			.ReadU32(m_AssetBundleHeader.Flags, false)
			.good())
		{
			return false;
		}
		if (m_AssetBundleHeader.AssetBundleVersion < s_nAssetBundleVersionMin)
		{
			return false;
		}
		if (m_AssetBundleHeader.AssetBundleVersion > s_nAssetBundleVersionMax)
		{
			return false;
		}
		if (m_AssetBundleHeader.CompleteFileSize != m_nFileSize)
		{
			return false;
		}
		if (m_AssetBundleHeader.DataHeaderSize.Compressed == 0)
		{
			return false;
		}
		if (m_AssetBundleHeader.DataHeaderSize.Compressed >= m_AssetBundleHeader.CompleteFileSize)
		{
			return false;
		}
		if (m_AssetBundleHeader.DataHeaderSize.Uncompressed == 0)
		{
			return false;
		}
		if (!CStream::IsSizeSafe(m_AssetBundleHeader.DataHeaderSize.Uncompressed))
		{
			return false;
		}
		if ((m_AssetBundleHeader.Flags & ~0x3FF) != 0)
		{
			return false;
		}
		n32 nCompressionType = m_AssetBundleHeader.Flags & 0x3F;
		if (nCompressionType >= kCompressionTypeMax)
		{
			return false;
		}
		if (nCompressionType == kCompressionTypeNone)
		{
			if (m_AssetBundleHeader.DataHeaderSize.Uncompressed != m_AssetBundleHeader.DataHeaderSize.Compressed)
			{
				return false;
			}
		}
		if (nCompressionType == kCompressionTypeLz4 || nCompressionType == kCompressionTypeLz4HC)
		{
			if (m_AssetBundleHeader.DataHeaderSize.Compressed > INT32_MAX)
			{
				return false;
			}
			if (m_AssetBundleHeader.DataHeaderSize.Uncompressed > INT32_MAX)
			{
				return false;
			}
		}
		if (m_AssetBundleHeader.AssetBundleVersion >= 7)
		{
			n64 nPos = istringstream::tellg();
			n32 nSize = static_cast<n32>(Align(nPos, 16) - nPos);
			if (!CStream::IsPaddingValid(nSize))
			{
				return false;
			}
		}
	}
	else if (m_AssetBundleHeader.Signature == s_sSignatureUnityArchive)
	{
		if (!CStream::ReadN64(m_AssetBundleHeader.Offset, false).good())
		{
			return false;
		}
		n64 nPosAfterOffset = istringstream::tellg();
		if (m_AssetBundleHeader.Offset < nPosAfterOffset)
		{
			return false;
		}
		if (m_AssetBundleHeader.Offset >= m_nFileSize)
		{
			return false;
		}
		if (!istringstream::seekg(static_cast<ptrdiff_t>(m_AssetBundleHeader.Offset)).good())
		{
			return false;
		}
		if (!CStream::ReadN32(m_AssetBundleHeader.AssetBundleVersion, false).good())
		{
			return false;
		}
		if (m_AssetBundleHeader.AssetBundleVersion != 5)
		{
			return false;
		}
		if (!CStream::ReadString(m_AssetBundleHeader.UnityVersion)
			.ReadString(m_AssetBundleHeader.UnityRevision)
			.Read(m_AssetBundleHeader.Hash, sizeof(m_AssetBundleHeader.Hash))
			.ReadU32(m_AssetBundleHeader.CRC, false)
			.good())
		{
			return false;
		}
		// TODO: need samples
		return false;
	}
	else if (m_AssetBundleHeader.Signature == s_sSignatureUnityWeb || m_AssetBundleHeader.Signature == s_sSignatureUnityRaw)
	{
		if (!CStream::ReadN32(m_AssetBundleHeader.AssetBundleVersion, false)
			.ReadString(m_AssetBundleHeader.UnityVersion)
			.ReadString(m_AssetBundleHeader.UnityRevision)
			.good())
		{
			return false;
		}
		if (m_AssetBundleHeader.AssetBundleVersion < s_nAssetBundleVersionMin)
		{
			return false;
		}
		if (m_AssetBundleHeader.AssetBundleVersion > s_nAssetBundleVersionMax)
		{
			return false;
		}
		if (m_AssetBundleHeader.AssetBundleVersion > 3)
		{
			if (!CStream::Read(m_AssetBundleHeader.Hash, sizeof(m_AssetBundleHeader.Hash))
				.ReadU32(m_AssetBundleHeader.CRC, false)
				.good())
			{
				return false;
			}
		}
		if (!CStream::ReadU32(m_AssetBundleHeader.MinimumStreamedBytes, false)
			.ReadN32(m_AssetBundleHeader.HeaderSize, false)
			.ReadN32(m_AssetBundleHeader.NumberOfLevelsToDownload, false)
			.ReadN32(m_AssetBundleHeader.BlockCount, false)
			.good())
		{
			return false;
		}
		if (m_AssetBundleHeader.MinimumStreamedBytes == 0)
		{
			return false;
		}
		if (m_AssetBundleHeader.MinimumStreamedBytes > m_nFileSize)
		{
			return false;
		}
		if (m_AssetBundleHeader.MinimumStreamedBytes < m_nFileSize)
		{
			istringstream::pos_type pos = istringstream::tellg();
			if (!istringstream::seekg(m_AssetBundleHeader.MinimumStreamedBytes).good())
			{
				return false;
			}
			n64 nSize = m_nFileSize - m_AssetBundleHeader.MinimumStreamedBytes;
			if (!CStream::IsPaddingValid(static_cast<ptrdiff_t>(nSize)))
			{
				return false;
			}
			if (!istringstream::seekg(pos).good())
			{
				return false;
			}
		}
		if (m_AssetBundleHeader.HeaderSize <= 0)
		{
			return false;
		}
		if (m_AssetBundleHeader.NumberOfLevelsToDownload <= 0)
		{
			return false;
		}
		if (m_AssetBundleHeader.BlockCount <= 0)
		{
			return false;
		}
		n64 nAllBlockSize = 0;
		m_AssetBundleHeader.BlockSize.resize(m_AssetBundleHeader.BlockCount);
		for (n32 i = 0; i < m_AssetBundleHeader.BlockCount; i++)
		{
			if (!CStream::ReadU32(m_AssetBundleHeader.BlockSize[i].Compressed, false)
				.ReadU32(m_AssetBundleHeader.BlockSize[i].Uncompressed, false)
				.good())
			{
				return false;
			}
			if (m_AssetBundleHeader.BlockSize[i].Compressed == 0)
			{
				return false;
			}
			if (m_AssetBundleHeader.BlockSize[i].Compressed >= m_nFileSize)
			{
				return false;
			}
			if (m_AssetBundleHeader.BlockSize[i].Uncompressed == 0)
			{
				return false;
			}
			nAllBlockSize += m_AssetBundleHeader.BlockSize[i].Uncompressed;
			if (nAllBlockSize < 0)
			{
				return false;
			}
		}
		if (!CStream::IsSizeSafe(nAllBlockSize))
		{
			return false;
		}
		if (m_AssetBundleHeader.AssetBundleVersion >= 2)
		{
			u32 uCompleteFileSize = 0;
			if (!CStream::ReadU32(uCompleteFileSize, false).good())
			{
				return false;
			}
			m_AssetBundleHeader.CompleteFileSize = uCompleteFileSize;
			if (m_AssetBundleHeader.CompleteFileSize != m_nFileSize)
			{
				return false;
			}
		}
		else
		{
			m_AssetBundleHeader.CompleteFileSize = m_nFileSize;
		}
		if (m_AssetBundleHeader.AssetBundleVersion >= 3)
		{
			if (!CStream::ReadU32(m_AssetBundleHeader.DataHeaderSize.Uncompressed, false).good())
			{
				return false;
			}
		}
		n64 nPos = istringstream::tellg();
		if (nPos > m_AssetBundleHeader.HeaderSize)
		{
			return false;
		}
		n32 nSize = static_cast<n32>(m_AssetBundleHeader.HeaderSize - nPos);
		if (nSize >= 4)
		{
			return false;
		}
		if (!CStream::IsPaddingValid(nSize))
		{
			return false;
		}
	}
	return true;
}
