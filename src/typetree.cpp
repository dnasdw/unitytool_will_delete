#include "typetree.h"

STypeTreeNode::STypeTreeNode()
	: Version(1)
	, Level(0)
	, Flags(0)
	, TypeStringOffset(0)
	, NameStringOffset(0)
	, Size(0)
	, Index(0)
	, MetaFlags(0)
	, Node18Unknown0x18(0)
	, Node2Unknown0x4(0)
	, ChildCount(0)
{
}

bool STypeTreeNode::IsAlign() const
{
	return (MetaFlags & (kTypeTreeMetaFlagsAlignBytes/* | kTypeTreeMetaFlagsAnyChildUsesAlignBytes*/)) != 0;
}

STypeTreeRoot::STypeTreeRoot()
	: ClassIdV2(0)
	, IsStripped(false)
	, ScriptIndex(-1)
	, ChildCount(0)
	, StringSize(0)
	, RefTypeCount(0)
	, ClassIdV1(0)
	, TypeTree(nullptr)
{
	memset(ScriptId, 0, sizeof(ScriptId));
	memset(OldTypeHash, 0, sizeof(OldTypeHash));
}

bool STypeTreeRoot::CreateTypeTree()
{
	if (ChildCount > 1)
	{
		stack<n32> sIndex;
		sIndex.push(0);
		for (n32 i = 1; i < ChildCount; i++)
		{
			STypeTreeNode& node = IndexedNode[i];
			if (node.Level > static_cast<n32>(sIndex.size()))
			{
				return false;
			}
			while (node.Level < static_cast<n32>(sIndex.size()))
			{
				sIndex.pop();
			}
			n32 nParentIndex = sIndex.top();
			STypeTreeNode& parentNode = IndexedNode[nParentIndex];
			parentNode.ChildIndex.push_back(i);
			sIndex.push(i);
		}
	}
	for (n32 i = 0; i < ChildCount; i++)
	{
		STypeTreeNode& node = IndexedNode[i];
		n32 nChildCount = static_cast<n32>(node.ChildIndex.size());
		if (node.ChildCount != nChildCount)
		{
			if (node.ChildCount != 0)
			{
				return false;
			}
			node.ChildCount = nChildCount;
		}
	}
	return true;
}

const STypeTreeNode* STypeTreeRoot::GetNodeByIndex(n32 a_nIndex) const
{
	const STypeTreeNode* pNode = nullptr;
	map<n32, STypeTreeNode>::const_iterator it = IndexedNode.find(a_nIndex);
	if (it != IndexedNode.end())
	{
		pNode = &it->second;
	}
	return pNode;
}

STypeTree::STypeTree()
	: BuildTargetPlatform(0)
	, HasTypeTree(true)
	, IsRefTypeTypeTree(false)
	, TypeCount(0)
{
}

const STypeTreeRoot* STypeTree::GetRoot(const string& a_sAssemblyName, const string& a_sNamespaceName, const string& a_sClassName) const
{
	const STypeTreeRoot* pRoot = nullptr;
	map<string, map<string, map<string, n32>>>::const_iterator itAssembly = AssemblyNamespaceClassIndex.find(a_sAssemblyName);
	if (itAssembly != AssemblyNamespaceClassIndex.end())
	{
		const map<string, map<string, n32>>& mNamespaceClassIndex = itAssembly->second;
		map<string, map<string, n32>>::const_iterator itNamespace = mNamespaceClassIndex.find(a_sNamespaceName);
		if (itNamespace != mNamespaceClassIndex.end())
		{
			const map<string, n32>& mClassIndex = itNamespace->second;
			map<string, n32>::const_iterator itClass = mClassIndex.find(a_sClassName);
			if (itClass != mClassIndex.end())
			{
				n32 nRootIndex = itClass->second;
				pRoot = &Root[nRootIndex];
			}
		}
	}
	return pRoot;
}
