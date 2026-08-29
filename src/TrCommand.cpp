#include "TrCommand.h"

// Constructor.
TrCommand::TrCommand(const std::vector <std::string>& arguments_) : Command(arguments_) {
	if (this->options.size() != 0) throw CommandSyntaxException("Error: Too many options!");
	try {
		int inPos = this->checkInputRedirection();
		int outPos = this->checkOutputRedirection();

		// Redirection is present only at the end of a command.
		for (int i = inPos + 1; i < this->arguments.size() && i > 1; i++) {
			if (this->arguments[i][0] != '<' || this->arguments[i][0] != '>') {
				throw CommandSyntaxException("Error: Redirection must happen at the end of a command!");
			}
		}

		for (int i = outPos + 1; i < this->arguments.size() && i > 1; i++) {
			if (this->arguments[i][0] != '<' || this->arguments[i][0] != '>') {
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
			if (outArg.length() < 2 || (outArg.length() < 3 && outArg[1] == '>')) throw CommandSyntaxException("Error: Output redirection must not be empty!");
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

		switch (this->arguments.size()) {
		case 0: case 1:
			throw CommandSyntaxException("Error: Not enough arguments!");
			break;

		case 2:										// tr "what"
			if (this->arguments[1][0] != '"') throw CommandSyntaxException("Error: Missing argument 'what'!");
			this->what = this->arguments[1].substr(1, this->arguments[1].size() - 2);
			break;

		case 3:
			if (this->arguments[1][0] == '"') {		// tr "what" "with"
				this->what = this->arguments[1].substr(1, this->arguments[1].size() - 2);
				if (this->arguments[2][0] != '"') throw CommandSyntaxException("Error: Invalid tr call!");
				this->with = this->arguments[2].substr(1, this->arguments[2].size() - 2);
			}
			else {									// tr input.txt "what"
				if (this->arguments[2][0] != '"') throw CommandSyntaxException("Error: Missing argument 'what'!");
				this->what = this->arguments[2].substr(1, this->arguments[2].size() - 2);
				std::string fileName = this->arguments[1];
				std::ifstream fileCheck(fileName);
				if (!fileCheck.good()) {
					throw FileSystemException("Error: Can't open file " + fileName);
				}
				else {
					this->setInputStream(std::make_unique<FileInputStream>(fileName));
				}
			}
			break;

		case 4:
			if (this->arguments[1][0] == '"') {		// tr "arg" "what" "with"
				std::string inputString = this->arguments[1].substr(1, this->arguments[1].size() - 2);
				this->setInputStream(std::make_unique<StringInputStream>(inputString));
				this->what = this->arguments[2].substr(1, this->arguments[2].size() - 2);
				this->with = this->arguments[3].substr(1, this->arguments[3].size() - 2);
			}
			else {									// tr input.txt "what" "with"
				std::string fileName = this->arguments[1];
				std::ifstream fileCheck(fileName);
				if (!fileCheck.good()) {
					throw FileSystemException("Error: Can't open file " + fileName);
				}
				else {
					this->setInputStream(std::make_unique<FileInputStream>(fileName));
				}
				if (this->arguments[2][0] != '"' || this->arguments[3][0] != '"') throw CommandSyntaxException("Error: Invalid tr call!");
				this->what = this->arguments[2].substr(1, this->arguments[2].size() - 2);
				this->with = this->arguments[3].substr(1, this->arguments[3].size() - 2);
			}
			break;

		default:
			throw CommandSyntaxException("Error: Too many arguments!");
		}
	}
	catch (const CommandSyntaxException& ex) {	// pass further
		throw ex;
	}
}

void TrCommand::run() {
	std::string line;
	while (!this->input->eof()) {
		line = this->input->readLine();
		for (int i = 0; i < line.length(); i++) {
			if (line[i] == what[0]) {
				int j = 0;
				while (line[i] == what[j] && i < line.length() && j < what.length()) {
					i++;
					j++;
				}
				if (j == what.length()) {
					result += with;
					if (i < line.length()) result += line[i];
				}
				else {
					while (j >= 0) {
						result += line[i - j];
						j--;
					}
				}
			}
			else {
				result += line[i];
			}
		}
		result += '\n';
	}
	// Erase newline at end
	result = result.substr(0, result.size() - 1);
}