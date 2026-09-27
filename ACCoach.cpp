/**
 * @file ACCoach.cpp
 * @brief Implementation file for the ACCoach class.
 *
 * Contains the definitions of all member functions declared in ACCoach.h.
 * ACCoach applies a 2.5x fare multiplier.
 */

#include "ACCoach.h"  // Include the ACCoach class header

/**
 * @brief Constructs an ACCoach with the given ID.
 *
 * Delegates to the Coach base constructor, passing "AC" as the
 * coach type string. The base constructor handles seat creation.
 *
 * @param id The coach identifier number.
 */
ACCoach::ACCoach(int id)
    : Coach(id, "AC") {
    // Body intentionally empty — base constructor handles initialization
}

/**
 * @brief Calculates the fare for an AC coach seat.
 *
 * The AC coach applies a 2.5x surcharge on the base fare.
 *
 * @param baseFare The base fare per seat for the train.
 * @return baseFare * 2.5
 */
double ACCoach::calculateFare(double baseFare) const {
    return baseFare * 2.5;  // 150% surcharge for AC coach
}

/**
 * @brief Returns the class name of this coach.
 * @return The string "AC".
 */
string ACCoach::getCoachClassName() const {
    return "AC";
}
