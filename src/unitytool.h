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
		kParseOptionReturnUnknownArgument,
		kParseOptionReturnOptionConflict
	};
	enum EAction
	{
		kActionNone,
		kActionExtract,
		kActionCreate,
		kActionHelp
	};
	enum EFileType
	{
		kFileTypeUnknown,
		kFileTypeAssetBundle,
		kFileTypeAssets
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
	bool extractFile();
	bool createFile();
	EAction m_eAction;
	EFileType m_eFileType;
	UString m_sFileName;
	UString m_sDirName;
	UString m_sLuaFileName;
	UString m_sBackupFileName;
	bool m_bUnite;
	bool m_bSplit;
	bool m_bVerbose;
	UString m_sMessage;
};

#endif	// UNITYTOOL_H_
