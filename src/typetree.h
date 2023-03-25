#ifndef TYPETREE_H_
#define TYPETREE_H_

#include <sdw.h>

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
};

#endif	// TYPETREE_H_
