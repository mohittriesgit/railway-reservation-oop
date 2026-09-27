/**
 * @file InputHandler.cpp
 * @brief Implementation file for the InputHandler class.
 *
 * Contains the definitions of all member functions declared in InputHandler.h.
 * This is the ONLY file in the system that uses std::cin directly.
 */

#include "InputHandler.h"  // Include the InputHandler class header
#include <iostream>         // For std::cin
#include <string>           // For std::string and std::getline
#include <limits>           // For std::numeric_limits (to clear input buffer)

using std::cin;
using std::getline;
using std::numeric_limits;
using std::streamsize;

/**
 * @brief Reads an integer from standard input.
 *
 * After reading the integer, the remaining characters in the input
 * buffer (including the newline) are discarded so that subsequent
 * getline calls work correctly.
 *
 * @return The integer value entered by the user.
 */
int InputHandler::getIntInput() const {
    int value;              // Variable to hold the user's integer input
    cin >> value;           // Read the integer from standard input
    // Clear the rest of the input buffer up to and including the newline,
    // to prevent leftover characters from affecting subsequent reads.
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;           // Return the integer value to the caller
}

/**
 * @brief Reads a full line of text from standard input.
 *
 * Uses std::getline so that the entire line (including spaces) is
 * captured in the returned string.
 *
 * @return The string entered by the user.
 */
string InputHandler::getStringInput() const {
    string value;           // Variable to hold the user's string input
    getline(cin, value);    // Read the full line from standard input
    return value;           // Return the string to the caller
}

/**
 * @brief Reads a double from standard input.
 *
 * After reading the double, the remaining characters in the input
 * buffer (including the newline) are discarded.
 *
 * @return The double value entered by the user.
 */
double InputHandler::getDoubleInput() const {
    double value;           // Variable to hold the user's double input
    cin >> value;           // Read the double from standard input
    // Clear the rest of the input buffer.
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;           // Return the double value to the caller
}
