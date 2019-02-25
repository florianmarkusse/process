#pragma once
#include "../Platforms.h"
#ifdef LINUX_PLATFORM

#include <time.h>
#include <string>

/*
	Utility function that returns the current time in format:
	{ [\Day \Month \Day \Time \Year] }

	@return The current time
*/
std::string getCurrentFormattedTime()
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	return "["
		+ std::to_string(tm.tm_mday)
		+ "-"
		+ std::to_string(tm.tm_mon + 1)
		+ "-"
		+ std::to_string(tm.tm_year + 1900)
		+ " "
		+ std::to_string(tm.tm_hour)
		+ ":"
		+ std::to_string(tm.tm_min)
		+ ":"
		+ std::to_string(tm.tm_sec)
		+ "]";
}

#endif // LINUX_PLATFORM
