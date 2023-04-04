#ifndef ASSETS_H_
#define ASSETS_H_

#include "stringstream.h"
#include "typetree.h"

class CAssets : public CStringStream
{
public:
	struct SAssetsHeader
	{
		n32 AssetsVersion;
		n64 MetadataSize;
		n64 FileSize;
		n64 DataOffset;
		bool LittleEndian;
		SAssetsHeader();
	};
	struct SFileEntry
	{
		n64 PathId;
		n64 Offset;
		u32 Size;
		n32 TypeIndex;
		n32 ClassIdV1;
		n32 ClassId;
		n16 ScriptIndex;
		bool IsStripped;
		bool IsDestroyed;
		n32 ClassIdV2;
		n64 DummySize;
		SFileEntry();
	};
	struct SFileEntryCompare
	{
	public:
		SFileEntryCompare(const vector<SFileEntry>& a_vFileEntry);
		bool operator()(const n32& a_nLhsIndex, const n32& a_nRhsIndex) const;
	private:
		const vector<SFileEntry>& m_vFileEntry;
	};
	struct SFileIdEntry
	{
		n32 FileId;
		n64 PathId;
		SFileIdEntry();
	};
	struct SExternalReference
	{
		string Unknown0x0;
		u32 Guid[4];
		u32 Type;
		string Path;
		SExternalReference();
	};
	CAssets();
	virtual ~CAssets();
	void SetFileSize(n64 a_nFileSize);
	void SetPathRes(const map<string, string>& a_mPathRes);
	void SetFileName(const UString& a_sFileName);
	void SetResFileName(const vector<UString>& a_vResFileName);
	void SetDirName(const UString& a_sDirName);
	void SetObjectFileName(const UString& a_sObjectFileName);
	void SetBackupFileName(const UString& a_sBackupFileName);
	void SetVerbose(bool a_bVerbose);
	bool ExtractFile();
	static bool IsAssetsFile(const UString& a_sFileName);
private:
	template<typename IStreamType>
	static bool readAssetsHeader(IStreamType& a_Stream, SAssetsHeader& a_AssetsHeader);
	static bool readTypeTreeNodeString(string& a_sDestString, u32 a_uStringOffset, const string& a_sTypeTreeRootString);
	bool readMetadata();
	bool readTypeTree(STypeTree& a_TypeTree);
	bool readTypeTreeRoot(STypeTreeRoot& a_TypeTreeRoot, n32 a_nRootIndex, bool a_bNotWriteIDHashForScriptType);
	bool readTypeTreeNodeV2(STypeTreeRoot& a_TypeTreeRoot, n32 a_nRootIndex);
	bool readTypeTreeNodeV1(STypeTreeRoot& a_TypeTreeRoot);
	bool readFileEntry();
	bool readFileIdEntry();
	bool readExternalReference();
	bool readContainer();
	bool mergeContainer(const map<n32, map<n64, string>>& a_mContainerFilePath);
	bool readName();
	static const string s_sCommonString;
	n64 m_nFileSize;
	map<string, string> m_mPathRes;
	UString m_sFileName;
	vector<UString> m_vResFileName;
	UString m_sDirName;
	UString m_sObjectFileName;
	UString m_sBackupFileName;
	bool m_bVerbose;
	SAssetsHeader m_AssetsHeader;
	n64 m_nDataOffsetMin;
	n64 m_nDataOffsetMax;
	STypeTree m_TypeTree;
	u32 m_uBigIDEnabled;
	n32 m_nFileEntryCount;
	vector<SFileEntry> m_vFileEntry;
	vector<n32> m_vFileIndexSortByOffset;
	n32 m_nFileIdEntryCount;
	vector<SFileIdEntry> m_vFileIdEntry;
	n32 m_nExternalReferenceCount;
	vector<SExternalReference> m_vExternalReference;
	STypeTree m_RefTypeTypeTree;
	string m_sUserInformation;
	map<n32, map<n64, string>> m_mContainerFilePath;
	vector<string> m_vFileEntryName;
	vector<string> m_vFileOutputName;
};

#endif	// ASSETS_H
