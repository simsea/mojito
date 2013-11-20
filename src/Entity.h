/**
 * (c) 2013 Andrew Payne. All rights reserved.
 */
#ifndef _MOJITO_ENTITY_H_
#define _MOJITO_ENTITY_H_

#include "Platform.h"
#include "Component.h"
#include "Lifecycle.h"
#include "PropertyMap.h"

namespace mojito
{
	class EntityManager;

	/**
	 * @brief Rules engine Entity class. 
	 * @details All game objects are Entities. Entities are component stores and
	 * arbitrary property maps. Components created on an entity can read and 
	 * write values into the Entity property store. Behaviour of game objects is
	 * determined by Component attachment.
	 */
	class Entity : public PropertyMap
	{
	public:
		~Entity();

		/** Entity creation message label */
		static const Label Created;
		/** Entity destruction message label */
		static const Label Destroyed;
		/** Entity modification message label */
		static const Label Modified;
		
		/**
		 * Add a component of type T into the Entity. There can only be one of a
		 * given component type in the Entity at the same time.
		 * @tparam T the type of the Component derived class
		 * @return the newly created Component shared pointer of type T
		 */
		template< class T > std::shared_ptr< T > addComponent();
		/**
		 * Remove a component of a given type from the Entity
		 * @tparam T the type of the Component derived class
		 */
		template< class T > void removeComponent();
		/**
		 * Check if a component of a type exists in the Entity
		 * @tparam T the type of the Component derived class
		 * @return true if a type derived from T exists, false otherwise
		 */
		template< class T > bool hasComponent() const;
		/**
		 * Get a component of a given type
		 * @tparam T the type of the Component derived class
		 * @return a shared pointer to the Component, or NULL if one does not exist
		 */
		template< class T > std::shared_ptr< T > getComponent() const;
		/**
		 * Get all of the components derived from a given type
		 * @tparam T the type of the Component derived class
		 * @return a vector of shared pointers of Component objects that match
		 */
		template< class T > std::vector< std::shared_ptr< T > > getComponents() const;

		/**
		 * Get the id of the Entity
		 * @return id
		 */
		Id getId() const { return m_id; }
		
		/**
		 * check if an entity is enabled or not
		 * @return true if enabled, false otherwise
		 */
		bool isEnabled() const { return Lifecycle_Enabled == m_state; }
		
		/**
		 * Mark entity as enabled or disabled
		 * @param enabled true for enabled, false for disabled
		 */
		void setEnabled(bool enabled);
		
		/**
		 * get the EntityManager that this entity is associated with
		 * @return EntityManager
		 */
		EntityManager* getManager() const { return m_manager; }

	private:
		Entity();

		void registerComponent(Id typeId);
		void unregisterComponent(Id typeId);
		
		Id m_id;
		EntityManager* m_manager;
		SharedComponent m_components;
		Lifecycle m_state;

		friend class EntityManager;
	};
	
	/** Shared pointer type for Entity */
	typedef std::shared_ptr< Entity > SharedEntity;

	template< class T >
	inline std::shared_ptr<T> Entity::addComponent()
	{
		std::shared_ptr<T> component = getComponent<T>();
		if (nullptr == component)
		{
			component = std::make_shared<T>(T());
			component->m_entityId = getId();
			if (nullptr != m_components)
				m_components->m_prev = component;
			component->m_next = m_components;
			m_components = component;
			registerComponent(T::TypeId);
		}
		return component;
	}

	template< class T >
	inline void Entity::removeComponent()
	{
		SharedComponent cur = m_components;
		while (nullptr != cur)
		{
			if (cur->isDerivedFrom(T::TypeId))
			{
				if (nullptr == cur->m_prev)
					m_components = cur->m_next;
				else
					cur->m_prev->m_next = cur->m_next;
				unregisterComponent(T::TypeId);
				break;
			}
			cur = cur->m_next;
		}
	}

	template< class T > 
	inline bool Entity::hasComponent() const
	{
		return nullptr != getComponent<T>();				
	}

	template< class T>
	inline std::shared_ptr<T> Entity::getComponent() const
	{	
		SharedComponent cur = m_components;
		while (nullptr != cur)
		{
			if (cur->isDerivedFrom(T::TypeId))
				return std::static_pointer_cast<T>(cur);
			cur = cur->m_next;
		}
		return nullptr;
	}

	template< class T > 
	inline std::vector< std::shared_ptr<T> > Entity::getComponents() const
	{
		std::vector<T*> entities;
		SharedComponent cur = m_components;
		while (nullptr != cur)
		{
			if (cur->isDerivedFrom(T::TypeId))
				entities.push_back( std::static_pointer_cast< T >(cur) );
			cur = cur->m_next;
		}
		return entities;
	}
}

#endif

