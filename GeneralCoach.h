/**
 * @file GeneralCoach.h
 * @brief Header file for the GeneralCoach class.
 *
 * GeneralCoach is a concrete derived class of Coach.
 * It represents the most basic and affordable coach type
 * with a fare multiplier of 1.0 (no surcharge).
 */

#ifndef GENERALCOACH_H
#define GENERALCOACH_H

#include "Coach.h"  // Required for inheritance from Coach

/**
 * @class GeneralCoach
 * @brief Represents a General (unreserved/basic) coach on a train.
 *
 * Inherits from Coach. Overrides calculateFare() to apply a 1.0x
 * multiplier (i.e., no surcharge on the base fare) and
 * getCoachClassName() to return "General".
 */
class GeneralCoach : public Coach {
public:
    /**
     * @brief Constructs a GeneralCoach with the given coach ID.
     *
     * Passes the ID and the string "General" to the Coach base constructor.
     *
     * @param id The numeric coach identifier.
     */
    GeneralCoach(int id);

    /**
     * @brief Calculates the fare for a General coach.
     *
     * General coaches have no surcharge: fare = baseFare * 1.0.
     *
     * @param baseFare The base fare per seat.
     * @return The calculated fare (equal to baseFare).
     */
    double calculateFare(double baseFare) const override;

    /**
     * @brief Returns the class name of this coach type.
     * @return The string "General".
     */
    string getCoachClassName() const override;
};

#endif // GENERALCOACH_H
