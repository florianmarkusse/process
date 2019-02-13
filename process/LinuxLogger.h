#ifdef LINUX_PLATFORM
#pragma once



#include "ILogger.h"

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