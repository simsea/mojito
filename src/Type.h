/**
 * (c) 2013 Andrew Payne. All rights reserved.
 */
#ifndef _MOJITO_TYPE_H_
#define _MOJITO_TYPE_H_

#include "Platform.h"

namespace mojito
{
	struct Type
	{
		uint32_t typeId;
		const Type* parent;
		
		static const Type Null;
		
		Type()
		: typeId(0)
		, parent(NULL)
		{
		}
		
		Type(uint32_t typeId, const Type* parent)
		: typeId(typeId)
		, parent(parent)
		{
		}
		
		bool isDerivedFrom(const Type& other) const
		{
			if (other.typeId == typeId)
				return true;
			if (NULL != parent)
				return parent->isDerivedFrom(other);
			return false;
		}
		
		bool operator==(const Type& other) const
		{
			return typeId == other.typeId;
		}
		
		bool operator!=(const Type& other) const
		{
			return typeId != other.typeId;
		}
		
		bool operator<(const Type& other) const
		{
			return typeId < other.typeId;
		}
		
		bool operator>(const Type& other) const
		{
			return typeId > other.typeId;
		}
	};
}

template <>
struct std::__1::hash<mojito::Type> : public unary_function<mojito::Type, size_t>
{
	size_t operator()(mojito::Type __v) const { return static_cast<unsigned int>(__v.typeId); }
};

#endif
