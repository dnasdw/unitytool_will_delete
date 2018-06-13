#ifndef ASSETBUNDLE_H_
#define ASSETBUNDLE_H_

#include <sdw.h>

class CAssetBundle
{
public:
	struct SAssetBundleHeader
	{
		string Signature;
		u32 Unknown1;
		string Version1;
		string Version2;
		u32 FileSize1;
		u32 DataOffset;
		u32 Unknown6;
		u32 Unknown7;
		u32 CompressedSize;
		u32 UncompressedSize;
		u32 FileSize2;
		u32 AssetsOffset;
	};
	CAssetBundle();
	~CAssetBundle();
	void SetFileName(const UString& a_sFileName);
	void SetDirName(const UString& a_sDirName);
	void SetLuaFileName(const UString& a_sLuaFileName);
	void SetBackupFileName(const UString& a_sBackupFileName);
	void SetVerbose(bool a_bVerbose);
	bool ExtractFile();
private:
	bool readAssetBundleHeader();
	bool readU32(u32& a_uValue, bool a_bLittleEndian = true);
	bool readString(string& a_sValue);
	UString m_sFileName;
	UString m_sDirName;
	UString m_sLuaFileName;
	UString m_sBackupFileName;
	bool m_bVerbose;
	FILE* m_fpAssetBundle;
	vector<u8> m_vAssetBundle;
	u32 m_uAssetBundleOffset;
	SAssetBundleHeader m_AssetBundleHeader;
};

#endif	// ASSETBUNDLE_H_
