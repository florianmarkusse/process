#pragma once
#include <string>
#include <Windows.h>
#include <vector>
                                                                                
/*
	Class for managing the creation of processes for logging purposes.

	Florian Markusse
*/
namespace logger 
{
	// Flag for creating a process with an extra console or not.
	enum class ProcessCreationFlags : DWORD
	{
		none = 0,
		newConsole = CREATE_NEW_CONSOLE,
	};

	class Process
	{

	private:
		std::vector<char> m_cmdLine;			
		PROCESS_INFORMATION m_processInfo {};

	public:
		Process(
			const std::string &executablePath,
			const std::string &commandLineArguments,
			ProcessCreationFlags processCreationFlags = 
			ProcessCreationFlags::newConsole);

		Process(const Process &) = delete;
		Process(Process &&other) noexcept;

		Process &operator=(const Process &) = delete;
		Process &operator=(Process &&other) noexcept;

		virtual ~Process() noexcept;

		void terminate(int exitCode = 0);
	};
} // namespace logger