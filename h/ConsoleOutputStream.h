#ifndef OOP1PROJECT_CONSOLEOUTPUTSTREAM_H
#define OOP1PROJECT_CONSOLEOUTPUTSTREAM_H
#include "OutputStream.h"
#include <iostream>

// Concrete output stream, reads output from console (std::cout).
class ConsoleOutputStream : public OutputStream {
public:
	// Constructor.
	ConsoleOutputStream() : OutputStream() {}

	// Destructor.
	~ConsoleOutputStream() = default;
	
	// Writes to the console.
	void write(const std::string& data) override;

	// Writes to the console. Newline included.
	void writeLine(const std::string& data) override;
};

#endif
