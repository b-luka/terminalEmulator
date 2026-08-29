#include "DateCommand.h"

// Constructor.
DateCommand::DateCommand(const std::vector <std::string>& arguments_) : ConsoleCommand(arguments_) {
	if (typeid(*(this->input)) != typeid(ConsoleInputStream)) {
		throw CommandSyntaxException("Error: Command date has no input!");
	}

	if (this->options.size() != 0) throw CommandSyntaxException("Error: Too many options!");
}

// Overriden. Prints the current date to the output. dd/mm/yyyy format.
void DateCommand::run() {
	auto now = std::chrono::system_clock::now();
	std::time_t nowTimeT = std::chrono::system_clock::to_time_t(now);
	std::tm nowTm;
	localtime_s(&nowTm, &nowTimeT);

	int day, month, year;
	day = nowTm.tm_mday;
	month = nowTm.tm_mon + 1;
	year = nowTm.tm_year + 1900;

	std::string dayStr = "", monthStr = "", yearStr = "";
	if (day < 10) dayStr += "0";
	if (month < 10) monthStr += "0";
	dayStr += std::to_string(day);
	monthStr += std::to_string(month);
	yearStr += std::to_string(year);

	std::string date = dayStr + "/" + monthStr + "/" + yearStr;
	this->result += date;
}

// Prints result to output.
void DateCommand::printResult() const {
	if (this->result == "") return;

	if (typeid(*(this->output)) == typeid(FileOutputStream)) {
		this->output->write(result);
		return;
	}
	this->output->writeLine(result);
}