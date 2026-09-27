/**
 * @file CancellationTransaction.cpp
 * @brief Implementation file for the CancellationTransaction class.
 *
 * Prompts for PNR, verifies ownership and status, shows booking
 * details, confirms cancellation, processes refund.
 */

#include "CancellationTransaction.h"
#include "Screen.h"
#include "InputHandler.h"
#include "ReservationDatabase.h"
#include "Booking.h"
#include <string>

using std::to_string;

/**
 * @brief Constructor. Delegates to Transaction base constructor.
 */
CancellationTransaction::CancellationTransaction(int passengerID,
                                                   Screen& screen,
                                                   InputHandler& inputHandler,
                                                   ReservationDatabase& database)
    : Transaction(passengerID, screen, inputHandler, database) {
}

/**
 * @brief Executes the cancellation transaction.
 *
 * Flow:
 * 1. Prompts for PNR (or 0 to go back)
 * 2. Validates booking exists, belongs to passenger, is active
 * 3. Displays booking details and refund amount
 * 4. Asks for confirmation
 * 5. Processes cancellation and displays results
 */
void CancellationTransaction::execute() {
    Screen& screen = getScreen();
    InputHandler& input = getInputHandler();
    ReservationDatabase& db = getDatabase();

    screen.displaySeparator();
    screen.displayMessageLine("=== CANCEL BOOKING ===");
    screen.displaySeparator();

    // Prompt for PNR number
    screen.displayMessage("Enter PNR Number (or 0 to go back): ");
    int pnr = input.getIntInput();

    // Check for cancellation of the transaction itself
    if (pnr == 0) {
        screen.displaySeparator();
        return;
    }

    // Look up the booking by PNR
    Booking* booking = db.getBookingByPNR(pnr);

    // Validate the booking
    if (booking == nullptr) {
        screen.displayMessageLine("Error: Booking with PNR " +
                                  to_string(pnr) + " not found.");
        screen.displaySeparator();
        return;
    }

    // Check ownership
    if (booking->getPassengerID() != getPassengerID()) {
        screen.displayMessageLine("Error: This booking does not belong to you.");
        screen.displaySeparator();
        return;
    }

    // Check if already cancelled
    if (!booking->isActive()) {
        screen.displayMessageLine("Error: This booking is already cancelled.");
        screen.displaySeparator();
        return;
    }

    // Display booking details and refund info
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

    screen.displayMessage("Refund Amount: ");
    screen.displayDollarAmount(booking->getFare());
    screen.displayMessageLine("");

    // Prompt for confirmation
    screen.displayMessage("Confirm cancellation? (1 = Yes, 0 = No): ");
    int confirm = input.getIntInput();

    if (confirm != 1) {
        screen.displayMessageLine("Cancellation aborted.");
        screen.displaySeparator();
        return;
    }

    // Save refund amount before cancellation
    double refund = booking->getFare();

    // Process the cancellation
    bool success = db.cancelBooking(pnr, getPassengerID());

    if (success) {
        screen.displaySeparator();
        screen.displayMessageLine("Booking with PNR " + to_string(pnr) +
                                  " has been cancelled successfully.");
        screen.displayMessage("Refund of ");
        screen.displayDollarAmount(refund);
        screen.displayMessageLine(" has been credited to your wallet.");
    } else {
        screen.displayMessageLine("Cancellation failed. Please try again.");
    }

    // Display updated wallet balance
    screen.displayMessage("Updated Wallet Balance: ");
    screen.displayDollarAmount(db.getWalletBalance(getPassengerID()));
    screen.displayMessageLine("");
    screen.displaySeparator();
}
