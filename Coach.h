/**
 * @file Coach.h
 * @brief Header file for the abstract base class Coach.
 *
 * The Coach class serves as the abstract base for all coach types
 * (GeneralCoach, SleeperCoach, ACCoach). It stores a collection of
 * Seat objects and defines the interface that derived classes must
 * implement for fare calculation and coach identification.
 */

#ifndef COACH_H
#define COACH_H

#include <string>    // Required for std::string data member
#include <vector>    // Required for std::vector<Seat> data member
#include "Seat.h"    // Required because we store Seat objects (not pointers)

using std::string;
using std::vector;

/**
 * @class Coach
 * @brief Abstract base class representing a train coach.
 *
 * Cannot be instantiated directly. Derived classes (GeneralCoach,
 * SleeperCoach, ACCoach) must override the pure virtual functions
 * calculateFare() and getCoachClassName().
 *
 * Each coach contains a fixed number of seats (SEATS_PER_COACH)
 * and provides methods to query seat availability and assign seats.
 */
class Coach {
private:
    int coachID;             ///< Unique numeric identifier for this coach
    string coachType;        ///< Coach type string (set by derived classes)
    vector<Seat> seats;      ///< Collection of Seat objects in this coach

public:
    /**
     * @brief Static constant defining the number of seats per coach.
     *
     * Every coach (regardless of type) has exactly 10 seats.
     */
    static const int SEATS_PER_COACH = 10;

    /**
     * @brief Constructs a Coach with the given ID and type.
     *
     * Fills the seats vector with SEATS_PER_COACH Seat objects,
     * numbered from 1 to SEATS_PER_COACH. Seat types are assigned
     * in a rotating pattern: Window, Middle, Aisle.
     *
     * @param id   The coach ID number.
     * @param type The coach type string (e.g., "General", "Sleeper", "AC").
     */
    Coach(int id, string type);

    /**
     * @brief Virtual destructor.
     *
     * Required because Coach has virtual functions. Ensures proper
     * cleanup when deleting through base class pointers.
     */
    virtual ~Coach();

    /**
     * @brief Counts and returns the number of available (unbooked) seats.
     * @return The number of seats where isAvailable() returns true.
     */
    int getAvailableSeatCount() const;

    /**
     * @brief Returns the coach ID.
     * @return The integer coach ID.
     */
    int getCoachID() const;

    /**
     * @brief Returns the coach type string.
     * @return The coach type (e.g., "General", "Sleeper", "AC").
     */
    string getCoachType() const;

    /**
     * @brief Returns a pointer to the first available seat in this coach.
     *
     * Scans through the seats vector and returns a pointer to the first
     * Seat whose isAvailable() method returns true. Returns nullptr if
     * all seats are booked.
     *
     * @return Pointer to the first available Seat, or nullptr if none.
     */
    Seat* getAvailableSeat();

    /**
     * @brief Pure virtual function to calculate the fare for this coach type.
     *
     * Each derived class applies its own fare multiplier to the base fare.
     *
     * @param baseFare The base fare amount per seat.
     * @return The calculated fare after applying the coach-specific multiplier.
     */
    virtual double calculateFare(double baseFare) const = 0;

    /**
     * @brief Pure virtual function returning the class name of this coach.
     *
     * Each derived class returns its specific name string.
     *
     * @return The coach class name string (e.g., "General", "Sleeper", "AC").
     */
    virtual string getCoachClassName() const = 0;

    /**
     * @brief Returns a pointer to the Seat with the given seat number.
     *
     * This utility method is used during cancellation to find and release
     * a specific seat by its number.
     *
     * @param seatNumber The seat number to find.
     * @return Pointer to the matching Seat, or nullptr if not found.
     */
    Seat* getSeatByNumber(int seatNumber);
};

#endif // COACH_H
