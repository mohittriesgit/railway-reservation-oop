/**
 * @file BookingTransaction.h
 * @brief Header file for the BookingTransaction class.
 *
 * BookingTransaction allows a passenger to book a ticket on a train.
 */

#ifndef BOOKINGTRANSACTION_H
#define BOOKINGTRANSACTION_H

#include "Transaction.h"  // Required for inheritance
#include <string>

using std::string;

/**
 * @class BookingTransaction
 * @brief Transaction to book a train ticket.
 */
class BookingTransaction : public Transaction {
private:
    string journeyDate;  ///< Journey date entered by user

public:
    /** @brief Constructor. */
    BookingTransaction(int passengerID, Screen& screen,
                       InputHandler& inputHandler,
                       ReservationDatabase& database);

    /** @brief Executes the booking transaction. */
    void execute() override;
};

#endif // BOOKINGTRANSACTION_H
