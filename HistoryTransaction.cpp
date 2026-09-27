/**
 * @file HistoryTransaction.cpp
 * @brief Implementation file for the HistoryTransaction class.
 *
 * Retrieves and displays all booking records for the current passenger.
 */

#include "HistoryTransaction.h"
#include "Screen.h"
#include "InputHandler.h"
#include "ReservationDatabase.h"
#include "Booking.h"
#include <vector>
#include <string>
#include <iomanip>

using std::vector;
using std::to_string;

/**
 * @brief Constructor. Delegates to Transaction base constructor.
 */
HistoryTransaction::HistoryTransaction(int passengerID, Screen& screen,
                                       InputHandler& inputHandler,
                                       ReservationDatabase& database)
    : Transaction(passengerID, screen, inputHandler, database) {
}

/**
 * @brief Executes the history transaction.
 *
 * Retrieves all bookings for the passenger and displays a summary
 * table with PNR, Train, Date, and Status for each booking.
 */
void HistoryTransaction::execute() {
    Screen& screen = getScreen();
    ReservationDatabase& db = getDatabase();

    screen.displaySeparator();
    screen.displayMessageLine("=== BOOKING HISTORY ===");
    screen.displaySeparator();

    // Get all bookings for this passenger
    vector<Booking*> history = db.getBookingHistory(getPassengerID());

    if (history.empty()) {
        // No bookings found
        screen.displayMessageLine("No bookings found.");
    } else {
        // Display summary header
        screen.displayMessageLine("PNR       | Train               | Date           | Status");
        screen.displaySeparator();

        // Display one line per booking
        for (size_t i = 0; i < history.size(); ++i) {
            Booking* b = history[i];
            // Format each booking as a summary row
            string line = to_string(b->getPNR()) + "    | " +
                          b->getTrainName();

            // Pad train name to 20 characters for alignment
            while (line.length() < 36) {
                line += " ";
            }
            line += "| " + b->getJourneyDate();

            // Pad date for alignment
            while (line.length() < 53) {
                line += " ";
            }
            line += "| " + b->getBookingStatus();

            screen.displayMessageLine(line);
        }
    }

    screen.displaySeparator();

    // Display wallet balance
    screen.displayMessage("Wallet Balance: ");
    screen.displayDollarAmount(db.getWalletBalance(getPassengerID()));
    screen.displayMessageLine("");
    screen.displaySeparator();
}
