/**
 * (c) 2013 Andrew Payne. All rights reserved.
 */
#ifndef _MOJITO_COMPONENT_H_
#define _MOJITO_COMPONENT_H_

#include "Crc.h"
#include "Label.h"
#include "Lifecycle.h"
#include "PropertyMap.h"

namespace mojito
{
	/**
	 * @brief Base class for all components
	 * @details Mojito is an entity/component model. This is the 
	 * base class for all components. Components implement a basic RTTI like 
	 * strategy for object interrogation. Therefore, derived classes should use 
	 * the provided macros DECLARE_COMPONENT and DEFINE_COMPONENT to provided
	 * the correct override type information.
	 * @code{.cpp}
	 * // header
	 * class MyComponent : public Component
	 * {
	 * public:
	 *		DECLARE_COMPONENT(MyComponent, Component);
	 *		...
	 * };
	 *
	 * // cpp
	 * DEFINE_COMPONENT(MyComponent)
	 * ...
	 * @endcode
	 * It is also suggested that, for convenience, sub classes also typedef 
	 * their own std::shared_ptr type in their header file.
	 * @code{.cpp}
	 * typedef std::shared_ptr<MyComponent> SharedMyComponent;
	 * @endcode
	 */
	class Component
	{
	protected:
		Component();
	public:
		virtual ~Component() {}

		// base-class versions of derived information
		/** Component class Type id */
		static const Id TypeId;
		/** Component class Type name */
		static const Label TypeName;
		
		// -- RTTI-like base code --
		/**
		 * Get the type id assocated with the object
		 * @return class TypeId
		 */
		virtual Id getTypeId() const { return TypeId; }
		/**
		 * Get the type name assocated with the object
		 * @return class TypeName
		 */
		virtual Label getTypeName() const { return TypeName; }
		/**
		 * Check if an object is derived from a given type id
		 * @param typeId the type id to check against
		 * @return true if the object is or is derived from the type specified by typeId
		 */
		virtual bool isDerivedFrom(Id typeId) const { return TypeId == typeId; }
		
		/**
		 * get the id of the entity to which this component is attached
		 * @return entity Id
		 */
		Id getEntityId() const { return m_entityId; }
		
	private:		
		Id m_entityId;
		// intrusive storage
		std::shared_ptr<Component> m_prev;
		std::shared_ptr<Component> m_next;

		friend class Entity;
	};
	
	/**
	 * Shared pointer for Component
	 */
	typedef std::shared_ptr< Component > SharedComponent;
}

#define DECLARE_COMPONENT(Name, Parent) \
public:\
static const Id TypeId; \
static const mojito::Label TypeName; \
virtual bool isDerivedFrom(Id typeId) const { \
return TypeId == typeId ? true : Parent::isDerivedFrom(typeId); } \
virtual Id getTypeId() const { return TypeId; } \
virtual mojito::Label getTypeName() const { return TypeName; }


#define DEFINE_COMPONENT(Name) \
const Id Name::TypeId = mojito::crc32(#Name); \
const mojito::Label Name::TypeName = mojito::Label::FromString(#Name);

#endif

