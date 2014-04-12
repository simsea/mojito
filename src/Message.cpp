/**
 * (c) 2013 Andrew Payne. All rights reserved.
 */
#include "Message.h"

using namespace mojito;

Message::Message(Label type, const EntityId& entityId)
: m_type(type)
, m_entityId(entityId)
{
}

Message::Message(Label type, Entity* entity)
: m_type(type)
, m_entityId(nullptr == entity ? 0 : entity->getId())
{
}

Message::~Message()
{
}

Message* Message::clone() const
{
	return new Message(m_type, m_entityId);
}

Message& Message::set(Label key, const Property& value)
{
	setProperty(key, value);
	return *this;
}

