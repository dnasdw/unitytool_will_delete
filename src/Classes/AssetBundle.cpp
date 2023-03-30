#include "AssetBundle.h"
#include "../basictype.h"
#include "../classid.h"

STypeTreeRoot nsu::AssetBundle::s_TypeTreeRoot;
bool nsu::AssetBundle::s_bInitRoot = false;

nsu::AssetBundle::AssetBundle()
	: m_nAssetsVersion(0)
	, m_bLittleEndian(true)
	, m_pTypeTreeRoot(nullptr)
	, m_pRefTypeTypeTree(nullptr)
{
}

nsu::AssetBundle::~AssetBundle()
{
}

void nsu::AssetBundle::SetAssetsVersion(n32 a_nAssetsVersion)
{
	m_nAssetsVersion = a_nAssetsVersion;
}

void nsu::AssetBundle::SetLittleEndian(bool a_bLittleEndian)
{
	m_bLittleEndian = a_bLittleEndian;
}

void nsu::AssetBundle::SetTypeTreeRoot(const STypeTreeRoot* a_pTypeTreeRoot)
{
	m_pTypeTreeRoot = a_pTypeTreeRoot;
}

void nsu::AssetBundle::SetRefTypeTypeTree(const STypeTree* a_pRefTypeTypeTree)
{
	m_pRefTypeTypeTree = a_pRefTypeTypeTree;
}

const map<n32, map<n64, string>>& nsu::AssetBundle::GetContainerFilePath() const
{
	return m_mContainerFilePath;
}

bool nsu::AssetBundle::ReadContainer()
{
	if (m_pTypeTreeRoot == nullptr)
	{
		return readContainerCommon();
	}
	else
	{
		return readContainer();
	}
}

bool nsu::AssetBundle::readContainerCommon()
{
	if (!s_bInitRoot)
	{
		s_TypeTreeRoot.ClassIdV2 = kClassIdAssetBundle_142;
		STypeTreeNode& AssetBundle_Base_0 = s_TypeTreeRoot.IndexedNode[0];
		AssetBundle_Base_0.Level = 0;
		AssetBundle_Base_0.Size = -1;
		AssetBundle_Base_0.Index = 0;
		AssetBundle_Base_0.Type = "AssetBundle";
		AssetBundle_Base_0.Name = "Base";
		STypeTreeNode& string_m_Name_1 = s_TypeTreeRoot.IndexedNode[1];
		string_m_Name_1.Level = 1;
		string_m_Name_1.Size = -1;
		string_m_Name_1.Index = 1;
		string_m_Name_1.Type = "string";
		string_m_Name_1.Name = "m_Name";
		STypeTreeNode& Array_Array_2 = s_TypeTreeRoot.IndexedNode[2];
		Array_Array_2.Level = 2;
		Array_Array_2.Flags = kTypeTreeFlagsIsArray;
		Array_Array_2.Size = -1;
		Array_Array_2.Index = 2;
		Array_Array_2.MetaFlags = kTypeTreeMetaFlagsAlignBytes;
		Array_Array_2.Type = "Array";
		Array_Array_2.Name = "Array";
		STypeTreeNode& int_size_3 = s_TypeTreeRoot.IndexedNode[3];
		int_size_3.Level = 3;
		int_size_3.Size = 4;
		int_size_3.Index = 3;
		int_size_3.Type = "int";
		int_size_3.Name = "size";
		STypeTreeNode& char_data_4 = s_TypeTreeRoot.IndexedNode[4];
		char_data_4.Level = 3;
		char_data_4.Size = 1;
		char_data_4.Index = 4;
		char_data_4.Type = "char";
		char_data_4.Name = "data";
		STypeTreeNode& vector_m_PreloadTable_5 = s_TypeTreeRoot.IndexedNode[5];
		vector_m_PreloadTable_5.Level = 1;
		vector_m_PreloadTable_5.Size = -1;
		vector_m_PreloadTable_5.Index = 5;
		vector_m_PreloadTable_5.Type = "vector";
		vector_m_PreloadTable_5.Name = "m_PreloadTable";
		STypeTreeNode& Array_Array_6 = s_TypeTreeRoot.IndexedNode[6];
		Array_Array_6.Level = 2;
		Array_Array_6.Flags = kTypeTreeFlagsIsArray;
		Array_Array_6.Size = -1;
		Array_Array_6.Index = 6;
		Array_Array_6.MetaFlags = kTypeTreeMetaFlagsAlignBytes;
		Array_Array_6.Type = "Array";
		Array_Array_6.Name = "Array";
		STypeTreeNode& int_size_7 = s_TypeTreeRoot.IndexedNode[7];
		int_size_7.Level = 3;
		int_size_7.Size = 4;
		int_size_7.Index = 7;
		int_size_7.Type = "int";
		int_size_7.Name = "size";
		STypeTreeNode& PPtr_Object__data_8 = s_TypeTreeRoot.IndexedNode[8];
		PPtr_Object__data_8.Level = 3;
		PPtr_Object__data_8.Index = 8;
		PPtr_Object__data_8.Type = "PPtr<Object>";
		PPtr_Object__data_8.Name = "data";
		STypeTreeNode& int_m_FileID_9 = s_TypeTreeRoot.IndexedNode[9];
		int_m_FileID_9.Level = 4;
		int_m_FileID_9.Size = 4;
		int_m_FileID_9.Index = 9;
		int_m_FileID_9.Type = "int";
		int_m_FileID_9.Name = "m_FileID";
		STypeTreeNode& int_SInt64_m_PathID_10 = s_TypeTreeRoot.IndexedNode[10];
		int_SInt64_m_PathID_10.Level = 4;
		int_SInt64_m_PathID_10.Index = 10;
		int_SInt64_m_PathID_10.Name = "m_PathID";
		STypeTreeNode& map_m_Container_11 = s_TypeTreeRoot.IndexedNode[11];
		map_m_Container_11.Level = 1;
		map_m_Container_11.Size = -1;
		map_m_Container_11.Index = 11;
		map_m_Container_11.Type = "map";
		map_m_Container_11.Name = "m_Container";
		STypeTreeNode& Array_Array_12 = s_TypeTreeRoot.IndexedNode[12];
		Array_Array_12.Level = 2;
		Array_Array_12.Flags = kTypeTreeFlagsIsArray;
		Array_Array_12.Size = -1;
		Array_Array_12.Index = 12;
		Array_Array_12.Type = "Array";
		Array_Array_12.Name = "Array";
		STypeTreeNode& int_size_13 = s_TypeTreeRoot.IndexedNode[13];
		int_size_13.Level = 3;
		int_size_13.Size = 4;
		int_size_13.Index = 13;
		int_size_13.Type = "int";
		int_size_13.Name = "size";
		STypeTreeNode& pair_data_14 = s_TypeTreeRoot.IndexedNode[14];
		pair_data_14.Level = 3;
		pair_data_14.Size = -1;
		pair_data_14.Index = 14;
		pair_data_14.Type = "pair";
		pair_data_14.Name = "data";
		STypeTreeNode& string_first_15 = s_TypeTreeRoot.IndexedNode[15];
		string_first_15.Level = 4;
		string_first_15.Size = -1;
		string_first_15.Index = 15;
		string_first_15.Type = "string";
		string_first_15.Name = "first";
		STypeTreeNode& Array_Array_16 = s_TypeTreeRoot.IndexedNode[16];
		Array_Array_16.Level = 5;
		Array_Array_16.Flags = kTypeTreeFlagsIsArray;
		Array_Array_16.Size = -1;
		Array_Array_16.Index = 16;
		Array_Array_16.MetaFlags = kTypeTreeMetaFlagsAlignBytes;
		Array_Array_16.Type = "Array";
		Array_Array_16.Name = "Array";
		STypeTreeNode& int_size_17 = s_TypeTreeRoot.IndexedNode[17];
		int_size_17.Level = 6;
		int_size_17.Size = 4;
		int_size_17.Index = 17;
		int_size_17.Type = "int";
		int_size_17.Name = "size";
		STypeTreeNode& char_data_18 = s_TypeTreeRoot.IndexedNode[18];
		char_data_18.Level = 6;
		char_data_18.Size = 1;
		char_data_18.Index = 18;
		char_data_18.Type = "char";
		char_data_18.Name = "data";
		STypeTreeNode& AssetInfo_second_19 = s_TypeTreeRoot.IndexedNode[19];
		AssetInfo_second_19.Level = 4;
		AssetInfo_second_19.Index = 19;
		AssetInfo_second_19.Type = "AssetInfo";
		AssetInfo_second_19.Name = "second";
		STypeTreeNode& int_preloadIndex_20 = s_TypeTreeRoot.IndexedNode[20];
		int_preloadIndex_20.Level = 5;
		int_preloadIndex_20.Size = 4;
		int_preloadIndex_20.Index = 20;
		int_preloadIndex_20.Type = "int";
		int_preloadIndex_20.Name = "preloadIndex";
		STypeTreeNode& int_preloadSize_21 = s_TypeTreeRoot.IndexedNode[21];
		int_preloadSize_21.Level = 5;
		int_preloadSize_21.Size = 4;
		int_preloadSize_21.Index = 21;
		int_preloadSize_21.Type = "int";
		int_preloadSize_21.Name = "preloadSize";
		STypeTreeNode& PPtr_Object__asset_22 = s_TypeTreeRoot.IndexedNode[22];
		PPtr_Object__asset_22.Level = 5;
		PPtr_Object__asset_22.Index = 22;
		PPtr_Object__asset_22.Type = "PPtr<Object>";
		PPtr_Object__asset_22.Name = "asset";
		STypeTreeNode& int_m_FileID_23 = s_TypeTreeRoot.IndexedNode[23];
		int_m_FileID_23.Level = 6;
		int_m_FileID_23.Size = 4;
		int_m_FileID_23.Index = 23;
		int_m_FileID_23.Type = "int";
		int_m_FileID_23.Name = "m_FileID";
		STypeTreeNode& int_SInt64_m_PathID_24 = s_TypeTreeRoot.IndexedNode[24];
		int_SInt64_m_PathID_24.Level = 6;
		int_SInt64_m_PathID_24.Index = 24;
		int_SInt64_m_PathID_24.Name = "m_PathID";
		if (m_nAssetsVersion >= 14)
		{
			int_SInt64_m_PathID_10.Type = "SInt64";
			int_SInt64_m_PathID_10.Size = 8;
			int_SInt64_m_PathID_24.Type = "SInt64";
			int_SInt64_m_PathID_24.Size = 8;
		}
		else
		{
			int_SInt64_m_PathID_10.Type = "int";
			int_SInt64_m_PathID_10.Size = 4;
			int_SInt64_m_PathID_24.Type = "int";
			int_SInt64_m_PathID_24.Size = 4;
		}
		PPtr_Object__data_8.Size = int_m_FileID_9.Size + int_SInt64_m_PathID_10.Size;
		PPtr_Object__asset_22.Size = int_m_FileID_23.Size + int_SInt64_m_PathID_24.Size;
		AssetInfo_second_19.Size = int_preloadIndex_20.Size + int_preloadSize_21.Size + PPtr_Object__asset_22.Size;
		s_TypeTreeRoot.ChildCount = static_cast<n32>(s_TypeTreeRoot.IndexedNode.size());
		if (!s_TypeTreeRoot.CreateTypeTree())
		{
			return false;
		}
		s_bInitRoot = true;
	}
	const STypeTreeRoot* pTypeTreeRoot = m_pTypeTreeRoot;
	SetTypeTreeRoot(&s_TypeTreeRoot);
	bool bResult = readContainer();
	SetTypeTreeRoot(pTypeTreeRoot);
	return bResult;
}

bool nsu::AssetBundle::readContainer()
{
	if (m_pTypeTreeRoot == nullptr)
	{
		return readContainerCommon();
	}
	if (m_pTypeTreeRoot->ChildCount == 0)
	{
		return readContainerCommon();
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
	ETravelContainerStep eStep = kTravelContainerStepBeforeTravel;
	stack<pair<n32, n32>> sContainerChildTypeCount;
	SBasicType basicType;
	bool bHasClassName = false;
	bool bHasNamespaceName = false;
	bool bHasAssemblyName = false;
	string sClassName;
	string sNamespaceName;
	string sAssemblyName;
	bool bHasFileId = false;
	bool bHasPathId = false;
	bool bHasPath = false;
	n32 nFileId = 0;
	n64 nPathId = 0;
	string sPath;
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
			n32 nChildType = kContainerChildTypeNone;
			if (eStep == kTravelContainerStepTravelling)
			{
				pair<n32, n32>& pTypeCount = sContainerChildTypeCount.top();
				nChildType = pTypeCount.first;
				n32& nTypeCount = pTypeCount.second;
				nTypeCount--;
				if (nTypeCount == 0)
				{
					sContainerChildTypeCount.pop();
				}
			}
			if (eStep == kTravelContainerStepBeforeTravel && pNode->Level == 1 && pNode->Type == "map" && pNode->Name == "m_Container")
			{
				if (pNode->ChildCount != 1)
				{
					return false;
				}
				eStep = kTravelContainerStepTravelling;
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
					if (eStep == kTravelContainerStepTravelling && nChildType == kContainerChildTypeArray)
					{
						sContainerChildTypeCount.push(make_pair(nChildType + 1, nArraySize));
					}
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
					if (eStep == kTravelContainerStepTravelling && nChildType == kContainerChildTypeArrayDataSecondAssetFileIdPathId)
					{
						if (pNode->Name == "m_FileID")
						{
							if (bHasFileId)
							{
								return false;
							}
							bHasFileId = true;
							if (pNode->Size != 4)
							{
								return false;
							}
							nFileId = basicType.Value.N32;
							if (bHasFileId && bHasPathId && bHasPath)
							{
								if (!mergeContainer(nFileId, nPathId, sPath))
								{
									return false;
								}
								bHasFileId = false;
								bHasPathId = false;
								bHasPath = false;
							}
						}
						else if (pNode->Name == "m_PathID")
						{
							if (bHasPathId)
							{
								return false;
							}
							bHasPathId = true;
							switch (pNode->Size)
							{
							case 4:
								nPathId = basicType.Value.N32;
								break;
							case 8:
								nPathId = basicType.Value.N64;
								break;
							default:
								return false;
							}
							if (bHasFileId && bHasPathId && bHasPath)
							{
								if (!mergeContainer(nFileId, nPathId, sPath))
								{
									return false;
								}
								bHasFileId = false;
								bHasPathId = false;
								bHasPath = false;
							}
						}
					}
					else if (bIsTravellingManagedReferenceRegistry && nManagedReferenceRegistryChildType == kManagedReferenceRegistryChildTypeRefIdsArrayDataRidTypeData)
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
					if (eStep == kTravelContainerStepTravelling && nChildType == kContainerChildTypeArrayDataFirstSecond && pNode->Name == "first")
					{
						if (bHasPath)
						{
							return false;
						}
						bHasPath = true;
						sPath.swap(sString);
						if (bHasFileId && bHasPathId && bHasPath)
						{
							if (!mergeContainer(nFileId, nPathId, sPath))
							{
								return false;
							}
							bHasFileId = false;
							bHasPathId = false;
							bHasPath = false;
						}
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
						if (eStep == kTravelContainerStepTravelling)
						{
							sContainerChildTypeCount.push(make_pair(nChildType + 1, 1));
						}
						if (bIsTravellingManagedReferenceRegistry)
						{
							dManagedReferenceRegistryChildTypeCount.push_front(make_pair(nManagedReferenceRegistryChildType + 1, 1));
						}
					}
				}
			}
			if (eStep == kTravelContainerStepTravelling && sContainerChildTypeCount.empty())
			{
				eStep = kTravelContainerStepAfterTravel;
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

bool nsu::AssetBundle::mergeContainer(n32 a_nFileId, n64 a_nPathId, const string& a_sPath)
{
	map<n64, string>& mPath = m_mContainerFilePath[a_nFileId];
	if (!mPath.insert(make_pair(a_nPathId, a_sPath)).second)
	{
		return false;
	}
	return true;
}
