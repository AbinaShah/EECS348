// calculator.cpp
// Contains all the actual logic for trimming strings,
// validating if a string is a double, and adding two string doubles.

#include "calculator.hpp"     // Include function declarations
#include <string>             // For using string data type
#include <algorithm>          // For max()
#include <cctype>             // For isdigit()

// Removes spaces and tabs from beginning and end of a string
std::string trim(std::string s) {
    int start = s.find_first_not_of(" \t\r\n");  // find where non-space starts
    int end = s.find_last_not_of(" \t\r\n");     // find where non-space ends
    if (start == std::string::npos) return "";   // if all spaces, return empty string
    return s.substr(start, end - start + 1);     // return trimmed substring
}

// Checks if the given string is a valid double format (like "1.23", "-5.0", "+000.1")
bool isValidDouble(std::string s) {
    int i = 0;

    // First character can be '+' or '-'
    if (s[i] == '+' || s[i] == '-') i++;

    bool digitsBefore = false;

    // Check digits before decimal point
    while (i < s.size() && isdigit(s[i])) {
        digitsBefore = true;
        i++;
    }

    // Check for optional decimal point
    if (i < s.size() && s[i] == '.') {
        i++;

        bool digitsAfter = false;

        // Must have at least one digit after the dot
        while (i < s.size() && isdigit(s[i])) {
            digitsAfter = true;
            i++;
        }

        if (!digitsAfter) return false;  // Invalid if nothing after decimal
    }

    // Return true only if we reached the end and had digits before dot
    return digitsBefore && i == s.size();
}

// Adds zeros to left or right to make string equal in length
std::string pad(std::string s, int len, bool left) {
    while (s.size() < len) {
        s = left ? "0" + s : s + "0";  // add zero in front or back
    }
    return s;
}

// Adds two valid double strings (like "1.5" + "-123.456")
// Does not use any double or float conversion
std::string addStrings(std::string a, std::string b) {
    // Split a into integer and decimal parts
    int dotA = a.find('.');
    int dotB = b.find('.');

    std::string intA = (dotA == std::string::npos) ? a : a.substr(0, dotA);
    std::string decA = (dotA == std::string::npos) ? "" : a.substr(dotA + 1);

    std::string intB = (dotB == std::string::npos) ? b : b.substr(0, dotB);
    std::string decB = (dotB == std::string::npos) ? "" : b.substr(dotB + 1);

    // Pad decimal parts to same length (on the right)
    int maxDec = std::max(decA.size(), decB.size());
    decA = pad(decA, maxDec, false);
    decB = pad(decB, maxDec, false);

    // Pad integer parts to same length (on the left)
    int maxInt = std::max(intA.size(), intB.size());
    intA = pad(intA, maxInt);
    intB = pad(intB, maxInt);

    std::string resultDec = "";  // result of decimal addition
    int carry = 0;               // carry for addition

    // Add decimal digits from right to left
    for (int i = maxDec - 1; i >= 0; i--) {
        int sum = (decA[i] - '0') + (decB[i] - '0') + carry;
        carry = sum / 10;
        resultDec = char((sum % 10) + '0') + resultDec;
    }

    std::string resultInt = "";  // result of integer addition

    // Add integer digits from right to left
    for (int i = maxInt - 1; i >= 0; i--) {
        int dA = isdigit(intA[i]) ? intA[i] - '0' : 0;
        int dB = isdigit(intB[i]) ? intB[i] - '0' : 0;
        int sum = dA + dB + carry;
        carry = sum / 10;
        resultInt = char((sum % 10) + '0') + resultInt;
    }

    // If there's any carry left, add it to the front
    if (carry > 0) {
        resultInt = char(carry + '0') + resultInt;
    }

    // Remove leading zeros from integer part (e.g., "000123" → "123")
    while (resultInt.size() > 1 && resultInt[0] == '0') {
        resultInt = resultInt.substr(1);
    }

    // Return combined result
    return resultDec == "" ? resultInt : resultInt + "." + resultDec;
}
