/**
 * @file Passenger.cpp
 * @brief Implementation file for the Passenger class.
 *
 * Contains the definitions of all member functions and static
 * constants declared in Passenger.h.
 */

#include "Passenger.h"  // Include the Passenger class header

/**
 * @brief Definition of the initial wallet balance constant.
 *
 * Every new passenger account starts with Rs. 5000.00 in their wallet.
 */
const double Passenger::INITIAL_WALLET_BALANCE = 5000.0;

/**
 * @brief Constructs a Passenger with all account details.
 *
 * Uses a member initializer list to set all data members.
 *
 * @param id      The unique passenger ID.
 * @param pwd     The account password.
 * @param nm      The passenger's full name.
 * @param email   The passenger's email address.
 * @param balance The initial wallet balance.
 */
Passenger::Passenger(int id, string pwd, string nm, string email, double balance)
    : passengerID(id), password(pwd), name(nm), email(email),
      walletBalance(balance) {
    // Body intentionally empty — initialization done via initializer list
}

/**
 * @brief Validates the given password against the stored password.
 *
 * Performs a simple string comparison.
 *
 * @param inputPassword The password to check.
 * @return true if passwords match, false otherwise.
 */
bool Passenger::validatePassword(string inputPassword) const {
    return inputPassword == password;  // Direct string comparison
}

/**
 * @brief Returns the passenger ID.
 * @return The integer passenger ID.
 */
int Passenger::getPassengerID() const {
    return passengerID;
}

/**
 * @brief Returns the passenger's full name.
 * @return The name string.
 */
string Passenger::getName() const {
    return name;
}

/**
 * @brief Returns the passenger's email address.
 * @return The email string.
 */
string Passenger::getEmail() const {
    return email;
}

/**
 * @brief Returns the current wallet balance.
 * @return The wallet balance as a double.
 */
double Passenger::getWalletBalance() const {
    return walletBalance;
}

/**
 * @brief Debits the given amount from the wallet.
 *
 * Subtracts the specified amount from the wallet balance.
 * The caller must ensure sufficient balance before calling this method.
 *
 * @param amount The amount to debit.
 */
void Passenger::debit(double amount) {
    walletBalance -= amount;  // Subtract amount from balance
}

/**
 * @brief Credits the given amount to the wallet.
 *
 * Adds the specified amount to the wallet balance.
 * Used when processing refunds.
 *
 * @param amount The amount to credit.
 */
void Passenger::credit(double amount) {
    walletBalance += amount;  // Add amount to balance
}
