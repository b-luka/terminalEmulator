#include "TimeCommand.h"

// Constructor.
TimeCommand::TimeCommand(const std::vector <std::string>& arguments_) : ConsoleCommand(arguments_) {
	if (typeid(*(this->input)) != typeid(ConsoleInputStream)) 
		throw CommandSyntaxException("Error: Command time has no input!");
	if (this->options.size() != 0) throw CommandSyntaxException("Error: Too many options!");
}

// Overriden. Prints the current time to the output. hh:mm:ss format.
void TimeCommand::run() {
	auto now = std::chrono::system_clock::now();
	std::time_t nowTimeT = std::chrono::system_clock::to_time_t(now);
	std::tm nowTm;
	localtime_s(&nowTm, &nowTimeT);

	int hour, min, sec;
	hour = nowTm.tm_hour;
	min = nowTm.tm_min;
	sec = nowTm.tm_sec;

	std::string hourStr = "", minStr = "", secStr = "";
	if (hour < 10) hourStr += "0";
	if (min < 10) minStr += "0";
	if (sec < 10) secStr += "0";
	hourStr += std::to_string(hour);
	minStr += std::to_string(min);
	secStr += std::to_string(sec);

	std::string timeStr = hourStr + ":" + minStr + ":" + secStr;
	this->result += timeStr;
}

// Prints result to output.
void TimeCommand::printResult() const {
	if (this->result == "") return;

	if (typeid(*(this->output)) == typeid(FileOutputStream)) {
		this->output->write(result);
		return;
	}
	this->output->writeLine(result);
}