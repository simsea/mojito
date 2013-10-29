/**
 * (c) 2013 Andrew Payne. All rights reserved.
 */
#include "Component.h"
#include "Entity.h"

using namespace mojito;

const Id Component::TypeId = crc32("Component");
const Label Component::TypeName = Label::FromString("Component");

Component::Component()
: m_entityId(0)
, m_prev(nullptr)
, m_next(nullptr)
{

}

