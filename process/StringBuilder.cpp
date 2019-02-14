#include "StringBuilder.h"

#include <cstdarg>

std::string StringBuilder::build(const char * format, ...)
{
	std::string result;
	int f;
	va_list arguments;

	va_start(arguments, format);

	while (*format) {

		if (*format == 'd') {

			f = va_arg(arguments, int);

			result += std::to_string(f);
		} else {
			result += *format;
		}
		format++;
	}

	va_end(arguments);

	return result;
}
