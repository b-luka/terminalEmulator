#include "FileSystemCommand.h"

// Constructor.
FileSystemCommand::FileSystemCommand(const std::vector <std::string>& arguments_) : Command(arguments_) {
	if (checkInputRedirection() != -1 || checkOutputRedirection() != -1)
		throw CommandSyntaxException("Error: Redirection not allowed!");

	if (arguments_.size() > 2) 
		throw CommandSyntaxException("Error: Too many arguments!");
	
	else if (arguments_.size() < 2) 
		throw CommandSyntaxException("Error: Not enough arguments!");

	std::string fileName = arguments_[1];
	if (fileName[0] == '"' && fileName[fileName.size() - 1] == '"') 
		fileName = fileName.substr(1, fileName.size() - 2);

	// If quoted only on one side
	else if (fileName[0] == '"' || fileName[fileName.size() - 1] == '"') 
		throw CommandSyntaxException("Error: Improper quoting!");
	

	this->setInputStream(std::make_unique<StringInputStream>(fileName));
}