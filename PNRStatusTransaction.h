/**
 * @file PNRStatusTransaction.h
 * @brief Header file for the PNRStatusTransaction class.
 *
 * PNRStatusTransaction allows a passenger to check the status
 * of a booking using its PNR number.
 */

#ifndef PNRSTATUSTRANSACTION_H
#define PNRSTATUSTRANSACTION_H

#include "Transaction.h"  // Required for inheritance

/**
 * @class PNRStatusTransaction
 * @brief Transaction to check booking status by PNR.
 */
class PNRStatusTransaction : public Transaction {
public:
    /** @brief Constructor. */
    PNRStatusTransaction(int passengerID, Screen& screen,
                         InputHandler& inputHandler,
                         ReservationDatabase& database);

    /** @brief Executes the PNR status check transaction. */
    void execute() override;
};

#endif // PNRSTATUSTRANSACTION_H
