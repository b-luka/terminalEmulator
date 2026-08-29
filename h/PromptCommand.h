#ifndef OOP1PROJECT_PROMPTCOMMAND_H
#define OOP1PROJECT_PROMPTCOMMAND_H
#include "ConsoleCommand.h"

class Instance;

// Concrete prompt command, replaces command window prompt.
class PromptCommand : public ConsoleCommand {
public:
	// Overriden. Changes instance prompt.
	void run() override;

	// Constructor.
	//PromptCommand(const std::vector <std::string>& arguments_, Instance* instance_ = nullptr) : ConsoleCommand(arguments_), instance(instance_) {}
	PromptCommand(const std::vector <std::string>& arguments_, Instance* instance_ = nullptr);

	// Destructor.
	virtual ~PromptCommand() = default;

private:
	Instance* instance;
};

#endif
