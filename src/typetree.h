#ifndef TYPETREE_H_
#define TYPETREE_H_

#include <sdw.h>

enum ETypeTreeFlags
{
	kTypeTreeFlagsNone = 0,
	kTypeTreeFlagsIsArray = 1 << 0,
	kTypeTreeFlagsIsManagedReference = 1 << 1,
	kTypeTreeFlagsIsManagedReferenceRegistry = 1 << 2,
	kTypeTreeFlagsIsArrayOfRefs = 1 << 3
};

enum ETypeTreeMetaFlags
{
	kTypeTreeMetaFlagsNone = 0,
	kTypeTreeMetaFlagsAlignBytes = 1 << 14,
	kTypeTreeMetaFlagsAnyChildUsesAlignBytes = 1 << 15
};

enum EManagedReferenceRegistryChildType
{
	kManagedReferenceRegistryChildTypeNone,
	kManagedReferenceRegistryChildTypeRefIds,
	kManagedReferenceRegistryChildTypeRefIdsArray,
	kManagedReferenceRegistryChildTypeRefIdsArrayData,
	kManagedReferenceRegistryChildTypeRefIdsArrayDataRidTypeData,
	kManagedReferenceRegistryChildTypeRefIdsArrayDataTypeClassNamespaceAssembly,
	kManagedReferenceRegistryChildTypeMax
};

struct STypeTree;

struct STypeTreeNode
{
	u16 Version;
	u8 Level;
	u8 Flags;
	u32 TypeStringOffset;
	u32 NameStringOffset;
	n32 Size;
	n32 Index;
	u32 MetaFlags;
	u64 Node18Unknown0x18;
	string Type;
	string Name;
	n32 Node2Unknown0x4;
	n32 ChildCount;
	vector<n32> ChildIndex;
	STypeTreeNode();
	bool IsAlign() const;
};

struct STypeTreeRoot
{
	n32 ClassIdV2;
	bool IsStripped;
	n16 ScriptIndex;
	u32 ScriptId[4];
	u32 OldTypeHash[4];
	n32 ChildCount;
	n32 StringSize;
	map<n32, STypeTreeNode> IndexedNode;
	string String;
	n32 RefTypeCount;
	vector<u32> RefTypeIndex;
	string ClassName;
	string NamespaceName;
	string AssemblyName;
	n32 ClassIdV1;
	STypeTree* TypeTree;
	STypeTreeRoot();
	bool CreateTypeTree();
	const STypeTreeNode* GetNodeByIndex(n32 a_nIndex) const;
};

struct STypeTree
{
	string Version;
	n32 BuildTargetPlatform;
	bool HasTypeTree;
	bool IsRefTypeTypeTree;
	n32 TypeCount;
	vector<STypeTreeRoot> Root;
	map<string, map<string, map<string, n32>>> AssemblyNamespaceClassIndex;
	map<n32, n32> ClassIdV1Index;
	STypeTree();
	const STypeTreeRoot* GetRoot(const string& a_sAssemblyName, const string& a_sNamespaceName, const string& a_sClassName) const;
};

#endif	// TYPETREE_H_
