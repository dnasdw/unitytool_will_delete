#ifndef BASICTYPE_H_
#define BASICTYPE_H_

#include "stream.h"

struct SBasicType
{
public:
	enum EType
	{
		kTypeNone,
		kTypeBool,
		kTypeN8,
		kTypeN16,
		kTypeN32,
		kTypeN64,
		kTypeU8,
		kTypeU16,
		kTypeU32,
		kTypeU64,
		kTypeF32,
		kTypeF64
	};
	union UValue
	{
		bool Bool;
		n8 N8;
		n16 N16;
		n32 N32;
		n64 N64;
		u8 U8;
		u16 U16;
		u32 U32;
		u64 U64;
		f32 F32;
		f64 F64;
	};
	EType Type;
	UValue Value;
	SBasicType();
	bool Init(const string& a_sType, n32 a_nSize);
	template<typename IStreamType>
	bool Read(CStream<IStreamType>& a_Stream, bool a_bLittleEndian)
	{
		switch (Type)
		{
		case kTypeBool:
			{
				u8 uBool = 0;
				if (!a_Stream.ReadU8(uBool).good())
				{
					return false;
				}
				Value.Bool = uBool != 0;
				if (uBool != 0 && uBool != 1)
				{
					return false;
				}
			}
			break;
		case kTypeN8:
		case kTypeU8:
			if (!a_Stream.ReadU8(Value.U8).good())
			{
				return false;
			}
			break;
		case kTypeN16:
		case kTypeU16:
			if (!a_Stream.ReadU16(Value.U16, a_bLittleEndian).good())
			{
				return false;
			}
			break;
		case kTypeN32:
		case kTypeU32:
		case kTypeF32:
			if (!a_Stream.ReadU32(Value.U32, a_bLittleEndian).good())
			{
				return false;
			}
			break;
		case kTypeN64:
		case kTypeU64:
		case kTypeF64:
			if (!a_Stream.ReadU64(Value.U64, a_bLittleEndian).good())
			{
				return false;
			}
			break;
		default:
			return false;
		}
		return true;
	}
};

#endif	// BASICTYPE_H_
