/**
 * (c) 2013 Andrew Payne. All rights reserved.
 */
#include "Message.h"

using namespace mojito;

Message::Message(Label type, SharedEntity entity)
: m_type(type)
, m_entity(entity)
{
}

Message::~Message()
{
}

Message* Message::clone() const
{
	return new Message(m_type, m_entity);
}

Message& Message::set(Label key, const Property& value)
{
	setProperty(key, value);
	return *this;
}

