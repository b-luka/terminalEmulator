#ifndef OOP1PROJECT_HEADCOMMAND_H
#define OOP1PROJECT_HEADCOMMAND_H
#include "ConsoleCommand.h"

// Concrete command head, prints first -n_ lines to the output.
class HeadCommand : public ConsoleCommand {
public:
	// Overriden. Prints first -n_ lines to the output.
	void run() override;

	// Constructor
	HeadCommand(const std::vector <std::string>& arguments_);

	// Destructor.
	~HeadCommand() = default;
};

#endif
