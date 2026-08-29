#ifndef OOP1PROJECT_FILESYSTEMCOMMAND_H
#define OOP1PROJECT_FILESYSTEMCOMMAND_H
#include "Command.h"

// Abstract command type. Used for interacting with the file system.
class FileSystemCommand : public Command {
public:
	// Abstract. To be overriden. Runs a command given the arguments.
	virtual void run() = 0;

	// Virtual destructor.
	virtual ~FileSystemCommand() = default;

protected:
	// Constructor.
	FileSystemCommand(const std::vector <std::string>& arguments_);
};

#endif