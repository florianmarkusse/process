#pragma once
#include <string>

/*
	Interface for classes that need to print their contents to the logger.

	Florian Markusse
*/

namespace logger
{
	class IPrintable {

	public:
		virtual std::string toString() = 0;

	};
} // namespace logger
