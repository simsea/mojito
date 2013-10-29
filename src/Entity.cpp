/**
 * (c) 2013 Andrew Payne. All rights reserved.
 */
#include "Entity.h"
#include "EntityManager.h"

using namespace mojito;

const Label Entity::Created = LABEL(Created);
const Label Entity::Destroyed = LABEL(Destroyed);
const Label Entity::Modified = LABEL(Modified);

Entity::Entity()
: m_id(0)
, m_manager(NULL)
, m_components(nullptr)
, m_state(Lifecycle_Created)
{
	
}

Entity::~Entity()
{
	m_components = nullptr;
}

void Entity::setEnabled(bool enabled)
{
	if (Lifecycle_Created == m_state || Lifecycle_Destroyed == m_state)
		return;
	m_state = enabled ? Lifecycle_Enabled : Lifecycle_Disabled;
}

void Entity::registerComponent(Id typeId)
{
	m_manager->registerComponent(typeId, m_id);
}

void Entity::unregisterComponent(Id typeId)
{
	m_manager->unregisterComponent(typeId, m_id);
}

