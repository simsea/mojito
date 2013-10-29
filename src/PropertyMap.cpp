/**
 * (c) 2013 Andrew Payne. All rights reserved.
 */
#include "PropertyMap.h"

using namespace mojito;

PropertyMap::~PropertyMap()
{
	m_properties.clear();
}

void PropertyMap::setProperty(const Label& name, const Property& value)
{
	m_properties[ name ] = value;
}

bool PropertyMap::hasProperty(const Label& name) const
{
	auto iter = m_properties.find( name );
	return m_properties.end() != iter;
}

const Property& PropertyMap::getProperty(const Label& name) const
{
	auto iter = m_properties.find( name );
	if (m_properties.end() == iter)
		return Property::Default;
	return iter->second;
}

void PropertyMap::removeProperty(const Label& name)
{
	auto iter = m_properties.find( name );
	if (m_properties.end() == iter)
		return;
	m_properties.erase(iter);
}

std::set<Label> PropertyMap::getKeys() const
{
	std::set<Label>	keys;
	for (auto iter = m_properties.begin(); iter != m_properties.end(); ++iter)
		keys.insert(iter->first);
	return keys;
}

