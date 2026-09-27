/**
 * @file ReservationDatabase.h
 * @brief Header file for the ReservationDatabase class.
 *
 * Central database for the Railway Reservation System. Stores all
 * passengers, trains, and bookings. Analogous to BankDatabase in ATM.
 */

#ifndef RESERVATIONDATABASE_H
#define RESERVATIONDATABASE_H

#include <string>
#include <vector>
#include "Passenger.h"  // Stored by value in vector
#include "Booking.h"    // Stored by value in vector

using std::string;
using std::vector;

// Forward declaration — trains stored as pointers
class Train;

/**
 * @class ReservationDatabase
 * @brief Central database managing passengers, trains, and bookings.
 */
class ReservationDatabase {
private:
    vector<Passenger> passengers;  ///< All registered passengers
    vector<Train*> trains;         ///< All trains (heap-allocated)
    vector<Booking> bookings;      ///< All booking records
    int nextPNR;                   ///< Next PNR number to assign

    /** @brief Admin password for admin login. */
    static const string ADMIN_PASSWORD;

    /** @brief Finds a passenger by ID. Returns pointer or nullptr. */
    Passenger* getPassenger(int passengerID);

    /** @brief Finds a train by number. Returns pointer or nullptr. */
    Train* getTrain(int trainNumber);

public:
    /** @brief Constructor. Hardcodes test passengers and trains. */
    ReservationDatabase();

    /** @brief Destructor. Deletes all Train pointers. */
    ~ReservationDatabase();

    /** @brief Authenticates a passenger with ID and password. */
    bool authenticatePassenger(int passengerID, string password);

    /** @brief Searches trains by source and destination (case-insensitive). */
    vector<Train*> searchTrains(string src, string dest);

    /** @brief Returns wallet balance of passenger. */
    double getWalletBalance(int passengerID);

    /** @brief Returns name of passenger. */
    string getPassengerName(int passengerID);

    /** @brief Debits amount from passenger wallet. Returns false if insufficient. */
    bool debitPassenger(int passengerID, double amount);

    /** @brief Credits amount to passenger wallet. */
    void creditPassenger(int passengerID, double amount);

    /** @brief Creates a booking. Returns pointer to new Booking or nullptr. */
    Booking* createBooking(int passengerID, int trainNumber,
                           string coachType, string journeyDate);

    /** @brief Cancels a booking by PNR. Returns true if successful. */
    bool cancelBooking(int PNR, int passengerID);

    /** @brief Finds a booking by PNR. Returns pointer or nullptr. */
    Booking* getBookingByPNR(int PNR);

    /** @brief Returns all bookings for a given passenger. */
    vector<Booking*> getBookingHistory(int passengerID);

    // ==================== ADMIN FEATURES ====================

    /** @brief Authenticates admin with a password. */
    bool authenticateAdmin(string password);

    /** @brief Returns a const reference to all passengers for admin viewing. */
    const vector<Passenger>& getAllPassengers() const;

    /** @brief Returns a const reference to all trains for admin viewing. */
    const vector<Train*>& getAllTrains() const;

    /** @brief Adds a new train to the database. Returns true if successful. */
    bool addTrain(int number, string name, string src, string dest,
                  double fare, string dep, string arr);

    /** @brief Removes a train by number. Returns true if found and removed. */
    bool removeTrain(int trainNumber);
};

#endif // RESERVATIONDATABASE_H
