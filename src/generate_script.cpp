#include "generate_script.h"
#include "name.h"

CGenerateScript::CGenerateScript()
	: m_bVerbose(false)
	, m_bGenerateBat(true)
{
}

CGenerateScript::~CGenerateScript()
{
}

void CGenerateScript::SetVerbose(bool a_bVerbose)
{
	m_bVerbose = a_bVerbose;
}

void CGenerateScript::SetGenerateBat(bool a_bGenerateBat)
{
	m_bGenerateBat = a_bGenerateBat;
}

void CGenerateScript::SetExePath(const UString& a_sExePath)
{
	m_sExePath = UToU8(a_sExePath);
}

void CGenerateScript::SetExtractScriptFileName(const UString& a_sExtractScriptFileName)
{
	m_sExtractScriptFileName = a_sExtractScriptFileName;
}

void CGenerateScript::SetExtractSrcDirName(const UString& a_sExtractSrcDirName)
{
	m_sExtractSrcDirName = UToU8(a_sExtractSrcDirName);
}

void CGenerateScript::SetExtractDestDirName(const UString& a_sExtractDestDirName)
{
	m_sExtractDestDirName = UToU8(a_sExtractDestDirName);
}

void CGenerateScript::SetCreateScriptFileName(const UString& a_sCreateScriptFileName)
{
	m_sCreateScriptFileName = a_sCreateScriptFileName;
}

void CGenerateScript::SetCreateSrcDirName(const UString& a_sCreateSrcDirName)
{
	m_sCreateSrcDirName = UToU8(a_sCreateSrcDirName);
}

void CGenerateScript::SetCreateDestDirName(const UString& a_sCreateDestDirName)
{
	m_sCreateDestDirName = UToU8(a_sCreateDestDirName);
}

void CGenerateScript::SetPatternFileName(const UString& a_sPatternFileName)
{
	m_sPatternFileName = a_sPatternFileName;
}

bool CGenerateScript::GenerateScript()
{
	if (!buildPatternList())
	{
		return false;
	}
	if (!buildFileNameList())
	{
		return false;
	}
	if (!outputScript())
	{
		return false;
	}
	return true;
}

bool CGenerateScript::buildPatternList()
{
	m_vPatternList.clear();
	FILE* fp = UFopen(m_sPatternFileName, USTR("rb"));
	if (fp == nullptr)
	{
		return false;
	}
	Fseek(fp, 0, SEEK_END);
	u32 uSize = static_cast<u32>(Ftell(fp));
	Fseek(fp, 0, SEEK_SET);
	char* pTxt = new char[uSize + 1];
	fread(pTxt, 1, uSize, fp);
	fclose(fp);
	pTxt[uSize] = '\0';
	u32 uPos = 0;
	if (uSize >= 3 && memcmp(pTxt, "\xEF\xBB\xBF", 3) == 0)
	{
		uPos = 3;
	}
	string sTxt(pTxt + uPos);
	delete[] pTxt;
	bool bResult = true;
	vector<string> vTxt = SplitOf(sTxt, "\r\n");
	for (vector<string>::const_iterator it = vTxt.begin(); it != vTxt.end(); ++it)
	{
		sTxt = Trim(*it);
		if (!sTxt.empty() && !StartWith(sTxt, "//"))
		{
			try
			{
				URegex rPattern(U8ToU(sTxt), regex_constants::ECMAScript | regex_constants::icase);
				m_vPatternList.push_back(rPattern);
			}
			catch (regex_error& e)
			{
				UPrintf(USTR("ERROR: %") PRIUS USTR("\n\n"), AToU(e.what()).c_str());
				bResult = false;
			}
		}
	}
	return bResult;
}

bool CGenerateScript::matchInPatternList(const UString& a_sPath) const
{
	bool bMatch = false;
	for (vector<URegex>::const_iterator it = m_vPatternList.begin(); it != m_vPatternList.end(); ++it)
	{
		if (regex_search(a_sPath, *it))
		{
			bMatch = true;
			break;
		}
	}
	return bMatch;
}

bool CGenerateScript::buildFileNameList()
{
	vector<UString> vFileName;
	vector<UString> vDir;
	queue<vector<UString>> qPath;
	qPath.push(vDir);
	queue<UString> qDir;
	qDir.push(U8ToU(m_sExtractSrcDirName));
	while (!qDir.empty())
	{
		UString& sParent = qDir.front();
		vDir = qPath.front();
#if SDW_PLATFORM == SDW_PLATFORM_WINDOWS
		WIN32_FIND_DATAW ffd;
		HANDLE hFind = INVALID_HANDLE_VALUE;
		wstring sPattern = sParent + L"/*";
		hFind = FindFirstFileW(sPattern.c_str(), &ffd);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			do
			{
				if ((ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
				{
					UString sFileName;
					for (vector<UString>::iterator it = vDir.begin(); it != vDir.end(); ++it)
					{
						sFileName += L"/" + *it;
					}
					sFileName += L"/";
					sFileName += ffd.cFileName;
					sFileName.erase(0, 1);
					if (matchInPatternList(sFileName))
					{
						vFileName.push_back(sFileName);
					}
					else
					{
						UString::size_type uPos = sFileName.rfind(USTR("."));
						if (uPos != UString::npos)
						{
							if (EndWith(sFileName, USTR(".resource")) || EndWith(sFileName, USTR(".resS")))
							{
								m_mResFileName[UToU8(sFileName.substr(0, uPos))].push_back(UToU8(sFileName));
							}
						}
					}
				}
				else if ((ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0 && wcscmp(ffd.cFileName, L".") != 0 && wcscmp(ffd.cFileName, L"..") != 0)
				{
					vDir.push_back(ffd.cFileName);
					qPath.push(vDir);
					vDir.pop_back();
					wstring sDir = sParent + L"/" + ffd.cFileName;
					qDir.push(sDir);
				}
			} while (FindNextFileW(hFind, &ffd) != 0);
			FindClose(hFind);
		}
#else
		DIR* pDir = opendir(sParent.c_str());
		if (pDir != nullptr)
		{
			dirent* pDirent = nullptr;
			while ((pDirent = readdir(pDir)) != nullptr)
			{
				string sName = pDirent->d_name;
#if SDW_PLATFORM == SDW_PLATFORM_MACOS
				sName = TSToS<string, string>(sName, "UTF-8-MAC", "UTF-8");
#endif
				// handle cases where d_type is DT_UNKNOWN
				if (pDirent->d_type == DT_UNKNOWN)
				{
					string sPath = sParent + "/" + sName;
					Stat st;
					if (UStat(sPath.c_str(), &st) == 0)
					{
						if (S_ISREG(st.st_mode))
						{
							pDirent->d_type = DT_REG;
						}
						else if (S_ISDIR(st.st_mode))
						{
							pDirent->d_type = DT_DIR;
						}
					}
				}
				if (pDirent->d_type == DT_REG)
				{
					UString sFileName;
					for (vector<UString>::iterator it = vDir.begin(); it != vDir.end(); ++it)
					{
						sFileName += "/" + *it;
					}
					sFileName += "/";
					sFileName += sName;
					sFileName.erase(0, 1);
					if (matchInPatternList(sFileName))
					{
						vFileName.push_back(sFileName);
					}
					else
					{
						UString::size_type uPos = sFileName.rfind(USTR("."));
						if (uPos != UString::npos)
						{
							if (EndWith(sFileName, USTR(".resource")) || EndWith(sFileName, USTR(".resS")))
							{
								m_mResFileName[UToU8(sFileName.substr(0, uPos))].push_back(UToU8(sFileName));
							}
						}
					}
				}
				else if (pDirent->d_type == DT_DIR && strcmp(pDirent->d_name, ".") != 0 && strcmp(pDirent->d_name, "..") != 0)
				{
					vDir.push_back(sName);
					qPath.push(vDir);
					vDir.pop_back();
					string sDir = sParent + "/" + sName;
					qDir.push(sDir);
				}
			}
			closedir(pDir);
		}
#endif
		qPath.pop();
		qDir.pop();
	}
	n32 nFileCount = static_cast<n32>(vFileName.size());
	m_vSplitFile.resize(nFileCount);
	m_vFileName.resize(nFileCount);
	for (n32 i = 0; i < nFileCount; i++)
	{
		string sFileName = UToU8(vFileName[i]);
		string::size_type uPos = sFileName.rfind(".split");
		bool bSplitFile = uPos != string::npos;
		m_vSplitFile[i] = bSplitFile;
		if (bSplitFile)
		{
			sFileName = sFileName.substr(0, uPos);
		}
		m_vFileName[i] = sFileName;
	}
	vector<string> vFileOutputName;
	CName::GenerateNewNameVector(m_vFileName, m_vFileOutputName, true);
	return true;
}

bool CGenerateScript::outputScript()
{
	string sExtractScript;
	string sCreateScript;
	n32 nFileCount = static_cast<n32>(m_vFileName.size());
	if (m_bGenerateBat)
	{
		m_sExtractSrcDirName = Replace(m_sExtractSrcDirName, "/", "\\");
		m_sExtractDestDirName = Replace(m_sExtractDestDirName, "/", "\\");
		m_sCreateSrcDirName = Replace(m_sCreateSrcDirName, "/", "\\");
		m_sCreateDestDirName = Replace(m_sCreateDestDirName, "/", "\\");
		sExtractScript += Format("MD \"%s\\_unite\"\r\n", m_sExtractDestDirName.c_str());
		for (n32 i = 0; i < nFileCount; i++)
		{
			const string& sFileName = m_vFileName[i];
			const string& sFileOutputName = m_vFileOutputName[i];
			if (m_vSplitFile[i])
			{
				sExtractScript += Format("XCOPY \"%s\\%s.split*\" \"%s\\_unite\\%s.split*\"\r\n"
					, m_sExtractSrcDirName.c_str(), sFileName.c_str()
					, m_sExtractDestDirName.c_str(), sFileName.c_str());
				sExtractScript += Format("\"%s\" --unite -xvfdob \"%s\\_unite\\%s\" \"%s\\data\\%s.dir\" \"%s\\_json\\%s.json\" \"%s\\_backup\\%s.bak\""
					, m_sExePath.c_str()
					, m_sExtractDestDirName.c_str(), sFileName.c_str()
					, m_sExtractDestDirName.c_str(), sFileOutputName.c_str()
					, m_sExtractDestDirName.c_str(), sFileOutputName.c_str()
					, m_sExtractDestDirName.c_str(), sFileOutputName.c_str());
				map<string, vector<string>>::const_iterator it = m_mResFileName.find(sFileName);
				if (it != m_mResFileName.end())
				{
					const vector<string>& vResFileName = it->second;
					for (vector<string>::const_iterator itRes = vResFileName.begin(); itRes != vResFileName.end(); ++itRes)
					{
						sExtractScript += Format(" --res \"%s\\%s\"", m_sExtractSrcDirName.c_str(), itRes->c_str());
					}
				}
				sExtractScript += " || PAUSE\r\n";
				sExtractScript += Format("DEL \"%s\\_unite\\%s.split*\"\r\n", m_sExtractDestDirName.c_str(), sFileName.c_str());
				// TODO: create script
			}
			else
			{
				sExtractScript += Format("\"%s\" -xvfdob \"%s\\%s\" \"%s\\data\\%s.dir\" \"%s\\_json\\%s.json\" \"%s\\_backup\\%s.bak\""
					, m_sExePath.c_str()
					, m_sExtractSrcDirName.c_str(), sFileName.c_str()
					, m_sExtractDestDirName.c_str(), sFileOutputName.c_str()
					, m_sExtractDestDirName.c_str(), sFileOutputName.c_str()
					, m_sExtractDestDirName.c_str(), sFileOutputName.c_str());
				map<string, vector<string>>::const_iterator it = m_mResFileName.find(sFileName);
				if (it != m_mResFileName.end())
				{
					const vector<string>& vResFileName = it->second;
					for (vector<string>::const_iterator itRes = vResFileName.begin(); itRes != vResFileName.end(); ++itRes)
					{
						sExtractScript += Format(" --res \"%s\\%s\"", m_sExtractSrcDirName.c_str(), itRes->c_str());
					}
				}
				sExtractScript += " || PAUSE\r\n";
				// TODO: create script
			}
		}
	}
	else
	{
		// TODO: non windows
	}
	if (!m_sExtractScriptFileName.empty())
	{
		FILE* fp = UFopen(m_sExtractScriptFileName, USTR("wb"));
		if (fp == nullptr)
		{
			return false;
		}
		fwrite(sExtractScript.c_str(), 1, sExtractScript.size(), fp);
		fclose(fp);
	}
	if (!m_sExtractScriptFileName.empty())
	{
		FILE* fp = UFopen(m_sCreateScriptFileName, USTR("wb"));
		if (fp == nullptr)
		{
			return false;
		}
		fwrite(sCreateScript.c_str(), 1, sCreateScript.size(), fp);
		fclose(fp);
	}
	return true;
}
