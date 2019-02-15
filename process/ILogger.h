#pragma once

#include <string>
#include <ostream>

/*
	Interface that every platform (Windows, Linux and Apple) has to inherit that
	provides the logging on a seperate console window.

	Florian Markusse
*/

namespace logger 
{

	class ILogger {

	public:

		// Print in white color.
		virtual void info(const std::string &message) = 0;
		// Print in amber/yellow color.
		virtual void warn(const std::string &message) = 0;
		// Print in red color.
		virtual void error(const std::string &message) = 0;
		// Print in green color.
		virtual void success(const std::string &message) = 0;
	};

} // namespace logger
