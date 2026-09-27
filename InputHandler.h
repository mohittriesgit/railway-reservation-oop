/**
 * @file InputHandler.h
 * @brief Header file for the InputHandler class.
 *
 * The InputHandler class is responsible for all input from the keyboard.
 * It simulates the keypad of the Railway Reservation System.
 * No other class in the system is allowed to use cin directly;
 * all input must go through this class.
 */

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <string>  // Required for std::string return type

using std::string;

/**
 * @class InputHandler
 * @brief Handles all console input for the Railway Reservation System.
 *
 * This class encapsulates every input operation, ensuring that
 * no other class in the system directly accesses std::cin.
 * It provides methods for reading integers, strings, and doubles.
 */
class InputHandler {
public:
    /**
     * @brief Reads and returns an integer value from standard input.
     * @return The integer entered by the user.
     */
    int getIntInput() const;

    /**
     * @brief Reads and returns a full line of text from standard input.
     *
     * Uses std::getline to capture the entire line, including spaces.
     *
     * @return The string entered by the user.
     */
    string getStringInput() const;

    /**
     * @brief Reads and returns a double value from standard input.
     * @return The double entered by the user.
     */
    double getDoubleInput() const;
};

#endif // INPUTHANDLER_H
