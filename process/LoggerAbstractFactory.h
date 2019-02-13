#pragma once

#include "ILogger.h"
#include "windows/WindowsLogger.h"

#include <memory>
#include <ostream>

namespace logger
{

	class LoggerAbstractFactory
	{
	private:
		std::shared_ptr<WindowsLogger> m_factory;

	public:
		LoggerAbstractFactory(std::string name);
		~LoggerAbstractFactory();

		friend std::ostream& operator<<(const LoggerAbstractFactory& loggerAbstractFactory, const std::string & message);
	};

} // namespace logger

