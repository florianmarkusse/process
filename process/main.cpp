#include "console.h"
#include <iomanip>
#include <iostream>

int main()
{
	// creation
	logger::Console debug { "debug" };

	// using new console for output
	debug << "debug console\n";
	// std stream manipulators function as usual
	debug << std::hex << std::setfill('0') << std::setw(8) << 123456 << "\nflush!\n" << std::flush;

	// creation
	logger::Console debug2 { "debug2" };
	// using new console for output
	debug2 << "debug console2\n";
	// std stream manipulators function as usual
	debug2 << std::hex << std::setfill('0') << std::setw(8) << 123456 << "\nflush!\n" << std::flush;

	// wait for user input so the display stays up
	std::cout << "Program finished, press any key to exit\n";
	std::cin.get();
	// RAII destroys all used resources and terminates the helper process
}