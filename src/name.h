#ifndef NAME_H_
#define NAME_H_

#include <sdw.h>

class CName
{
public:
	static void GenerateNewNameVector(const vector<string>& a_vOldName, vector<string>& a_vNewName, bool a_bRemoveExtName);
	static void GenerateNewNameMap(const set<string>& a_sOldName, map<string, string>& a_mOldNewName, bool a_bRemoveExtName);
};

#endif	// NAME_H_
