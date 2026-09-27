/**
 * @file ReservationDatabase.cpp
 * @brief Implementation file for the ReservationDatabase class.
 *
 * Contains all database operations: authentication, search, booking,
 * cancellation, and history retrieval.
 */

#include "ReservationDatabase.h"
#include "Train.h"     // Full definition needed for Train method calls
#include "Coach.h"     // Full definition needed for Coach method calls
#include "Seat.h"      // Full definition needed for Seat method calls
#include <algorithm>   // For std::transform (case-insensitive compare)
#include <cctype>      // For std::tolower

/**
 * @brief Helper function to convert a string to lowercase.
 * Used for case-insensitive station name comparison.
 * @param s The input string.
 * @return A lowercase copy of the input string.
 */
static string toLower(string s) {
    for (size_t i = 0; i < s.size(); ++i) {
        s[i] = static_cast<char>(tolower(static_cast<unsigned char>(s[i])));
    }
    return s;
}

/**
 * @brief Constructor. Initializes the database with hardcoded test data.
 *
 * Creates 3 test passengers and 4 test trains as specified.
 */
ReservationDatabase::ReservationDatabase()
    : nextPNR(100001) {
    // === Hardcoded Passengers ===
    passengers.push_back(Passenger(1001, "pass1", "Arjun Kumar",
                                   "arjun@email.com", 5000.0));
    passengers.push_back(Passenger(1002, "pass2", "Priya Sharma",
                                   "priya@email.com", 3000.0));
    passengers.push_back(Passenger(1003, "pass3", "Rahul Singh",
                                   "rahul@email.com", 8000.0));

    // === Hardcoded Trains (heap-allocated) ===
    trains.push_back(new Train(12001, "Rajdhani Express", "Chennai", "Delhi",
                               500.0, "06:00", "28:00"));
    trains.push_back(new Train(12002, "Shatabdi Express", "Chennai", "Mumbai",
                               400.0, "07:30", "22:00"));
    trains.push_back(new Train(12003, "Mail Express", "Bangalore", "Delhi",
                               300.0, "18:00", "44:00"));
    trains.push_back(new Train(12004, "Duronto Express", "Mumbai", "Kolkata",
                               450.0, "09:00", "33:00"));
}

/**
 * @brief Destructor. Frees all dynamically allocated Train objects.
 */
ReservationDatabase::~ReservationDatabase() {
    for (size_t i = 0; i < trains.size(); ++i) {
        delete trains[i];
    }
}

/**
 * @brief Finds a passenger by ID.
 * @param passengerID The ID to search for.
 * @return Pointer to matching Passenger, or nullptr.
 */
Passenger* ReservationDatabase::getPassenger(int passengerID) {
    for (size_t i = 0; i < passengers.size(); ++i) {
        if (passengers[i].getPassengerID() == passengerID) {
            return &passengers[i];
        }
    }
    return nullptr;
}

/**
 * @brief Finds a train by number.
 * @param trainNumber The train number to search for.
 * @return Pointer to matching Train, or nullptr.
 */
Train* ReservationDatabase::getTrain(int trainNumber) {
    for (size_t i = 0; i < trains.size(); ++i) {
        if (trains[i]->getTrainNumber() == trainNumber) {
            return trains[i];
        }
    }
    return nullptr;
}

/**
 * @brief Authenticates a passenger using ID and password.
 */
bool ReservationDatabase::authenticatePassenger(int passengerID, string password) {
    Passenger* p = getPassenger(passengerID);
    if (p != nullptr) {
        return p->validatePassword(password);
    }
    return false;
}

/**
 * @brief Searches for trains matching source and destination (case-insensitive).
 */
vector<Train*> ReservationDatabase::searchTrains(string src, string dest) {
    vector<Train*> results;
    string srcLower = toLower(src);
    string destLower = toLower(dest);

    for (size_t i = 0; i < trains.size(); ++i) {
        if (toLower(trains[i]->getSourceStation()) == srcLower &&
            toLower(trains[i]->getDestStation()) == destLower) {
            results.push_back(trains[i]);
        }
    }
    return results;
}

/**
 * @brief Returns wallet balance of the given passenger.
 */
double ReservationDatabase::getWalletBalance(int passengerID) {
    Passenger* p = getPassenger(passengerID);
    if (p != nullptr) {
        return p->getWalletBalance();
    }
    return 0.0;
}

/**
 * @brief Returns the name of the given passenger.
 */
string ReservationDatabase::getPassengerName(int passengerID) {
    Passenger* p = getPassenger(passengerID);
    if (p != nullptr) {
        return p->getName();
    }
    return "";
}

/**
 * @brief Debits amount from passenger. Returns false if insufficient balance.
 */
bool ReservationDatabase::debitPassenger(int passengerID, double amount) {
    Passenger* p = getPassenger(passengerID);
    if (p != nullptr && p->getWalletBalance() >= amount) {
        p->debit(amount);
        return true;
    }
    return false;
}

/**
 * @brief Credits amount to passenger wallet.
 */
void ReservationDatabase::creditPassenger(int passengerID, double amount) {
    Passenger* p = getPassenger(passengerID);
    if (p != nullptr) {
        p->credit(amount);
    }
}

/**
 * @brief Creates a new booking.
 *
 * Finds train, gets coach, gets available seat, checks balance,
 * debits fare, books seat, creates Booking record.
 *
 * @return Pointer to the created Booking, or nullptr on failure.
 */
Booking* ReservationDatabase::createBooking(int passengerID, int trainNumber,
                                            string coachType, string journeyDate) {
    // Find the train
    Train* train = getTrain(trainNumber);
    if (train == nullptr) {
        return nullptr;
    }

    // Find the coach of the requested type
    Coach* coach = train->getCoachByType(coachType);
    if (coach == nullptr) {
        return nullptr;
    }

    // Get the first available seat
    Seat* seat = coach->getAvailableSeat();
    if (seat == nullptr) {
        return nullptr;
    }

    // Calculate fare using polymorphic method
    double fare = coach->calculateFare(train->getBaseFare());

    // Check and debit passenger balance
    if (!debitPassenger(passengerID, fare)) {
        return nullptr;  // Insufficient balance
    }

    // Book the seat
    seat->book();

    // Create booking record with auto-incrementing PNR
    bookings.push_back(Booking(nextPNR, passengerID, trainNumber,
                               train->getTrainName(),
                               train->getSourceStation(),
                               train->getDestStation(),
                               journeyDate,
                               train->getSchedule().getDepartureTime(),
                               coachType, seat->getSeatNumber(), fare));

    int currentPNR = nextPNR;
    nextPNR++;  // Increment PNR for next booking

    // Return pointer to the booking we just added
    return getBookingByPNR(currentPNR);
}

/**
 * @brief Cancels a booking identified by PNR.
 *
 * Verifies ownership, marks as cancelled, releases seat, refunds fare.
 *
 * @return true if cancellation succeeded, false otherwise.
 */
bool ReservationDatabase::cancelBooking(int PNR, int passengerID) {
    // Find the booking
    Booking* booking = getBookingByPNR(PNR);
    if (booking == nullptr) {
        return false;
    }

    // Verify the booking belongs to this passenger
    if (booking->getPassengerID() != passengerID) {
        return false;
    }

    // Check if already cancelled
    if (!booking->isActive()) {
        return false;
    }

    // Get refund amount before cancelling
    double refundAmount = booking->getFare();

    // Cancel the booking
    booking->cancel();

    // Find the train and release the seat
    Train* train = getTrain(booking->getTrainNumber());
    if (train != nullptr) {
        Coach* coach = train->getCoachByType(booking->getCoachType());
        if (coach != nullptr) {
            Seat* seat = coach->getSeatByNumber(booking->getSeatNumber());
            if (seat != nullptr) {
                seat->release();  // Free the seat
            }
        }
    }

    // Credit the refund to the passenger's wallet
    creditPassenger(passengerID, refundAmount);

    return true;
}

/**
 * @brief Finds a booking by its PNR number.
 * @return Pointer to the matching Booking, or nullptr.
 */
Booking* ReservationDatabase::getBookingByPNR(int PNR) {
    for (size_t i = 0; i < bookings.size(); ++i) {
        if (bookings[i].getPNR() == PNR) {
            return &bookings[i];
        }
    }
    return nullptr;
}

/**
 * @brief Returns all bookings belonging to a given passenger.
 */
vector<Booking*> ReservationDatabase::getBookingHistory(int passengerID) {
    vector<Booking*> history;
    for (size_t i = 0; i < bookings.size(); ++i) {
        if (bookings[i].getPassengerID() == passengerID) {
            history.push_back(&bookings[i]);
        }
    }
    return history;
}

// ==================== ADMIN FEATURES ====================

/**
 * @brief Admin password constant. Used for admin authentication.
 */
const string ReservationDatabase::ADMIN_PASSWORD = "admin123";

/**
 * @brief Authenticates admin by checking password.
 * @param password The password entered by the user.
 * @return true if password matches the admin password.
 */
bool ReservationDatabase::authenticateAdmin(string password) {
    return password == ADMIN_PASSWORD;
}

/**
 * @brief Returns a const reference to all passengers.
 * Used by admin to view all registered user information.
 */
const vector<Passenger>& ReservationDatabase::getAllPassengers() const {
    return passengers;
}

/**
 * @brief Returns a const reference to all trains.
 * Used by admin to view and manage the train fleet.
 */
const vector<Train*>& ReservationDatabase::getAllTrains() const {
    return trains;
}

/**
 * @brief Adds a new train to the database.
 *
 * Checks for duplicate train numbers before adding.
 *
 * @return true if the train was added, false if train number already exists.
 */
bool ReservationDatabase::addTrain(int number, string name, string src,
                                   string dest, double fare,
                                   string dep, string arr) {
    // Check for duplicate train number
    if (getTrain(number) != nullptr) {
        return false;  // Train number already exists
    }

    // Create and add the new train
    trains.push_back(new Train(number, name, src, dest, fare, dep, arr));
    return true;
}

/**
 * @brief Removes a train from the database by its train number.
 *
 * Finds the train, deletes the heap-allocated object, and removes
 * the pointer from the trains vector.
 *
 * @param trainNumber The train number to remove.
 * @return true if the train was found and removed, false otherwise.
 */
bool ReservationDatabase::removeTrain(int trainNumber) {
    for (size_t i = 0; i < trains.size(); ++i) {
        if (trains[i]->getTrainNumber() == trainNumber) {
            delete trains[i];               // Free the heap memory
            trains.erase(trains.begin() + i); // Remove from vector
            return true;
        }
    }
    return false;  // Train not found
}
