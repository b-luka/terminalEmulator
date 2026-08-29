#include "ConsoleCommand.h"

// Constructor.
ConsoleCommand::ConsoleCommand(const std::vector <std::string>& arguments_) : Command(arguments_) {
	try {
		int inPos = this->checkInputRedirection();
		int outPos = this->checkOutputRedirection();

		// Redirection is present only at the end of a command.
		for (int i = inPos + 1; i < this->arguments.size() && i > 1; i++) {
			if (this->arguments[i][0] != '<' && this->arguments[i][0] != '>') {
				throw CommandSyntaxException("Error: Redirection must happen at the end of a command!");
			}
		}
		
		for (int i = outPos + 1; i < this->arguments.size() && i > 1; i++) {
			if (this->arguments[i][0] != '<' && this->arguments[i][0] != '>') {
				throw CommandSyntaxException("Error: Redirection must happen at the end of a command!");
			}
		}

		// Filter redirection out of arguments and set redirects.
		if (inPos > 0) {
			std::string fileName = this->redirectionFileName(this->arguments[inPos]);
			if (fileName.length() < 2) throw CommandSyntaxException("Error: Input redirection must not be empty!");
			std::ifstream fileCheck(fileName);
			if (!fileCheck.good()) {
				throw FileSystemException("Error: Can't open file " + fileName);
			}
			else {
				this->setInputStream(std::make_unique<FileInputStream>(fileName));
				this->inputRedirectionPresent = true;
			}
			this->arguments.erase(this->arguments.begin() + inPos);
			outPos = this->checkOutputRedirection();
		}

		if (outPos > 0) {
			std::string outArg = this->arguments[outPos];
			if (outArg.length() < 2 || (outArg.length() < 3 && outArg[1] == '>'))
				throw CommandSyntaxException("Error: Output redirection must not be empty!");

			std::string fileName = this->redirectionFileName(outArg);
			if (outArg[1] == '>') {
				this->setOutputStream(std::make_unique<FileOutputStream>(fileName, FileOutputStream::APPEND));
			}
			else {
				this->setOutputStream(std::make_unique<FileOutputStream>(fileName, FileOutputStream::WRITE));
			}
			this->outputRedirectionPresent = true;
			this->arguments.erase(this->arguments.begin() + outPos);
			
		}
		

		for (int i = 0; i < arguments.size(); i++) {
			if (arguments[i][0] == '-') {
				this->options.push_back(arguments[i]);
				this->arguments.erase(this->arguments.begin() + i);
				i--;
			}
		}

		// Only command name and argument remain in arguments.
		if (this->arguments.size() > 2) throw CommandSyntaxException("Error: Too many arguments!");

		if (this->arguments.size() == 2) {
			if (inPos > 0) throw CommandSyntaxException("Error: Input can't be set and redirected at the same time!");
			std::string inArg = this->arguments[1];
			if (inArg[0] == '"') {
				inArg = inArg.substr(1, inArg.size() - 2);
				this->setInputStream(std::make_unique<StringInputStream>(inArg));
			}
			else {
				std::ifstream fileCheck(inArg);
				if (!fileCheck.good()) {
					throw FileSystemException("Error: Can't open file " + inArg);
				}
				else {
					this->setInputStream(std::make_unique<FileInputStream>(inArg));
				}
			}
		}
	}
	catch (const CommandSyntaxException& ex) {
		throw ex;
	}
}