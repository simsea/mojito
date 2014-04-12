/**
 * (c) 2013 Andrew Payne. All rights reserved.
 */
#ifndef _MOJITO_ENTITY_ID_H_
#define _MOJITO_ENTITY_ID_H_

#include "Platform.h"

namespace mojito
{
	struct EntityId
	{
		uint32_t id;
		EntityId() { id = 0; }
		EntityId(uint32_t id) { this->id = id; }
		bool operator==(const EntityId& other) const { return other.id == id; }
		bool operator!=(const EntityId& other) const { return other.id != id; }
		bool operator<(const EntityId& other) const { return other.id < id; }
		bool operator>(const EntityId& other) const { return other.id > id; }
		EntityId(const EntityId& other) { id = other.id; }
		EntityId& operator=(const EntityId& other) { id = other.id; return *this; }
		static const EntityId Null;
	};
}

template <>
struct std::__1::hash<mojito::EntityId> : public unary_function<mojito::EntityId, size_t>
{
	size_t operator()(mojito::EntityId __v) const { return static_cast<unsigned int>(__v.id); }
};

#endif
