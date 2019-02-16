#include "LoggerAbstractFactory.h"

#include <iostream>

int main() {

	auto log = logger::LoggerAbstractFactory::createLogger("test");

	// wait for user input so the display stays up
	std::cout << "Program finished, press any key to exit\n";
	std::cin.get();
	// RAII destroys all used resources and terminates the helper process
}
