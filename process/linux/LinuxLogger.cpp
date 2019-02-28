#include "LinuxLogger.h"
#ifdef LINUX_PLATFORM

#include "MessageQueue.h"
#include "../LoggingStreamBuffer.h"
#include "CurrentTime.h"

#include <mqueue.h>
#include <string>
#include <iostream>

#define EXIT_CHAR 1
#define INFO_CHAR 2
#define WARN_CHAR 3
#define ERROR_CHAR 4
#define SUCCESS_CHAR 5

/*
	Class for handling each console window on the windows operating system for
	logging purposes.

	Florian Markusse
*/
namespace logger
{

	/*
		Creates a unique name using a random number generator.

		@param base; The base name from which the random number is concatenated.

		@return The generated unique name.
	*/
	std::string LinuxLogger::createUniqueMessageQueueName(const std::string & base)
	{
		return base + std::to_string(::rand());
	}

	/*
		<Constructor>
		Creates a LinuxLogger instance. Also creates the new process that is
		to be used to log to.

		@param base; The name to be given to the terminal of the new process.

		@return The created LinuxLogger instance
	*/
	LinuxLogger::LinuxLogger(const std::string & name)
		: basic_ostream {
			new LoggingStreamBuffer {
				m_output,
				BufferSize {
					4096
				}
			}
		},
		m_output {
			MessageQueue::create(createUniqueMessageQueueName("/" + name),
			MessageQueueMode::write)
		}
	{
		// Need another process to run for the parent that logs the messages
		// sent to it.
		constexpr static char const * CHILD_PROCESS_LOCATION =
			"/home/florian/Desktop/processCorss/childprocess/main";
		// Set up a buffer for the arguments.
		constexpr static unsigned int SYSTEM_CALL_LENGTH = 512;
		char argumentBuffer[SYSTEM_CALL_LENGTH];

		// Fill the buffer with the arguments for creating the new process.
		snprintf(
			argumentBuffer,
			sizeof(argumentBuffer),
			"gnome-terminal --title=%s -- %s %s",
			name.c_str(),
			CHILD_PROCESS_LOCATION,
			m_output.getMessageQueueName().c_str());

		// Execute the system call with the built string.
		system(argumentBuffer);
	}

	/*
		<Deconstructor>
		sends the termination signal to the logging process and 
		closes the message queue
	*/
	LinuxLogger::~LinuxLogger()
	{
		*( this )
			<< static_cast<char> (EXIT_CHAR)
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
			<< static_cast<char> (INFO_CHAR)
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
			<< static_cast<char> (WARN_CHAR)
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
			<< static_cast<char> (ERROR_CHAR)
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
			<< static_cast<char> (SUCCESS_CHAR)
			<< getCurrentFormattedTime()
			<< " "
			<< message
			<< std::endl;
	}
} // namespace logger

#endif // LINUX_PLATFORM