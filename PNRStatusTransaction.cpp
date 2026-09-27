/**
 * @file PNRStatusTransaction.cpp
 * @brief Implementation file for the PNRStatusTransaction class.
 *
 * Prompts for PNR, validates ownership, and displays booking details.
 */

#include "PNRStatusTransaction.h"
#include "Screen.h"
#include "InputHandler.h"
#include "ReservationDatabase.h"
#include "Booking.h"
#include <string>

using std::to_string;

/**
 * @brief Constructor. Delegates to Transaction base constructor.
 */
PNRStatusTransaction::PNRStatusTransaction(int passengerID, Screen& screen,
                                           InputHandler& inputHandler,
                                           ReservationDatabase& database)
    : Transaction(passengerID, screen, inputHandler, database) {
}

/**
 * @brief Executes the PNR status check.
 *
 * Flow:
 * 1. Prompts for PNR (or 0 to go back)
 * 2. Looks up booking
 * 3. Validates ownership
 * 4. Displays full booking details
 */
void PNRStatusTransaction::execute() {
    Screen& screen = getScreen();
    InputHandler& input = getInputHandler();
    ReservationDatabase& db = getDatabase();

    screen.displaySeparator();
    screen.displayMessageLine("=== PNR STATUS CHECK ===");
    screen.displaySeparator();

    // Prompt for PNR number
    screen.displayMessage("Enter PNR Number (or 0 to go back): ");
    int pnr = input.getIntInput();

    // Check for go-back request
    if (pnr == 0) {
        screen.displaySeparator();
        return;
    }

    // Look up the booking
    Booking* booking = db.getBookingByPNR(pnr);

    if (booking == nullptr) {
        screen.displayMessageLine("Error: No booking found with PNR " +
                                  to_string(pnr) + ".");
        screen.displaySeparator();
        return;
    }

    // Verify this booking belongs to the current passenger
    if (booking->getPassengerID() != getPassengerID()) {
        screen.displayMessageLine("Error: This booking does not belong to you.");
        screen.displaySeparator();
        return;
    }

    // Display the full booking details
    screen.displayBookingDetails(
        booking->getPNR(),
        booking->getTrainName(),
        booking->getTrainNumber(),
        booking->getSourceStation(),
        booking->getDestStation(),
        booking->getJourneyDate(),
        booking->getDepartureTime(),
        booking->getCoachType(),
        booking->getSeatNumber(),
        db.getPassengerName(getPassengerID()),
        booking->getFare(),
        booking->getBookingStatus()
    );

    // Display wallet balance
    screen.displayMessage("Wallet Balance: ");
    screen.displayDollarAmount(db.getWalletBalance(getPassengerID()));
    screen.displayMessageLine("");
    screen.displaySeparator();
}
