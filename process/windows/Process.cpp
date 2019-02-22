#include "Process.h"
#include <iostream>

/*
	Class for managing the creation of processes with regards to creating
	extra consoles for logging purposes.

	Florian Markusse
*/
namespace logger
{
	/*
		<Constructor>
		Creates a Process instance and the child process.

		@param executablePath; The path to the executable for the child process
		to run.
		@param commandLineArguments; The command line arguments to be supplied
		to the child process.
		@param processCreationFlags; With which flags the child process is to be
		created.
	*/
	logger::Process::Process(
		const std::string & executablePath,
		const std::string & commandLineArguments,
		ProcessCreationFlags processCreationFlags)
	{
		// Set m_cmdLine.
		std::copy(std::begin(commandLineArguments),
			std::end(commandLineArguments),
			std::back_inserter(m_cmdLine));
		m_cmdLine.push_back('\0');

		STARTUPINFO startupInfo;
		GetStartupInfoA(&startupInfo);

		if (!static_cast<bool>( CreateProcessA(
			executablePath.c_str(),
			m_cmdLine.data(),
			nullptr,
			nullptr,
			FALSE,
			static_cast<DWORD>( processCreationFlags ),
			nullptr,
			nullptr,
			&startupInfo,
			&m_processInfo) )) {
			printf("CreateProcessA failed (%d).\n", GetLastError());
		}
	}

	/*
		<Move constructor>
		Moves the member variables of the "other" instance to this instance and
		sets the "other" instance to an invalid process.

		@param other; The other Process instance.
	*/
	logger::Process::Process(Process && other) noexcept
		: m_cmdLine { std::move(other.m_cmdLine) },
		m_processInfo { other.m_processInfo }
	{
		// Other process is no longer valid.
		other.m_processInfo.hThread = INVALID_HANDLE_VALUE;
		other.m_processInfo.hProcess = INVALID_HANDLE_VALUE;
	}

	/*
		<Move assignment operator>
		Terminates the current process, moves the member variables of the
		"other" instance to this instance and sets the "other" instance to an
		invalid process. Afterwards, returns the current instance.

		@param other; The other Process instance.

		@return The current Process instance.
	*/
	Process & logger::Process::operator=(Process && other) noexcept
	{
		// Current process is no longer valid.
		terminate();

		// Move "other" member variables to this process.
		m_cmdLine = std::move(other.m_cmdLine);
		m_processInfo = other.m_processInfo;

		// Other process is no longer valid.
		other.m_processInfo.hThread = INVALID_HANDLE_VALUE;
		other.m_processInfo.hProcess = INVALID_HANDLE_VALUE;

		return *this;
	}

	/*
		<Deconstructor>, <virtual>
		Terminates the process.
	*/
	logger::Process::~Process() noexcept
	{
		terminate();
	}

	/*
		<Move constructor>
		Moves the member variables of the "other" instance to this instance and
		sets the "other" instance to an invalid process.

		@param other; The other Process instance.
	*/
	void logger::Process::terminate(int exitCode)
	{
		// Terminate the thread.
		if (m_processInfo.hThread != INVALID_HANDLE_VALUE) {
			TerminateThread(m_processInfo.hThread, exitCode);
			CloseHandle(m_processInfo.hThread);
			m_processInfo.hThread = INVALID_HANDLE_VALUE;
		}
		// Terminate the process.
		if (m_processInfo.hProcess != INVALID_HANDLE_VALUE) {
			TerminateThread(m_processInfo.hProcess, exitCode);
			CloseHandle(m_processInfo.hProcess);
			m_processInfo.hProcess = INVALID_HANDLE_VALUE;
		}
	}
} // namespace logger
