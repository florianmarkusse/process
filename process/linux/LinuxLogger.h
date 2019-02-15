#ifdef LINUX_PLATFORM
#pragma once
#include "ILogger.h"

/*
	Class for handling each console window on the windows operating system for
	logging purposes.

	Florian Markusse
*/
namespace logger
{

	class LinuxLogger : public ILogger
	{
	public:
		LinuxLogger();
		~LinuxLogger();
	};

} // namespace logger

#endif // LINUX_PLATFORM