#include "ConsoleStreamBuffer.h"

/*
	Class for managing the content written to a Console instance.

	Florian Markusse
*/

namespace logger
{

	/*
		<override>
		Handles overflow to the stream buffer to ensure that there is space at
		the put area.

		@param character; The character that is overflowing or EoF.

		@return The character that is handled correctly or EoF when not 
		successful.
	*/
	std::basic_streambuf<char>::int_type 
		logger::ConsoleStreamBuffer::overflow(int_type character)
	{
		// Put area is full, thus publish!
		publish();

		// Check if the put area is still valid.
		if (character != traits_type::eof()) {
			*pptr() = character;
			pbump(1);
			return character;
		}

		return traits_type::eof();
	}

	/*
		<override>
		Synchronizes the put area buffer with the character sequence by
		publishing.

		@return 0.
	*/
	std::basic_streambuf<char>::int_type logger::ConsoleStreamBuffer::sync()
	{
		publish();
		return 0;
	}

	/*
		Write the contents of the put area to the pipe and resets the put area
		pointers.
	*/
	void logger::ConsoleStreamBuffer::publish()
	{
		const int size = pptr() - pbase();

		if (size > 0) {
			m_output.write(
				logger::Buffer { m_buffer.data(), static_cast<size_t> (size) });
			setp(m_buffer.data(), m_buffer.data() + m_buffer.size());
		}
	}

	/*
		<Constructor>
		Write the contents of the put area to the pipe and resets the put area
		pointers.
	*/
	logger::ConsoleStreamBuffer::ConsoleStreamBuffer(
		Pipe & output, 
		BufferSize bufferSize)
		: m_output { output }, m_buffer(bufferSize.value)
	{
		char * const begin = m_buffer.data();
		char * const end = begin + m_buffer.size();
		setp(begin, end);
	}

}
