/**
 * (c) 2013 Andrew Payne. All rights reserved.
 */
#ifndef _MOJITO_PROPERTY_H_
#define _MOJITO_PROPERTY_H_

#include "Platform.h"
#include "Label.h"

namespace mojito
{
	/**
	 * @brief Aligned property store
	 */
	class Property
	{
	private:
		union PropertyValue
		{
			float floatVal;
			int intVal;
			char* strVal;
			bool boolVal;
		};
		
		enum PropertyType
		{
			Type_None,
			Type_Float,
			Type_Integer,
			Type_String,
			Type_Boolean,
		};
		
	public:
		/**
		 * Constructor
		 */
		Property();
		/**
		 * Copy constructor
		 * @param other the other Property to copy from
		 */
		Property(const Property& other);
		/**
		 * Constructor
		 * @param floatVal float value
		 */
		Property(float floatVal);
		/**
		 * Constructor
		 * @param intVal integer value
		 */
		Property(int intVal);
		/**
		 * Constructor
		 * @param intVal unsigned integer value
		 */
		Property(unsigned int intVal);
		/**
		 * Constructor
		 * @param strVal c-string value
		 */
		Property(const char* strVal);
		/**
		 * Constructor
		 * @param strVal std::string value
		 */
		Property(const std::string& strVal);
		/**
		 * Constructor
		 * @param boolVal boolean value
		 */
		Property(bool boolVal);
		// destructor
		~Property();
		
		/**
		 * float casting operator
		 * @return Property as a float
		 */
		operator float () const;
		/**
		 * integer casting operator
		 * @return Property as an int
		 */
		operator int () const;
		/**
		 * unsigned integer casting operator
		 * @return Property as an unsigned int
		 */
		operator unsigned int () const;
		/**
		 * c-string casting operator
		 * @return Property as a c-string
		 */
		operator const char* () const;
		/**
		 * string casting operator
		 * @return Property as a string
		 */
		operator std::string () const;
		/**
		 * Label casting operator
		 * @return Property as a Label
		 */
		operator Label () const;
		/**
		 * boolean casting operator
		 * @return Property as a bool
		 */
		operator bool () const;
		
		/**
		 * equality operator
		 * @param other the other Property
		 * @return true if Properties represent the same value, false otherwise
		 */
		bool operator==(const Property& other);
		/**
		 * inequality operator
		 * @param other the other Property
		 * @return true if Properties represent different values, false otherwise
		 */
		bool operator!=(const Property& other);
		
		/**
		 * assignment operator
		 * @param other another property to copy from
		 * @return this
		 */
		Property& operator=(const Property& other);
		/**
		 * assignment operator
		 * @param floatVal a float value
		 * @return this
		 */
		Property& operator=(float floatVal);
		/**
		 * assignment operator
		 * @param intVal an integer value
		 * @return this
		 */
		Property& operator=(int intVal);
		/**
		 * assignment operator
		 * @param intVal an unsigned integer value
		 * @return this
		 */
		Property& operator=(unsigned int intVal);
		/**
		 * assignment operator
		 * @param strVal a c-string value
		 * @return this
		 */
		Property& operator=(const char* strVal);
		/**
		 * assignment operator
		 * @param strVal a string value
		 * @return this
		 */
		Property& operator=(const std::string& strVal);
		/**
		 * assignment operator
		 * @param boolVal a boolean value
		 * @return this
		 */
		Property& operator=(bool boolVal);
		
		/** Constant default Property */
		static const Property Default;
	
	private:
		void clear();

		PropertyType m_type;
		PropertyValue m_value;
	};
}

#endif

