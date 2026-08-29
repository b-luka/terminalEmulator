#include "HeadCommand.h"

// Constructor.
HeadCommand::HeadCommand(const std::vector <std::string>& arguments_) : ConsoleCommand(arguments_) {
	// head always has one option
	if (this->options.size() == 0) throw CommandSyntaxException("Error: No option specified!");
	if (this->options.size() > 1) throw CommandSyntaxException("Error: Too many options!");

	std::string option = this->options[0];

	if (option[1] != 'n')
		throw CommandSyntaxException("Error: " + this->options[0] + " is not a valid option for command head!");
	if (option.size() <= 2) throw CommandSyntaxException("Error: Number must be specified!");
	for (int i = 2; i < option.size(); i++) {
		if (option[i] < '0' || option[i] > '9') {
			throw CommandSyntaxException("Error: Option must be a in the format -nddddd!");
		}
		else if (i > 6) {
			throw CommandSyntaxException("Error: Number too large or invalid!");
		}
	}
}

// Overriden. Prints first -n_ lines to the output.
void HeadCommand::run() {
	int maxLines = std::stoi(options[0].substr(2, options[0].size()));
	int linesRead = 0;

	std::string line;

	while (!this->input->eof()) {
		line = this->input->readLine();
		for (char c : line) {
			if (c == '\n') linesRead++;
			if (linesRead < maxLines) result += c;
		}
		if (linesRead < maxLines) result += "\n";
		linesRead++;
	}
	// Erase newline at end
	result = result.substr(0, result.size() - 1);
}