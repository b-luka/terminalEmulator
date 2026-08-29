#include "PromptCommand.h"
#include "Instance.h"

// Constructor.
PromptCommand::PromptCommand(const std::vector <std::string>& arguments_, Instance* instance_) : ConsoleCommand(arguments_), instance(instance_) {
	if (typeid(*(this->input)) != typeid(StringInputStream))
		throw CommandSyntaxException("Error: Invalid input for command prompt!");
	if (this->options.size() != 0) throw CommandSyntaxException("Error: Too many options!");
}


// Overriden. Changes instance prompt.
void PromptCommand::run() {
	std::string line = this->input->readLine();
	if (!this->input->eof()) throw CommandSyntaxException("Error: Prompt must be entered in 1 line!");
	if (line.empty()) throw CommandSyntaxException("Error: Prompt can't be empty!");
	this->instance->setPrompt(line);
}