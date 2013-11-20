/**
 * (c) 2013 Andrew Payne. All rights reserved.
 */
#include "Property.h"

using namespace mojito;

const Property Property::Default = Property();

Property::Property()
: m_type(Type_None)
{
}

Property::Property(const Property& other)
: m_type(other.m_type)
{
	*this = other;
}

Property::Property(float floatVal)
: m_type(Type_Float)
{
	m_value.floatVal = floatVal;
}

Property::Property(int intVal)
: m_type(Type_Integer)
{
	m_value.intVal = intVal;
}

Property::Property(unsigned int intVal)
: m_type(Type_Integer)
{
	m_value.intVal = intVal;
}

Property::Property(const char* strVal)
: m_type(Type_String)
{
	if (NULL == strVal || 0 == *strVal)
	{
		m_type = Type_None;
		return;
	}
	size_t length = strlen(strVal);
	m_value.strVal = new char[ length + 1 ];
	strcpy(m_value.strVal, strVal);
}

Property::Property(const std::string& strVal)
: m_type(Type_String)
{
	if (strVal.empty())
	{
		m_type = Type_None;
		return;
	}
	m_value.strVal = new char[ strVal.size() + 1 ];
	strcpy(m_value.strVal, strVal.c_str());
}

Property::Property(bool boolVal)
: m_type(Type_Boolean)
{
	m_value.boolVal = boolVal;
}

Property::Property(void* ptrVal)
: m_type(Type_Pointer)
{
	m_value.ptrVal = ptrVal;
}

Property::~Property()
{
	clear();
}

void Property::clear()
{
	if (m_type == Type_String)
		delete [] m_value.strVal;
	m_type = Type_None;
	m_value.intVal = 0;
}

bool Property::operator==(const Property& other)
{
	if (m_type != other.m_type)
		return false;
	switch (m_type)
	{
		case Type_String: return strcmp(m_value.strVal, other.m_value.strVal) == 0;
		case Type_Boolean: return m_value.boolVal == other.m_value.boolVal;
		case Type_Integer: return m_value.intVal == other.m_value.intVal;
		case Type_Float: return m_value.floatVal == other.m_value.floatVal;
		case Type_Pointer: return m_value.ptrVal == other.m_value.ptrVal;
		case Type_None: return false;
	}
	return false;
}

bool Property::operator!=(const Property& other)
{
	if (m_type != other.m_type)
		return true;
	switch (m_type)
	{
		case Type_String: return strcmp(m_value.strVal, other.m_value.strVal) != 0;
		case Type_Boolean: return m_value.boolVal != other.m_value.boolVal;
		case Type_Integer: return m_value.intVal != other.m_value.intVal;
		case Type_Float: return m_value.floatVal != other.m_value.floatVal;
		case Type_Pointer: return m_value.ptrVal != other.m_value.ptrVal;
		case Type_None: return false;
	}
	return false;
}

Property::operator float () const
{
	if (Type_Float == m_type)
		return m_value.floatVal;
	else if (Type_Integer)
		return (float) m_value.intVal;
	return 0.0f;
}

Property::operator int () const
{
	if (Type_Integer == m_type)
		return m_value.intVal;
	else if (Type_Float == m_type)
		return (int)m_value.floatVal;
	return 0;
}

Property::operator unsigned int () const
{
	if (Type_Integer == m_type)
		return (unsigned int) m_value.intVal;
	else if (Type_Float == m_type)
		return (unsigned int)m_value.floatVal;
	return 0;
}

Property::operator const char* () const
{
	if (Type_String == m_type)
		return m_value.strVal;
	return "";
}

Property::operator std::string () const
{
	if (Type_String == m_type)
		return m_value.strVal;
	return "";
}

Property::operator Label () const
{
	if (Type_String == m_type)
		return Label::FromString(m_value.strVal);
	return Label::Null;
}

Property::operator bool () const
{
	if (Type_Boolean == m_type)
		return m_value.boolVal;
	return false;
}

Property::operator void*() const
{
	if (Type_Pointer == m_type)
		return m_value.ptrVal;
	return NULL;
}

Property& Property::operator=(const Property& other)
{
	clear();
	m_type = other.m_type;
	switch (m_type)
	{
	case Type_String:
	{
		size_t len = strlen(other.m_value.strVal);
		m_value.strVal = new char[ len + 1 ];
		strcpy(m_value.strVal, other.m_value.strVal);
		break;
	}
	case Type_Float:
		m_value.floatVal = other.m_value.floatVal;
		break;
	case Type_Integer:
		m_value.intVal = other.m_value.intVal;
		break;
	case Type_Boolean:
		m_value.boolVal = other.m_value.boolVal;
		break;
	case Type_Pointer:
		m_value.ptrVal = other.m_value.ptrVal;
	case Type_None:
		break;
	}
	return *this;
}

Property& Property::operator=(float floatVal)
{
	clear();	
	m_value.floatVal = floatVal;
	m_type = Type_Float;
	return *this;
}

Property& Property::operator=(int intVal)
{
	clear();	
	m_value.intVal = intVal;
	m_type = Type_Integer;
	return *this;
}

Property& Property::operator=(unsigned int intVal)
{
	clear();	
	m_value.intVal = (int) intVal;
	m_type = Type_Integer;
	return *this;
}

Property& Property::operator=(const char* strVal)
{
	clear();	
	
	if (NULL == strVal || 0 == *strVal)
	{
		m_type = Type_None;
		return *this;
	}
	size_t length = strlen(strVal);
	m_value.strVal = new char[ length + 1 ];
	strcpy(m_value.strVal, strVal);
	m_type = Type_String;
	return *this;
}

Property& Property::operator=(const std::string& strVal)
{
	clear();	
	
	if (strVal.empty())
	{
		m_type = Type_None;
		return *this;
	}
	m_value.strVal = new char[ strVal.size() + 1 ];
	strcpy(m_value.strVal, strVal.c_str());
	m_type = Type_String;
	return *this;
}

Property& Property::operator=(bool boolVal)
{
	clear();	
	m_value.boolVal = boolVal;
	m_type = Type_Boolean;
	return *this;
}

Property& Property::operator=(void* ptrVal)
{
	clear();
	m_value.ptrVal = ptrVal;
	m_type = Type_Pointer;
	return *this;
}

