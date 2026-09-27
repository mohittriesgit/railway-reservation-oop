/**
 * @file Seat.h
 * @brief Header file for the Seat class.
 *
 * The Seat class represents a single seat within a coach.
 * Each seat has a number, a type (Window, Aisle, or Middle),
 * and a booking status that indicates whether it is currently reserved.
 */

#ifndef SEAT_H
#define SEAT_H

#include <string>  // Required for std::string data member

using std::string;

/**
 * @class Seat
 * @brief Represents one seat in a train coach.
 *
 * Each Seat object tracks its seat number, its type (Window, Aisle,
 * or Middle), and whether it has been booked. Seats start as available
 * and can be booked or released.
 */
class Seat {
private:
    int seatNumber;    ///< The numeric identifier of this seat within a coach
    bool isBooked;     ///< Booking status: true if reserved, false if available
    string seatType;   ///< The type of seat: "Window", "Aisle", or "Middle"

public:
    /**
     * @brief Constructs a Seat with the given number and type.
     *
     * The seat is initialized as not booked (available).
     *
     * @param number The seat number (1-based within the coach).
     * @param type   The seat type string (e.g., "Window", "Aisle", "Middle").
     */
    Seat(int number, string type);

    /**
     * @brief Checks whether this seat is available for booking.
     * @return true if the seat is not booked, false otherwise.
     */
    bool isAvailable() const;

    /**
     * @brief Marks this seat as booked.
     *
     * Sets the internal isBooked flag to true.
     */
    void book();

    /**
     * @brief Releases this seat, making it available again.
     *
     * Sets the internal isBooked flag to false.
     */
    void release();

    /**
     * @brief Returns the seat number.
     * @return The integer seat number.
     */
    int getSeatNumber() const;

    /**
     * @brief Returns the seat type.
     * @return The seat type string (e.g., "Window").
     */
    string getSeatType() const;
};

#endif // SEAT_H
