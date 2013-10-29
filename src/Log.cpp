/**
 * (c) 2013 Andrew Payne. All rights reserved.
 */
#include "Log.h"
#include "Platform.h"

using namespace mojito;

void Logger::log(Level level, const char* msg, ...)
{
	static char buffer[1024];
	//memset(buffer, 0, 1024);
	char levelChar = ' ';
	switch(level)
	{
	case Info: levelChar = 'I'; break;
	case Warning: levelChar = 'W'; break;
	case Error: levelChar = 'E'; break;
	case Verbose: levelChar = 'V'; break;
	}

	va_list args;
	va_start(args, msg);
	(void) vsnprintf(buffer, 1024, msg, args);
	va_end(args);
	printf("[%c] %s\n", levelChar, buffer);
}

