#include "../Platforms.h"
#ifdef LINUX_PLATFORM
#include "LinuxLogger.h"
#include "MessageQueue.h"





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
	{
		constexpr static char * CHILD_PROCESS_LOCATION = R"(/home/florian/Desktop/processCorss/childprocess/main)";
		std::string queueName = createUniquePipeName("/");

		char outputBuffer[512] = "0w0 what's this?";

		MessageQueue messageQueue = MessageQueue::create(queueName, MessageQueueMode::write);
		messageQueue.write( Buffer {
			outputBuffer,
			strlen(outputBuffer) + 1
		});

		pid_t processID;

		processID = fork();

		if (processID == -1) {
			perror("Failed to fork process\n");
			exit(EXIT_FAILURE);
		}
		
		if (processID == 0) {
			// Child process

			char argumentBuffer[512];

			
			snprintf(argumentBuffer, 
			sizeof(argumentBuffer), 
			"gnome-terminal -- %s %s",
			CHILD_PROCESS_LOCATION,
			queueName.c_str());

			system(argumentBuffer);
			
			/*
			std::cout << "hello\n";

			MessageQueue read = MessageQueue::open("/testerer", MessageQueueMode::read);

			std::array<char, 4096> buffer = 
				std::array<char, 4096>{};

			unsigned int bytesRead = read.read( Buffer {
				buffer.data(),
				buffer.size()
			});

			std::cout << "i read " << bytesRead << " bytes\n";

			for (unsigned int i = 0; i < bytesRead; ++i) {
				std::cout << buffer[i];
			}

			std::cout << std::endl;
			*/
			/*
			close(pipeFileDescriptors[1]);

			while (read(pipeFileDescriptors[0], &buffer, 1)) {
				write(STDOUT_FILENO, &buffer, 1);
			}

			write(STDOUT_FILENO, "\n", 1);
			close(pipeFileDescriptors[0]);
			*/
			

			_exit(EXIT_SUCCESS);


		} else {
			// Parent process
			wait(NULL);
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