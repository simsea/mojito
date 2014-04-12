/**
 * (c) 2013 Andrew Payne. All rights reserved.
 */
#ifndef _MOJITO_PROCESSOR_H_
#define _MOJITO_PROCESSOR_H_

#include "Entity.h"
#include "Filter.h"
#include "Message.h"

namespace mojito
{
	/**
	 * @brief Base class for processors (behaviours)
	 * @details Component is a data-only structure, so processing is left to the
	 * processor implementations
	 */
	class Processor : public IMessageHandler
	{
	public:
		/**
		 * Constructor with filter specification
		 * @param filter a filter specification that details the subset of Entities that 
		 * this processor will operate on
		 */
		Processor(const Filter& filter);
		virtual ~Processor();
		
		/**
		 * do the actions for the processor
		 * @param dt update delta time in seconds
		 */
		void process(float dt);
		/**
		 * process the entities that the processor is interested in
		 * @param dt update delta time in seconds
		 * @param entities a list of entities
		 */
		virtual void processEntities(float dt, const std::set<Entity*>& entities) = 0;
		/**
		 * IMessageHandler messaging interface
		 * @param message the message received
		 */
		virtual void handleMessage(const Message& /*message*/) { }
		
		/**
		 * get the entity manager that this processor is operating within
		 * @return EntityManager
		 */
		EntityManager* getManager() const { return m_manager; }

	private:
		Filter m_filter;
		EntityManager* m_manager;

		friend class EntityManager;
	};
}

#endif

