#ifndef OOP1PROJECT_WCCOMAND_H
#define OOP1PROJECT_WCCOMAND_H
#include "ConsoleCommand.h"

// Concrete command wc, counts characters or words in a stream.
class WcCommand : public ConsoleCommand {
public:
	// Counts characters or words, depending on the given option.
	void run() override;

	// Constructor.
	WcCommand(const std::vector <std::string>& arguments_);

	// Destructor.
	virtual ~WcCommand() = default;

private:
	// Defines the counting mode.
	enum countMode { WORD, CHARACTER, INVALID };
	countMode mode;

	// Counts characters from the input.
	void countCharacters();

	// Counts words from the input.
	void countWords();
};

#endif
