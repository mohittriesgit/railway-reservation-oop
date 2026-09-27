/**
 * @file SearchTransaction.h
 * @brief Header file for the SearchTransaction class.
 *
 * SearchTransaction allows a passenger to search for trains
 * between a source and destination station.
 */

#ifndef SEARCHTRANSACTION_H
#define SEARCHTRANSACTION_H

#include "Transaction.h"  // Required for inheritance
#include <string>

using std::string;

/**
 * @class SearchTransaction
 * @brief Transaction to search for available trains by route.
 */
class SearchTransaction : public Transaction {
private:
    string sourceStation;  ///< Source station entered by user
    string destStation;    ///< Destination station entered by user

public:
    /** @brief Constructor. */
    SearchTransaction(int passengerID, Screen& screen,
                      InputHandler& inputHandler,
                      ReservationDatabase& database);

    /** @brief Executes the search transaction. */
    void execute() override;
};

#endif // SEARCHTRANSACTION_H
