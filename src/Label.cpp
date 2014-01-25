/**
 * (c) 2013 Andrew Payne. All rights reserved.
 */
#include "Label.h"
#include "Utils.h"

#define USE_STACK_BUFFER
#define BUFFER_SIZE (512 * 1024)

using namespace mojito;

namespace
{
	class StringInternPool
	{
	public:
		StringInternPool()
		{
#ifdef USE_STACK_BUFFER
			m_next = &m_buffer[0];
#endif
		}
		
		~StringInternPool()
		{
			for (auto iter = m_map.begin(); iter != m_map.end(); ++iter)
				freeString( iter->second );
		}
		
		char* getUniqueString(const char* str)
		{
			if (NULL == str || 0 == *str)
				return NULL;
			auto iter = m_map.find(str);
			if (m_map.end() != iter)
				return iter->second;
			// add a new one
			char* unique = duplicateString(str);
			m_map[ unique ] = unique;
			return unique;
		}
		
	private:
		char* duplicateString(const char* str)
		{
			if (NULL == str)
				return NULL;
			size_t len = strlen(str) + 1;
			char* dupe = NULL;
#ifdef USE_STACK_BUFFER
			char* upper = &m_buffer[ sizeof(m_buffer) ];
			if (m_next + len < upper)
			{
				dupe = m_next;
				m_next += len;
			}
#endif
			if (NULL == dupe)
				dupe = new char[ len ];
			strcpy(dupe, str);
			return dupe;
		}
		
		void freeString(char* str)
		{
#ifdef USE_STACK_BUFFER
			char* lower = &m_buffer[0];
			char* upper = &m_buffer[ sizeof(m_buffer) ];
			if (str < lower || str >= upper)
				delete [] str;
#else
			delete [] str;
#endif
		}
		
		std::map< const char*, char*, CaseInsensitiveComparator > m_map;
#ifdef USE_STACK_BUFFER
		char m_buffer[ BUFFER_SIZE ];
		char* m_next;
#endif
	};
	
	StringInternPool* GetPool()
	{
		static StringInternPool pool;
		return &pool;
	}
}

const Label Label::Null = Label::Label();

Label::Label()
: m_ref(NULL)
{
}

Label::Label(char* ref)
: m_ref(ref)
{

}

Label::Label(const Label& other)
: m_ref(other.m_ref)
{
	
}

Label::~Label()
{

}

Label& Label::operator=(const Label& other)
{
	m_ref = other.m_ref;
	return *this;
}

/*static*/ Label Label::FromString(const char* str)
{
	if (NULL == str || 0 == *str)
		return Label::Null;
	char* unique = GetPool()->getUniqueString(str);
	return Label(unique);
}

/*static*/ Label Label::FromString(const std::string& str)
{
	if (str.empty())
		return Label::Null;
	char* unique = GetPool()->getUniqueString(str.c_str());
	return Label(unique);
}

