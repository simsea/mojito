/**
 * (c) 2013 Andrew Payne. All rights reserved.
 */
#ifndef _MOJITO_ENTITY_MANAGER_H_
#define _MOJITO_ENTITY_MANAGER_H_

#include "Platform.h"
#include "Entity.h"
#include "Filter.h"
#include "Message.h"
#include "Processor.h"

namespace mojito
{
	/**
	 * @brief class to manage life cycle of all entities created in the world
	 * @details 
	 */
	class EntityManager : public IMessageDispatcher
	{
	public:
		EntityManager();
		virtual ~EntityManager();

		/**
		 * update the entity manager
		 * @param dt delta time in seconds
		 */
		void update(float dt);
		
		/**
		 * Create an entity in the EntityManager
		 * @return the shared pointer to the entity
		 */
		Entity* createEntity();
		/**
		 * Destroy an entity
		 * @param entityId the id of the entity to destroy
		 */
		void destroyEntity(const EntityId& entityId);
		/**
		 * Get an entity by id
		 * @param entityId entity id
		 * @return the shared pointer to the entity, or NULL if none can be found
		 */
		Entity* getEntityById(const EntityId& entityId) const;
		/**
		 * Get entities using an entity type filter
		 * @param filter the filter
		 */
		std::set<Entity*> getEntities(const Filter& filter);

		/**
		 * Add a processor.
		 * @param processor the processor to add
		 */
		void addProcessor(Processor* processor);

		/**
		 * IMessageDispatcher message interface
		 * @param message the message to dispatch
		 */
		void dispatchMessage(const Message& message);

		/**
		 * add a message handler
		 * @param handler message handler
		 */
		void addMessageHandler(IMessageHandler* handler);
		
		/**
		 * remove a message handler
		 * @param handler message handler
		 */
		void removeMessageHandler(IMessageHandler* handler);
		
		/**
		 * Get the number of entities currently in the system
		 * @return number of entities (acitve and inactive)
		 */
		uint32_t getEntityCount() const;
		
		/**
		 * Get the number of active entities currently in the system
		 * @return active entity count
		 */
		uint32_t getActiveEntityCount() const;
		
		/**
		 * release all currently managed entity objects
		 */
		void releaseAll();
		
	private:
		void registerComponent(const Type& typeId, const EntityId& entityId);
		void unregisterComponent(const Type& typeId, const EntityId& entityId);
		
		void getEntities(const Type& typeId, std::set<Entity*>& entities);
		
		HashMap<EntityId, Entity*> m_entities;
		HashMap<Type, HashSet< Entity* > > m_componentTypeToEntities;
		std::vector< Processor* > m_processors;
		std::vector< IMessageHandler* > m_handlers;
		std::vector< Entity* > m_entitiesToDestroy;
		uint32_t m_nextId;
		
		friend class Entity;
	};
}

#endif

