/**
 * (c) 2013 Andrew Payne. All rights reserved.
 */
#ifndef _MOJITO_ENTITY_PROCESSOR_H_
#define _MOJITO_ENTITY_PROCESSOR_H_

#include "Processor.h"

namespace mojito
{
	class EntityProcessor : public Processor
	{
	public:
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

