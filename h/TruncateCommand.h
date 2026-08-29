#ifndef OOP1PROJECT_TRUNCATECOMMAND_H
#define OOP1PROJECT_TRUNCATECOMMAND_H
#include "FileSystemCommand.h"

// Concrete command truncate, deletes file content.
class TruncateCommand : public FileSystemCommand {
public:
	// Overriden. Deletes file content.
	void run() override;

	// Constructor.
	TruncateCommand(const std::vector <std::string>& arguments_) : FileSystemCommand(arguments_) {
		if (this->options.size() != 0) throw CommandSyntaxException("Error: Too many options!");
	}

	// Destructor.
	virtual ~TruncateCommand() = default;
};

#endif
