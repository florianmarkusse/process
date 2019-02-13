#pragma once
#include "Pipe.h"

#include <string>
#include <vector>

/*
	Class for managing the content written to a Console instance.

	Florian Markusse
*/

namespace logger
{

	class ConsoleStreamBuffer : public std::basic_streambuf<char> {

	private:
		Pipe &m_output;
		std::vector<char> m_buffer;
		
	protected:
		int_type overflow(int_type character = traits_type::eof()) override;
		int_type sync() override;

		virtual void publish();

	public:
		explicit ConsoleStreamBuffer(Pipe &output, BufferSize bufferSize);
	};

} // namespace logger

