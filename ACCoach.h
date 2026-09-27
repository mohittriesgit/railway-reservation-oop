/**
 * @file ACCoach.h
 * @brief Header file for the ACCoach class.
 *
 * ACCoach is a concrete derived class of Coach.
 * It represents the premium air-conditioned coach type
 * with a fare multiplier of 2.5.
 */

#ifndef ACCOACH_H
#define ACCOACH_H

#include "Coach.h"  // Required for inheritance from Coach

/**
 * @class ACCoach
 * @brief Represents an Air-Conditioned (AC) coach on a train.
 *
 * Inherits from Coach. Overrides calculateFare() to apply a 2.5x
 * multiplier on the base fare and getCoachClassName() to return "AC".
 */
class ACCoach : public Coach {
public:
    /**
     * @brief Constructs an ACCoach with the given coach ID.
     *
     * Passes the ID and the string "AC" to the Coach base constructor.
     *
     * @param id The numeric coach identifier.
     */
    ACCoach(int id);

    /**
     * @brief Calculates the fare for an AC coach.
     *
     * AC coaches have a 150% surcharge: fare = baseFare * 2.5.
     *
     * @param baseFare The base fare per seat.
     * @return The calculated fare (baseFare * 2.5).
     */
    double calculateFare(double baseFare) const override;

    /**
     * @brief Returns the class name of this coach type.
     * @return The string "AC".
     */
    string getCoachClassName() const override;
};

#endif // ACCOACH_H
