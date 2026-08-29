#include "FileInputStream.h"

// Constructor.
FileInputStream::FileInputStream(const std::string& fileName_) : InputStream() {
	this->inputFile = std::ifstream(fileName_);
	this->isGood = this->inputFile.good();

	if (this->inputFile.fail()) {		// no permission to open file
		throw FileSystemException("Error: No permission to open file " + fileName_ + "!");
	}
}

// Destructor.
FileInputStream::~FileInputStream() {
	if (this->inputFile.is_open()) this->inputFile.close();
}

// Overriden. Reads a line from private field inputFile.
std::string FileInputStream::readLine() {
	std::string result;
	std::getline(this->inputFile, result);
	if (inputFile.eof()) this->isEOF = true;
	return result;
}

// Returns true if opening the file was successul.
bool FileInputStream::good() const { return this->isGood; }