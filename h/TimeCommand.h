#ifndef OOP1PROJECT_TIMECOMMAND_H
#define OOP1PROJECT_TIMECOMMAND_H
#include "ConsoleCommand.h"
#include <chrono>

// Concrete command time, writes the current time to the output.
class TimeCommand : public ConsoleCommand {
public:
	// Overriden. Prints the current time to the output. hh:mm:ss format.
	void run() override;

	// Constructor.
	TimeCommand(const std::vector <std::string>& arguments_);

	// Destructor.
	virtual ~TimeCommand() = default;

	// Prints result to output. Overriden.
	void printResult() const override;
};

#endif
