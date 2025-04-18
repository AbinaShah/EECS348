// main.cpp
// Only handles user input and calling functions from calculator.cpp

#include "calculator.hpp"
#include <iostream>
#include <fstream>

int main() {
    std::string file;
    std::cout << "Enter filename: ";
    std::cin >> file;

    std::ifstream in(file);
    if (!in) {
        std::cout << "File couldn't be opened.\n";
        return 1;
    }

    std::string line;
    std::string fixed = "-123.456";  // this is what we add to every valid input

    while (getline(in, line)) {
        line = trim(line);  // clean up the input line
        std::cout << "Input: " << line << " -> ";

        if (isValidDouble(line)) {
            std::string sum = addStrings(line, fixed);
            std::cout << "Valid. After adding -123.456: " << sum << std::endl;
        } else {
            std::cout << "Invalid double format." << std::endl;
        }
    }

    return 0;
}
