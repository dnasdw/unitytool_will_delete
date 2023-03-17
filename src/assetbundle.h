#ifndef ASSETBUNDLE_H_
#define ASSETBUNDLE_H_

#include "stringstream.h"

class CAssetBundle : public CStringStream
{
public:
	enum EArchiveNodeFlags
	{
		kArchiveNodeFlagsNone = 0,
		kArchiveNodeFlagsDirectory = 1 << 0,
		kArchiveNodeFlagsDeleted = 1 << 1,
		kArchiveNodeFlagsSerializedFile = 1 << 2,
		kArchiveNodeFlagsError = 0xFFFFFFF8
	};
	enum ECompressionType
	{
		kCompressionTypeNone,
		kCompressionTypeLzma,
		kCompressionTypeLz4,
		kCompressionTypeLz4HC,
		kCompressionTypeMax
	};
	struct SSize
	{
		u32 Uncompressed;
		u32 Compressed;
		u32 Flags;
		SSize();
	};
	struct SAssetBundleHeader
	{
		string Signature;
		n64 Offset;
		n32 AssetBundleVersion;
		string UnityVersion;
		string UnityRevision;
		u8 Hash[16];
		u32 CRC;
		u32 MinimumStreamedBytes;
		n32 HeaderSize;
		n32 NumberOfLevelsToDownload;
		n32 BlockCount;
		vector<SSize> BlockSize;
		n64 CompleteFileSize;
		SSize DataHeaderSize;
		u32 Flags;
		SAssetBundleHeader();
	};
	struct SAssetsEntry
	{
		n64 Offset;
		n64 Size;
		u32 Flags;
		string Name;
		SAssetsEntry();
	};
	CAssetBundle();
	virtual ~CAssetBundle();
	void SetFileName(const UString& a_sFileName);
	void SetDirName(const UString& a_sDirName);
	void SetObjectFileName(const UString& a_sObjectFileName);
	void SetBackupFileName(const UString& a_sBackupFileName);
	void SetVerbose(bool a_bVerbose);
	bool ExtractFile();
	static bool IsAssetBundleFile(const UString& a_sFileName);
	static const string s_sSignatureUnityRaw;
	static const string s_sSignatureUnityWeb;
	static const string s_sSignatureUnityArchive;
	static const string s_sSignatureUnityFS;
	static const n32 s_nAssetBundleVersionMin;
	static const n32 s_nAssetBundleVersionMax;
private:
	bool readAssetBundleHeader();
	bool readAssetsEntry();
	bool extractAssetsEntry();
	UString m_sFileName;
	UString m_sDirName;
	UString m_sObjectFileName;
	UString m_sBackupFileName;
	bool m_bVerbose;
	n64 m_nFileSize;
	SAssetBundleHeader m_AssetBundleHeader;
	bool m_bUnityFS;
	n32 m_nAssetsEntryCount;
	vector<SAssetsEntry> m_vAssetsEntry;
};

#endif	// ASSETBUNDLE_H_
