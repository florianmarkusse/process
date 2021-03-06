#pragma once
#include "../Platforms.h"
#ifdef WINDOWS_PLATFORM

#include "Pipe.h"
#include "Process.h"
#include "../ILogger.h"

/*
	Class for handling each console window on the windows operating system for
	logging purposes.

	Florian Markusse
*/
namespace logger
{
	class WindowsLogger : public ILogger, public std::ostream
	{
	private:
		Pipe m_output;
		Process m_helper;

		static std::string createUniquePipeName(const std::string & base);
		static std::string buildCommandLine(
			const std::string & title,
			const std::string & pipeName);

	public:
		explicit WindowsLogger(const std::string & name);

		void info(const std::string &message) override;
		void warn(const std::string &message) override;
		void error(const std::string &message) override;
		void success(const std::string &message) override;
	};
} // namespace logger

#endif // WINDOWS_PLATFORM
