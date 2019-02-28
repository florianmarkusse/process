#include "LoggerAbstractFactory.h"

#include <iostream>

int main()
{
	auto log = logger::LoggerAbstractFactory::createLogger("test");

	log->info("sending good vibes");
	log->info("sending good vibes");
	log->info("sending good vibes");
	log->info("sending good vibes");
	log->info("sending good vibes");
	log->warn("sending warning vibes");
	log->error("sending warning vibes");
	log->success("sending warning vibes");

	auto log2 = logger::LoggerAbstractFactory::createLogger("tester");

	log2->info("sending good vibes");
	log2->warn("sending warning vibes");
	log2->error("sending warning vibes");
	log2->success("sending warning vibes");

	// wait for user input so the display stays up
	std::cout << "Program finished, press any key to exit\n";
	std::cin.get();
	// RAII destroys all used resources and terminates the helper process
}