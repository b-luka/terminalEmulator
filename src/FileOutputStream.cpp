#include "FileOutputStream.h"

// Constructor.
FileOutputStream::FileOutputStream(const std::string& fileName_, FileOutputStream::writeMode mode_) {
	this->mode = mode_;

	switch (mode_) {
	case FileOutputStream::WRITE:
		this->outputFile.open(fileName_);
	break;
	case FileOutputStream::APPEND:
		this->outputFile.open(fileName_, std::ios_base::app);
	break;
	default:
		throw GenericException("Error: Invalid write mode!");
	}
	if (this->outputFile.fail()) {
		throw FileSystemException("Error: No permission to open file " + fileName_ + "!");
	}
}

// Destructor.
FileOutputStream::~FileOutputStream() {
	this->outputFile.close();
}

// Writes to the file.
void FileOutputStream::write(const std::string& data) {
	this->outputFile << data;
}

// Writes to the file. Newline included.
void FileOutputStream::writeLine(const std::string& data) {
	this->outputFile << data << std::endl;
}