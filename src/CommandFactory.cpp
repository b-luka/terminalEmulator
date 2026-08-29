#include "CommandFactory.h"

// Given the first argument, evaluates which command will be created.
CommandFactory::commandType CommandFactory::evaluateCommand(const std::string& first) {
	if (first == "echo") return ECHO;
	if (first == "time") return TIME;
	if (first == "date") return DATE;
	if (first == "touch") return TOUCH;
	if (first == "wc") return WC;
	if (first == "prompt") return PROMPT;
	if (first == "truncate") return TRUNCATE;
	if (first == "rm") return RM;
	if (first == "batch") return BATCH;
	if (first == "head") return HEAD;
	if (first == "tr") return TR;
	return INVALID;
}

// Given an std::vector of std::string, creates corresponding command
Command* CommandFactory::getCommand(const std::vector <std::string>& args) {
	if (args.size() == 0) return nullptr;
	CommandFactory::commandType type = CommandFactory::evaluateCommand(args[0]);

	switch (type) {
	case ECHO:
		return new EchoCommand(args);
	case TIME:
		return new TimeCommand(args);
	case DATE:
		return new DateCommand(args);
	case TOUCH:
		return new TouchCommand(args);
	case WC:
		return new WcCommand(args);
	case PROMPT:
		return new PromptCommand(args, instance);
	case TRUNCATE:
		return new TruncateCommand(args);
	case RM:
		return new RmCommand(args);
	case BATCH:
		return new BatchCommand(args, instance);
	case HEAD:
		return new HeadCommand(args);
	case TR:
		return new TrCommand(args);
	default:
		std::cout << "Unknown command: " << args[0] << "\n";
		return nullptr;
	}
}