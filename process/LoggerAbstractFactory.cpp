#include "LoggerAbstractFactory.h"
#include "Platforms.h"
#ifdef WINDOWS_PLATFORM
	#include "windows/WindowsLogger.h"
#endif // WINDOWS_PLATFORM
#ifdef APPLE_PLATFORM
		return nullptr;
#endif // APPLE_PLATFORM
#ifdef LINUX_PLATFORM
	#include "linux/LinuxLogger.h"
#endif // LINUX_PLATFORM

namespace logger
{
	
	/*
		Returns the correct ILogger instance based on the platform used at 
		compile-time.

		@param name The title of the console window to log on.

		@return The created logger instance.
	*/
	std::shared_ptr<ILogger> LoggerAbstractFactory::createLogger(
		const std::string & name)
	{
#ifdef WINDOWS_PLATFORM
		return std::make_shared<WindowsLogger>(name);
#endif // WINDOWS_PLATFORM
#ifdef APPLE_PLATFORM
		return nullptr;
#endif // APPLE_PLATFORM
#ifdef LINUX_PLATFORM
		return std::make_shared<LinuxLogger>(name);
#endif // LINUX_PLATFORM
	}

} // namespace logger
