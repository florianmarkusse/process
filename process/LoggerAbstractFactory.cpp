#include "LoggerAbstractFactory.h"
#include "Platforms.h"
#ifdef WINDOWS_PLATFORM
	#include "windows/WindowsLogger.h"
#endif // WINDOWS_PLATFORM

namespace logger
{

	LoggerAbstractFactory::LoggerAbstractFactory(std::string name)
	{
#ifdef WINDOWS_PLATFORM
		m_factory = std::make_shared<WindowsLogger>(name);
#endif // WINDOWS_PLATFORM
#ifdef APPLE_PLATFORM
		m_factory = nullptr;
#endif // APPLE_PLATFORM
#ifdef LINUX_PLATFORM
		m_factory = nullptr;
#endif // LINUX_PLATFORM
	}

	LoggerAbstractFactory::~LoggerAbstractFactory()
	{
	}

	std::ostream & operator<<(const LoggerAbstractFactory & loggerAbstractFactory, const std::string & message)
	{
		*(loggerAbstractFactory.m_factory) << message;
		return *( loggerAbstractFactory.m_factory );
	}

} // namespace logger
