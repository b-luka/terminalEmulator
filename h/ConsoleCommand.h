#ifndef OOP1PROJECT_CONSOLECOMMAND_H
#define OOP1PROJECT_CONSOLECOMMAND_H
#include "Command.h"

// Abstract class. Command meant to be interact with the console.
class ConsoleCommand : public Command {
public:
	// Abstract. To be overriden. Runs a command given the arguments.
	virtual void run() = 0;

	// Virtual destructor.
	virtual ~ConsoleCommand() = default;

protected:
	// Constructor.
	ConsoleCommand(const std::vector <std::string>& arguments_);
};

#endif
