#ifndef OOP1PROJECT_TOUCHCOMMAND_H
#define OOP1PROJECT_TOUCHCOMMAND_H
#include "FileSystemCommand.h"

// Concrete command touch, creates a file if it doesn't exist, prints error otherwise.
class TouchCommand : public FileSystemCommand {
public:
	// Reads from given input and creates file if it doesn't already exists, shows error otherwise
	void run();

	// Constructor.
	TouchCommand(const std::vector <std::string>& arguments_) : FileSystemCommand(arguments_) {
		if (this->options.size() != 0) throw CommandSyntaxException("Error: Too many options!");
	}

	// Destructor.
	~TouchCommand() = default;
};

#endif
