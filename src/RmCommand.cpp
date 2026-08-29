#include "RmCommand.h"

// Reads from given input and removes file.
void RmCommand::run() {
	std::string line = this->input->readLine();
	if (!this->input->eof()) throw CommandSyntaxException("Error: Rm argument must be entered in 1 line!");
	std::ifstream fileCheck(line);
	bool fileExists = fileCheck.good();
	fileCheck.close();
	if (!fileExists) throw FileSystemException("Error: File " + line + " doesn't exist!");

	int status = std::remove(line.c_str());
	if (status != 0) {
		throw FileSystemException("Error: Couldn't remove file " + line + "!");
	}
}