#ifdef LINUX_PLATFORM
#pragma once
#include "../ILogger.h"

/*
	Class for handling each console window on the windows operating system for
	logging purposes.

	Florian Markusse
*/
namespace logger
{

	class LinuxLogger : public ILogger
	{

	private:
		static std::string createUniquePipeName(std::string base);

	public:
		LinuxLogger(const std::string & name);
		~LinuxLogger();

		void info(const std::string &message) override;
		void warn(const std::string &message) override;
		void error(const std::string &message) override;
		void success(const std::string &message) override;

	};

} // namespace logger

#endif // LINUX_PLATFORM