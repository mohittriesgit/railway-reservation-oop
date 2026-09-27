/**
 * @file Screen.h
 * @brief Header file for the Screen class.
 *
 * The Screen class is responsible for all output to the console.
 * It simulates the display screen of the Railway Reservation System.
 * No other class in the system is allowed to use cout directly;
 * all output must go through this class.
 */

#ifndef SCREEN_H
#define SCREEN_H

#include <string>  // Required for std::string parameter types

using std::string;

/**
 * @class Screen
 * @brief Handles all console output for the Railway Reservation System.
 *
 * This class encapsulates every output operation, ensuring that
 * no other class in the system directly accesses std::cout.
 * It provides methods for displaying messages, formatted monetary
 * amounts, separators, and structured train/booking information.
 */
class Screen {
public:
    /**
     * @brief Displays a message without a trailing newline.
     * @param message The string message to display.
     */
    void displayMessage(string message) const;

    /**
     * @brief Displays a message followed by a newline character.
     * @param message The string message to display.
     */
    void displayMessageLine(string message) const;

    /**
     * @brief Displays a monetary amount formatted to 2 decimal places
     *        with the "Rs." prefix.
     * @param amount The monetary amount to display.
     */
    void displayDollarAmount(double amount) const;

    /**
     * @brief Displays a separator line consisting of 50 dashes.
     *
     * Used to visually separate sections of output on the console.
     */
    void displaySeparator() const;

    /**
     * @brief Displays column headers for the train listing table.
     *
     * Headers: TrainNo | TrainName | From | To | Departure | Arrival |
     *          General | Sleeper | AC
     */
    void displayTrainHeader() const;

    /**
     * @brief Displays one row of train information formatted to columns.
     * @param trainNo   The train number.
     * @param name      The train name.
     * @param src       The source station.
     * @param dest      The destination station.
     * @param dep       The departure time.
     * @param arr       The arrival time.
     * @param gen       Available seats in General coach.
     * @param sl        Available seats in Sleeper coach.
     * @param ac        Available seats in AC coach.
     */
    void displayTrainRow(int trainNo, string name, string src, string dest,
                         string dep, string arr, int gen, int sl, int ac) const;

    /**
     * @brief Displays full booking details in a labeled format.
     * @param PNR           The PNR (Passenger Name Record) number.
     * @param trainName     The name of the train.
     * @param trainNo       The train number.
     * @param src           The source station.
     * @param dest          The destination station.
     * @param date          The journey date.
     * @param dep           The departure time.
     * @param coachType     The type of coach (General/Sleeper/AC).
     * @param seatNo        The assigned seat number.
     * @param passengerName The name of the passenger.
     * @param fare          The fare amount.
     * @param status        The booking status (CONFIRMED/CANCELLED).
     */
    void displayBookingDetails(int PNR, string trainName, int trainNo,
                               string src, string dest, string date,
                               string dep, string coachType, int seatNo,
                               string passengerName, double fare,
                               string status) const;
};

#endif // SCREEN_H
