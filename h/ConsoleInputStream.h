#ifndef OOP1PROJECT_CONSOLEINPUTSTREAM_H
#define OOP1PROJECT_CONSOLEINPUTSTREAM_H
#include "InputStream.h"
#include <iostream>

// Concrete input stream, reads input from console (std::cin).
class ConsoleInputStream : public InputStream {
public:
	// Reads line using std::getline().
	std::string readLine() override;
	
	// Constructor.
	ConsoleInputStream();
	
	// Destructor.
	~ConsoleInputStream() = default;

	// Returns true if EOF is entered.
	bool eof() const override;
private:
	// Maximum length of each input.
	int maxLineLength;
};

#endif
