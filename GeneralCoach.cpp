/**
 * @file GeneralCoach.cpp
 * @brief Implementation file for the GeneralCoach class.
 *
 * Contains the definitions of all member functions declared in GeneralCoach.h.
 * GeneralCoach applies a 1.0x fare multiplier (no surcharge).
 */

#include "GeneralCoach.h"  // Include the GeneralCoach class header

/**
 * @brief Constructs a GeneralCoach with the given ID.
 *
 * Delegates to the Coach base constructor, passing "General" as the
 * coach type string. The base constructor handles seat creation.
 *
 * @param id The coach identifier number.
 */
GeneralCoach::GeneralCoach(int id)
    : Coach(id, "General") {
    // Body intentionally empty — base constructor handles initialization
}

/**
 * @brief Calculates the fare for a General coach seat.
 *
 * The General coach applies no surcharge. The fare is exactly
 * equal to the base fare (multiplier = 1.0).
 *
 * @param baseFare The base fare per seat for the train.
 * @return baseFare * 1.0
 */
double GeneralCoach::calculateFare(double baseFare) const {
    return baseFare * 1.0;  // No multiplier for General coach
}

/**
 * @brief Returns the class name of this coach.
 * @return The string "General".
 */
string GeneralCoach::getCoachClassName() const {
    return "General";
}
