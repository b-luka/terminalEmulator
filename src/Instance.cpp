#include "Instance.h"

// Subarray helper method. Returns all element found within [start, end).
std::vector <std::string> Instance::subvector(const std::vector <std::string>& arr, size_t start, size_t end) const {
	if (end == -1) end = arr.size();
	if (start > end || start < 0 || end < 0 || start > arr.size() - 1 || end > arr.size()) 
		throw GenericException("Error: Invalid input!");
	
	std::vector <std::string> result;
	for (size_t i = start; i < end; i++) result.push_back(arr[i]);

	return result;
}

// Finds position of the next pipe symbol in arguments (-1 if not found).
int Instance::popNextPipePos(std::vector <std::string>& arguments) const {
	for (int i = 0; i < arguments.size(); i++) {
		if (arguments[i] == "|") {
			arguments[i] = "| (popped)";
			return i;
		}
	}
	return -1;
}

// Reads and executes commands until the given input is EOF.
void Instance::run() {
	while (true) {
		try {
			std::cout << this->prompt << " ";
			std::vector<std::string> lineArgs = this->inputStream->getArguments();

			if (std::cin.eof()) break;
			if (lineArgs.size() == 0) continue;

			this->runCommand(lineArgs);
		}
		catch (const GenericException& ex) {
			ex.printMessage();
		}
	}
}

// Runs a single command (or a pipe of commands) in a single line.
// Argument saveToString defaults to false. If true, returns the command result instead of printing it.
std::string Instance::runCommand(std::vector <std::string>& lineArgs, bool saveToString) {
	std::string result = "";
	bool hasPipe = false;
	bool lastInPipe = false;
	size_t errorPosition = 0;

	for (const std::string& arg : lineArgs) {
		char first = arg[0];
		if ((first >= 'A' && first <= 'Z') ||
			(first >= 'a' && first <= 'z') ||
			(first >= '0' && first <= '9') ||
			(first == '|' || first == '>' || first == '<' ||
			 first == '"' || first == '-' || first == '/' ||
			 first == '\\' || first == '.')) {
			errorPosition += arg.length() + 1;
		}
		else throw CommandVocabException("Error: Invalid syntax!", lineArgs, errorPosition);
	}

	int nextPipe = popNextPipePos(lineArgs);
	int start = 0;
	std::string lastResult = "";
	while (nextPipe != -1) {	// In the middle of a pipe
		std::vector <std::string> args = subvector(lineArgs, start, nextPipe);

		if (hasPipe) Command::addPreviousResult(args, lastResult);

		std::unique_ptr<Command> cmd(commandFactory.getCommand(args));
		if (cmd != nullptr) {
			// Redirection can only happen at the end of a line (pipe)
			if ((cmd->hasInputRedirection() || cmd->hasOutputRedirection()) && !lastInPipe) {
				if (!hasPipe && cmd->hasOutputRedirection()) 		// Unless it's input redirection at the start, but no output
					throw CommandSyntaxException("Error: Can't redirect in the middle of a pipe!");
			}
			cmd->run();
			lastResult = cmd->getResult();
		}

		start = nextPipe + 1;
		if (start > lineArgs.size() - 1) 
			throw CommandSyntaxException("Error: Can't end line with '|'!");

		nextPipe = popNextPipePos(lineArgs);
		if (!hasPipe) hasPipe = true;
		if (nextPipe == -1) lastInPipe = true;
	}

	if (hasPipe) {
		std::vector <std::string> args = subvector(lineArgs, start, nextPipe);
		Command::addPreviousResult(args, lastResult);

		std::unique_ptr<Command> cmd(commandFactory.getCommand(args));
		if (cmd != nullptr) {
			cmd->run();
			if (!saveToString) cmd->printResult();
			else result = cmd->getResult();
		}
	}
	else {
		std::unique_ptr<Command> cmd(commandFactory.getCommand(lineArgs));
		if (cmd != nullptr) {
			cmd->run();
			if (!saveToString) cmd->printResult();
			else result = cmd->getResult();
		}
	}
	
	return result;
}
