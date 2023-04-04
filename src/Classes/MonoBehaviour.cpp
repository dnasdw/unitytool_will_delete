#include "MonoBehaviour.h"
#include "../basictype.h"
#include "../classid.h"

STypeTreeRoot nsu::MonoBehaviour::s_TypeTreeRoot;
bool nsu::MonoBehaviour::s_bInitRoot = false;

nsu::MonoBehaviour::MonoBehaviour()
	: m_nAssetsVersion(0)
	, m_bLittleEndian(true)
	, m_pTypeTreeRoot(nullptr)
	, m_pRefTypeTypeTree(nullptr)
{
}

nsu::MonoBehaviour::~MonoBehaviour()
{
}

void nsu::MonoBehaviour::SetAssetsVersion(n32 a_nAssetsVersion)
{
	m_nAssetsVersion = a_nAssetsVersion;
}

void nsu::MonoBehaviour::SetLittleEndian(bool a_bLittleEndian)
{
	m_bLittleEndian = a_bLittleEndian;
}

void nsu::MonoBehaviour::SetTypeTreeRoot(const STypeTreeRoot* a_pTypeTreeRoot)
{
	m_pTypeTreeRoot = a_pTypeTreeRoot;
}

void nsu::MonoBehaviour::SetRefTypeTypeTree(const STypeTree* a_pRefTypeTypeTree)
{
	m_pRefTypeTypeTree = a_pRefTypeTypeTree;
}

const string& nsu::MonoBehaviour::GetName() const
{
	return m_sName;
}

bool nsu::MonoBehaviour::ReadName()
{
	if (m_pTypeTreeRoot == nullptr)
	{
		return readNameCommon();
	}
	else
	{
		return readName();
	}
}

bool nsu::MonoBehaviour::readNameCommon()
{
	if (!s_bInitRoot)
	{
		s_TypeTreeRoot.ClassIdV2 = kClassIdMonoBehaviour_114;
		STypeTreeNode& MonoBehaviour_Base_0 = s_TypeTreeRoot.IndexedNode[0];
		MonoBehaviour_Base_0.Level = 0;
		MonoBehaviour_Base_0.Size = -1;
		MonoBehaviour_Base_0.Index = 0;
		MonoBehaviour_Base_0.Type = "MonoBehaviour";
		MonoBehaviour_Base_0.Name = "Base";
		STypeTreeNode& PPtr_GameObject__m_GameObject_1 = s_TypeTreeRoot.IndexedNode[1];
		PPtr_GameObject__m_GameObject_1.Level = 1;
		PPtr_GameObject__m_GameObject_1.Index = 1;
		PPtr_GameObject__m_GameObject_1.Type = "PPtr<GameObject>";
		PPtr_GameObject__m_GameObject_1.Name = "m_GameObject";
		STypeTreeNode& int_m_FileID_2 = s_TypeTreeRoot.IndexedNode[2];
		int_m_FileID_2.Level = 2;
		int_m_FileID_2.Size = 4;
		int_m_FileID_2.Index = 2;
		int_m_FileID_2.Type = "int";
		int_m_FileID_2.Name = "m_FileID";
		STypeTreeNode& int_SInt64_m_PathID_3 = s_TypeTreeRoot.IndexedNode[3];
		int_SInt64_m_PathID_3.Level = 2;
		int_SInt64_m_PathID_3.Index = 3;
		int_SInt64_m_PathID_3.Name = "m_PathID";
		STypeTreeNode& UInt8_m_Enabled_4 = s_TypeTreeRoot.IndexedNode[4];
		UInt8_m_Enabled_4.Level = 1;
		UInt8_m_Enabled_4.Size = 1;
		UInt8_m_Enabled_4.Index = 4;
		UInt8_m_Enabled_4.MetaFlags = kTypeTreeMetaFlagsAlignBytes;
		UInt8_m_Enabled_4.Type = "UInt8";
		UInt8_m_Enabled_4.Name = "m_Enabled";
		STypeTreeNode& PPtr_MonoScript__m_Script_5 = s_TypeTreeRoot.IndexedNode[5];
		PPtr_MonoScript__m_Script_5.Level = 1;
		PPtr_MonoScript__m_Script_5.Index = 5;
		PPtr_MonoScript__m_Script_5.Type = "PPtr<MonoScript>";
		PPtr_MonoScript__m_Script_5.Name = "m_Script";
		STypeTreeNode& int_m_FileID_6 = s_TypeTreeRoot.IndexedNode[6];
		int_m_FileID_6.Level = 2;
		int_m_FileID_6.Size = 4;
		int_m_FileID_6.Index = 6;
		int_m_FileID_6.Type = "int";
		int_m_FileID_6.Name = "m_FileID";
		STypeTreeNode& int_SInt64_m_PathID_7 = s_TypeTreeRoot.IndexedNode[7];
		int_SInt64_m_PathID_7.Level = 2;
		int_SInt64_m_PathID_7.Index = 7;
		int_SInt64_m_PathID_7.Name = "m_PathID";
		STypeTreeNode& string_m_Name_8 = s_TypeTreeRoot.IndexedNode[8];
		string_m_Name_8.Level = 1;
		string_m_Name_8.Size = -1;
		string_m_Name_8.Index = 8;
		string_m_Name_8.Type = "string";
		string_m_Name_8.Name = "m_Name";
		STypeTreeNode& Array_Array_9 = s_TypeTreeRoot.IndexedNode[9];
		Array_Array_9.Level = 2;
		Array_Array_9.Flags = kTypeTreeFlagsIsArray;
		Array_Array_9.Size = -1;
		Array_Array_9.Index = 9;
		Array_Array_9.MetaFlags = kTypeTreeMetaFlagsAlignBytes;
		Array_Array_9.Type = "Array";
		Array_Array_9.Name = "Array";
		STypeTreeNode& int_size_10 = s_TypeTreeRoot.IndexedNode[10];
		int_size_10.Level = 3;
		int_size_10.Size = 4;
		int_size_10.Index = 10;
		int_size_10.Type = "int";
		int_size_10.Name = "size";
		STypeTreeNode& char_data_11 = s_TypeTreeRoot.IndexedNode[11];
		char_data_11.Level = 3;
		char_data_11.Size = 1;
		char_data_11.Index = 11;
		char_data_11.Type = "char";
		char_data_11.Name = "data";
		if (m_nAssetsVersion >= 14)
		{
			int_SInt64_m_PathID_3.Type = "SInt64";
			int_SInt64_m_PathID_3.Size = 8;
			int_SInt64_m_PathID_7.Type = "SInt64";
			int_SInt64_m_PathID_7.Size = 8;
		}
		else
		{
			int_SInt64_m_PathID_3.Type = "int";
			int_SInt64_m_PathID_3.Size = 4;
			int_SInt64_m_PathID_7.Type = "int";
			int_SInt64_m_PathID_7.Size = 4;
		}
		PPtr_GameObject__m_GameObject_1.Size = int_m_FileID_2.Size + int_SInt64_m_PathID_3.Size;
		PPtr_MonoScript__m_Script_5.Size = int_m_FileID_6.Size + int_SInt64_m_PathID_7.Size;
		s_TypeTreeRoot.ChildCount = static_cast<n32>(s_TypeTreeRoot.IndexedNode.size());
		if (!s_TypeTreeRoot.CreateTypeTree())
		{
			return false;
		}
		s_bInitRoot = true;
	}
	const STypeTreeRoot* pTypeTreeRoot = m_pTypeTreeRoot;
	SetTypeTreeRoot(&s_TypeTreeRoot);
	bool bResult = readName();
	SetTypeTreeRoot(pTypeTreeRoot);
	return bResult;
}

bool nsu::MonoBehaviour::readName()
{
	if (m_pTypeTreeRoot == nullptr)
	{
		return readNameCommon();
	}
	if (m_pTypeTreeRoot->ChildCount == 0)
	{
		return readNameCommon();
	}
	n32 nRefTypeLevel = 0;
	stack<n32> sRefTypeLevel;
	sRefTypeLevel.push(nRefTypeLevel);
	map<n32, deque<pair<pair<const STypeTreeRoot*, n32>, n32>>> mRootIndexCount;
	mRootIndexCount[nRefTypeLevel].push_front(make_pair(make_pair(m_pTypeTreeRoot, 0), 1));
	map<n32, bool> mIsTravellingManagedReferenceRegistry;
	mIsTravellingManagedReferenceRegistry[nRefTypeLevel] = false;
	map<n32, n32> mVersion;
	mVersion[nRefTypeLevel] = 0;
	map<n32, n64> mRid;
	mRid[nRefTypeLevel] = 0;
	map<n32, deque<pair<n32, n32>>> mManagedReferenceRegistryChildTypeCount;
	EReadNameStep eStep = kReadNameStepBeforeRead;
	SBasicType basicType;
	bool bHasClassName = false;
	bool bHasNamespaceName = false;
	bool bHasAssemblyName = false;
	string sClassName;
	string sNamespaceName;
	string sAssemblyName;
	while (!sRefTypeLevel.empty())
	{
		nRefTypeLevel = sRefTypeLevel.top();
		while (!mRootIndexCount[nRefTypeLevel].empty())
		{
			deque<pair<pair<const STypeTreeRoot*, n32>, n32>>& dRootIndexCount = mRootIndexCount[nRefTypeLevel];
			pair<pair<const STypeTreeRoot*, n32>, n32>* pRootIndexCount = &dRootIndexCount.front();
			const STypeTreeRoot* pRoot = pRootIndexCount->first.first;
			n32 nIndex = pRootIndexCount->first.second;
			n32& nCount = pRootIndexCount->second;
			const STypeTreeNode* pNode = pRoot->GetNodeByIndex(nIndex);
			if (pNode == nullptr)
			{
				return false;
			}
			nCount--;
			if (nCount == -1)
			{
				dRootIndexCount.pop_front();
				if (pNode->IsAlign())
				{
					n64 nPos = istringstream::tellg();
					n32 nPaddingSize = static_cast<n32>(Align(nPos, 4) - nPos);
					if (!CStream::IsPaddingValid(nPaddingSize))
					{
						return false;
					}
				}
				continue;
			}
			if (eStep == kReadNameStepBeforeRead && pNode->Level == 1 && pNode->Type == "string" && pNode->Name == "m_Name")
			{
				if (pNode->ChildCount != 1)
				{
					return false;
				}
				eStep = kReadNameStepReading;
			}
			bool& bIsTravellingManagedReferenceRegistry = mIsTravellingManagedReferenceRegistry[nRefTypeLevel];
			n32& nVersion = mVersion[nRefTypeLevel];
			n64& nRid = mRid[nRefTypeLevel];
			deque<pair<n32, n32>>& dManagedReferenceRegistryChildTypeCount = mManagedReferenceRegistryChildTypeCount[nRefTypeLevel];
			n32 nManagedReferenceRegistryChildType = kManagedReferenceRegistryChildTypeNone;
			if (bIsTravellingManagedReferenceRegistry)
			{
				pair<n32, n32>& pTypeCount = dManagedReferenceRegistryChildTypeCount.front();
				nManagedReferenceRegistryChildType = pTypeCount.first;
				n32& nTypeCount = pTypeCount.second;
				nTypeCount--;
				if (nTypeCount == 0)
				{
					dManagedReferenceRegistryChildTypeCount.pop_front();
				}
			}
			if ((pNode->Flags & kTypeTreeFlagsIsManagedReferenceRegistry) != 0)
			{
				if (bIsTravellingManagedReferenceRegistry)
				{
					return false;
				}
				bIsTravellingManagedReferenceRegistry = true;
				if (pNode->ChildCount < 2)
				{
					return false;
				}
				n32 nVersionIndex = pNode->ChildIndex[0];
				const STypeTreeNode* pVersionNode = pRoot->GetNodeByIndex(nVersionIndex);
				if (pVersionNode == nullptr)
				{
					return false;
				}
				if (pVersionNode->Size != 4 || pVersionNode->ChildCount != 0)
				{
					return false;
				}
				if (!basicType.Init(pVersionNode->Type, pVersionNode->Size))
				{
					return false;
				}
				if (!basicType.Read(*this, m_bLittleEndian))
				{
					return false;
				}
				nVersion = basicType.Value.N32;
				if (nVersion != 2 && nVersion != 1)
				{
					return false;
				}
				if (pNode->ChildCount != 2)
				{
					return false;
				}
				nRid = 0;
				for (vector<n32>::const_reverse_iterator rit = pNode->ChildIndex.rbegin(); rit != pNode->ChildIndex.rend(); ++rit)
				{
					n32 nChildIndex = *rit;
					dRootIndexCount.push_front(make_pair(make_pair(pRoot, nChildIndex), 1));
					if (nVersion == 2)
					{
						dManagedReferenceRegistryChildTypeCount.push_front(make_pair(kManagedReferenceRegistryChildTypeRefIds, 1));
					}
					else if (nVersion == 1)
					{
						dManagedReferenceRegistryChildTypeCount.push_front(make_pair(kManagedReferenceRegistryChildTypeRefIdsArrayData, 1));
					}
				}
				// pop version index
				dRootIndexCount.pop_front();
				dManagedReferenceRegistryChildTypeCount.pop_front();
				continue;
			}
			if ((pNode->Flags & kTypeTreeFlagsIsArray) != 0)
			{
				if (pNode->ChildCount != 2)
				{
					return false;
				}
				n32 nArraySizeIndex = pNode->ChildIndex[0];
				n32 nArrayDataIndex = pNode->ChildIndex[1];
				const STypeTreeNode* pArraySizeNode = pRoot->GetNodeByIndex(nArraySizeIndex);
				if (pArraySizeNode == nullptr)
				{
					return false;
				}
				if (pArraySizeNode->Size != 4 || pArraySizeNode->ChildCount != 0)
				{
					return false;
				}
				if (!basicType.Init(pArraySizeNode->Type, pArraySizeNode->Size))
				{
					return false;
				}
				if (!basicType.Read(*this, m_bLittleEndian))
				{
					return false;
				}
				n32 nArraySize = basicType.Value.N32;
				if (nArraySize < 0)
				{
					return false;
				}
				if (nArraySize > 0)
				{
					dRootIndexCount.push_front(make_pair(make_pair(pRoot, nArrayDataIndex), nArraySize));
					if (bIsTravellingManagedReferenceRegistry && nManagedReferenceRegistryChildType == kManagedReferenceRegistryChildTypeRefIdsArray)
					{
						dManagedReferenceRegistryChildTypeCount.push_front(make_pair(nManagedReferenceRegistryChildType + 1, nArraySize));
					}
				}
			}
			else
			{
				if (pNode->ChildCount == 0 && pNode->Size == 0)
				{
					if (bIsTravellingManagedReferenceRegistry && nManagedReferenceRegistryChildType == kManagedReferenceRegistryChildTypeRefIdsArrayDataRidTypeData)
					{
						if (!bHasClassName || !bHasNamespaceName || !bHasAssemblyName)
						{
							return false;
						}
						if (m_pRefTypeTypeTree == nullptr)
						{
							return false;
						}
						const STypeTreeRoot* pRefTypeRoot = m_pRefTypeTypeTree->GetRoot(sAssemblyName, sNamespaceName, sClassName);
						if (pRefTypeRoot == nullptr)
						{
							return false;
						}
						if (pRefTypeRoot->ChildCount == 0)
						{
							return false;
						}
						bHasClassName = false;
						bHasNamespaceName = false;
						bHasAssemblyName = false;
						nRefTypeLevel++;
						sRefTypeLevel.push(nRefTypeLevel);
						mIsTravellingManagedReferenceRegistry[nRefTypeLevel] = false;
						mVersion[nRefTypeLevel] = 0;
						mRootIndexCount[nRefTypeLevel].push_front(make_pair(make_pair(pRefTypeRoot, 0), 1));
					}
				}
				else if (pNode->ChildCount == 0 && pNode->Size > 0)
				{
					if (!basicType.Init(pNode->Type, pNode->Size))
					{
						return false;
					}
					if (!basicType.Read(*this, m_bLittleEndian))
					{
						return false;
					}
					if (bIsTravellingManagedReferenceRegistry && nManagedReferenceRegistryChildType == kManagedReferenceRegistryChildTypeRefIdsArrayDataRidTypeData)
					{
						nRid = basicType.Value.N64;
					}
				}
				else if (pNode->Type == "string")
				{
					if (pNode->ChildCount != 1)
					{
						return false;
					}
					n32 nStringArrayIndex = pNode->ChildIndex[0];
					const STypeTreeNode* pStringArrayNode = pRoot->GetNodeByIndex(nStringArrayIndex);
					if (pStringArrayNode == nullptr)
					{
						return false;
					}
					if (pStringArrayNode->ChildCount != 2)
					{
						return false;
					}
					n32 nStringArraySizeIndex = pStringArrayNode->ChildIndex[0];
					n32 nStringArrayDataIndex = pStringArrayNode->ChildIndex[1];
					const STypeTreeNode* pStringArraySizeNode = pRoot->GetNodeByIndex(nStringArraySizeIndex);
					if (pStringArraySizeNode == nullptr)
					{
						return false;
					}
					if (pStringArraySizeNode->Size != 4 || pStringArraySizeNode->ChildCount != 0)
					{
						return false;
					}
					if (!basicType.Init(pStringArraySizeNode->Type, pStringArraySizeNode->Size))
					{
						return false;
					}
					if (!basicType.Read(*this, m_bLittleEndian))
					{
						return false;
					}
					n32 nStringSize = basicType.Value.N32;
					if (nStringSize < 0)
					{
						return false;
					}
					const STypeTreeNode* pStringArrayDataNode = pRoot->GetNodeByIndex(nStringArrayDataIndex);
					if (pStringArrayDataNode == nullptr)
					{
						return false;
					}
					if (pStringArrayDataNode->Size != 1 || pStringArrayDataNode->ChildCount != 0)
					{
						return false;
					}
					string sString;
					if (nStringSize != 0)
					{
						sString.resize(nStringSize);
						if (!CStream::Read(&*sString.begin(), nStringSize).good())
						{
							return false;
						}
					}
					if (pNode->IsAlign() || pStringArrayNode->IsAlign() || pStringArrayDataNode->IsAlign())
					{
						n64 nPos = istringstream::tellg();
						n32 nPaddingSize = static_cast<n32>(Align(nPos, 4) - nPos);
						if (!CStream::IsPaddingValid(nPaddingSize))
						{
							return false;
						}
					}
					if (eStep == kReadNameStepReading)
					{
						m_sName.swap(sString);
						eStep = kReadNameStepAfterRead;
					}
					else if (bIsTravellingManagedReferenceRegistry && nManagedReferenceRegistryChildType == kManagedReferenceRegistryChildTypeRefIdsArrayDataTypeClassNamespaceAssembly)
					{
						if (!bHasClassName)
						{
							bHasClassName = true;
							sClassName.swap(sString);
						}
						else if (!bHasNamespaceName)
						{
							bHasNamespaceName = true;
							sNamespaceName.swap(sString);
						}
						else if (!bHasAssemblyName)
						{
							bHasAssemblyName = true;
							sAssemblyName.swap(sString);
						}
						else
						{
							return false;
						}
						if (bHasAssemblyName)
						{
							// [0]: string asm
							// [1]: ReferencedManagedType type
							// [2]: ReferencedObjectData data
							// [3]: ReferencedObject data for version 2
							// [4]: Array Array for version 2
							// [5]: vector RefIds for version 2
							// [6]: ManagedReferencesRegistry references for version 2
							// [3]: ReferencedObject 00000000 for version 1
							// [4]: ManagedReferencesRegistry references for version 1
							if (dRootIndexCount.size() < 4)
							{
								return false;
							}
							// [0]: kManagedReferenceRegistryChildTypeRefIdsArrayDataRidTypeData for ReferencedObjectData data
							if (dManagedReferenceRegistryChildTypeCount.size() < 1)
							{
								return false;
							}
							bool bReturn = false;
							bool bLoopVersion1 = true;
							if (sClassName == "Terminus" && sNamespaceName == "UnityEngine.DMAT" && sAssemblyName == "FAKE_ASM")
							{
								bReturn = true;
								bLoopVersion1 = false;
							}
							else if (nRid == -1 || nRid == -2)
							{
								bReturn = true;
							}
							if (nVersion == 1)
							{
								nRid++;
							}
							if (bLoopVersion1 && nVersion == 1)
							{
								// [3]: ReferencedObject 00000000
								dRootIndexCount[3].second++;
								// [0]: kManagedReferenceRegistryChildTypeRefIdsArrayDataRidTypeData for ReferencedObjectData data
								dManagedReferenceRegistryChildTypeCount.insert(dManagedReferenceRegistryChildTypeCount.begin() + 1, make_pair(kManagedReferenceRegistryChildTypeRefIdsArrayData, 1));
							}
							if (bReturn)
							{
								// [0]: string asm
								// [1]: ReferencedManagedType type
								for (n32 i = 0; i < 2; i++)
								{
									pRootIndexCount = &dRootIndexCount[i];
									pRoot = pRootIndexCount->first.first;
									nIndex = pRootIndexCount->first.second;
									pNode = pRoot->GetNodeByIndex(nIndex);
									if (pNode == nullptr)
									{
										return false;
									}
									if (pNode->IsAlign())
									{
										n64 nPos = istringstream::tellg();
										n32 nPaddingSize = static_cast<n32>(Align(nPos, 4) - nPos);
										if (!CStream::IsPaddingValid(nPaddingSize))
										{
											return false;
										}
									}
								}
								// pop asm index
								dRootIndexCount.pop_front();
								// pop type index
								dRootIndexCount.pop_front();
								// pop data index
								dRootIndexCount.pop_front();
								dManagedReferenceRegistryChildTypeCount.pop_front();
							}
						}
					}
				}
				else
				{
					for (vector<n32>::const_reverse_iterator rit = pNode->ChildIndex.rbegin(); rit != pNode->ChildIndex.rend(); ++rit)
					{
						n32 nChildIndex = *rit;
						dRootIndexCount.push_front(make_pair(make_pair(pRoot, nChildIndex), 1));
						if (bIsTravellingManagedReferenceRegistry)
						{
							dManagedReferenceRegistryChildTypeCount.push_front(make_pair(nManagedReferenceRegistryChildType + 1, 1));
						}
					}
				}
			}
			if (mIsTravellingManagedReferenceRegistry[nRefTypeLevel] && mManagedReferenceRegistryChildTypeCount[nRefTypeLevel].empty())
			{
				mIsTravellingManagedReferenceRegistry[nRefTypeLevel] = false;
			}
		}
		sRefTypeLevel.pop();
	}
	return true;
}
