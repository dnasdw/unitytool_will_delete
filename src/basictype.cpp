#include "basictype.h"

SBasicType::SBasicType()
	: Type(kTypeNone)
{
	memset(&Value, 0, sizeof(Value));
}

bool SBasicType::Init(const string& a_sType, n32 a_nSize)
{
	if (a_sType == "bool")
	{
		Type = kTypeBool;
	}
	else if (a_sType == "SInt8" || a_sType == "char")
	{
		Type = kTypeN8;
	}
	else if (a_sType == "SInt16")
	{
		Type = kTypeN16;
	}
	else if (a_sType == "SInt32" || a_sType == "int" || a_sType == "Type*")
	{
		Type = kTypeN32;
	}
	else if (a_sType == "SInt64")
	{
		Type = kTypeN64;
	}
	else if (a_sType == "UInt8")
	{
		Type = kTypeU8;
	}
	else if (a_sType == "UInt16")
	{
		Type = kTypeU16;
	}
	else if (a_sType == "UInt32" || a_sType == "unsigned int")
	{
		Type = kTypeU32;
	}
	else if (a_sType == "UInt64" || a_sType == "FileSize")
	{
		Type = kTypeU64;
	}
	else if (a_sType == "float")
	{
		Type = kTypeF32;
	}
	else if (a_sType == "double")
	{
		Type = kTypeF64;
	}
	else
	{
		switch (a_nSize)
		{
		case 1:
			Type = kTypeN8;
			break;
		case 2:
			Type = kTypeN16;
			break;
		case 4:
			Type = kTypeN32;
			break;
		case 8:
			Type = kTypeN64;
			break;
		default:
			return false;
		}
	}
	return true;
}
