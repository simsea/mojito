/**
 * (c) 2013 Andrew Payne. All rights reserved.
 */
#include "Crc.h"

/**
 * @private
 */
static unsigned long crc32_table[256];
/**
 * @private
 */
static bool crc32_initialized = false;

/**
 * @private
 */
static unsigned long crc32_reflect(unsigned long ref, char ch)
{
	unsigned long value(0);
	for (int i = 1; i < (ch + 1); i++)
	{
		if (ref & 1)
			value |= 1 << (ch - i);
		ref >>= 1;
	}
	return value;
}

/**
 * @private
 */
static void crc32_init()
{
	crc32_initialized = true;
	unsigned long polynomial = 0x04c11db7;
	for (int i = 0; i <= 0xff; i++)
	{
		crc32_table[i] = crc32_reflect(i, 8) << 24;
		for (int j = 0; j < 8; j++)
			crc32_table[i] = (crc32_table[i] << 1) ^ (crc32_table[i] & (1 << 31) ? polynomial : 0);
		crc32_table[i] = crc32_reflect(crc32_table[i], 32);
	}
}

uint32_t mojito::crc32(const char* str)
{
	if (!crc32_initialized)
		crc32_init();
	unsigned long crc = 0xffffffff;
	size_t len = strlen(str);
	const unsigned char* buffer = (const unsigned char*)str;
	while ( --len )
		crc = (crc >> 8) ^ crc32_table[(crc & 0xff) ^ *buffer++];
	return (uint32_t)(crc ^ 0xffffffff);
}

