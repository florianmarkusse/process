#include "LoggerAbstractFactory.h"
#include <cstdarg>
#include <iomanip>
#include <iostream>

int main() {

	auto log = logger::LoggerAbstractFactory::createLogger("debugWiiiiiiindow");

	int i = 35;

	log->info("Printing variables: " + std::to_string(i) + "\n");
	log->info("Objects also work, just inherit IPrintable interface\n");
	log->warn("Warning\n");
	log->success("Succ sexx\n");
	log->error("Segfault :(\n");

	auto log2 = logger::LoggerAbstractFactory::createLogger("SECOND LOGG");

	log2->info("nothing more to mention sadly\n");

	// wait for user input so the display stays up
	std::cout << "Program finished, press any key to exit\n";
	std::cin.get();
	// RAII destroys all used resources and terminates the helper process
}
