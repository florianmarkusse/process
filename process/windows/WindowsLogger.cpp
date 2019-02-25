#include "WindowsLogger.h"
#include "../LoggingStreamBuffer.h"
#include "CurrentTime.h"

/*
	Class for handling each console window for logging purposes.

	Florian Markusse
*/
namespace logger
{
	constexpr static unsigned int DEFAULT_BUFFER_SIZE = 4096;
	// Executable location for the child process.
	const std::string EXECUTABLE_NAME =
		R"(C:\dev\Project1\x64\Debug\Project1.exe)";

	/*
		<Constructor>
		Creates a unique pipe name using a random number generator.

		@param base; The base name from which the random number is concatenated.

		@return The generated unique pipe name.
	*/
	std::string WindowsLogger::createUniquePipeName(const std::string & base)
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
	std::string WindowsLogger::buildCommandLine(const std::string & title, const std::string & pipeName)
	{
		return EXECUTABLE_NAME + " \"" + title + "\" \"" + pipeName + "\"";
	}

	/*
		<Constructor>
		Created the Console instance

		@return The created Console instance.
	*/
	WindowsLogger::WindowsLogger(const std::string & name)
		: basic_ostream {
			new LoggingStreamBuffer {
				m_output,
				BufferSize {
					DEFAULT_BUFFER_SIZE
				}
			}
	},
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
			ProcessCreationFlags::newConsole
	}
	{
	}

	/*
		<override>
		Logs a message as an informationial message to the console this logger
		is associated with.

		@param message; The message to log to the logger.
	*/
	void WindowsLogger::info(const std::string & message)
	{
		*( this )
			<< static_cast<typename std::underlying_type<LogLevel>::type>
			( LogLevel::info )
			<< getCurrentFormattedTime()
			<< " "
			<< message
			<< std::flush;
	}

	/*
		<override>
		Logs a message as a warning message to the console this logger
		is associated with.

		@param message; The message to log to the logger.
	*/
	void WindowsLogger::warn(const std::string & message)
	{
		*( this )
			<< static_cast<typename std::underlying_type<LogLevel>::type>
			( LogLevel::warn )
			<< getCurrentFormattedTime()
			<< " "
			<< message
			<< std::flush;
	}

	/*
		<override>
		Logs a message as an error message to the console this logger
		is associated with.

		@param message; The message to log to the logger.
	*/
	void WindowsLogger::error(const std::string & message)
	{
		*( this )
			<< static_cast<typename std::underlying_type<LogLevel>::type>
			( LogLevel::error )
			<< getCurrentFormattedTime()
			<< " "
			<< message
			<< std::flush;
	}

	/*
		<override>
		Logs a message as a success message to the console this logger
		is associated with.

		@param message; The message to log to the logger.
	*/
	void WindowsLogger::success(const std::string & message)
	{
		*( this )
			<< static_cast<typename std::underlying_type<LogLevel>::type>
			( LogLevel::success )
			<< getCurrentFormattedTime()
			<< " "
			<< message
			<< std::flush;
	}
} // namespace logger