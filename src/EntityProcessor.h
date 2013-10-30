/**
 * (c) 2013 Andrew Payne. All rights reserved.
 */
#ifndef _MOJITO_ENTITY_PROCESSOR_H_
#define _MOJITO_ENTITY_PROCESSOR_H_

#include "Processor.h"

namespace mojito
{
	/**
	 * @brief Entity processor specialization
	 * @details Processor specialization that processes specific filtered entity lists.
	 * Child classes of EntityProcessor must implement the process method
	 */
	class EntityProcessor : public Processor
	{
	public:
		/**
		 * Constructor with filter specification
		 * @param filter a filter specification that details the subset of Entities that 
		 * this processor will operate on
		 */
		EntityProcessor(const Filter& filter);
		virtual ~EntityProcessor();
		
		/**
		 * process an entity that this processor is interested in
		 * @param dt update delta time in seconds
		 * @param entity the entity
		 */
		virtual void processEntity(float dt, SharedEntity entity) = 0;
		void processEntities(float dt, const std::set<SharedEntity>& entities);
		
	private:
		
	};
}

#endif

