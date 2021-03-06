/**
 * (c) 2013 Andrew Payne. All rights reserved.
 */
#ifndef _MOJITO_LABEL_H_
#define _MOJITO_LABEL_H_

#include "Platform.h"

namespace mojito
{
	/**
	 * @brief string interning structure
	 * @details String interning. A Label will be case insensitive in compare, 
	 * but case preserving in construction.
	 * @code{.cpp}
	 * Label label0 = LABEL(THISLABEL);
	 * Label label1 = LABEL(thisLabel);
	 * printf("equal: %s\n", label0 == label1 ? "true" : "false"); // outputs "equal: true"
	 * printf("label0: %s\n", label0.toString()); // outputs: "THISLABEL"
	 * printf("label1: %s\n", label1.toString()); // outputs: "thisLabel"
	 * @endcode
	 */
	class Label
	{
	public:
		Label();
		/**
		 * Copy constructor
		 * @param other the Label to copy
		 */
		Label(const Label& other);
		~Label();

		/** Constant Null Label */
		static const Label Null;
		/**
		 * Factory method to construct a Label from a string
		 * @param str the string to convert
		 * @return a constructed Label with interned string
		 */
		static Label FromString(const char* str);
		/**
		 * Factory method to construct a Label from a string
		 * @param str the string to convert
		 * @return a constructed Label with interned string
		 */
		static Label FromString(const std::string& str);
		
		Label& operator=(const Label& other);
		friend bool operator==(const Label& label0, const Label& label1);
		friend bool operator!=(const Label& label0, const Label& label1);
		friend bool operator<(const Label& label0, const Label& label1);
		friend bool operator>(const Label& label0, const Label& label1);
		
		/**
		 * get the internal case-preserved c-string value
		 * @return c-string value
		 */
		const char* toString() const { return m_ref; }
		/**
		 * get the internal case-preserved c-string value
		 * @return c-string value
		 */
		const char* c_str() const { return m_ref; }
	
	private:
		Label(char* ref);
		
		char* m_ref;
	};

	/**
	 * equality operator between two Labels
	 * @param label0 the first label
	 * @param label1 the second label
	 * @return true if equal, false otherwise
	 */
	inline bool operator==(const Label& label0, const Label& label1) { return label0.m_ref == label1.m_ref; }
	/**
	 * inequality operator between two Labels
	 * @param label0 the first label
	 * @param label1 the second label
	 * @return true if not equal, false otherwise
	 */
	inline bool operator!=(const Label& label0, const Label& label1) { return label0.m_ref != label1.m_ref; }
	/**
	 * less than operator between two Labels (arbitrary, but consistent)
	 * @param label0 the first label
	 * @param label1 the second label
	 * @return true if label0 is less than label1, false otherwise
	 */
	inline bool operator<(const Label& label0, const Label& label1) { return label0.m_ref < label1.m_ref; }
	/**
	 * greater than operator between two Labels (arbitrary, but consistent)
	 * @param label0 the first label
	 * @param label1 the second label
	 * @return true if label0 is greater than label1, false otherwise
	 */
	inline bool operator>(const Label& label0, const Label& label1) { return label0.m_ref > label1.m_ref; }
}
	
#define LABEL(str) mojito::Label::FromString(#str)

template <>
struct std::__1::hash<mojito::Label> : public unary_function<mojito::Label, size_t>
{
	size_t operator()(mojito::Label __v) const { return std::__1::hash<unsigned int>()( (unsigned int)__v.c_str() ); }
};

#endif

