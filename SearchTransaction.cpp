/**
 * @file SearchTransaction.cpp
 * @brief Implementation file for the SearchTransaction class.
 *
 * Prompts user for source and destination, searches database,
 * and displays matching trains with seat availability.
 */

#include "SearchTransaction.h"
#include "Screen.h"
#include "InputHandler.h"
#include "ReservationDatabase.h"
#include "Train.h"
#include "Schedule.h"
#include <vector>

using std::vector;
using std::to_string;

/**
 * @brief Constructor. Delegates to Transaction base constructor.
 */
SearchTransaction::SearchTransaction(int passengerID, Screen& screen,
                                     InputHandler& inputHandler,
                                     ReservationDatabase& database)
    : Transaction(passengerID, screen, inputHandler, database),
      sourceStation(""), destStation("") {
}

/**
 * @brief Executes the search transaction.
 *
 * Prompts for source and destination stations, searches the database,
 * and displays results in a formatted table.
 */
void SearchTransaction::execute() {
    Screen& screen = getScreen();
    InputHandler& input = getInputHandler();
    ReservationDatabase& db = getDatabase();

    screen.displaySeparator();
    screen.displayMessageLine("=== SEARCH TRAINS ===");
    screen.displaySeparator();

    // Prompt for source station
    screen.displayMessage("Enter Source Station: ");
    sourceStation = input.getStringInput();

    // Prompt for destination station
    screen.displayMessage("Enter Destination Station: ");
    destStation = input.getStringInput();

    // Search the database for matching trains
    vector<Train*> results = db.searchTrains(sourceStation, destStation);

    screen.displaySeparator();

    if (results.empty()) {
        // No trains found for this route
        screen.displayMessageLine("No trains found from " + sourceStation +
                                  " to " + destStation + ".");
    } else {
        // Display the results in a formatted table
        screen.displayMessageLine("Trains from " + sourceStation +
                                  " to " + destStation + ":");
        screen.displaySeparator();
        screen.displayTrainHeader();
        screen.displaySeparator();

        // Display one row per matching train
        for (size_t i = 0; i < results.size(); ++i) {
            Train* t = results[i];
            screen.displayTrainRow(
                t->getTrainNumber(),
                t->getTrainName(),
                t->getSourceStation(),
                t->getDestStation(),
                t->getSchedule().getDepartureTime(),
                t->getSchedule().getArrivalTime(),
                t->getAvailableSeats("General"),
                t->getAvailableSeats("Sleeper"),
                t->getAvailableSeats("AC")
            );
        }
    }

    screen.displaySeparator();

    // Display updated wallet balance
    screen.displayMessage("Wallet Balance: ");
    screen.displayDollarAmount(db.getWalletBalance(getPassengerID()));
    screen.displayMessageLine("");
}
