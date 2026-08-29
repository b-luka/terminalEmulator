#include "WcCommand.h"

// Constructor.
WcCommand::WcCommand(const std::vector <std::string>& arguments_) : ConsoleCommand(arguments_) {
	// wc always has one option
	switch (this->options.size()) {
	case 0:
		throw CommandSyntaxException("Error: No option specified");
	break;
	case 1:
		if (this->options[0] == "-w") {
			this->mode = WcCommand::WORD;
		}
		else if (this->options[0] == "-c") {
			this->mode = WcCommand::CHARACTER;
		}
		else {
			throw CommandSyntaxException("Error: " + this->options[0] + " is not a valid option for command wc");
		}
	break;
	default:
		throw CommandSyntaxException("Error: Too many options!");
	}
}

// Counts characters from the input.
void WcCommand::countCharacters() {
	int chars = 0;
	std::string line;
	while (!this->input->eof()) {
		line = this->input->readLine();
		for (char curr : line) {
			if (curr != '\n') chars++;
		}
	}
	this->result += std::to_string(chars);
}

// Counts words from the input.
void WcCommand::countWords() {
	int words = 0;
	char prev = ' ';
	std::string line;
	while (!this->input->eof()) {
		line = this->input->readLine() + '\n';
		for (char curr : line) {
			if (!std::isspace(prev) && std::isspace(curr)) words++;
			prev = curr;
		}
	}
	this->result += std::to_string(words);
}

// Counts characters or words, depending on the given option.
void WcCommand::run() {
	switch (this->mode) {
	case WcCommand::CHARACTER:
		this->countCharacters();
	break;
	case WcCommand::WORD:
		this->countWords();
	break;
	default:
		throw GenericException("Error: Couldn't process command!");
	}
}