#ifndef OOP1PROJECT_OUTPUTSTREAM_H
#define OOP1PROJECT_OUTPUTSTREAM_H
#include <string>

// Abstract class. Represents an output stream to write to.
class OutputStream {
public:
	// Abstract. Writes to an output stream.
	virtual void write(const std::string& data) = 0;

	// Abstract. Writes to an output stream. Newline (should be) included.
	virtual void writeLine(const std::string& data) = 0;

	// Destructor.
	virtual ~OutputStream() = default;

protected:
	// Constructor. Abstract class.
	OutputStream() = default;
};

#endif
