/**
 * (c) 2013 Andrew Payne. All rights reserved.
 */
#include "Filter.h"

using namespace mojito;

Filter::Filter()
{
}

Filter::~Filter()
{
}

Filter& Filter::all(std::initializer_list<Id> values)
{
	for (auto& value : values)
		m_all.insert(value);
	return *this;
}

Filter& Filter::except(std::initializer_list<Id> values)
{
	for (auto& value : values)
		m_except.insert(value);
	return *this;
}

Filter& Filter::one(std::initializer_list<Id> values)
{
	for (auto& value : values)
		m_one.insert(value);
	return *this;
}

