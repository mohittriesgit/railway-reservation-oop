/**
 * @file Transaction.cpp
 * @brief Implementation file for the abstract base class Transaction.
 */

#include "Transaction.h"

/**
 * @brief Constructs a Transaction using member initializer list.
 */
Transaction::Transaction(int passengerID, Screen& screen,
                         InputHandler& inputHandler,
                         ReservationDatabase& database)
    : passengerID(passengerID), screen(screen),
      inputHandler(inputHandler), database(database) {
}

/** @brief Virtual destructor — no dynamic resources to free. */
Transaction::~Transaction() {
}

int Transaction::getPassengerID() const { return passengerID; }
Screen& Transaction::getScreen() const { return screen; }
InputHandler& Transaction::getInputHandler() const { return inputHandler; }
ReservationDatabase& Transaction::getDatabase() const { return database; }
