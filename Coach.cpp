2/**
 * @file Coach.cpp
 * @brief Implementation file for the abstract base class Coach.
 *
 * Contains the definitions of all non-pure-virtual member functions
 * declared in Coach.h. The pure virtual functions (calculateFare and
 * getCoachClassName) are implemented by derived classes.
 */

#include "Coach.h"  // Include the Coach class header

/**
 * @brief Constructs a Coach with the given ID and type.
 *
 * Uses a member initializer list for coachID and coachType.
 * Populates the seats vector with SEATS_PER_COACH Seat objects.
 * Seat types are assigned in a rotating pattern:
 *   Window, Middle, Aisle, Window, Middle, Aisle, ...
 *
 * @param id   The numeric coach identifier.
 * @param type The coach type string (e.g., "General").
 */
Coach::Coach(int id, string type)
    : coachID(id), coachType(type) {
    // Array of seat type labels, cycling through three positions
    string seatTypes[] = {"Window", "Middle", "Aisle"};

    // Create SEATS_PER_COACH seats, numbered 1 through SEATS_PER_COACH
    for (int i = 1; i <= SEATS_PER_COACH; ++i) {
        // Assign seat type based on position: (i-1) % 3 gives 0, 1, 2 pattern
        seats.push_back(Seat(i, seatTypes[(i - 1) % 3]));
    }
}

/**
 * @brief Virtual destructor.
 *
 * No dynamic memory is allocated directly by Coach (seats are stored
 * by value in a vector), so the default cleanup is sufficient.
 */
Coach::~Coach() {
    // Nothing to explicitly clean up; vector handles Seat destruction
}

/**
 * @brief Counts the number of available (unbooked) seats in this coach.
 *
 * Iterates through all seats and increments a counter for each seat
 * that reports isAvailable() == true.
 *
 * @return The number of available seats.
 */
int Coach::getAvailableSeatCount() const {
    int count = 0;  // Counter for available seats

    // Iterate through every seat in the coach
    for (size_t i = 0; i < seats.size(); ++i) {
        if (seats[i].isAvailable()) {
            ++count;  // Increment count if seat is available
        }
    }

    return count;  // Return the total count of available seats
}

/**
 * @brief Returns the coach ID.
 * @return The integer coach ID.
 */
int Coach::getCoachID() const {
    return coachID;
}

/**
 * @brief Returns the coach type string.
 * @return The coach type (e.g., "General", "Sleeper", "AC").
 */
string Coach::getCoachType() const {
    return coachType;
}

/**
 * @brief Returns a pointer to the first available seat.
 *
 * Scans the seats vector from the beginning and returns a pointer
 * to the first Seat that is not booked. If all seats are booked,
 * returns nullptr.
 *
 * @return Pointer to the first available Seat, or nullptr.
 */
Seat* Coach::getAvailableSeat() {
    // Iterate through all seats looking for the first available one
    for (size_t i = 0; i < seats.size(); ++i) {
        if (seats[i].isAvailable()) {
            return &seats[i];  // Return pointer to first available seat
        }
    }
    return nullptr;  // No seats available
}

/**
 * @brief Returns a pointer to the Seat with the given seat number.
 *
 * Used during cancellation to locate a specific seat by its number.
 *
 * @param seatNumber The seat number to search for.
 * @return Pointer to the matching Seat, or nullptr if not found.
 */
Seat* Coach::getSeatByNumber(int seatNumber) {
    // Iterate through all seats to find the matching seat number
    for (size_t i = 0; i < seats.size(); ++i) {
        if (seats[i].getSeatNumber() == seatNumber) {
            return &seats[i];  // Return pointer to the matching seat
        }
    }
    return nullptr;  // Seat number not found
}
