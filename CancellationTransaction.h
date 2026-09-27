/**
 * @file CancellationTransaction.h
 * @brief Header file for the CancellationTransaction class.
 *
 * CancellationTransaction allows a passenger to cancel an
 * existing confirmed booking and receive a refund.
 */

#ifndef CANCELLATIONTRANSACTION_H
#define CANCELLATIONTRANSACTION_H

#include "Transaction.h"  // Required for inheritance

/**
 * @class CancellationTransaction
 * @brief Transaction to cancel a booking by PNR.
 */
class CancellationTransaction : public Transaction {
public:
    /** @brief Constructor. */
    CancellationTransaction(int passengerID, Screen& screen,
                            InputHandler& inputHandler,
                            ReservationDatabase& database);

    /** @brief Executes the cancellation transaction. */
    void execute() override;
};

#endif // CANCELLATIONTRANSACTION_H
