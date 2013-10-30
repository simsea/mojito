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
		~EntityManager();

		/**
		 * update the entity manager
		 * @param dt delta time in seconds
		 */
		void update(float dt);
		
		/**
		 * Create an entity in the EntityManager
		 * @return the shared pointer to the entity
		 */
		SharedEntity createEntity();
		/**
		 * Destroy an entity
		 * @param entityId the id of the entity to destroy
		 */
		void destroyEntity(Id entityId);
		/**
		 * Get an entity by id
		 * @param entityId entity id
		 * @return the shared pointer to the entity, or NULL if none can be found
		 */
		SharedEntity getEntityById(Id entityId) const;
		/**
		 * Get entities using an entity type filter
		 * @param filter the filter
		 */
		std::set<SharedEntity> getEntities(const Filter& filter);

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
		
	private:
		void releaseAll();
		void registerComponent(Id typeId, Id entityId);
		void unregisterComponent(Id typeId, Id entityId);
		
		std::map<Id, SharedEntity> m_entities;
		std::map<Id, std::set< SharedEntity > > m_componentTypeToEntities;
		std::vector< Processor* > m_processors;
		std::vector< IMessageHandler* > m_handlers;
		Id m_nextId;
		
		friend class Entity;
	};
}

#endif

