// calculator.cpp
// Contains all the actual logic for checking and adding string doubles

#include "calculator.hpp"
#include <string>
#include <algorithm>
#include <cctype>

// Removes spaces from start and end
std::string trim(std::string s) {
    int start = s.find_first_not_of(" \t\r\n");
    int end = s.find_last_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    return s.substr(start, end - start + 1);
}

// Checks if the string follows double number rules
bool isValidDouble(std::string s) {
    int i = 0;
    if (s[i] == '+' || s[i] == '-') i++;

    bool digitsBefore = false;
    while (i < s.size() && isdigit(s[i])) {
        digitsBefore = true;
        i++;
    }

    if (i < s.size() && s[i] == '.') {
        i++;
        bool digitsAfter = false;
        while (i < s.size() && isdigit(s[i])) {
            digitsAfter = true;
            i++;
        }
        if (!digitsAfter) return false;
    }

    return digitsBefore && i == s.size();
}

// Adds 0s to make lengths equal
std::string pad(std::string s, int len, bool left = true) {
    while (s.size() < len) {
        s = left ? "0" + s : s + "0";
    }
    return s;
}

// Adds two double strings (like '1.5' + '2.3') manually
std::string addStrings(std::string a, std::string b) {
    int dotA = a.find('.');
    int dotB = b.find('.');

    std::string intA = (dotA == std::string::npos) ? a : a.substr(0, dotA);
    std::string decA = (dotA == std::string::npos) ? "" : a.substr(dotA + 1);

    std::string intB = (dotB == std::string::npos) ? b : b.substr(0, dotB);
    std::string decB = (dotB == std::string::npos) ? "" : b.substr(dotB + 1);

    int maxDec = std::max(decA.size(), decB.size());
    decA = pad(decA, maxDec, false);
    decB = pad(decB, maxDec, false);

    int maxInt = std::max(intA.size(), intB.size());
    intA = pad(intA, maxInt);
    intB = pad(intB, maxInt);

    std::string resultDec = "";
    int carry = 0;

    for (int i = maxDec - 1; i >= 0; i--) {
        int sum = (decA[i] - '0') + (decB[i] - '0') + carry;
        carry = sum / 10;
        resultDec = char((sum % 10) + '0') + resultDec;
    }

    std::string resultInt = "";
    for (int i = maxInt - 1; i >= 0; i--) {
        int dA = isdigit(intA[i]) ? intA[i] - '0' : 0;
        int dB = isdigit(intB[i]) ? intB[i] - '0' : 0;
        int sum = dA + dB + carry;
        carry = sum / 10;
        resultInt = char((sum % 10) + '0') + resultInt;
    }

    if (carry > 0) resultInt = char(carry + '0') + resultInt;

    while (resultInt.size() > 1 && resultInt[0] == '0') {
        resultInt = resultInt.substr(1);
    }

    return resultDec == "" ? resultInt : resultInt + "." + resultDec;
}