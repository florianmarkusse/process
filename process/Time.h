#pragma once
#include <string>
#include <ctime>

#define BUFFER_SIZE 28

/*
	Utility function that returns the current time in format:
	{ [\Day \Month \Day \Time \Year] }

	@return The current time
*/
std::string getCurrentFormattedTime()
{
	char currentTime[BUFFER_SIZE];
	// Want the format to be [time]
	currentTime[0] = '[';

	std::time_t  time = std::time(nullptr);
	errno_t error = ctime_s(currentTime + 1, BUFFER_SIZE - 1, &time);

	for (unsigned int i = 1; i < 50; ++i) {
		if (currentTime[i] == '\n') {
			// Want the format to be [time]
			currentTime[i] = ']';
		}
	}

	return currentTime;
}