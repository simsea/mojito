/**
 * (c) 2013 Andrew Payne. All rights reserved.
 */
#ifndef _MOJITO_UTILITY_H_
#define _MOJITO_UTILITY_H_

#include "Platform.h"

namespace mojito
{
	/**
	 * @brief Case insensitive comparator for string maps
	 */
	struct CaseInsensitiveComparator
	{
		/**
		 * Comparator evaluation function. see std::map docs for more.
		 * @param s0 the first string
		 * @param s1 the second string
		 * @return true if s0 < s1, false otherwise
		 */
		inline bool operator()(const std::string& s0, const std::string& s1) const
		{
			return strcasecmp(s0.c_str(), s1.c_str()) < 0;
		}
	};

	/**
	 * approximation equality for floating point values.
	 * @param v0 the first value
	 * @param v1 the second value
	 * @param epsilon the tolerance value
	 * @return true if v0 and v1 are equal within epsilon, false otherwise
	 */
	inline bool equals(float v0, float v1, float epsilon = EPSILON)
	{
		return fabsf(v0 - v1) < epsilon;
	}
}

#endif

