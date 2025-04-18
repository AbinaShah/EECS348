// calculator.hpp
// Just lists the function names so they can be shared between files

#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <string>

// removes extra spaces from start and end
std::string trim(std::string s);

// checks if a string is a valid double
bool isValidDouble(std::string s);

// adds two double strings without using double type
std::string addStrings(std::string a, std::string b);

#endif