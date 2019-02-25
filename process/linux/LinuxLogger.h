#pragma once
#include "../Platforms.h"
#ifdef LINUX_PLATFORM

#include "../ILogger.h"
#include "MessageQueue.h"

#include <ostream>

/*
	Class for handling each console window on the windows operating system for
	logging purposes.

	Florian Markusse
*/
namespace logger
{
	class LinuxLogger : public ILogger, public std::ostream
	{
	private:
		MessageQueue m_output;
		std::string m_queueName;

		static std::string createUniquePipeName(const std::string & base);

	public:
		explicit LinuxLogger(const std::string & name);
		~LinuxLogger();

		void info(const std::string &message) override;
		void warn(const std::string &message) override;
		void error(const std::string &message) override;
		void success(const std::string &message) override;
	};
} // namespace logger

#endif // LINUX_PLATFORM
