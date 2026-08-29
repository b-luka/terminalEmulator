#ifndef OOP1PROJECT_STRINGINPUTSTREAM_H
#define OOP1PROJECT_STRINGINPUTSTREAM_H
#include "InputStream.h"
#include <string>

// Single line input stream.
class StringInputStream : public InputStream {
public:
	// Constructor.
	StringInputStream(const std::string& lines_ = "");

	// Destructor.
	~StringInputStream() = default;

	// Overriden. Reads line.
	std::string readLine() override;

private:
	// Lines to read from.
	std::string lines;
};

#endif
