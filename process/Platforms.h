#pragma once

#ifdef _WIN32
	#define WINDOWS_PLATFORM
#endif // _WIN32
#ifdef __APPLE__
	#define APPLE_PLATFORM
#endif // __APPLE__
#ifdef __linux__
	#define LINUX_PLATFORM
#endif // __linux__