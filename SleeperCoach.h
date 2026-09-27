/**
 * @file SleeperCoach.h
 * @brief Header file for the SleeperCoach class.
 *
 * SleeperCoach is a concrete derived class of Coach.
 * It represents a mid-tier coach with a fare multiplier of 1.5.
 */

#ifndef SLEEPERCOACH_H
#define SLEEPERCOACH_H

#include "Coach.h"  // Required for inheritance from Coach

/**
 * @class SleeperCoach
 * @brief Represents a Sleeper coach on a train.
 *
 * Inherits from Coach. Overrides calculateFare() to apply a 1.5x
 * multiplier on the base fare and getCoachClassName() to return "Sleeper".
 */
class SleeperCoach : public Coach {
public:
    /**
     * @brief Constructs a SleeperCoach with the given coach ID.
     *
     * Passes the ID and the string "Sleeper" to the Coach base constructor.
     *
     * @param id The numeric coach identifier.
     */
    SleeperCoach(int id);

    /**
     * @brief Calculates the fare for a Sleeper coach.
     *
     * Sleeper coaches have a 50% surcharge: fare = baseFare * 1.5.
     *
     * @param baseFare The base fare per seat.
     * @return The calculated fare (baseFare * 1.5).
     */
    double calculateFare(double baseFare) const override;

    /**
     * @brief Returns the class name of this coach type.
     * @return The string "Sleeper".
     */
    string getCoachClassName() const override;
};

#endif // SLEEPERCOACH_H
