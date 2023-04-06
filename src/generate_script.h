#ifndef GENERATE_SCRIPT_H_
#define GENERATE_SCRIPT_H_

#include <sdw.h>

class CGenerateScript
{
public:
	CGenerateScript();
	~CGenerateScript();
	void SetVerbose(bool a_bVerbose);
	void SetGenerateBat(bool a_bGenerateBat);
	void SetExePath(const UString& a_sExePath);
	void SetExtractScriptFileName(const UString& a_sExtractScriptFileName);
	void SetExtractSrcDirName(const UString& a_sExtractSrcDirName);
	void SetExtractDestDirName(const UString& a_sExtractDestDirName);
	void SetCreateScriptFileName(const UString& a_sCreateScriptFileName);
	void SetCreateSrcDirName(const UString& a_sCreateSrcDirName);
	void SetCreateDestDirName(const UString& a_sCreateDestDirName);
	void SetPatternFileName(const UString& a_sPatternFileName);
	bool GenerateScript();
private:
	bool buildPatternList();
	bool matchInPatternList(const UString& a_sPath) const;
	bool buildFileNameList();
	bool outputScript();
	bool m_bVerbose;
	bool m_bGenerateBat;
	string m_sExePath;
	UString m_sExtractScriptFileName;
	string m_sExtractSrcDirName;
	string m_sExtractDestDirName;
	UString m_sCreateScriptFileName;
	string m_sCreateSrcDirName;
	string m_sCreateDestDirName;
	UString m_sPatternFileName;
	vector<URegex> m_vPatternList;
	map<string, vector<string>> m_mResFileName;
	vector<bool> m_vSplitFile;
	vector<string> m_vFileName;
	vector<string> m_vFileOutputName;
};

#endif	// GENERATE_SCRIPT_H_
