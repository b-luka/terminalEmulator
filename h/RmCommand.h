#ifndef OOP1PROJECT_RMCOMMAND_H
#define OOP1PROJECT_RMCOMMAND_H
#include "FileSystemCommand.h"
#include <cstdio>

// Concrete command rm, deletes a file if it exists.
class RmCommand : public FileSystemCommand {
public:
	// Reads from given input and removes file.
	void run();

	// Constructor.
	RmCommand(const std::vector <std::string>& arguments_) : FileSystemCommand(arguments_) {
		if (this->options.size() != 0) throw CommandSyntaxException("Error: Too many options!");
	};

	// Destructor.
	~RmCommand() = default;
};

#endif
