#include "ConsoleInputStream.h"

ConsoleInputStream::ConsoleInputStream() : InputStream() {}

// Reads line using std::getline().
std::string ConsoleInputStream::readLine() {
    std::string result;
    std::getline(std::cin, result);
    return result;
}

bool ConsoleInputStream::eof() const {
    if (std::cin.eof()) {
        std::cin.clear();
        return true;
    }
    return false;
}