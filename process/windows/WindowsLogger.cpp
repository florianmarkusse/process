#include "WindowsLogger.h"
#include "ConsoleStreamBuffer.h"

/*
	Class for handling each console window for logging purposes.

	Florian Markusse
*/

using namespace std::string_literals;

namespace logger
{
	constexpr static unsigned int DEFAULT_BUFFER_SIZE = 4096;
	// Executable location for the child process.
	const std::string EXECUTABLE_NAME = "windows//Project1.exe"s; 

	/*
		<Constructor>
		Creates a unique pipe name using a random number generator.

		@param base; The base name from which the random number is concatenated.

		@return The generated unique pipe name.
	*/
	std::string WindowsLogger::createUniquePipeName(std::string base)
	{
		return base + std::to_string(::rand());
	}

	/*
		Create the command line, this is depenedent on the executable used for
		the child process.

		@param title; The title of the console.
		@param pipeName; The name of the pipe.

		@return The command line arguments for the child process.
	*/
	std::string WindowsLogger::buildCommandLine(std::string title, std::string pipeName)
	{
		return EXECUTABLE_NAME + " \"" + title + "\" \"" + pipeName + "\"";
	}

	/*
		<Constructor>
		Created the Console instance

		@return The created Console instance.
	*/
	WindowsLogger::WindowsLogger(std::string name)
		: basic_ostream { new ConsoleStreamBuffer { 
		m_output, BufferSize { DEFAULT_BUFFER_SIZE } } },
		m_output {
			Pipe::create(
				createUniquePipeName(name),
				PipeMode::write,
				ReadBufferSize { 0 },
				WriteBufferSize { DEFAULT_BUFFER_SIZE })
		},
		m_helper { 
		EXECUTABLE_NAME, 
		buildCommandLine(name, m_output.getPipeName()), 
		ProcessCreationFlags::newConsole }
	{
	}

	void WindowsLogger::info(const std::string & message)
	{
	}

	void WindowsLogger::warn(const std::string & message)
	{
	}

	void WindowsLogger::error(const std::string & message)
	{
	}

	void WindowsLogger::success(const std::string & message)
	{
	}


} // namespace logger
