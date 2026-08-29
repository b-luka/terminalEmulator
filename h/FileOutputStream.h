#ifndef OOP1PROJECT_FILEOUTPUTSTREAM_H
#define OOP1PROJECT_FILEOUTPUTSTREAM_H
#include "OutputStream.h"
#include "GenericException.h"
#include <fstream>

// Concrete output stream, writes output to specified file.
class FileOutputStream : public OutputStream {
public:
	// Write mode to differentiate if old file content should be kept or not.
	enum writeMode { WRITE, APPEND };

	// Constructor. Write mode defaults to write.
	FileOutputStream(const std::string& fileName_, FileOutputStream::writeMode mode_ = FileOutputStream::WRITE);

	// Destructor.
	~FileOutputStream();

	// Writes to the console.
	void write(const std::string& data) override;

	// Writes to the console. Newline included.
	void writeLine(const std::string& data) override;

private:
	// File to write to.
	std::ofstream outputFile;


	// Write mode.
	writeMode mode;
};

#endif
