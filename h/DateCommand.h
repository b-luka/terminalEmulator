#ifndef OOP1PROJECT_DATECOMMAND_H
#define OOP1PROJECT_DATECOMMAND_H
#include "ConsoleCommand.h"
#include <chrono>

// Concrete command date, writes the current date to the output.
class DateCommand : public ConsoleCommand {
public:
	// Overriden. Prints the current date to the output. dd/mm/yyyy format.
	void run() override;

	// Constructor.
	DateCommand(const std::vector <std::string>& arguments_);

	// Destructor.
	virtual ~DateCommand() = default;

	// Prints result to output. Overriden.
	void printResult() const override;
};

#endif
