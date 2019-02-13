#pragma once

#include <string>
#include <ostream>

namespace logger 
{

	class ILogger {

	public:
		virtual void info(const std::string &message) = 0;
		virtual void warn(const std::string &message) = 0;
		virtual void error(const std::string &message) = 0;
		virtual void success(const std::string &message) = 0;
	};

} // namespace logger
