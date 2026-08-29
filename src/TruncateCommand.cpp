#include "TruncateCommand.h"

// Overriden. Deletes file content.
void TruncateCommand::run() {
	std::string line = this->input->readLine();
	if (!this->input->eof()) throw CommandSyntaxException("Error: Truncate argument must be entered in 1 line!");
	std::ifstream fileCheck(line);
	bool fileExists = fileCheck.good();
	fileCheck.close();
	if (!fileExists) throw FileSystemException("Error: File " + line + " doesn't exist!");

	std::ofstream newFile(line);
	if (newFile.fail()) throw FileSystemException("Error: No permission to open file " + line + "!");
	newFile.close();
}