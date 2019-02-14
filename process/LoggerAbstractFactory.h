#pragma once

#include "ILogger.h"
#include "windows/WindowsLogger.h"

#include <memory>
#include <ostream>

namespace logger
{

	class LoggerAbstractFactory
	{
	public:
		static std::shared_ptr<ILogger> createLogger(const std::string &name);
	};

} // namespace logger

