/**
 * (c) 2013 Andrew Payne. All rights reserved.
 */
#ifndef _MOJITO_FILTER_H_
#define _MOJITO_FILTER_H_

#include "Platform.h"

namespace mojito
{
	class Filter
	{
	public:
		Filter();
		~Filter();
		
		Filter& all(std::initializer_list<Id> values);
		Filter& except(std::initializer_list<Id> values);
		Filter& one(std::initializer_list<Id> values);
		
		const std::set<Id>& getAll() const { return m_all; }
		const std::set<Id>& getExcept() const { return m_except; }
		const std::set<Id>& getOne() const { return m_one; }
		
	private:
		std::set<Id> m_all;
		std::set<Id> m_except;
		std::set<Id> m_one;
	};
}

#endif

