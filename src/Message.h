/**
 * (c) 2013 Andrew Payne. All rights reserved.
 */
#ifndef _MOJITO_MESSAGE_H_
#define _MOJITO_MESSAGE_H_

#include "Platform.h"
#include "Label.h"
#include "PropertyMap.h"
#include "Entity.h"

namespace mojito
{
	/**
	 * @brief Entity messages
	 * @details Message can carry simple type payloads in key/value pairs (see PropertyMap)
	 */
	class Message : public PropertyMap
	{
	public:
		Message() { }
		/**
		 * Constructor
		 * @param type the type of the message
		 * @param entity the shared pointer of the entity that this message relates to
		 */
		Message(Label type, SharedEntity entity);
		~Message();
		
		/**
		 * Get the type of the message determined by issuing context
		 * @return the type label for the message
		 */
		Label getType() const { return m_type; }
		/**
		 * Clone a message (derived classes should override this)
		 * @return a cloned copy of the message
		 */
		Message* clone() const;
		/**
		 * Get the entity payload
		 * @return entity
		 */
		SharedEntity getEntity() const { return m_entity; }
		
		/**
		 * In-line parameter set
		 * @param key the key for the value
		 * @param value the property
		 * @return this Message object
		 */
		Message& set(Label key, const Property& value);
		
	private:
		Message(const Message&) { }
		
		Label m_type;
		SharedEntity m_entity;
	};
	
	/**
	 * @brief Message handler interface
	 */
	class IMessageHandler
	{
	public:
		virtual ~IMessageHandler() { }
		/**
		 * handle a dispatched message (message will be deleted shortly thereafter.
		 * If you intend on holding on to the message, you should clone your own
		 * copy of the message)
		 * @param message the message to handle
		 */
		virtual void handleMessage(const Message& message) = 0;
	};

	/**
	 * @brief Message dispatcher interface
	 */
	class IMessageDispatcher
	{
	public:
		virtual ~IMessageDispatcher() { }
		/**
		 * dispatch a message
		 */
		virtual void dispatchMessage(const Message& message) = 0;
	};
}

#endif

