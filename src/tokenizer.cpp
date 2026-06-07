// tokenize.cpp
#include "tokenizer.hpp"

#include <sstream>

std::vector<std::string> tokenize(const std::string& source) {
    std::string spaced;
    
    // Adding space around () makes string.size * 3
    // but choose * 2 for a reasonable estimation.
    spaced.reserve(source.size() * 2);

    bool inside_comment = false;

    for (char ch : source) {
        if (inside_comment) {
            if (ch == '\n') {
                inside_comment = false;
                spaced += ' ';
            }
            continue;
        }

        if (ch == ';') {
            inside_comment = true;
        } else if (ch == '(' || ch == ')') {
            spaced += ' ';
            spaced += ch;
            spaced += ' ';
        } else {
            spaced += ch;
        }
    }

    std::istringstream stream(spaced);
    std::vector<std::string> tokens;
    std::string token;

    while (stream >> token) {
        tokens.push_back(token);
    }

    return tokens;
}