/**
 * @file Screen.cpp
 * @brief Implementation file for the Screen class.
 *
 * Contains the definitions of all member functions declared in Screen.h.
 * This is the ONLY file in the system that uses std::cout directly.
 */

#include "Screen.h"   // Include the Screen class header
#include <iostream>    // For std::cout
#include <iomanip>     // For std::setw, std::left, std::fixed, std::setprecision

using std::cout;
using std::endl;
using std::setw;
using std::left;
using std::fixed;
using std::setprecision;

/**
 * @brief Displays a message without a trailing newline.
 * @param message The message string to print.
 */
void Screen::displayMessage(string message) const {
    cout << message;
}

/**
 * @brief Displays a message followed by a newline.
 * @param message The message string to print.
 */
void Screen::displayMessageLine(string message) const {
    cout << message << endl;
}

/**
 * @brief Displays a monetary amount with "Rs." prefix, formatted
 *        to exactly 2 decimal places.
 * @param amount The monetary value to display.
 */
void Screen::displayDollarAmount(double amount) const {
    cout << "Rs." << fixed << setprecision(2) << amount;
}

/**
 * @brief Displays a visual separator: a line of 50 dashes.
 */
void Screen::displaySeparator() const {
    cout << "--------------------------------------------------" << endl;
}

/**
 * @brief Displays the column header row for the train listing table.
 *
 * The columns are: TrainNo, TrainName, From, To, Departure, Arrival,
 * General (available seats), Sleeper (available seats), AC (available seats).
 */
void Screen::displayTrainHeader() const {
    cout << left
         << setw(10) << "TrainNo"
         << setw(20) << "TrainName"
         << setw(12) << "From"
         << setw(12) << "To"
         << setw(12) << "Departure"
         << setw(10) << "Arrival"
         << setw(10) << "General"
         << setw(10) << "Sleeper"
         << setw(6)  << "AC"
         << endl;
}

/**
 * @brief Displays one row of formatted train information.
 *
 * Each column is aligned to match the header printed by displayTrainHeader().
 *
 * @param trainNo   Train number.
 * @param name      Train name.
 * @param src       Source station.
 * @param dest      Destination station.
 * @param dep       Departure time string.
 * @param arr       Arrival time string.
 * @param gen       Available General seats.
 * @param sl        Available Sleeper seats.
 * @param ac        Available AC seats.
 */
void Screen::displayTrainRow(int trainNo, string name, string src, string dest,
                             string dep, string arr, int gen, int sl, int ac) const {
    cout << left
         << setw(10) << trainNo
         << setw(20) << name
         << setw(12) << src
         << setw(12) << dest
         << setw(12) << dep
         << setw(10) << arr
         << setw(10) << gen
         << setw(10) << sl
         << setw(6)  << ac
         << endl;
}

/**
 * @brief Displays complete booking details in a labeled, multi-line format.
 *
 * Each field is printed on its own labeled line for clarity.
 *
 * @param PNR           PNR number.
 * @param trainName     Name of the train.
 * @param trainNo       Train number.
 * @param src           Source station.
 * @param dest          Destination station.
 * @param date          Journey date.
 * @param dep           Departure time.
 * @param coachType     Coach type string (General/Sleeper/AC).
 * @param seatNo        Assigned seat number.
 * @param passengerName Name of the passenger.
 * @param fare          Ticket fare.
 * @param status        Booking status (CONFIRMED/CANCELLED).
 */
void Screen::displayBookingDetails(int PNR, string trainName, int trainNo,
                                   string src, string dest, string date,
                                   string dep, string coachType, int seatNo,
                                   string passengerName, double fare,
                                   string status) const {
    cout << endl;
    cout << "========== BOOKING DETAILS ==========" << endl;
    cout << "  PNR Number     : " << PNR << endl;
    cout << "  Passenger Name : " << passengerName << endl;
    cout << "  Train Name     : " << trainName << endl;
    cout << "  Train Number   : " << trainNo << endl;
    cout << "  From           : " << src << endl;
    cout << "  To             : " << dest << endl;
    cout << "  Journey Date   : " << date << endl;
    cout << "  Departure Time : " << dep << endl;
    cout << "  Coach Type     : " << coachType << endl;
    cout << "  Seat Number    : " << seatNo << endl;
    cout << "  Fare           : Rs." << fixed << setprecision(2) << fare << endl;
    cout << "  Status         : " << status << endl;
    cout << "=====================================" << endl;
    cout << endl;
}
