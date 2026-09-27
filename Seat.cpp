/**
 * @file Seat.cpp
 * @brief Implementation file for the Seat class.
 *
 * Contains the definitions of all member functions declared in Seat.h.
 * Each function is fully implemented with working logic.
 */

#include "Seat.h"  // Include the Seat class header

/**
 * @brief Constructs a Seat with the given number and type.
 *
 * Uses a member initializer list to initialize all data members.
 * The seat starts as not booked (available).
 *
 * @param number The seat number within the coach.
 * @param type   The seat type (e.g., "Window", "Aisle", "Middle").
 */
Seat::Seat(int number, string type)
    : seatNumber(number), isBooked(false), seatType(type) {
    // Body intentionally empty — all initialization done via initializer list
}

/**
 * @brief Checks if this seat is available.
 *
 * A seat is available if it has not been booked.
 *
 * @return true if the seat is not booked, false otherwise.
 */
bool Seat::isAvailable() const {
    return !isBooked;  // Available means NOT booked
}

/**
 * @brief Books this seat by setting the isBooked flag to true.
 */
void Seat::book() {
    isBooked = true;   // Mark seat as reserved
}

/**
 * @brief Releases this seat by setting the isBooked flag to false.
 *
 * This is used during booking cancellation to free the seat.
 */
void Seat::release() {
    isBooked = false;  // Mark seat as available again
}

/**
 * @brief Returns the seat number.
 * @return The integer seat number.
 */
int Seat::getSeatNumber() const {
    return seatNumber;
}

/**
 * @brief Returns the seat type string.
 * @return The type of seat (e.g., "Window", "Aisle", "Middle").
 */
string Seat::getSeatType() const {
    return seatType;
}
