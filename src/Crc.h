/**
 * (c) 2013 Andrew Payne. All rights reserved.
 */
#ifndef _MOJITO_CRC_H_
#define _MOJITO_CRC_H_

#include "Platform.h"

namespace mojito
{
	/**
	 * Calculate 32-bit CRC checksum value for a c-string
	 * @param str
	 * @return 32-bit CRC value
	 */
	uint32_t crc32(const char* str);
}

#endif

