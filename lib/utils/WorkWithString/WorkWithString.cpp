#include "WorkWithString.hpp"

std::vector<std::string> SplitString(std::string str, char delimiter) {
    std::vector<std::string> result;
    std::string currentWord;

    for (char c : str) {
        if (c == delimiter) {
            if (!currentWord.empty()) {
                result.push_back(currentWord);
                currentWord.clear();
            }
        } else {
            currentWord += c;
        }
    }

    if (!currentWord.empty()) {
        result.push_back(currentWord);
    }

    return result;
}