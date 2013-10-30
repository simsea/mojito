/**
 * (c) 2013 Andrew Payne. All rights reserved.
 */
#ifndef _MOJITO_FILTER_H_
#define _MOJITO_FILTER_H_

#include "Platform.h"

namespace mojito
{
	/**
	 * @brief class used to filter entities based on Component content
	 * @details the EntityManager can return a list of entities based on
	 * the Components attached to the Entity. The Filter class is used to
	 * instruct the EntityManager about how to filter the list of returned
	 * Entities.
	 */
	class Filter
	{
	public:
		Filter();
		~Filter();
		
		/**
		 * Add a condition to the filter that any Entity returned must contain
		 * all of the Component types listed
		 * @param values the Component::TypeId values
		 * @return this
		 */
		Filter& all(std::initializer_list<Id> values);
		/**
		 * Add a condition that any Entity returned must not contain the 
		 * Component types listed
		 * @param values the Component::TypeId values
		 * @return this
		 */
		Filter& except(std::initializer_list<Id> values);
		/**
		 * Add a condition that any Entity returned must contain at least one
		 * of the Component types listed
		 * @param values the Component::TypeId values
		 * @return this
		 */
		Filter& one(std::initializer_list<Id> values);
		
		/**
		 * get the set of "All" conditions
		 * @return the set of "All" conditions
		 */
		const std::set<Id>& getAll() const { return m_all; }
		/**
		 * get the set of "Except" conditions
		 * @return the set of "Except" conditions
		 */
		const std::set<Id>& getExcept() const { return m_except; }
		/**
		 * get the set of "One Of" conditions
		 * @return the set of "One Of" conditions
		 */
		const std::set<Id>& getOne() const { return m_one; }
		
	private:
		std::set<Id> m_all;
		std::set<Id> m_except;
		std::set<Id> m_one;
	};
}

#endif

