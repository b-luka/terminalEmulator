#ifndef OOP1PROJECT_BATCHCOMMAND_H
#define OOP1PROJECT_BATCHCOMMAND_H
#include "ConsoleCommand.h"

class Instance;

// Concrete command batch, executes commands from input.
class BatchCommand : public ConsoleCommand {
public:

	// Executes commands from input.
	void run() override;

	// Constructor.
	BatchCommand(const std::vector <std::string>& arguments_, Instance* instance_ = nullptr)
		: ConsoleCommand(arguments_), instance(instance_), commandResults("") {
	if (this->options.size() != 0) throw CommandSyntaxException("Error: Too many options!");
	}

	// Destructor.
	~BatchCommand() = default;

private:
	// Instance pointer.
	Instance* instance;

	// Results of executed commands, the result of batch itself is it's errors.
	std::string commandResults;
};

#endif
