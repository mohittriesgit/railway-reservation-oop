/**
 * @file Passenger.h
 * @brief Header file for the Passenger class.
 *
 * The Passenger class represents a registered user account in the
 * Railway Reservation System. It is analogous to the Account class
 * in the ATM case study. Each passenger has credentials, personal
 * information, and a wallet balance.
 */

#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>  // Required for std::string data members

using std::string;

/**
 * @class Passenger
 * @brief Represents a registered passenger account.
 *
 * Stores the passenger's ID, password, name, email, and wallet balance.
 * Provides methods for authentication and financial operations.
 */
class Passenger {
private:
    int passengerID;       ///< Unique passenger identifier
    string password;       ///< Password for authentication
    string name;           ///< Full name of the passenger
    string email;          ///< Email address of the passenger
    double walletBalance;  ///< Current wallet balance for ticket purchases

public:
    /**
     * @brief Initial wallet balance for new passengers.
     *
     * All new passenger accounts start with this balance.
     */
    static const double INITIAL_WALLET_BALANCE;

    /**
     * @brief Constructs a Passenger with all account details.
     *
     * @param id      The unique passenger ID.
     * @param pwd     The account password.
     * @param nm      The passenger's full name.
     * @param email   The passenger's email address.
     * @param balance The initial wallet balance.
     */
    Passenger(int id, string pwd, string nm, string email, double balance);

    /**
     * @brief Validates the given password against the stored password.
     *
     * @param inputPassword The password string to check.
     * @return true if the input matches the stored password, false otherwise.
     */
    bool validatePassword(string inputPassword) const;

    /**
     * @brief Returns the passenger ID.
     * @return The integer passenger ID.
     */
    int getPassengerID() const;

    /**
     * @brief Returns the passenger's full name.
     * @return The name string.
     */
    string getName() const;

    /**
     * @brief Returns the passenger's email address.
     * @return The email string.
     */
    string getEmail() const;

    /**
     * @brief Returns the current wallet balance.
     * @return The wallet balance as a double.
     */
    double getWalletBalance() const;

    /**
     * @brief Debits (subtracts) the given amount from the wallet balance.
     *
     * The caller should verify sufficient balance before calling this.
     *
     * @param amount The amount to subtract.
     */
    void debit(double amount);

    /**
     * @brief Credits (adds) the given amount to the wallet balance.
     *
     * Used for refunds during booking cancellation.
     *
     * @param amount The amount to add.
     */
    void credit(double amount);
};

#endif // PASSENGER_H
