#pragma once
#include "ILogger.h"
#include "windows/WindowsLogger.h"

#include <memory>
#include <ostream>

/*
	Abstract factory class for handling the creation of the correct ILogger
	instance.

	Florian Markusse
*/
namespace logger
{

	class LoggerAbstractFactory
	{
	public:
		static std::shared_ptr<ILogger> createLogger(const std::string &name);
	};

} // namespace logger

