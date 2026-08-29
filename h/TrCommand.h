#ifndef OOP1PROJECT_TRCOMMAND_H
#define OOP1PROJECT_TRCOMMAND_H
#include "Command.h"

// Concrete tr command. Replaces every occurence of a string with another. Derived from base Command
// because of its specific input.
class TrCommand : public Command {
public:
	// Replace every occurence of 'what' with 'with'.
	void run() override;

	// Constructor
	TrCommand(const std::vector <std::string>& arguments_);

	// Destructor
	~TrCommand() = default;

private:
	// String to be replaced.
	std::string what;

	// String to replace.
	std::string with;
};

#endif
