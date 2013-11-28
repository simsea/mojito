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
		Id typeId;
		const Type* parent;
		
		Type()
		{
			typeId = 0;
			parent = NULL;
		}
		
		Type(Id typeId, const Type* parent)
		{
			this->typeId = typeId;
			this->parent = parent;
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
		
		bool operator<(const Type& other) const
		{
			return typeId < other.typeId;
		}
	};
}

#endif
