#include "InputStream.h"

// Constructor.
InputStream::InputStream() {
    this->isEOF = false;
}

// Using readLine(), separates line into arguments.
std::vector <std::string> InputStream::getArguments() {
    std::string input = this->readLine();
    bool isQuoted = false;
    if (input.length() > this->maxLineLength) input = input.substr(0, this->maxLineLength);
    std::string current = "";
    std::vector <std::string> result;

    for (int i = 0; i < input.length(); i++) {
        if (!isQuoted) {
            switch (input[i]) {
            // Piping
            case '|':
                if (!current.empty()) result.push_back(current);
                result.push_back("|");
                // Skip to next nonblank character
                i++;
                while (std::isspace(input[i]) && i < input.length()) i++;
                current.clear();
                if (i < input.length()) current += input[i];
            break;

            // Input redirection
            case '<':
                current += input[i];
                i++;
                while (std::isspace(input[i]) && i < input.length()) i++;
                if (i < input.length()) current += input[i];
            break;

            // Output redirection
            case '>':
                current += input[i];
                i++;
                while (std::isspace(input[i]) && i < input.length()) i++;
                if (i < input.length()) {
                    current += input[i];
                    if (input[i] == '>') {
                        i++;
                        while (std::isspace(input[i]) && i < input.length()) i++;
                        if (i < input.length()) current += input[i];
                    }
                }
                break;
            
            // Quotation
            case '\"':
                current += input[i];
                isQuoted = !isQuoted;
            break;

            // Blank space (https://en.cppreference.com/w/cpp/string/byte/isspace)
            case ' ': case '\f': case '\n': case '\r': case '\t': case '\v':
                if (!current.empty()) result.push_back(current);
                current.clear();
            break;

            default:
                current += input[i];
            }
        }
        else {
            switch (input[i]) {
            case '"':
                current += input[i];
                if (!current.empty()) result.push_back(current);
                current.clear();
                isQuoted = !isQuoted;
            break;
            default:
                current += input[i];
            }
        }
        
    }

    if (!current.empty()) result.push_back(current);

    return result;
}

// Returns isEOF.
bool InputStream::eof() const {
    return this->isEOF;
}