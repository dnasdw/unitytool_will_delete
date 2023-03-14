#include "assetbundle.h"
#include <lzma457lib/lzma457lib.h>
#include "filestream.h"
#include "lz4.h"

const string CAssetBundle::s_sSignatureUnityRaw = "UnityRaw";
const string CAssetBundle::s_sSignatureUnityWeb = "UnityWeb";
const string CAssetBundle::s_sSignatureUnityArchive = "UnityArchive";
const string CAssetBundle::s_sSignatureUnityFS = "UnityFS";
const n32 CAssetBundle::s_nAssetBundleVersionMin = 1;
const n32 CAssetBundle::s_nAssetBundleVersionMax = 8;

CAssetBundle::SSize::SSize()
	: Uncompressed(0)
	, Compressed(0)
	, Flags(0)
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

CAssetBundle::SAssetsEntry::SAssetsEntry()
	: Offset(0)
	, Size(0)
	, Flags(0)
{
}

CAssetBundle::CAssetBundle()
	: m_bVerbose(false)
	, m_nFileSize(0)
	, m_bUnityFS(false)
	, m_nAssetsEntryCount(0)
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
	if (!readAssetsEntry())
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

bool CAssetBundle::readAssetsEntry()
{
	string sData;
	if (m_bUnityFS)
	{
		string sDataHeader;
		istringstream::pos_type posAfterAssetBundleHeader = istringstream::tellg();
		if ((m_AssetBundleHeader.Flags & 0x80) != 0)
		{
			if (!istringstream::seekg(static_cast<ptrdiff_t>(m_AssetBundleHeader.CompleteFileSize - m_AssetBundleHeader.DataHeaderSize.Compressed)).good())
			{
				return false;
			}
		}
		n32 nCompressionType = m_AssetBundleHeader.Flags & 0x3F;
		switch (nCompressionType)
		{
		case kCompressionTypeNone:
			{
				sDataHeader.resize(m_AssetBundleHeader.DataHeaderSize.Uncompressed);
				if (!CStream::Read(&*sDataHeader.begin(), m_AssetBundleHeader.DataHeaderSize.Uncompressed).good())
				{
					return false;
				}
			}
			break;
		case kCompressionTypeLzma:
			{
				string sCompressedData;
				sCompressedData.resize(m_AssetBundleHeader.DataHeaderSize.Compressed);
				if (!CStream::Read(&*sCompressedData.begin(), m_AssetBundleHeader.DataHeaderSize.Compressed).good())
				{
					return false;
				}
				if (!CLzma457::Uncompress(sCompressedData, sDataHeader))
				{
					return false;
				}
				if (sDataHeader.size() != m_AssetBundleHeader.DataHeaderSize.Uncompressed)
				{
					return false;
				}
			}
			break;
		case kCompressionTypeLz4:
		case kCompressionTypeLz4HC:
			{
				sDataHeader.resize(m_AssetBundleHeader.DataHeaderSize.Uncompressed);
				string sCompressedData;
				sCompressedData.resize(m_AssetBundleHeader.DataHeaderSize.Compressed);
				if (!CStream::Read(&*sCompressedData.begin(), m_AssetBundleHeader.DataHeaderSize.Compressed).good())
				{
					return false;
				}
				n32 nUncompressedDataSize = m_AssetBundleHeader.DataHeaderSize.Uncompressed;
				if (!CLz4::Uncompress(&*sCompressedData.begin(), m_AssetBundleHeader.DataHeaderSize.Compressed, &*sDataHeader.begin(), nUncompressedDataSize))
				{
					return false;
				}
				if (nUncompressedDataSize != m_AssetBundleHeader.DataHeaderSize.Uncompressed)
				{
					return false;
				}
			}
			break;
		}
		if ((m_AssetBundleHeader.Flags & 0x80) != 0)
		{
			if (static_cast<n64>(istringstream::tellg()) != m_AssetBundleHeader.CompleteFileSize)
			{
				return false;
			}
			if (!istringstream::seekg(posAfterAssetBundleHeader).good())
			{
				return false;
			}
		}
		if ((m_AssetBundleHeader.Flags & 0x200) != 0)
		{
			n64 nPos = istringstream::tellg();
			n32 nSize = static_cast<n32>(Align(nPos, 16) - nPos);
			if (!CStream::IsPaddingValid(nSize))
			{
				return false;
			}
		}
		CStringStream dataHeader(sDataHeader);
		sDataHeader.clear();
		ShrinkToFit(sDataHeader);
		if (!dataHeader.Read(m_AssetBundleHeader.Hash, sizeof(m_AssetBundleHeader.Hash))
			.ReadN32(m_AssetBundleHeader.BlockCount, false)
			.good())
		{
			return false;
		}
		if (m_AssetBundleHeader.BlockCount <= 0)
		{
			return false;
		}
		string::size_type uAllBlockPos = 0;
		n64 nAllBlockSize = 0;
		m_AssetBundleHeader.BlockSize.resize(m_AssetBundleHeader.BlockCount);
		for (n32 i = 0; i < m_AssetBundleHeader.BlockCount; i++)
		{
			u16 uFlags = 0;
			if (!dataHeader.ReadU32(m_AssetBundleHeader.BlockSize[i].Uncompressed, false)
				.ReadU32(m_AssetBundleHeader.BlockSize[i].Compressed, false)
				.ReadU16(uFlags, false)
				.good())
			{
				return false;
			}
			m_AssetBundleHeader.BlockSize[i].Flags = uFlags;
			if (m_AssetBundleHeader.BlockSize[i].Uncompressed == 0)
			{
				return false;
			}
			if (m_AssetBundleHeader.BlockSize[i].Compressed == 0)
			{
				return false;
			}
			if (m_AssetBundleHeader.BlockSize[i].Compressed >= m_AssetBundleHeader.CompleteFileSize)
			{
				return false;
			}
			if ((m_AssetBundleHeader.BlockSize[i].Flags & ~0x7F) != 0)
			{
				return false;
			}
			nCompressionType = m_AssetBundleHeader.BlockSize[i].Flags & 0x3F;
			if (nCompressionType >= kCompressionTypeMax)
			{
				return false;
			}
			if (nCompressionType == kCompressionTypeLz4 || nCompressionType == kCompressionTypeLz4HC)
			{
				if (m_AssetBundleHeader.BlockSize[i].Uncompressed > INT32_MAX)
				{
					return false;
				}
				if (m_AssetBundleHeader.BlockSize[i].Compressed > INT32_MAX)
				{
					return false;
				}
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
		m_nAssetsEntryCount = 0;
		if (!dataHeader.ReadN32(m_nAssetsEntryCount, false).good())
		{
			return false;
		}
		if (m_nAssetsEntryCount <= 0)
		{
			return false;
		}
		m_vAssetsEntry.resize(m_nAssetsEntryCount);
		for (n32 i = 0; i < m_nAssetsEntryCount; i++)
		{
			SAssetsEntry& assetsEntry = m_vAssetsEntry[i];
			if (!dataHeader.ReadN64(assetsEntry.Offset, false)
				.ReadN64(assetsEntry.Size, false)
				.ReadU32(assetsEntry.Flags, false)
				.ReadString(assetsEntry.Name)
				.good())
			{
				return false;
			}
			if (assetsEntry.Offset < 0)
			{
				return false;
			}
			if (assetsEntry.Offset >= nAllBlockSize)
			{
				return false;
			}
			if (assetsEntry.Size <= 0)
			{
				return false;
			}
			if (assetsEntry.Size > nAllBlockSize)
			{
				return false;
			}
			if ((assetsEntry.Flags & kArchiveNodeFlagsError) != 0)
			{
				return false;
			}
			if (assetsEntry.Flags != kArchiveNodeFlagsNone
				&& assetsEntry.Flags != kArchiveNodeFlagsDirectory
				&& assetsEntry.Flags != kArchiveNodeFlagsDeleted
				&& assetsEntry.Flags != kArchiveNodeFlagsSerializedFile)
			{
				return false;
			}
			if ((assetsEntry.Flags & kArchiveNodeFlagsDirectory) != 0)
			{
				// TODO: need samples
				return false;
			}
			if ((assetsEntry.Flags & kArchiveNodeFlagsDeleted) != 0)
			{
				// TODO: need samples
				return false;
			}
		}
		sData.reserve(static_cast<string::size_type>(nAllBlockSize));
		for (n32 i = 0; i < m_AssetBundleHeader.BlockCount; i++)
		{
			u32 uUncompressedSize = m_AssetBundleHeader.BlockSize[i].Uncompressed;
			u32 uCompressedSize = m_AssetBundleHeader.BlockSize[i].Compressed;
			nCompressionType = m_AssetBundleHeader.BlockSize[i].Flags & 0x3F;
			switch (nCompressionType)
			{
			case kCompressionTypeNone:
				{
					sData.resize(uAllBlockPos + uUncompressedSize);
					if (!CStream::Read(&*sData.begin() + uAllBlockPos, uUncompressedSize).good())
					{
						return false;
					}
				}
				break;
			case kCompressionTypeLzma:
				{
					string sCompressedData;
					sCompressedData.resize(uCompressedSize + 8);
					if (!CStream::Read(&*sCompressedData.begin(), 5)
						.Read(&*sCompressedData.begin() + 13, uCompressedSize - 5)
						.good())
					{
						return false;
					}
					for (n32 j = 0; j < 4; j++)
					{
						sCompressedData[5 + j] = uUncompressedSize >> (j * 8) & 0xFF;
					}
					for (n32 j = 0; j < 4; j++)
					{
						sCompressedData[9 + j] = 0;
					}
					if (!CLzma457::Uncompress(sCompressedData, sData))
					{
						return false;
					}
					if (sData.size() != uAllBlockPos + uUncompressedSize)
					{
						return false;
					}
				}
				break;
			case kCompressionTypeLz4:
			case kCompressionTypeLz4HC:
				{
					sData.resize(uAllBlockPos + uUncompressedSize);
					string sCompressedData;
					sCompressedData.resize(uCompressedSize);
					if (!CStream::Read(&*sCompressedData.begin(), uCompressedSize).good())
					{
						return false;
					}
					n32 nUncompressedDataSize = uUncompressedSize;
					if (!CLz4::Uncompress(&*sCompressedData.begin(), uCompressedSize, &*sData.begin() + uAllBlockPos, nUncompressedDataSize))
					{
						return false;
					}
					if (nUncompressedDataSize != uUncompressedSize)
					{
						return false;
					}
				}
				break;
			}
			uAllBlockPos += uUncompressedSize;
		}
		if (uAllBlockPos != nAllBlockSize)
		{
			return false;
		}
		n64 nPosAfterData = istringstream::tellg();
		if ((m_AssetBundleHeader.Flags & 0x80) != 0)
		{
			if (nPosAfterData + m_AssetBundleHeader.DataHeaderSize.Compressed != m_AssetBundleHeader.CompleteFileSize)
			{
				return false;
			}
		}
		else
		{
			if (nPosAfterData != m_AssetBundleHeader.CompleteFileSize)
			{
				return false;
			}
		}
		istringstream::str(sData);
		sData.clear();
		ShrinkToFit(sData);
		if (static_cast<n64>(dataHeader.tellg()) != m_AssetBundleHeader.DataHeaderSize.Uncompressed)
		{
			return false;
		}
	}
	else if (m_AssetBundleHeader.Signature == s_sSignatureUnityArchive)
	{
		// TODO: need samples
		return false;
	}
	else if (m_AssetBundleHeader.Signature == s_sSignatureUnityWeb || m_AssetBundleHeader.Signature == s_sSignatureUnityRaw)
	{
		string::size_type uAllBlockPos = 0;
		n64 nAllBlockSize = 0;
		for (n32 i = 0; i < m_AssetBundleHeader.BlockCount; i++)
		{
			nAllBlockSize += m_AssetBundleHeader.BlockSize[i].Uncompressed;
		}
		sData.reserve(static_cast<string::size_type>(nAllBlockSize));
		if (m_AssetBundleHeader.Signature == s_sSignatureUnityWeb)
		{
			for (n32 i = 0; i < m_AssetBundleHeader.BlockCount; i++)
			{
				u32 uCompressedSize = m_AssetBundleHeader.BlockSize[i].Compressed;
				u32 uUncompressedSize = m_AssetBundleHeader.BlockSize[i].Uncompressed;
				string sCompressedData;
				sCompressedData.resize(uCompressedSize);
				if (!CStream::Read(&*sCompressedData.begin(), uCompressedSize).good())
				{
					return false;
				}
				if (!CLzma457::Uncompress(sCompressedData, sData))
				{
					return false;
				}
				if (sData.size() != uAllBlockPos + uUncompressedSize)
				{
					return false;
				}
				uAllBlockPos += uUncompressedSize;
			}
		}
		else
		{
			sData.resize(static_cast<string::size_type>(nAllBlockSize));
			for (n32 i = 0; i < m_AssetBundleHeader.BlockCount; i++)
			{
				u32 uUncompressedSize = m_AssetBundleHeader.BlockSize[i].Uncompressed;
				if (!CStream::Read(&*sData.begin() + uAllBlockPos, uUncompressedSize).good())
				{
					return false;
				}
				uAllBlockPos += uUncompressedSize;
			}
		}
		if (uAllBlockPos != nAllBlockSize)
		{
			return false;
		}
		istringstream::str(sData);
		sData.clear();
		ShrinkToFit(sData);
		n32 nAssetsEntryCount = 0;
		if (!CStream::ReadN32(nAssetsEntryCount, false).good())
		{
			return false;
		}
		if (nAssetsEntryCount <= 0)
		{
			return false;
		}
		m_vAssetsEntry.resize(nAssetsEntryCount);
		for (n32 i = 0; i < nAssetsEntryCount; i++)
		{
			SAssetsEntry& assetsEntry = m_vAssetsEntry[i];
			u32 uAssetsEntryOffset = 0;
			u32 uAssetsEntrySize = 0;
			if (!CStream::ReadString(assetsEntry.Name)
				.ReadU32(uAssetsEntryOffset, false)
				.ReadU32(uAssetsEntrySize, false)
				.good())
			{
				return false;
			}
			assetsEntry.Offset = uAssetsEntryOffset;
			assetsEntry.Size = uAssetsEntrySize;
			if (i == 0)
			{
				if (m_AssetBundleHeader.AssetBundleVersion >= 3)
				{
					if (assetsEntry.Offset != m_AssetBundleHeader.DataHeaderSize.Uncompressed)
					{
						return false;
					}
				}
				else
				{
					m_AssetBundleHeader.DataHeaderSize.Uncompressed = static_cast<u32>(assetsEntry.Offset);
				}
			}
			if (assetsEntry.Offset < m_AssetBundleHeader.DataHeaderSize.Uncompressed)
			{
				return false;
			}
			if (assetsEntry.Offset >= nAllBlockSize)
			{
				return false;
			}
			if (assetsEntry.Size == 0)
			{
				return false;
			}
			if (assetsEntry.Size > nAllBlockSize)
			{
				return false;
			}
		}
		n64 nPos = istringstream::tellg();
		if (nPos > m_AssetBundleHeader.DataHeaderSize.Uncompressed)
		{
			return false;
		}
		u32 uSize = static_cast<u32>(m_AssetBundleHeader.DataHeaderSize.Uncompressed - nPos);
		if (uSize >= 4)
		{
			return false;
		}
		if (!CStream::IsPaddingValid(uSize))
		{
			return false;
		}
	}
	return true;
}
