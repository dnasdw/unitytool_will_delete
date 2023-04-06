#ifndef UNITYTOOL_H_
#define UNITYTOOL_H_

#include <sdw.h>

class CUnityTool
{
public:
	enum EParseOptionReturn
	{
		kParseOptionReturnSuccess,
		kParseOptionReturnIllegalOption,
		kParseOptionReturnNoArgument,
		kParseOptionReturnOptionConflict
	};
	enum EAction
	{
		kActionNone,
		kActionExtract,
		kActionCreate,
		kActionGenerateScript,
		kActionSample,
		kActionHelp
	};
	enum EFileType
	{
		kFileTypeUnknown,
		kFileTypeAssetBundle,
		kFileTypeAssets,
	};
	struct SOption
	{
		const UChar* Name;
		int Key;
		const UChar* Doc;
	};
	CUnityTool();
	~CUnityTool();
	int ParseOptions(int a_nArgc, UChar* a_pArgv[]);
	int CheckOptions();
	int Help();
	int Action();
	static SOption s_Option[];
private:
	EParseOptionReturn parseOptions(const UChar* a_pName, int& a_nIndex, int a_nArgc, UChar* a_pArgv[]);
	EParseOptionReturn parseOptions(int a_nKey, int& a_nIndex, int a_nArgc, UChar* a_pArgv[]);
	bool checkFileType();
	bool extractFile();
	bool createFile();
	bool generateScriptFile();
	int sample();
	EAction m_eAction;
	UString m_sFileName;
	vector<UString> m_vResFileName;
	UString m_sDirName;
	UString m_sObjectFileName;
	UString m_sBackupFileName;
	bool m_bUnite;
	bool m_bSplit;
	bool m_bVerbose;
	bool m_bGenerateBat;
	UString m_sExePath;
	UString m_sExtractScriptFileName;
	UString m_sExtractSrcDirName;
	UString m_sExtractDestDirName;
	UString m_sCreateScriptFileName;
	UString m_sCreateSrcDirName;
	UString m_sCreateDestDirName;
	UString m_sPatternFileName;
	UString m_sMessage;
	EFileType m_eFileType;
};

#endif	// UNITYTOOL_H_
