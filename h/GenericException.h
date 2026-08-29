#ifndef OOP1PROJECT_EXCEPTIONS_H
#define OOP1PROJECT_EXCEPTIONS_H
#include <string>
#include <iostream>
#include <vector>

// Generic exception class.
class GenericException {
public:
	// Constructor.
	GenericException(const std::string& message_) : message(message_) {}

	// Destructor.
	virtual ~GenericException() = default;

	// Print error message. Virtual.
	virtual void printMessage() const { std::cout << this->message << '\n'; }

	// message getter
	virtual std::string getMessage() const { return this->message; }

protected:
	// Error message.
	std::string message;
};

// Command syntax exception.
class CommandSyntaxException : public GenericException {
public:
	// Constructor.
	CommandSyntaxException(const std::string& message_) : GenericException(message_) {}

	// Destructor.
	~CommandSyntaxException() = default;
};

// Command vocabulary exception.
class CommandVocabException : public GenericException {
public:
	// Constructor.
	CommandVocabException(const std::string& message_, const std::vector <std::string>& arguments_, size_t errorPosition_)
		: GenericException(message_), arguments(arguments_), errorPosition(errorPosition_) {}

	// Destructor.
	~CommandVocabException() = default;

	// Print error message with error position. Overriden.
	void printMessage() const override;

	// message getter. overriden
	std::string getMessage() const override;

private:
	// Error position.
	size_t errorPosition;

	// Current command arguments.
	std::vector <std::string> arguments;
};

// File system exception.
class FileSystemException : public GenericException {
public:
	// Constructor.
	FileSystemException(const std::string& message_) : GenericException(message_) {}

	// Destructor.
	~FileSystemException() = default;
};

#endif
