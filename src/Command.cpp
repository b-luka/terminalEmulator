#include "Command.h"

// Check if input redirection is present. -1 if not, index in arguments if it is.
int Command::checkInputRedirection() const {
	int pos = -1;
	bool found = false;
	for (int i = 0; i < arguments.size(); i++) {
		std::string arg = arguments[i];
		if (arg[0] == '<') {
			if (!found) {
				found = true;
			}
			else {
				throw CommandSyntaxException("Error: Can't redirect input twice!");
				return -2;
			}
			pos = i;
		}
	}
	return pos;
}

// Check if output redirection is present. -1 if not, index in arguments if it is.
int Command::checkOutputRedirection() const {
	int pos = -1;
	bool found = false;
	for (int i = 0; i < arguments.size(); i++) {
		std::string arg = arguments[i];
		if (arg[0] == '>') {
			if (!found) {
				found = true;
			}
			else {
				throw CommandSyntaxException("Error: Can't redirect output twice!");
				return -1;
			}
			pos = i;
		}
	}
	return pos;
}

// Remove > and < from a string (in case of redirection.
std::string Command::redirectionFileName(const std::string& input_) const {
	std::string res = "";
	for (char c : input_) {
		if (c != '>' && c != '<') res += c;
	}
	return res;
}

// Prints result to output.
void Command::printResult() const {
	if (this->result == "") return;

	if (typeid(*(this->output)) == typeid(FileOutputStream) ||
		typeid(*(this->input)) == typeid(ConsoleInputStream)) {
		this->output->write(result);
		return;
	}
	this->output->writeLine(result);
}

// Constructor.
Command::Command(const std::vector <std::string>& arguments_) {
	this->arguments = arguments_;
	this->options = std::vector <std::string>();
	this->output = std::make_unique<ConsoleOutputStream>();
	this->input = std::make_unique<ConsoleInputStream>();
	this->result = "";
	this->inputRedirectionPresent = false;
	this->outputRedirectionPresent = false;

	// Filter options out of arguments.
	for (int i = 0; i < arguments.size(); i++) {
		if (arguments[i][0] == '-') {
			if (arguments[i].size() < 2)
				throw CommandSyntaxException("Error: Empty option is not allowed!");
			this->options.push_back(arguments[i]);
			this->arguments.erase(this->arguments.begin() + i);
			i--;
		}
	}
}

// Input stream setter.
void Command::setInputStream(std::unique_ptr<InputStream> input_) {
	this->input = std::move(input_);
}

// Output stream setter.
void Command::setOutputStream(std::unique_ptr<OutputStream> output_) {
	this->output = std::move(output_);
}

// Add result to an argument array.
void Command::addPreviousResult(std::vector <std::string>& arguments, const std::string& argumentToAdd) {
	if (arguments.size() == 0) return;
	std::string lastResult = '\"' + argumentToAdd + '\"';
	int insertPos = 0;
	while (insertPos < arguments.size()) {		// Insert after arguments but before redirection, if redirection is present
		if (arguments[insertPos][0] == '>' || arguments[insertPos][0] == '<') break;
		insertPos++;
	}

	if (insertPos >= arguments.size()) {		// No redirection
		if (arguments[0] != "tr") arguments.push_back(lastResult);	// eg. echo 'lastResult', add as last
		else {														// eg. tr 'lastResult' 'what' 'with', add as 2nd, add 'with' as blank if needed
			arguments.resize(arguments.size() + 1);
			for (size_t i = arguments.size() - 1; i > 1; i--) arguments[i] = arguments[i - 1];
			arguments[1] = lastResult;

			if (arguments.size() < 3) throw CommandSyntaxException("Error: Missing argument 'what'!");
			
			// tr 'lastResult' 'what', append empty 'with' to get proper functionality
			if (arguments.size() == 3) arguments.push_back("\"\"");
			// if arguments.size() is 4 there's nothing to do, if it's greater an error will be thrown
			// in the constructor
		}
	}
	else {
		if (arguments[0] != "tr") {				// eg. echo 'lastResult' >>output.txt, add as last before redirection
			arguments.resize(arguments.size() + 1);
			for (size_t i = arguments.size() - 1; i > insertPos; i--) arguments[i] = arguments[i - 1];
			arguments[insertPos] = lastResult;
		}
		else {									// eg. tr 'lastResult' 'what' >>output.txt, add as 2nd, add 'with' as blank if needed
			arguments.resize(arguments.size() + 1);
			insertPos++;
			for (size_t i = arguments.size() - 1; i > 1; i--) arguments[i] = arguments[i - 1];
			arguments[1] = lastResult;

			if (insertPos < 3) throw CommandSyntaxException("Error: Missing argument 'what'!");
			// Guaranteed at least 4 elements eg. tr 'lastResult' 'what' >>output.txt
			switch (insertPos) {
			case 0: case 1: case 2:
				throw CommandSyntaxException("Error: Missing argument 'what'!");
				break;

			case 3:		// eg. tr 'lastResult' 'what' >>output.txt, add blank 'with' before >>output.txt
				arguments.resize(arguments.size() + 1);
				for (size_t i = arguments.size() - 1; i > insertPos; i--) arguments[i] = arguments[i - 1];
				arguments[insertPos] = "\"\"";
				break;

			case 4: break;

			default: throw CommandSyntaxException("Error: Too many arguments for command tr!");
			}
		}
	}
}