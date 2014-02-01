/**
 * (c) 2013 Andrew Payne. All rights reserved.
 */
#ifndef _MOJITO_LOG_H_
#define _MOJITO_LOG_H_

namespace mojito
{
	/**
	 * @brief Logger class
	 * @details Simple logging class
	 */
	class Logger
	{
	public:
		/**
		 * Log level
		 */
		enum Level
		{
			Info,
			Warning,
			Error,
			Verbose
		};

		/**
		 * Print log line
		 * @param level the log level
		 * @param msg the message format
		 * @param ... the arguments for the message format
		 */
		static void log(Level level, const char* msg, ...);

	private:
		Logger() { }
		~Logger() { }
	};
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu"

#define LOG_INFO(msg, ...) mojito::Logger::log(mojito::Logger::Info, msg, ##__VA_ARGS__)
#define LOG_WARN(msg, ...) mojito::Logger::log(mojito::Logger::Warning, msg, ##__VA_ARGS__)
#define LOG_ERROR(msg, ...) mojito::Logger::log(mojito::Logger::Error, msg, ##__VA_ARGS__)
#define LOG_VERBOSE(msg, ...) mojito::Logger::log(mojito::Logger::Verbose, msg, ##__VA_ARGS__)

#pragma clang diagnostic pop

#endif

