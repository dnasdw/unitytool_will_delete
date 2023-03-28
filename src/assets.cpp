#include "assets.h"
#include "filestream.h"
#include "version.h"

const string CAssets::s_sCommonString = Replace<string>(
	/*        0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F  */ """"""""""""""""""
	/* 0000h: 41 41 42 42 00 41 6E 69 6D 61 74 69 6F 6E 43 6C */ "AABB.AnimationCl"
	/* 0010h: 69 70 00 41 6E 69 6D 61 74 69 6F 6E 43 75 72 76 */ "ip.AnimationCurv"
	/* 0020h: 65 00 41 6E 69 6D 61 74 69 6F 6E 53 74 61 74 65 */ "e.AnimationState"
	/* 0030h: 00 41 72 72 61 79 00 42 61 73 65 00 42 69 74 46 */ ".Array.Base.BitF"
	/* 0040h: 69 65 6C 64 00 62 69 74 73 65 74 00 62 6F 6F 6C */ "ield.bitset.bool"
	/* 0050h: 00 63 68 61 72 00 43 6F 6C 6F 72 52 47 42 41 00 */ ".char.ColorRGBA."
	/* 0060h: 43 6F 6D 70 6F 6E 65 6E 74 00 64 61 74 61 00 64 */ "Component.data.d"
	/* 0070h: 65 71 75 65 00 64 6F 75 62 6C 65 00 64 79 6E 61 */ "eque.double.dyna"
	/* 0080h: 6D 69 63 5F 61 72 72 61 79 00 46 61 73 74 50 72 */ "mic_array.FastPr"
	/* 0090h: 6F 70 65 72 74 79 4E 61 6D 65 00 66 69 72 73 74 */ "opertyName.first"
	/* 00A0h: 00 66 6C 6F 61 74 00 46 6F 6E 74 00 47 61 6D 65 */ ".float.Font.Game"
	/* 00B0h: 4F 62 6A 65 63 74 00 47 65 6E 65 72 69 63 20 4D */ "Object.Generic M"
	/* 00C0h: 6F 6E 6F 00 47 72 61 64 69 65 6E 74 4E 45 57 00 */ "ono.GradientNEW."
	/* 00D0h: 47 55 49 44 00 47 55 49 53 74 79 6C 65 00 69 6E */ "GUID.GUIStyle.in"
	/* 00E0h: 74 00 6C 69 73 74 00 6C 6F 6E 67 20 6C 6F 6E 67 */ "t.list.long long"
	/* 00F0h: 00 6D 61 70 00 4D 61 74 72 69 78 34 78 34 66 00 */ ".map.Matrix4x4f."
	/* 0100h: 4D 64 46 6F 75 72 00 4D 6F 6E 6F 42 65 68 61 76 */ "MdFour.MonoBehav"
	/* 0110h: 69 6F 75 72 00 4D 6F 6E 6F 53 63 72 69 70 74 00 */ "iour.MonoScript."
	/* 0120h: 6D 5F 42 79 74 65 53 69 7A 65 00 6D 5F 43 75 72 */ "m_ByteSize.m_Cur"
	/* 0130h: 76 65 00 6D 5F 45 64 69 74 6F 72 43 6C 61 73 73 */ "ve.m_EditorClass"
	/* 0140h: 49 64 65 6E 74 69 66 69 65 72 00 6D 5F 45 64 69 */ "Identifier.m_Edi"
	/* 0150h: 74 6F 72 48 69 64 65 46 6C 61 67 73 00 6D 5F 45 */ "torHideFlags.m_E"
	/* 0160h: 6E 61 62 6C 65 64 00 6D 5F 45 78 74 65 6E 73 69 */ "nabled.m_Extensi"
	/* 0170h: 6F 6E 50 74 72 00 6D 5F 47 61 6D 65 4F 62 6A 65 */ "onPtr.m_GameObje"
	/* 0180h: 63 74 00 6D 5F 49 6E 64 65 78 00 6D 5F 49 73 41 */ "ct.m_Index.m_IsA"
	/* 0190h: 72 72 61 79 00 6D 5F 49 73 53 74 61 74 69 63 00 */ "rray.m_IsStatic."
	/* 01A0h: 6D 5F 4D 65 74 61 46 6C 61 67 00 6D 5F 4E 61 6D */ "m_MetaFlag.m_Nam"
	/* 01B0h: 65 00 6D 5F 4F 62 6A 65 63 74 48 69 64 65 46 6C */ "e.m_ObjectHideFl"
	/* 01C0h: 61 67 73 00 6D 5F 50 72 65 66 61 62 49 6E 74 65 */ "ags.m_PrefabInte"
	/* 01D0h: 72 6E 61 6C 00 6D 5F 50 72 65 66 61 62 50 61 72 */ "rnal.m_PrefabPar"
	/* 01E0h: 65 6E 74 4F 62 6A 65 63 74 00 6D 5F 53 63 72 69 */ "entObject.m_Scri"
	/* 01F0h: 70 74 00 6D 5F 53 74 61 74 69 63 45 64 69 74 6F */ "pt.m_StaticEdito"
	/* 0200h: 72 46 6C 61 67 73 00 6D 5F 54 79 70 65 00 6D 5F */ "rFlags.m_Type.m_"
	/* 0210h: 56 65 72 73 69 6F 6E 00 4F 62 6A 65 63 74 00 70 */ "Version.Object.p"
	/* 0220h: 61 69 72 00 50 50 74 72 3C 43 6F 6D 70 6F 6E 65 */ "air.PPtr<Compone"
	/* 0230h: 6E 74 3E 00 50 50 74 72 3C 47 61 6D 65 4F 62 6A */ "nt>.PPtr<GameObj"
	/* 0240h: 65 63 74 3E 00 50 50 74 72 3C 4D 61 74 65 72 69 */ "ect>.PPtr<Materi"
	/* 0250h: 61 6C 3E 00 50 50 74 72 3C 4D 6F 6E 6F 42 65 68 */ "al>.PPtr<MonoBeh"
	/* 0260h: 61 76 69 6F 75 72 3E 00 50 50 74 72 3C 4D 6F 6E */ "aviour>.PPtr<Mon"
	/* 0270h: 6F 53 63 72 69 70 74 3E 00 50 50 74 72 3C 4F 62 */ "oScript>.PPtr<Ob"
	/* 0280h: 6A 65 63 74 3E 00 50 50 74 72 3C 50 72 65 66 61 */ "ject>.PPtr<Prefa"
	/* 0290h: 62 3E 00 50 50 74 72 3C 53 70 72 69 74 65 3E 00 */ "b>.PPtr<Sprite>."
	/* 02A0h: 50 50 74 72 3C 54 65 78 74 41 73 73 65 74 3E 00 */ "PPtr<TextAsset>."
	/* 02B0h: 50 50 74 72 3C 54 65 78 74 75 72 65 3E 00 50 50 */ "PPtr<Texture>.PP"
	/* 02C0h: 74 72 3C 54 65 78 74 75 72 65 32 44 3E 00 50 50 */ "tr<Texture2D>.PP"
	/* 02D0h: 74 72 3C 54 72 61 6E 73 66 6F 72 6D 3E 00 50 72 */ "tr<Transform>.Pr"
	/* 02E0h: 65 66 61 62 00 51 75 61 74 65 72 6E 69 6F 6E 66 */ "efab.Quaternionf"
	/* 02F0h: 00 52 65 63 74 66 00 52 65 63 74 49 6E 74 00 52 */ ".Rectf.RectInt.R"
	/* 0300h: 65 63 74 4F 66 66 73 65 74 00 73 65 63 6F 6E 64 */ "ectOffset.second"
	/* 0310h: 00 73 65 74 00 73 68 6F 72 74 00 73 69 7A 65 00 */ ".set.short.size."
	/* 0320h: 53 49 6E 74 31 36 00 53 49 6E 74 33 32 00 53 49 */ "SInt16.SInt32.SI"
	/* 0330h: 6E 74 36 34 00 53 49 6E 74 38 00 73 74 61 74 69 */ "nt64.SInt8.stati"
	/* 0340h: 63 76 65 63 74 6F 72 00 73 74 72 69 6E 67 00 54 */ "cvector.string.T"
	/* 0350h: 65 78 74 41 73 73 65 74 00 54 65 78 74 4D 65 73 */ "extAsset.TextMes"
	/* 0360h: 68 00 54 65 78 74 75 72 65 00 54 65 78 74 75 72 */ "h.Texture.Textur"
	/* 0370h: 65 32 44 00 54 72 61 6E 73 66 6F 72 6D 00 54 79 */ "e2D.Transform.Ty"
	/* 0380h: 70 65 6C 65 73 73 44 61 74 61 00 55 49 6E 74 31 */ "pelessData.UInt1"
	/* 0390h: 36 00 55 49 6E 74 33 32 00 55 49 6E 74 36 34 00 */ "6.UInt32.UInt64."
	/* 03A0h: 55 49 6E 74 38 00 75 6E 73 69 67 6E 65 64 20 69 */ "UInt8.unsigned i"
	/* 03B0h: 6E 74 00 75 6E 73 69 67 6E 65 64 20 6C 6F 6E 67 */ "nt.unsigned long"
	/* 03C0h: 20 6C 6F 6E 67 00 75 6E 73 69 67 6E 65 64 20 73 */ " long.unsigned s"
	/* 03D0h: 68 6F 72 74 00 76 65 63 74 6F 72 00 56 65 63 74 */ "hort.vector.Vect"
	/* 03E0h: 6F 72 32 66 00 56 65 63 74 6F 72 33 66 00 56 65 */ "or2f.Vector3f.Ve"
	/* 03F0h: 63 74 6F 72 34 66 00 6D 5F 53 63 72 69 70 74 69 */ "ctor4f.m_Scripti"
	/* 0400h: 6E 67 43 6C 61 73 73 49 64 65 6E 74 69 66 69 65 */ "ngClassIdentifie"
	/* 0410h: 72 00 47 72 61 64 69 65 6E 74 00 54 79 70 65 2A */ "r.Gradient.Type*"
	/* 0420h: 00 69 6E 74 32 5F 73 74 6F 72 61 67 65 00 69 6E */ ".int2_storage.in"
	/* 0430h: 74 33 5F 73 74 6F 72 61 67 65 00 42 6F 75 6E 64 */ "t3_storage.Bound"
	/* 0440h: 73 49 6E 74 00 6D 5F 43 6F 72 72 65 73 70 6F 6E */ "sInt.m_Correspon"
	/* 0450h: 64 69 6E 67 53 6F 75 72 63 65 4F 62 6A 65 63 74 */ "dingSourceObject"
	/* 0460h: 00 6D 5F 50 72 65 66 61 62 49 6E 73 74 61 6E 63 */ ".m_PrefabInstanc"
	/* 0470h: 65 00 6D 5F 50 72 65 66 61 62 41 73 73 65 74 00 */ "e.m_PrefabAsset."
	/* 0480h: 46 69 6C 65 53 69 7A 65 00 48 61 73 68 31 32 38 */ "FileSize.Hash128"
	/*        0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F  */ """"""""""""""""""
	, ".", string(1, '\0'));

CAssets::SAssetsHeader::SAssetsHeader()
	: AssetsVersion(0)
	, MetadataSize(0)
	, FileSize(0)
	, DataOffset(0)
	, LittleEndian(true)
{
}

CAssets::SFileEntry::SFileEntry()
	: PathId(0)
	, Offset(0)
	, Size(0)
	, TypeIndex(-1)
	, ClassIdV1(0)
	, ClassId(0)
	, ScriptIndex(-1)
	, IsStripped(false)
	, IsDestroyed(false)
	, ClassIdV2(-2)
	, DummySize(0)
{
}

CAssets::SFileEntryCompare::SFileEntryCompare(const vector<SFileEntry>& a_vFileEntry)
	: m_vFileEntry(a_vFileEntry)
{
}

bool CAssets::SFileEntryCompare::operator()(const n32& a_nLhsIndex, const n32& a_nRhsIndex) const
{
	return m_vFileEntry[a_nLhsIndex].Offset < m_vFileEntry[a_nRhsIndex].Offset;
}

CAssets::CAssets()
	: m_nFileSize(0)
	, m_bVerbose(false)
	, m_nDataOffsetMin(0)
	, m_nDataOffsetMax(0)
	, m_uBigIDEnabled(0)
	, m_nFileEntryCount(0)
{
	m_TypeTree.IsRefTypeTypeTree = false;
	m_RefTypeTypeTree.IsRefTypeTypeTree = true;
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
	if (!readMetadata())
	{
		return false;
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

bool CAssets::readTypeTreeNodeString(string& a_sDestString, u32 a_uStringOffset, const string& a_sTypeTreeRootString)
{
	const string* pString = &a_sTypeTreeRootString;
	if ((a_uStringOffset & 0x80000000) != 0)
	{
		a_uStringOffset &= INT32_MAX;
		pString = &s_sCommonString;
	}
	if (a_uStringOffset >= static_cast<u32>(pString->size()))
	{
		return false;
	}
	if (a_uStringOffset != 0 && pString->at(a_uStringOffset - 1) != 0)
	{
		return false;
	}
	a_sDestString = pString->c_str() + a_uStringOffset;
	return true;
}

bool CAssets::readMetadata()
{
	n64 nPosAfterAssetsHeader = 0;
	if (m_AssetsHeader.AssetsVersion >= 22)
	{
		nPosAfterAssetsHeader = 0x30;
	}
	else if (m_AssetsHeader.AssetsVersion >= 9)
	{
		nPosAfterAssetsHeader = 0x14;
	}
	else
	{
		nPosAfterAssetsHeader = m_nDataOffsetMin;
	}
	if (m_AssetsHeader.AssetsVersion >= 9)
	{
		if (!istringstream::seekg(static_cast<ptrdiff_t>(nPosAfterAssetsHeader)).good())
		{
			return false;
		}
	}
	else
	{
		if (!istringstream::seekg(static_cast<ptrdiff_t>(m_nDataOffsetMax + 1)).good())
		{
			return false;
		}
	}
	if (!readTypeTree(m_TypeTree))
	{
		return false;
	}
	if (m_AssetsHeader.AssetsVersion >= 7 && m_AssetsHeader.AssetsVersion < 14)
	{
		if (!CStream::ReadU32(m_uBigIDEnabled, m_AssetsHeader.LittleEndian).good())
		{
			return false;
		}
		if (m_uBigIDEnabled != 0)
		{
			return false;
		}
	}
	if (!readFileEntry())
	{
		return false;
	}
	// TODO
	//if (!readTypeTree(m_RefTypeTypeTree))
	//{
	//	return false;
	//}
	//if (!CStream::ReadString(m_sUserInformation).good())
	//{
	//	return false;
	//}
	// TODO
	return true;
}

bool CAssets::readTypeTree(STypeTree& a_TypeTree)
{
	if (!a_TypeTree.IsRefTypeTypeTree)
	{
		if (m_AssetsHeader.AssetsVersion >= 7)
		{
			if (!CStream::ReadString(a_TypeTree.Version).good())
			{
				return false;
			}
		}
		if (m_AssetsHeader.AssetsVersion >= 8)
		{
			if (!CStream::ReadN32(a_TypeTree.BuildTargetPlatform, m_AssetsHeader.LittleEndian).good())
			{
				return false;
			}
		}
		if (m_AssetsHeader.AssetsVersion >= 13)
		{
			u8 uHasTypeTree = 1;
			if (!CStream::ReadU8(uHasTypeTree).good())
			{
				return false;
			}
			a_TypeTree.HasTypeTree = uHasTypeTree != 0;
			if (uHasTypeTree != 0 && uHasTypeTree != 1)
			{
				return false;
			}
		}
	}
	if (!a_TypeTree.IsRefTypeTypeTree || m_AssetsHeader.AssetsVersion >= 20)
	{
		if (!CStream::ReadN32(a_TypeTree.TypeCount, m_AssetsHeader.LittleEndian).good())
		{
			return false;
		}
		if (a_TypeTree.TypeCount < 0)
		{
			return false;
		}
		if (a_TypeTree.TypeCount > 0)
		{
			a_TypeTree.Root.resize(a_TypeTree.TypeCount);
			bool bNotWriteIDHashForScriptType = false;
			if (!a_TypeTree.IsRefTypeTypeTree)
			{
				if (a_TypeTree.Version != "0.0.0")
				{
					CVersion writeIDHashForScriptTypeVersion;
					if (!writeIDHashForScriptTypeVersion.Init("2018.3.0a1"))
					{
						return false;
					}
					CVersion version;
					if (!version.Init(a_TypeTree.Version))
					{
						return false;
					}
					bNotWriteIDHashForScriptType = version.Compare(writeIDHashForScriptTypeVersion) < 0;
				}
			}
			for (n32 i = 0; i < a_TypeTree.TypeCount; i++)
			{
				STypeTreeRoot& root = a_TypeTree.Root[i];
				root.TypeTree = &a_TypeTree;
				if (!readTypeTreeRoot(root, i, bNotWriteIDHashForScriptType))
				{
					return false;
				}
				if (m_AssetsHeader.AssetsVersion < 16)
				{
					if (!a_TypeTree.ClassIdV1Index.insert(make_pair(root.ClassIdV1, i)).second)
					{
						return false;
					}
				}
			}
		}
	}
	return true;
}

bool CAssets::readTypeTreeRoot(STypeTreeRoot& a_TypeTreeRoot, n32 a_nRootIndex, bool a_bNotWriteIDHashForScriptType)
{
	if (m_AssetsHeader.AssetsVersion >= 16)
	{
		u8 uIsStripped = 0;
		if (!CStream::ReadN32(a_TypeTreeRoot.ClassIdV2, m_AssetsHeader.LittleEndian)
			.ReadU8(uIsStripped)
			.good())
		{
			return false;
		}
		a_TypeTreeRoot.IsStripped = uIsStripped != 0;
		if (uIsStripped != 0 && uIsStripped != 1)
		{
			return false;
		}
	}
	else
	{
		if (!CStream::ReadN32(a_TypeTreeRoot.ClassIdV1, m_AssetsHeader.LittleEndian).good())
		{
			return false;
		}
		if (a_TypeTreeRoot.ClassIdV1 >= 0)
		{
			a_TypeTreeRoot.ClassIdV2 = a_TypeTreeRoot.ClassIdV1;
		}
		else
		{
			a_TypeTreeRoot.ClassIdV2 = -1;
		}
	}
	if (m_AssetsHeader.AssetsVersion >= 17)
	{
		if (!CStream::ReadN16(a_TypeTreeRoot.ScriptIndex, m_AssetsHeader.LittleEndian).good())
		{
			return false;
		}
	}
	if (m_AssetsHeader.AssetsVersion >= 13)
	{
		bool bScript = a_TypeTreeRoot.ClassIdV2 == -1 || a_TypeTreeRoot.ClassIdV2 == 114;
		if (!a_bNotWriteIDHashForScriptType)
		{
			bScript = bScript || a_TypeTreeRoot.ScriptIndex >= 0;
		}
		if (bScript)
		{
			for (n32 i = 0; i < SDW_ARRAY_COUNT(a_TypeTreeRoot.ScriptId); i++)
			{
				if (!CStream::ReadU32(a_TypeTreeRoot.ScriptId[i], m_AssetsHeader.LittleEndian).good())
				{
					return false;
				}
			}
		}
		for (n32 i = 0; i < SDW_ARRAY_COUNT(a_TypeTreeRoot.OldTypeHash); i++)
		{
			if (!CStream::ReadU32(a_TypeTreeRoot.OldTypeHash[i], m_AssetsHeader.LittleEndian).good())
			{
				return false;
			}
		}
	}
	if (m_TypeTree.HasTypeTree)
	{
		if (m_AssetsHeader.AssetsVersion >= 12 || m_AssetsHeader.AssetsVersion == 10)
		{
			if (!readTypeTreeNodeV2(a_TypeTreeRoot, a_nRootIndex))
			{
				return false;
			}
		}
		else
		{
			if (!readTypeTreeNodeV1(a_TypeTreeRoot))
			{
				return false;
			}
		}
		if (!a_TypeTreeRoot.CreateTypeTree())
		{
			return false;
		}
	}
	return true;
}

bool CAssets::readTypeTreeNodeV2(STypeTreeRoot& a_TypeTreeRoot, n32 a_nRootIndex)
{
	if (!CStream::ReadN32(a_TypeTreeRoot.ChildCount, m_AssetsHeader.LittleEndian).good())
	{
		return false;
	}
	if (a_TypeTreeRoot.ChildCount < 0)
	{
		return false;
	}
	if (a_TypeTreeRoot.ChildCount > 0)
	{
		if (!CStream::ReadN32(a_TypeTreeRoot.StringSize, m_AssetsHeader.LittleEndian).good())
		{
			return false;
		}
		if (a_TypeTreeRoot.StringSize < 0)
		{
			return false;
		}
		for (n32 i = 0; i < a_TypeTreeRoot.ChildCount; i++)
		{
			STypeTreeNode& node = a_TypeTreeRoot.IndexedNode[i];
			if (!CStream::ReadU16(node.Version, m_AssetsHeader.LittleEndian)
				.ReadU8(node.Level)
				.ReadU8(node.Flags)
				.ReadU32(node.TypeStringOffset, m_AssetsHeader.LittleEndian)
				.ReadU32(node.NameStringOffset, m_AssetsHeader.LittleEndian)
				.ReadN32(node.Size, m_AssetsHeader.LittleEndian)
				.ReadN32(node.Index, m_AssetsHeader.LittleEndian)
				.ReadU32(node.MetaFlags, m_AssetsHeader.LittleEndian)
				.good())
			{
				return false;
			}
			if (i == 0)
			{
				if (node.Level != 0)
				{
					return false;
				}
			}
			else
			{
				if (node.Level == 0)
				{
					return false;
				}
			}
			if (node.Size < 0 && node.Size != -1)
			{
				return false;
			}
			if (node.Index != i)
			{
				return false;
			}
			if (m_AssetsHeader.AssetsVersion >= 18)
			{
				if (!CStream::ReadU64(node.Node18Unknown0x18, m_AssetsHeader.LittleEndian).good())
				{
					return false;
				}
			}
		}
		if (a_TypeTreeRoot.StringSize != 0)
		{
			a_TypeTreeRoot.String.resize(a_TypeTreeRoot.StringSize);
			if (!CStream::Read(&*a_TypeTreeRoot.String.begin(), a_TypeTreeRoot.StringSize).good())
			{
				return false;
			}
		}
		for (n32 i = 0; i < a_TypeTreeRoot.ChildCount; i++)
		{
			STypeTreeNode& node = a_TypeTreeRoot.IndexedNode[i];
			if (!readTypeTreeNodeString(node.Type, node.TypeStringOffset, a_TypeTreeRoot.String))
			{
				return false;
			}
			if (!readTypeTreeNodeString(node.Name, node.NameStringOffset, a_TypeTreeRoot.String))
			{
				return false;
			}
		}
		if (m_AssetsHeader.AssetsVersion >= 21)
		{
			STypeTree& typeTree = *a_TypeTreeRoot.TypeTree;
			if (!typeTree.IsRefTypeTypeTree)
			{
				if (!CStream::ReadN32(a_TypeTreeRoot.RefTypeCount, m_AssetsHeader.LittleEndian).good())
				{
					return false;
				}
				if (a_TypeTreeRoot.RefTypeCount < 0)
				{
					return false;
				}
				if (a_TypeTreeRoot.RefTypeCount > 0)
				{
					a_TypeTreeRoot.RefTypeIndex.resize(a_TypeTreeRoot.RefTypeCount);
					for (n32 i = 0; i < a_TypeTreeRoot.RefTypeCount; i++)
					{
						if (!CStream::ReadU32(a_TypeTreeRoot.RefTypeIndex[i], m_AssetsHeader.LittleEndian).good())
						{
							return false;
						}
					}
				}
			}
			else
			{
				if (!CStringStream::ReadString(a_TypeTreeRoot.ClassName)
					.ReadString(a_TypeTreeRoot.NamespaceName)
					.ReadString(a_TypeTreeRoot.AssemblyName)
					.good())
				{
					return false;
				}
				if (a_TypeTreeRoot.ClassName.empty())
				{
					return false;
				}
				if (a_TypeTreeRoot.AssemblyName.empty())
				{
					return false;
				}
				if (!typeTree.AssemblyNamespaceClassIndex[a_TypeTreeRoot.AssemblyName][a_TypeTreeRoot.NamespaceName].insert(make_pair(a_TypeTreeRoot.ClassName, a_nRootIndex)).second)
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool CAssets::readTypeTreeNodeV1(STypeTreeRoot& a_TypeTreeRoot)
{
	stack<u32> sLevel;
	sLevel.push(0);
	while (!sLevel.empty())
	{
		u32 uLevel = sLevel.top();
		sLevel.pop();
		if (uLevel > UINT8_MAX)
		{
			return false;
		}
		n32 nIndex = static_cast<n32>(a_TypeTreeRoot.IndexedNode.size());
		STypeTreeNode& node = a_TypeTreeRoot.IndexedNode[nIndex];
		node.Level = static_cast<u8>(uLevel);
		if (nIndex == 0)
		{
			if (node.Level != 0)
			{
				return false;
			}
		}
		else
		{
			if (node.Level == 0)
			{
				return false;
			}
		}
		if (!CStream::ReadString(node.Type)
			.ReadString(node.Name)
			.ReadN32(node.Size, m_AssetsHeader.LittleEndian)
			.good())
		{
			return false;
		}
		if (node.Size < 0 && node.Size != -1)
		{
			return false;
		}
		if (m_AssetsHeader.AssetsVersion == 2)
		{
			if (!CStream::ReadN32(node.Node2Unknown0x4, m_AssetsHeader.LittleEndian).good())
			{
				return false;
			}
		}
		if (m_AssetsHeader.AssetsVersion != 3)
		{
			if (!CStream::ReadN32(node.Index, m_AssetsHeader.LittleEndian).good())
			{
				return false;
			}
			if (node.Index != nIndex)
			{
				return false;
			}
		}
		else
		{
			node.Index = nIndex;
		}
		u32 uFlags = 0;
		u32 uVersion = 0;
		if (!CStream::ReadU32(uFlags, m_AssetsHeader.LittleEndian)
			.ReadU32(uVersion, m_AssetsHeader.LittleEndian)
			.good())
		{
			return false;
		}
		node.Flags = static_cast<u8>(uFlags);
		node.Version = static_cast<u16>(uVersion);
		if (uFlags > UINT8_MAX)
		{
			return false;
		}
		if (uVersion > UINT16_MAX)
		{
			return false;
		}
		if (m_AssetsHeader.AssetsVersion != 3)
		{
			if (!CStream::ReadU32(node.MetaFlags, m_AssetsHeader.LittleEndian).good())
			{
				return false;
			}
		}
		if (!CStream::ReadN32(node.ChildCount, m_AssetsHeader.LittleEndian).good())
		{
			return false;
		}
		if (node.ChildCount < 0)
		{
			return false;
		}
		for (n32 i = 0; i < node.ChildCount; i++)
		{
			sLevel.push(uLevel + 1);
		}
	}
	a_TypeTreeRoot.ChildCount = static_cast<n32>(a_TypeTreeRoot.IndexedNode.size());
	return true;
}

bool CAssets::readFileEntry()
{
	if (!CStream::ReadN32(m_nFileEntryCount, m_AssetsHeader.LittleEndian).good())
	{
		return false;
	}
	if (m_nFileEntryCount < 0)
	{
		return false;
	}
	if (m_nFileEntryCount > 0)
	{
		m_vFileEntry.resize(m_nFileEntryCount);
		m_vFileIndexSortByOffset.resize(m_nFileEntryCount);
		n64 nMetadataOffsetBegin = 0;
		if (m_AssetsHeader.AssetsVersion >= 22)
		{
			nMetadataOffsetBegin = 0x30;
		}
		else if (m_AssetsHeader.AssetsVersion >= 9)
		{
			nMetadataOffsetBegin = 0x14;
		}
		else
		{
			nMetadataOffsetBegin = m_nDataOffsetMax + 1;
		}
		for (n32 i = 0; i < m_nFileEntryCount; i++)
		{
			SFileEntry& fileEntry = m_vFileEntry[i];
			m_vFileIndexSortByOffset[i] = i;
			if (m_AssetsHeader.AssetsVersion >= 14)
			{
				n64 nMetadataOffsetCurrent = istringstream::tellg();
				n64 nMetadataOffset = nMetadataOffsetCurrent - nMetadataOffsetBegin;
				n32 nPaddingSize = static_cast<n32>(Align(nMetadataOffset, 4) - nMetadataOffset);
				if (!CStream::IsPaddingValid(nPaddingSize))
				{
					return false;
				}
				if (!CStream::ReadN64(fileEntry.PathId, m_AssetsHeader.LittleEndian).good())
				{
					return false;
				}
			}
			else
			{
				n32 nPathId = 0;
				if (!CStream::ReadN32(nPathId, m_AssetsHeader.LittleEndian).good())
				{
					return false;
				}
				fileEntry.PathId = nPathId;
			}
			if (m_AssetsHeader.AssetsVersion >= 22)
			{
				if (!CStream::ReadN64(fileEntry.Offset, m_AssetsHeader.LittleEndian).good())
				{
					return false;
				}
			}
			else
			{
				u32 uOffset = 0;
				if (!CStream::ReadU32(uOffset, m_AssetsHeader.LittleEndian).good())
				{
					return false;
				}
				fileEntry.Offset = uOffset;
			}
			fileEntry.Offset += m_AssetsHeader.DataOffset;
			if (fileEntry.Offset < m_nDataOffsetMin)
			{
				return false;
			}
			if (!CStream::ReadU32(fileEntry.Size, m_AssetsHeader.LittleEndian).good())
			{
				return false;
			}
			if (fileEntry.Offset + fileEntry.Size > m_nDataOffsetMax)
			{
				return false;
			}
			if (m_AssetsHeader.AssetsVersion >= 16)
			{
				if (!CStream::ReadN32(fileEntry.TypeIndex, m_AssetsHeader.LittleEndian).good())
				{
					return false;
				}
				if (fileEntry.TypeIndex < 0)
				{
					return false;
				}
				if (fileEntry.TypeIndex >= m_TypeTree.TypeCount)
				{
					return false;
				}
				fileEntry.ClassIdV2 = m_TypeTree.Root[fileEntry.TypeIndex].ClassIdV2;
				fileEntry.ClassId = fileEntry.ClassIdV2;
			}
			else
			{
				n16 nClassId = 0;
				if (!CStream::ReadN32(fileEntry.ClassIdV1, m_AssetsHeader.LittleEndian)
					.ReadN16(nClassId, m_AssetsHeader.LittleEndian)
					.good())
				{
					return false;
				}
				fileEntry.ClassId = nClassId;
				if (m_TypeTree.TypeCount != 0)
				{
					map<n32, n32>::const_iterator it = m_TypeTree.ClassIdV1Index.find(fileEntry.ClassIdV1);
					if (it == m_TypeTree.ClassIdV1Index.end())
					{
						return false;
					}
					fileEntry.TypeIndex = it->second;
					fileEntry.ClassIdV2 = m_TypeTree.Root[fileEntry.TypeIndex].ClassIdV2;
				}
			}
			if (m_AssetsHeader.AssetsVersion <= 10)
			{
				u16 uIsDestroyed = 0;
				if (!CStream::ReadU16(uIsDestroyed, m_AssetsHeader.LittleEndian).good())
				{
					return false;
				}
				fileEntry.IsDestroyed = uIsDestroyed != 0;
				if (uIsDestroyed != 0 && uIsDestroyed != 1)
				{
					return false;
				}
			}
			if (m_AssetsHeader.AssetsVersion >= 11 && m_AssetsHeader.AssetsVersion < 17)
			{
				if (!CStream::ReadN16(fileEntry.ScriptIndex, m_AssetsHeader.LittleEndian).good())
				{
					return false;
				}
			}
			if (m_AssetsHeader.AssetsVersion >= 15 && m_AssetsHeader.AssetsVersion < 17)
			{
				u8 uIsStripped = 0;
				if (!CStream::ReadU8(uIsStripped).good())
				{
					return false;
				}
				fileEntry.IsStripped = uIsStripped != 0;
				if (uIsStripped != 0 && uIsStripped != 1)
				{
					return false;
				}
			}
		}
		stable_sort(m_vFileIndexSortByOffset.begin(), m_vFileIndexSortByOffset.end(), SFileEntryCompare(m_vFileEntry));
		for (n32 i = 0; i < m_nFileEntryCount; i++)
		{
			const SFileEntry& fileEntry = m_vFileEntry[m_vFileIndexSortByOffset[i]];
			if (i == 0)
			{
				if (fileEntry.Offset != m_nDataOffsetMin)
				{
					return false;
				}
			}
			else
			{
				SFileEntry& prevFileEntry = m_vFileEntry[m_vFileIndexSortByOffset[i - 1]];
				n64 nDummyOffset = Align(prevFileEntry.Offset + prevFileEntry.Size, 8);
				if (fileEntry.Offset != nDummyOffset)
				{
					if (fileEntry.Offset < nDummyOffset)
					{
						return false;
					}
					prevFileEntry.DummySize = fileEntry.Offset - nDummyOffset;
					if (prevFileEntry.DummySize % 8 != 0)
					{
						return false;
					}
				}
			}
			if (i == m_nFileEntryCount - 1)
			{
				if (fileEntry.Offset + fileEntry.Size != m_nDataOffsetMax)
				{
					return false;
				}
			}
		}
	}
	return true;
}
