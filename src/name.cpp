#include "name.h"

void CName::GenerateNewNameVector(const vector<string>& a_vOldName, vector<string>& a_vNewName, bool a_bRemoveExtName)
{
	size_t uSize = a_vOldName.size();
	a_vNewName.resize(uSize);
	vector<string> vExtName(uSize);
	map<string, set<size_t>> mNewNameOldIndex;
	size_t uIndex = 0;
	for (vector<string>::const_iterator it = a_vOldName.begin(); it != a_vOldName.end(); ++it)
	{
		string sNewName = *it;
		string::size_type uPos = sNewName.rfind(".");
		if (uPos != string::npos)
		{
			if (a_bRemoveExtName)
			{
				sNewName.erase(uPos);
			}
			else
			{
				vExtName[uIndex] = sNewName.substr(uPos);
			}
		}
		mNewNameOldIndex[sNewName].insert(uIndex);
		uIndex++;
	}
	set<string> sNewNameChecker;
	map<string, n32> mNewNameIndex;
	for (map<string, set<size_t>>::const_reverse_iterator rit = mNewNameOldIndex.rbegin(); rit != mNewNameOldIndex.rend(); ++rit)
	{
		string sNewName = rit->first;
		const set<size_t>& sOldIndex = rit->second;
		size_t uIndex = *sOldIndex.begin();
		if (sOldIndex.size() == 1)
		{
			sNewNameChecker.insert(sNewName);
			a_vNewName[uIndex] = sNewName;
		}
		else
		{
			const string& sExtName = vExtName[uIndex];
			string sPrefix = sNewName.substr(0, sNewName.size() - sExtName.size());
			for (set<size_t>::const_iterator it = sOldIndex.begin(); it != sOldIndex.end(); ++it)
			{
				uIndex = *it;
				while (true)
				{
					string sNewNameTest = sPrefix + Format("_%d", mNewNameIndex[sNewName]++) + sExtName;
					if (sNewNameChecker.insert(sNewNameTest).second)
					{
						a_vNewName[uIndex] = sNewNameTest;
						break;
					}
				}
			}
		}
	}
}

void CName::GenerateNewNameMap(const set<string>& a_sOldName, map<string, string>& a_mOldNewName, bool a_bRemoveExtName)
{
	vector<string> vOldName(a_sOldName.begin(), a_sOldName.end());
	vector<string> vNewName;
	GenerateNewNameVector(vOldName, vNewName, a_bRemoveExtName);
	size_t uIndex = 0;
	for (vector<string>::const_iterator it = vOldName.begin(); it != vOldName.end(); ++it)
	{
		a_mOldNewName[*it] = vNewName[uIndex++];
	}
}
