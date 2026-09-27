/**
 * @file Transaction.h
 * @brief Header file for the abstract base class Transaction.
 *
 * Transaction is the base class for all operations a passenger can
 * perform: search, book, cancel, PNR status, and history.
 * Analogous to Transaction in the ATM case study.
 */

#ifndef TRANSACTION_H
#define TRANSACTION_H

// Forward declarations — only references are stored
class Screen;
class InputHandler;
class ReservationDatabase;

/**
 * @class Transaction
 * @brief Abstract base class for all transaction types.
 *
 * Stores references to the shared Screen, InputHandler, and
 * ReservationDatabase objects, plus the current passenger's ID.
 */
class Transaction {
private:
    int passengerID;                    ///< ID of the logged-in passenger
    Screen& screen;                     ///< Reference to the output handler
    InputHandler& inputHandler;         ///< Reference to the input handler
    ReservationDatabase& database;      ///< Reference to the central database

public:
    /**
     * @brief Constructs a Transaction with all required references.
     */
    Transaction(int passengerID, Screen& screen, InputHandler& inputHandler,
                ReservationDatabase& database);

    /** @brief Virtual destructor for proper polymorphic cleanup. */
    virtual ~Transaction();

    /** @brief Returns the passenger ID. */
    int getPassengerID() const;

    /** @brief Returns reference to the Screen object. */
    Screen& getScreen() const;

    /** @brief Returns reference to the InputHandler object. */
    InputHandler& getInputHandler() const;

    /** @brief Returns reference to the ReservationDatabase object. */
    ReservationDatabase& getDatabase() const;

    /** @brief Pure virtual: execute this transaction. */
    virtual void execute() = 0;
};

#endif // TRANSACTION_H
