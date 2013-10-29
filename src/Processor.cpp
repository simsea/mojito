/**
 * (c) 2013 Andrew Payne. All rights reserved.
 */
#include "Processor.h"
#include "EntityManager.h"

using namespace mojito;

Processor::Processor(const Filter& filter)
: m_filter(filter)
, m_manager(NULL)
{
}

Processor::~Processor()
{
}

void Processor::process(float dt)
{
	if (NULL == m_manager)
		return;
	// find the entities that this processor is interested in
	std::set<SharedEntity> entities = m_manager->getEntities(m_filter);
	processEntities(dt, entities);
}

