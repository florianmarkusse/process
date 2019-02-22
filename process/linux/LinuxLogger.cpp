#include "../Platforms.h"
#ifdef LINUX_PLATFORM
#include "LinuxLogger.h"
#include "MessageQueue.h"
#include "../LoggingStreamBuffer.h"
#include "Time.h"

#include <mqueue.h>
#include <string>
#include <iostream>

#define EXIT_CHAR 1

/*
	Class for handling each console window on the windows operating system for
	logging purposes.

	Florian Markusse
*/
namespace logger
{
	/*
		<Constructor>
		Creates a unique pipe name using a random number generator.

		@param base; The base name from which the random number is concatenated.

		@return The generated unique pipe name.
	*/
	std::string LinuxLogger::createUniquePipeName(std::string base)
	{
		return base + std::to_string(::rand());
	}

	LinuxLogger::LinuxLogger(const std::string & name)
		: basic_ostream { new LoggingStreamBuffer {
		m_output, BufferSize { 4096 } } },
		m_output { MessageQueue::create(createUniquePipeName("/" + name), MessageQueueMode::write) }
	{
		constexpr static char const * CHILD_PROCESS_LOCATION = "/home/florian/Desktop/processCorss/childprocess/main";
		constexpr static unsigned int SYSTEM_CALL_LENGTH = 512;

		char argumentBuffer[SYSTEM_CALL_LENGTH];

		snprintf(
			argumentBuffer,
			sizeof(argumentBuffer),
			"gnome-terminal -- %s %s",
			CHILD_PROCESS_LOCATION,
			m_output.getMessageQueueName().c_str());

		system(argumentBuffer);
	}

	LinuxLogger::~LinuxLogger()
	{
		*( this )
			<< static_cast<char> ( EXIT_CHAR )
			<< std::flush;
	}

	/*
		<override>
		Logs a message as an informationial message to the console this logger
		is associated with.

		@param message; The message to log to the logger.
	*/
	void LinuxLogger::info(const std::string & message)
	{
		*( this )
			<< getCurrentFormattedTime()
			<< " "
			<< message
			<< std::endl;
	}

	/*
		<override>
		Logs a message as a warning message to the console this logger
		is associated with.

		@param message; The message to log to the logger.
	*/
	void LinuxLogger::warn(const std::string & message)
	{
		*( this )
			<< getCurrentFormattedTime()
			<< " "
			<< message
			<< std::endl;
	}

	/*
		<override>
		Logs a message as an error message to the console this logger
		is associated with.

		@param message; The message to log to the logger.
	*/
	void LinuxLogger::error(const std::string & message)
	{
		*( this )
			<< getCurrentFormattedTime()
			<< " "
			<< message
			<< std::endl;
	}

	/*
		<override>
		Logs a message as a success message to the console this logger
		is associated with.

		@param message; The message to log to the logger.
	*/
	void LinuxLogger::success(const std::string & message)
	{
		*( this )
			<< getCurrentFormattedTime()
			<< " "
			<< message
			<< std::endl;
	}
} // namespace logger

#endif // LINUX_PLATFORM
