#include "LoggerAbstractFactory.h"
#include <iomanip>
#include <iostream>
#include <cstdarg>

int main()
{

	auto log = logger::LoggerAbstractFactory::createLogger("debugWiindow");

	int i = 4;

	log->info("Objects working as well");


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