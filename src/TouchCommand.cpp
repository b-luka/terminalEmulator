#include "TouchCommand.h"

// Reads from given input and creates file if it doesn't already exists, shows error otherwise
void TouchCommand::run() {
	std::string line = this->input->readLine();
	if (!this->input->eof()) throw CommandSyntaxException("Error: Touch argument must be entered in 1 line!");
	std::ifstream fileCheck(line);
	bool fileExists = fileCheck.good();
	
	fileCheck.close();
	if (fileExists) throw FileSystemException("Error: File " + line + " already exists!");

	std::ofstream newFile(line);
	if (newFile.fail()) throw FileSystemException("Error: No permission to create file " + line + "!");
	newFile.close();
}
