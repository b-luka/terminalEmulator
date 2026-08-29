#ifndef OOP1PROJECT_INPUTSTREAM_H
#define OOP1PROJECT_INPUTSTREAM_H
#include <string>
#include <vector>
#include "GenericException.h"

// Abstract class. Represents an input stream to be read from.
class InputStream {
public:
	// Abstract. Reads a line from the input.
	virtual std::string readLine() = 0;

	// Using readLine(), separates line into arguments.
	std::vector <std::string> getArguments();

	// Destructor.
	virtual ~InputStream() = default;

	// Returns isEOF.
	virtual bool eof() const;

protected:
	// Constructor. Abstract class.
	InputStream();
	
	// Maximum length of a given line. All characters after it will be ignored.
	static const int maxLineLength = 512;

	// True if EOF reached.
	bool isEOF;
};

#endif
