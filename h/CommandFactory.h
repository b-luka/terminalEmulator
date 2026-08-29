#ifndef OOP1PROJECT_COMMANDFACTORY_H
#define OOP1PROJECT_COMMANDFACTORY_H
#include "Command.h"
#include "EchoCommand.h"
#include "TimeCommand.h"
#include "DateCommand.h"
#include "TouchCommand.h"
#include "WcCommand.h"
#include "PromptCommand.h"
#include "TruncateCommand.h"
#include "RmCommand.h"
#include "BatchCommand.h"
#include "HeadCommand.h"
#include "TrCommand.h"

class Instance;

// Factory DP. Given an std::vector of std::string, creates corresponding command.
// If failed, returns nullptr.
class CommandFactory {
public:
	// Constructor.
	CommandFactory(Instance* instance_) : instance(instance_) {}

	// Destructor.
	~CommandFactory() = default;

	// Given an std::vector of std::string, creates corresponding command.
	Command* getCommand(const std::vector <std::string>& args);

private:

	// Given the first argument, evaluates which command will be created.
	enum commandType {ECHO, TIME, DATE, TOUCH, WC, PROMPT, TRUNCATE, RM, BATCH, HEAD, TR, INVALID};
	static commandType evaluateCommand(const std::string& first);

	// Pointer to current instance.
	Instance* instance;
};

#endif
