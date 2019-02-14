#include "LoggerAbstractFactory.h"
#include "StringBuilder.h"
#include <iomanip>
#include <iostream>

int main()
{

	auto log = logger::LoggerAbstractFactory::createLogger("debugWiindow");

	int i = 4;

	auto string = StringBuilder::build("hello, d", 45);

	std::cout << string;

	log->info(string);


	/*
	logger::WindowsLogger debug { "debug" };
	
	debug << "debug console\n";
	// std stream manipulators function as usual
	debug << std::hex << std::setfill('0') << std::setw(8) << 123456 << "\nflush!\n" << std::flush;
	*/

	// wait for user input so the display stays up
	std::cout << "Program finished, press any key to exit\n";
	std::cin.get();
	// RAII destroys all used resources and terminates the helper process
}
