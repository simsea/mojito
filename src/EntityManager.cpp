/**
 * (c) 2013 Andrew Payne. All rights reserved.
 */
#include "EntityManager.h"
#include "Log.h"

using namespace mojito;

EntityManager::EntityManager()
: m_nextId(0)
{
}

EntityManager::~EntityManager()
{
	releaseAll();
	for (auto iter = m_entitiesToDestroy.begin(); iter != m_entitiesToDestroy.end(); ++iter)
		delete *iter;
	for (auto iter = m_processors.begin(); iter != m_processors.end(); ++iter)
		delete *iter;
}

Entity* EntityManager::createEntity()
{
	EntityId entityId = ++m_nextId;
	LOG_INFO("Creating Entity (%u)", entityId.id);
	Entity* entity = new Entity();
	entity->m_id = entityId;
	entity->m_manager = this;
	entity->m_state = Lifecycle_Enabled;
	m_entities[entityId] = entity;
	//dispatchMessage(Message(Entity::Created, entity));
	return entity;
}

void EntityManager::destroyEntity(const EntityId& entityId)
{
	auto iter = m_entities.find(entityId);
	if (m_entities.end() == iter)
		return;
	LOG_INFO("Destroying Entity (%u)", entityId.id);
	Entity* entity = iter->second;
	entity->m_state = Lifecycle_Destroyed;
	dispatchMessage(Message(Entity::Destroyed, entity));
	// remove component mappings
	for (auto citer = m_componentTypeToEntities.begin(); citer != m_componentTypeToEntities.end(); ++citer)
		citer->second.erase(entity);
	m_entities.erase(iter);
	m_entitiesToDestroy.push_back( entity );
}

void EntityManager::update(float dt)
{
	for (auto iter = m_entitiesToDestroy.begin(); iter != m_entitiesToDestroy.end(); ++iter)
		delete *iter;
	m_entitiesToDestroy.clear();
	
	for (auto iter = m_processors.begin(); iter != m_processors.end(); ++iter)
		(*iter)->process(dt);
}

void EntityManager::releaseAll()
{
	for (auto iter = m_entities.begin(); iter != m_entities.end(); ++iter)
	{
		dispatchMessage(Message(Entity::Destroyed, iter->second));
		m_entitiesToDestroy.push_back(iter->second);
	}
	// clear lists
	m_entities.clear();
	m_componentTypeToEntities.clear();
}

Entity* EntityManager::getEntityById(const EntityId& entityId) const
{
	auto iter = m_entities.find(entityId);
	if (m_entities.end() == iter)
		return nullptr;
	return iter->second;
}

void EntityManager::getEntities(const Type& id, std::set<Entity*>& entities)
{
	for (auto iter = m_componentTypeToEntities.begin(); iter != m_componentTypeToEntities.end(); ++iter)
	{
		if (iter->first.isDerivedFrom(id))
			entities.insert(iter->second.begin(), iter->second.end());
	}
}

std::set<Entity*> EntityManager::getEntities(const Filter& filter)
{
	std::set<Entity*> entities;
	if (!filter.getOne().empty())
	{
		for (auto& iter : filter.getOne())
			getEntities(iter, entities);
	}
	if (!filter.getAll().empty())
	{
		auto iter = filter.getAll().begin();
		Type typeId = *iter;
		std::set<Entity*> suspects;
		getEntities(typeId, suspects);
		if (!suspects.empty())
		{
			iter++;
			for (; iter != filter.getAll().end(); ++iter)
			{
				typeId = *iter;
				std::set<Entity*> ents;
				getEntities(typeId, ents);
				if (ents.empty())
				{
					suspects.clear();
					break;
				}
				std::set<Entity*> newSuspects;
				for (auto& siter : suspects)
				{
					if (ents.find(siter) != ents.end())
						newSuspects.insert(siter);
				}
				suspects = newSuspects;
			}
		}
		// if there's no "one of" requirement, add all these entities
		if (filter.getOne().empty())
			entities = suspects;
		else
		{
			std::set<Entity*> newEntities;
			// otherwise, we have to check that the entity exists in both sets
			for (auto iter = entities.begin(); iter != entities.end(); ++iter)
			{
				if (suspects.end() != suspects.find(*iter))
					newEntities.insert(*iter);
			}
			entities = newEntities;
		}
	}
	if (!filter.getExcept().empty())
	{
		std::set<Entity*> excluded;
		// add all entities that don't have those things in
		for (auto iter = m_componentTypeToEntities.begin(); iter != m_componentTypeToEntities.end(); ++iter)
		{
			for (auto fIter = filter.getExcept().begin(); fIter != filter.getExcept().end(); ++fIter)
			{
				if (fIter->isDerivedFrom(iter->first))
					excluded.insert(iter->second.begin(), iter->second.end());
			}
		}
		if (filter.getAll().empty() && filter.getOne().empty())
			entities = excluded;
		else
		{
			std::set<Entity*> newEntities;
			// otherwise, we have to check that the entity exists in both sets
			for (auto iter = entities.begin(); iter != entities.end(); ++iter)
			{
				if (excluded.end() != excluded.find(*iter))
					newEntities.insert(*iter);
			}
			entities = newEntities;
		}
	}
	return entities;
}

void EntityManager::registerComponent(const Type& typeId, const EntityId& entityId)
{
	Entity* entity = getEntityById(entityId);
	if (nullptr == entity)
		return;
	//LOG_INFO("registering component type %u for entity %u", typeId, entityId);
	m_componentTypeToEntities[typeId].insert(entity);
}

void EntityManager::unregisterComponent(const Type& typeId, const EntityId& entityId)
{
	Entity* entity = getEntityById(entityId);
	if (nullptr == entity)
		return;
	auto iter = m_componentTypeToEntities.find(typeId);
	if (m_componentTypeToEntities.end() == iter)
		return;
	iter->second.erase(entity);
}

void EntityManager::addProcessor(Processor* processor)
{
	if (NULL == processor || NULL != processor->m_manager)
		return;
	if (m_processors.end() != std::find(m_processors.begin(), m_processors.end(), processor))
		return;
	processor->m_manager = this;
	m_processors.push_back(processor);
}

void EntityManager::dispatchMessage(const Message& message)
{
	for (auto iter = m_handlers.begin(); iter != m_handlers.end(); ++iter)
		(*iter)->handleMessage( message );
}

void EntityManager::addMessageHandler(IMessageHandler* handler)
{
	if (NULL == handler)
		return;
	if (m_handlers.end() != std::find(m_handlers.begin(), m_handlers.end(), handler))
		return;
	m_handlers.push_back(handler);
}
		
void EntityManager::removeMessageHandler(IMessageHandler* handler)
{
	if (NULL == handler)
		return;
	auto iter = std::find(m_handlers.begin(), m_handlers.end(), handler);
	if (m_handlers.end() == iter)
		return;
	m_handlers.erase(iter);
}

uint32_t EntityManager::getEntityCount() const
{
	return (uint32_t) m_entities.size();
}

uint32_t EntityManager::getActiveEntityCount() const
{
	uint32_t result = 0;
	for (auto iter = m_entities.begin(); iter != m_entities.end(); ++iter)
		if (iter->second->isEnabled())
			result++;
	return result;
}


