#include "unitytool.h"

CUnityTool::SOption CUnityTool::s_Option[] =
{
	{ USTR("extract"), USTR('x'), USTR("extract the target file") },
	{ USTR("create"), USTR('c'), USTR("create the target file") },
	{ USTR("file"), USTR('f'), USTR("the target file") },
	{ USTR("res"), 0, USTR("the resource/resS file of the target file") },
	{ USTR("dir"), USTR('d'), USTR("the dir for the target file") },
	{ USTR("object"), USTR('o'), USTR("the metadata file for the target file") },
	{ USTR("backup"), USTR('b'), USTR("the backup binary file for the target file") },
	{ USTR("unite"), 0, USTR("unite from the .splitN files") },
	{ USTR("split"), 0, USTR("split to the .splitN files") },
	{ USTR("verbose"), USTR('v'), USTR("show the info") },
	{ USTR("sample"), 0, USTR("show the samples") },
	{ USTR("help"), USTR('h'), USTR("show this help") },
	{ nullptr, 0, nullptr }
};

CUnityTool::CUnityTool()
	: m_eAction(kActionNone)
	, m_bUnite(false)
	, m_bSplit(false)
	, m_bVerbose(false)
{
}

CUnityTool::~CUnityTool()
{
}

int CUnityTool::ParseOptions(int a_nArgc, UChar* a_pArgv[])
{
	if (a_nArgc <= 1)
	{
		return 1;
	}
	for (int i = 1; i < a_nArgc; i++)
	{
		int nArgpc = static_cast<int>(UCslen(a_pArgv[i]));
		if (nArgpc == 0)
		{
			continue;
		}
		int nIndex = i;
		if (a_pArgv[i][0] != USTR('-'))
		{
			UPrintf(USTR("ERROR: illegal option\n\n"));
			return 1;
		}
		else if (nArgpc > 1 && a_pArgv[i][1] != USTR('-'))
		{
			for (int j = 1; j < nArgpc; j++)
			{
				switch (parseOptions(a_pArgv[i][j], nIndex, a_nArgc, a_pArgv))
				{
				case kParseOptionReturnSuccess:
					break;
				case kParseOptionReturnIllegalOption:
					UPrintf(USTR("ERROR: illegal option\n\n"));
					return 1;
				case kParseOptionReturnNoArgument:
					UPrintf(USTR("ERROR: no argument\n\n"));
					return 1;
				case kParseOptionReturnOptionConflict:
					UPrintf(USTR("ERROR: option conflict\n\n"));
					return 1;
				}
			}
		}
		else if (nArgpc > 2 && a_pArgv[i][1] == USTR('-'))
		{
			switch (parseOptions(a_pArgv[i] + 2, nIndex, a_nArgc, a_pArgv))
			{
			case kParseOptionReturnSuccess:
				break;
			case kParseOptionReturnIllegalOption:
				UPrintf(USTR("ERROR: illegal option\n\n"));
				return 1;
			case kParseOptionReturnNoArgument:
				UPrintf(USTR("ERROR: no argument\n\n"));
				return 1;
			case kParseOptionReturnOptionConflict:
				UPrintf(USTR("ERROR: option conflict\n\n"));
				return 1;
			}
		}
		i = nIndex;
	}
	return 0;
}

int CUnityTool::CheckOptions()
{
	if (m_eAction == kActionNone)
	{
		UPrintf(USTR("ERROR: nothing to do\n\n"));
		return 1;
	}
	if (m_eAction != kActionSample && m_eAction != kActionHelp)
	{
		if (m_sFileName.empty())
		{
			UPrintf(USTR("ERROR: no --file option\n\n"));
			return 1;
		}
		if (m_sDirName.empty())
		{
			UPrintf(USTR("ERROR: no --dir option\n\n"));
			return 1;
		}
		if (m_sObjectFileName.empty())
		{
			UPrintf(USTR("ERROR: no --object option\n\n"));
			return 1;
		}
		if (m_sBackupFileName.empty())
		{
			UPrintf(USTR("ERROR: no --backup option\n\n"));
			return 1;
		}
	}
	return 0;
}

int CUnityTool::Help()
{
	UPrintf(USTR("unitytool %") PRIUS USTR(" by dnasdw\n\n"), AToU(UNITYTOOL_VERSION).c_str());
	UPrintf(USTR("usage: unitytool [option...] [option]...\n\n"));
	UPrintf(USTR("option:\n"));
	SOption* pOption = s_Option;
	while (pOption->Name != nullptr || pOption->Doc != nullptr)
	{
		if (pOption->Name != nullptr)
		{
			UPrintf(USTR("  "));
			if (pOption->Key != 0)
			{
				UPrintf(USTR("-%c,"), pOption->Key);
			}
			else
			{
				UPrintf(USTR("   "));
			}
			UPrintf(USTR(" --%-8") PRIUS, pOption->Name);
			if (UCslen(pOption->Name) >= 8 && pOption->Doc != nullptr)
			{
				UPrintf(USTR("\n%16") PRIUS, USTR(""));
			}
		}
		if (pOption->Doc != nullptr)
		{
			UPrintf(USTR("%") PRIUS, pOption->Doc);
		}
		UPrintf(USTR("\n"));
		pOption++;
	}
	return 0;
}

int CUnityTool::Action()
{
	if (m_eAction == kActionExtract)
	{
		if (!extractFile())
		{
			UPrintf(USTR("ERROR: extract file failed\n\n"));
			return 1;
		}
	}
	if (m_eAction == kActionCreate)
	{
		if (!createFile())
		{
			UPrintf(USTR("ERROR: create file failed\n\n"));
			return 1;
		}
	}
	if (m_eAction == kActionSample)
	{
		return sample();
	}
	if (m_eAction == kActionHelp)
	{
		return Help();
	}
	return 0;
}

CUnityTool::EParseOptionReturn CUnityTool::parseOptions(const UChar* a_pName, int& a_nIndex, int a_nArgc, UChar* a_pArgv[])
{
	if (UCscmp(a_pName, USTR("extract")) == 0)
	{
		if (m_eAction == kActionNone)
		{
			m_eAction = kActionExtract;
		}
		else if (m_eAction != kActionExtract && m_eAction != kActionHelp)
		{
			return kParseOptionReturnOptionConflict;
		}
	}
	else if (UCscmp(a_pName, USTR("create")) == 0)
	{
		if (m_eAction == kActionNone)
		{
			m_eAction = kActionCreate;
		}
		else if (m_eAction != kActionCreate && m_eAction != kActionHelp)
		{
			return kParseOptionReturnOptionConflict;
		}
	}
	else if (UCscmp(a_pName, USTR("file")) == 0)
	{
		if (a_nIndex + 1 >= a_nArgc)
		{
			return kParseOptionReturnNoArgument;
		}
		m_sFileName = a_pArgv[++a_nIndex];
	}
	else if (UCscmp(a_pName, USTR("res")) == 0)
	{
		if (a_nIndex + 1 >= a_nArgc)
		{
			return kParseOptionReturnNoArgument;
		}
		m_vResFileName.push_back(a_pArgv[++a_nIndex]);
	}
	else if (UCscmp(a_pName, USTR("dir")) == 0)
	{
		if (a_nIndex + 1 >= a_nArgc)
		{
			return kParseOptionReturnNoArgument;
		}
		m_sDirName = a_pArgv[++a_nIndex];
	}
	else if (UCscmp(a_pName, USTR("object")) == 0)
	{
		if (a_nIndex + 1 >= a_nArgc)
		{
			return kParseOptionReturnNoArgument;
		}
		m_sObjectFileName = a_pArgv[++a_nIndex];
	}
	else if (UCscmp(a_pName, USTR("backup")) == 0)
	{
		if (a_nIndex + 1 >= a_nArgc)
		{
			return kParseOptionReturnNoArgument;
		}
		m_sBackupFileName = a_pArgv[++a_nIndex];
	}
	else if (UCscmp(a_pName, USTR("unite")) == 0)
	{
		m_bUnite = true;
	}
	else if (UCscmp(a_pName, USTR("split")) == 0)
	{
		m_bSplit = true;
	}
	else if (UCscmp(a_pName, USTR("verbose")) == 0)
	{
		m_bVerbose = true;
	}
	else if (UCscmp(a_pName, USTR("sample")) == 0)
	{
		if (m_eAction == kActionNone)
		{
			m_eAction = kActionSample;
		}
		else if (m_eAction != kActionSample && m_eAction != kActionHelp)
		{
			return kParseOptionReturnOptionConflict;
		}
	}
	else if (UCscmp(a_pName, USTR("help")) == 0)
	{
		m_eAction = kActionHelp;
	}
	return kParseOptionReturnSuccess;
}

CUnityTool::EParseOptionReturn CUnityTool::parseOptions(int a_nKey, int& a_nIndex, int a_nArgc, UChar* a_pArgv[])
{
	for (SOption* pOption = s_Option; pOption->Name != nullptr || pOption->Key != 0 || pOption->Doc != nullptr; pOption++)
	{
		if (pOption->Key == a_nKey)
		{
			return parseOptions(pOption->Name, a_nIndex, a_nArgc, a_pArgv);
		}
	}
	return kParseOptionReturnIllegalOption;
}

bool CUnityTool::extractFile()
{
	bool bResult = false;
	if (m_bUnite)
	{
		FILE* fpTarget = nullptr;
		for (n32 i = 0; true; i++)
		{
			UString sSplitFileName = Format(USTR("%") PRIUS USTR(".split%d"), m_sFileName.c_str(), i);
			FILE* fpSplit = UFopen(sSplitFileName, USTR("rb"), false);
			if (fpSplit == nullptr)
			{
				break;
			}
			Fseek(fpSplit, 0, SEEK_END);
			n64 nSplitSize = Ftell(fpSplit);
			if (fpTarget == nullptr)
			{
				fpTarget = UFopen(m_sFileName, USTR("wb"));
				if (fpTarget == nullptr)
				{
					fclose(fpSplit);
					return false;
				}
			}
			CopyFile(fpTarget, fpSplit, 0, nSplitSize);
			fclose(fpSplit);
		}
		if (fpTarget != nullptr)
		{
			fclose(fpTarget);
		}
	}
	// TODO
	return bResult;
}

bool CUnityTool::createFile()
{
	bool bResult = false;
	// TODO
	if (m_bSplit)
	{
		FILE* fpTarget = UFopen(m_sFileName, USTR("rb"));
		if (fpTarget == nullptr)
		{
			return false;
		}
		Fseek(fpTarget, 0, SEEK_END);
		n64 nAssetsSize = Ftell(fpTarget);
		const n64 nSplitSize = 0x100000;
		n32 nSplitCount = static_cast<n32>(Align(nAssetsSize, nSplitSize) / nSplitSize);
		for (n32 i = 0; i < nSplitCount; i++)
		{
			UString sSplitFileName = Format(USTR("%") PRIUS USTR(".split%d"), m_sFileName.c_str(), i);
			FILE* fpSplit = UFopen(sSplitFileName, USTR("wb"));
			if (fpSplit == nullptr)
			{
				fclose(fpTarget);
				return false;
			}
			n64 nSize = min<n64>(nSplitSize, nAssetsSize - i * nSplitSize);
			CopyFile(fpSplit, fpTarget, i * nSplitSize, nSize);
			fclose(fpSplit);
		}
		fclose(fpTarget);
	}
	return bResult;
}

int CUnityTool::sample()
{
	UPrintf(USTR("sample:\n"));
	return 0;
}

int UMain(int argc, UChar* argv[])
{
	CUnityTool tool;
	if (tool.ParseOptions(argc, argv) != 0)
	{
		return tool.Help();
	}
	if (tool.CheckOptions() != 0)
	{
		return 1;
	}
	return tool.Action();
}
