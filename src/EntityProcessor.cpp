/**
 * (c) 2013 Andrew Payne. All rights reserved.
 */
#include "EntityProcessor.h"

using namespace mojito;

EntityProcessor::EntityProcessor(const Filter& filter)
: Processor(filter)
{
}

EntityProcessor::~EntityProcessor()
{
}

void EntityProcessor::processEntities(float dt, const std::set<SharedEntity>& entities)
{
	for (auto iter = entities.begin(); iter != entities.end(); ++iter)
		processEntity(dt, *iter);
}

