#include "BatchCommand.h"
#include "Instance.h"

// Executes commands from input.
void BatchCommand::run() {
	while (!this->input->eof()) {
		try {
			std::vector <std::string> args = this->input->getArguments();
			if (args.size() > 0)
				this->commandResults += this->instance->runCommand(args, true) + "\n";
		}
		catch (const GenericException& ex) {
			this->output->writeLine(ex.getMessage());
		}
	}
	std::cout << commandResults;
}