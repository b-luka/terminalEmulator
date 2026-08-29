#ifndef OOP1PROJECT_ECHOCOMMAND_H
#define OOP1PROJECT_ECHOCOMMAND_H
#include "ConsoleCommand.h"

// Concrete echo command. Passes input to output.
class EchoCommand : public ConsoleCommand {
public:
	// Pass input to output
	void run() override;

	// Constructor
	EchoCommand(const std::vector <std::string>& arguments_) : ConsoleCommand(arguments_) {
		if (this->options.size() != 0) throw CommandSyntaxException("Error: Too many options!");
	}

	// Destructor
	~EchoCommand() = default;
};

#endif
