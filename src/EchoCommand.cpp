#include "EchoCommand.h"

// Copies input to command result.
void EchoCommand::run() {
	std::string line;
	while (!this->input->eof()) {
		line = this->input->readLine();
		result += line + '\n';
	}
	// Erase newline at end
	result = result.substr(0, result.size() - 1);
}