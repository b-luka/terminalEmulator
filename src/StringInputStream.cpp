#include "StringInputStream.h"

// Constructor.
StringInputStream::StringInputStream(const std::string& lines_) : InputStream() {
	this->lines = lines_;
}

// Overriden. Reads a line from private field inputFile.
std::string StringInputStream::readLine() {
	int newLinePos = -1;
	std::string res = "";
	for (int i = 0; i < this->lines.size(); i++) {
		if (this->lines[i] == '\n') {
			newLinePos = i;
			break;
		}
		res += this->lines[i];
	}

	if (newLinePos == -1) {
		this->isEOF = true;
	}
	else {
		this->lines = this->lines.substr(newLinePos + 1);
	}
	return res;
}