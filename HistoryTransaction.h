/**
 * @file HistoryTransaction.h
 * @brief Header file for the HistoryTransaction class.
 *
 * HistoryTransaction displays all booking records for the
 * currently logged-in passenger.
 */

#ifndef HISTORYTRANSACTION_H
#define HISTORYTRANSACTION_H

#include "Transaction.h"  // Required for inheritance

/**
 * @class HistoryTransaction
 * @brief Transaction to display booking history for a passenger.
 */
class HistoryTransaction : public Transaction {
public:
    /** @brief Constructor. */
    HistoryTransaction(int passengerID, Screen& screen,
                       InputHandler& inputHandler,
                       ReservationDatabase& database);

    /** @brief Executes the history display transaction. */
    void execute() override;
};

#endif // HISTORYTRANSACTION_H
