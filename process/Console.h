#pragma once
#include "Pipe.h"
#include "Process.h"

/*
	Class for handling each console window for logging purposes.

	Florian Markusse
*/

namespace logger
{

	class Console : public std::ostream
	{
	private:
		Pipe m_output;
		Process m_helper;

		static std::string createUniquePipeName(std::string base);
		static std::string buildCommandLine(
			std::string title,
			std::string pipeName);

	public:
		explicit Console(std::string name);

		void error(const std::string &message);
		void warn(const std::string &message);
		void notify(const std::string &message);
		void success(const std::string &message);
	};

}

