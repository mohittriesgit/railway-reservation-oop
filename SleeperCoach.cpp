/**
 * @file SleeperCoach.cpp
 * @brief Implementation file for the SleeperCoach class.
 *
 * Contains the definitions of all member functions declared in SleeperCoach.h.
 * SleeperCoach applies a 1.5x fare multiplier.
 */

#include "SleeperCoach.h"  // Include the SleeperCoach class header

/**
 * @brief Constructs a SleeperCoach with the given ID.
 *
 * Delegates to the Coach base constructor, passing "Sleeper" as the
 * coach type string. The base constructor handles seat creation.
 *
 * @param id The coach identifier number.
 */
SleeperCoach::SleeperCoach(int id)
    : Coach(id, "Sleeper") {
    // Body intentionally empty — base constructor handles initialization
}

/**
 * @brief Calculates the fare for a Sleeper coach seat.
 *
 * The Sleeper coach applies a 1.5x surcharge on the base fare.
 *
 * @param baseFare The base fare per seat for the train.
 * @return baseFare * 1.5
 */
double SleeperCoach::calculateFare(double baseFare) const {
    return baseFare * 1.5;  // 50% surcharge for Sleeper coach
}

/**
 * @brief Returns the class name of this coach.
 * @return The string "Sleeper".
 */
string SleeperCoach::getCoachClassName() const {
    return "Sleeper";
}
