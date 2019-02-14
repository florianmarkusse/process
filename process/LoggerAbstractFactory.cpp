#include "LoggerAbstractFactory.h"
#include "Platforms.h"
#ifdef WINDOWS_PLATFORM
	#include "windows/WindowsLogger.h"
#endif // WINDOWS_PLATFORM

namespace logger
{
	
	std::shared_ptr<ILogger> LoggerAbstractFactory::createLogger(const std::string & name)
	{
#ifdef WINDOWS_PLATFORM
		return std::make_shared<WindowsLogger>(name);
#endif // WINDOWS_PLATFORM
#ifdef APPLE_PLATFORM
		return nullptr;
#endif // APPLE_PLATFORM
#ifdef LINUX_PLATFORM
		return nullptr;
#endif // LINUX_PLATFORM
	}

} // namespace logger
