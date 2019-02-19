#include "../Platforms.h"
#ifdef LINUX_PLATFORM
#include "LinuxLogger.h"
#include "MessageQueue.h"
#include "../LoggingStreamBuffer.h"





#include <sys/wait.h>
#include <unistd.h>
#include <mqueue.h>
#include <iostream>
#include <string>
#include <array>
#include <string.h>

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

		pid_t processID;

		processID = fork();

		if (processID == -1) {
			perror("Failed to fork process\n");
			exit(EXIT_FAILURE);
		}
		
		if (processID == 0) {
			// Child process
			m_processIDChild = processID;

			char argumentBuffer[512];

			snprintf(argumentBuffer, 
			sizeof(argumentBuffer), 
			"gnome-terminal -- %s %s",
			CHILD_PROCESS_LOCATION,
			m_output.getMessageQueueName().c_str());

			system(argumentBuffer);

			_exit(EXIT_SUCCESS);
		}
		

	}


	LinuxLogger::~LinuxLogger()
	{
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
			<< message
			<< std::flush;
	}

	/*
		<override>
		Logs a message as a warning message to the console this logger
		is associated with.

		@param message; The message to log to the logger.
	*/
	void LinuxLogger::warn(const std::string & message)
	{
		
	}

	/*
		<override>
		Logs a message as an error message to the console this logger
		is associated with.

		@param message; The message to log to the logger.
	*/
	void LinuxLogger::error(const std::string & message)
	{
		
	}

	/*
		<override>
		Logs a message as a success message to the console this logger
		is associated with.

		@param message; The message to log to the logger.
	*/
	void LinuxLogger::success(const std::string & message)
	{
		
	}

} // namespace logger

#endif // LINUX_PLATFORM