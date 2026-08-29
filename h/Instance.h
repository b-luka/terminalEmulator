#ifndef OOP1PROJECT_INSTANCE_H
#define OOP1PROJECT_INSTANCE_H
#include "CommandFactory.h"
#include "ConsoleInputStream.h"
#include "FileInputStream.h"
#include "ConsoleOutputStream.h"
#include "OutputStream.h"

#include <string>
#include <vector>
#include <iostream>
#include <list>

// An instance of a console terminal.
class Instance {
public:
	// Constructor.
	Instance()
		: inputStream(std::make_unique<ConsoleInputStream>()),
		prompt("$"),
		commandFactory(this) {}

	// Reads and executes commands until the given input is EOF.
	void run();

	// Runs a single command (or a pipe of commands) in a single line.
	// Argument saveToString defaults to false. If true, returns the command result instead of printing it.
	std::string runCommand(std::vector <std::string>& args, bool saveToString = false);

	// Destructor.
	~Instance() = default;

	// Prompt setter.
	void setPrompt(const std::string& prompt_) { this->prompt = prompt_; }

	// Finds position of the next pipe symbol in arguments (-1 if not found).
	int popNextPipePos(std::vector <std::string>& arguments) const;

	// Subarray helper method. Returns all element found within [start, end).
	std::vector <std::string> subvector(const std::vector <std::string>& arr, size_t start, size_t end) const;

private:
	// Input stream to read from.
	std::unique_ptr<ConsoleInputStream> inputStream;

	// Prompt printed before reading a line.
	std::string prompt;

	// Command factory to generate commands.
	CommandFactory commandFactory;
};

#endif
