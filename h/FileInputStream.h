#ifndef OOP1PROJECT_FILEINPUTSTREAM_H
#define OOP1PROJECT_FILEINPUTSTREAM_H
#include "InputStream.h"
#include <fstream>

// Concrete input stream, reads input from specified file.
class FileInputStream : public InputStream {
public:

	// Constructor.
	FileInputStream(const std::string& fileName_);

	// Destructor.
	~FileInputStream();

	// Overriden. Reads a line from private field inputFile.
	std::string readLine() override;
	
	// Returns true if opening the file was successul.
	bool good() const;

private:
	// File to read from.
	std::ifstream inputFile;

	// True if opening the file was successful.
	bool isGood;

};

#endif
