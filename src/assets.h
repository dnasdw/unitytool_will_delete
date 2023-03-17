#ifndef ASSETS_H_
#define ASSETS_H_

#include "stringstream.h"

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
};

#endif	// ASSETS_H
