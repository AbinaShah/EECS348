// main.cpp
// This file handles user input and calls functions from calculator.cpp

#include "calculator.hpp"  // includes the functions we defined
#include <iostream>        // for input/output
#include <fstream>         // to read from a file

int main() {
    std::string file;  // this will store the name of the input file

    std::cout << "Enter filename: ";  // ask user for file name
    std::cin >> file;  // get the file name from user

    std::ifstream in(file);  // open the file for reading
    if (!in) {  // if the file can't be opened
        std::cout << "File couldn't be opened.\n";  // show error
        return 1;  // exit with error code
    }

    std::string line;  // to store each line we read
    std::string fixed = "-123.456";  // this is the number we add to each valid input

    // go through each line in the file
    while (getline(in, line)) {
        line = trim(line);  // remove spaces from front and end

        std::cout << "Input: " << line << " -> ";  // show the input we're processing

        if (isValidDouble(line)) {  // check if it's a valid double
            std::string sum = addStrings(line, fixed);  // add -123.456 using string math
            std::cout << "Valid. After adding -123.456: " << sum << std::endl;  // show result
        } else {
            std::cout << "Invalid double format." << std::endl;  // if not valid, say so
        }
    }

    return 0;  // done
}
