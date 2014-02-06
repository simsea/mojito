/**
 * (c) 2013 Andrew Payne. All rights reserved.
 */
#ifndef _MOJITO_PROPERTYMAP_H_
#define _MOJITO_PROPERTYMAP_H_

#include "Platform.h"
#include "Label.h"
#include "Property.h"

namespace mojito
{
	/**
	 * @brief Property map interface
	 */
	class IPropertyMap
	{
	public:
		virtual ~IPropertyMap() { }
		/** 
		 * @private
		 * Check to see if the map has a property of a given name
		 * @param name the name of the property
		 * @return true if the property 'name' exists, false otherwise
		 */
		virtual bool hasProperty(const Label& name) const = 0;
		/** 
		 * @private
		 * Get a property by its key name
		 * @param name the name of the property
		 * @return the Property for the key, or Property::Default if it doesn't exist
		 */
		virtual const Property& getProperty(const Label& name) const = 0;
		/**
		 * @private
		 * Set a property key/value pair
		 * @param name the name of the property
		 * @param value the property value
		 */
		virtual void setProperty(const Label& name, const Property& value) = 0;
		/**
		 * @private
		 * Remove a property completely from the property map
		 * @param name the name of the property
		 */
		virtual void removeProperty(const Label& name) = 0;
		/**
		 * @private
		 * get the keys set in the property map
		 * @return set of keys
		 */
		virtual std::set<Label> getKeys() const = 0;
	};
	
	// -------------------------------------------------------------------------

	/**
	 * @brief default implementation of the Property Map interface (IPropertyMap)
	 */
	class PropertyMap : public IPropertyMap
	{
	public:
		virtual ~PropertyMap();
		void setProperty(const Label& name, const Property& value);
		bool hasProperty(const Label& name) const;
		const Property& getProperty(const Label& name) const;
		const Property& getProperty(const Label& name, const Property& defaultValue) const;
		void removeProperty(const Label& name);
		std::set<Label> getKeys() const;

	private:
		std::map< Label, Property > m_properties;
	};
}

#endif

