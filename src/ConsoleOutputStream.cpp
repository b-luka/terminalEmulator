#include "ConsoleOutputStream.h"

// Writes to the console.
void ConsoleOutputStream::write(const std::string& data) {
	std::cout << data;
}

// Writes to the console. Newline included.
void ConsoleOutputStream::writeLine(const std::string& data) {
	std::cout << data << std::endl;
}