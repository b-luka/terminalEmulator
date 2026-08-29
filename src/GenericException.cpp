#include "GenericException.h"

// Print error message with error position. Overriden.
void CommandVocabException::printMessage() const {
	std::cout << this->message << std::endl;
	if (!arguments.empty()) {
		for (const std::string& arg : this->arguments) {
			std::cout << arg << " ";
		}
		std::cout << std::endl;
		for (int i = 0; i < this->errorPosition - 1; i++) std::cout << " ";
		if (errorPosition > arguments[0].size()) std::cout << " ";
		std::cout << "^\n";
	}
}

// Message getter. Overriden.
std::string CommandVocabException::getMessage() const {
	std::string result = "";
	result += this->message + "\n";
	if (!arguments.empty()) {
		for (const std::string& arg : this->arguments) {
			result += arg + " ";
		}
		result += "\n";
		for (int i = 0; i < this->errorPosition - 1; i++) result += " ";
		if (errorPosition > arguments[0].size()) result += " ";
		result += "^";
	}
	return result;
}