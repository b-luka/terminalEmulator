#ifndef OOP1PROJECT_COMMAND_H
#define OOP1PROJECT_COMMAND_H
#include <string>
#include <vector>
#include <memory>
#include "OutputStream.h"
#include "ConsoleInputStream.h"
#include "ConsoleOutputStream.h"
#include "FileInputStream.h"
#include "FileOutputStream.h"
#include "InputStream.h"
#include "StringInputStream.h"
#include "FileInputStream.h"
#include "GenericException.h"

// Command abstraction. Abstract class. Represents a command that can be ran, and when ran sets it's result.
class Command {
public:
	// Abstract. To be overriden. Runs a command given the arguments.
	virtual void run() = 0;

	// Virtual destructor.
	virtual ~Command() = default;

	// Result string getter.
	std::string getResult() const { return this->result; }

	// Check if input redirection is present. -1 if not, index in arguments if it is.
	int checkInputRedirection() const;

	// Check if output redirection is present. -1 if not, index in arguments if it is.
	int checkOutputRedirection() const;

	// Prints result to output. Virtual.
	virtual void printResult() const;

	// Add result to an argument array.
	static void addPreviousResult(std::vector <std::string>& arguments, const std::string& argumentToAdd);

	// inputRedirectionPresent getter.
	bool hasInputRedirection() const { return this->inputRedirectionPresent; }

	// outputRedirectionPresent getter.
	bool hasOutputRedirection() const { return this->outputRedirectionPresent; }

protected:

	// Constructor.
	Command(const std::vector <std::string>& arguments_);

	// Array of strings representing arguments. First argument is always the command name.
	std::vector <std::string> arguments;

	// Output stream to be written to.
	std::unique_ptr<OutputStream> output;

	// Input stream to read from.
	std::unique_ptr<InputStream> input;

	// Input stream setter.
	virtual void setInputStream(std::unique_ptr<InputStream> input_);

	// Output stream setter.
	virtual void setOutputStream(std::unique_ptr<OutputStream> output_);

	// Resulting string.
	std::string result;

	// Remove > and < from a string (in case of redirection).
	std::string redirectionFileName(const std::string& input_) const;

	// Array of options (-x).
	std::vector <std::string> options;

	// Is input redirection present?
	bool inputRedirectionPresent;
	
	// Is output redirection present?
	bool outputRedirectionPresent;
};

#endif