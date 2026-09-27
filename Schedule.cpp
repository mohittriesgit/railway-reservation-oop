/**
 * @file Schedule.cpp
 * @brief Implementation file for the Schedule class.
 *
 * Contains the definitions of all member functions declared in Schedule.h.
 */

#include "Schedule.h"  // Include the Schedule class header

/**
 * @brief Constructs a Schedule with departure and arrival times.
 *
 * Uses a member initializer list to initialize both data members.
 *
 * @param dep The departure time string.
 * @param arr The arrival time string.
 */
Schedule::Schedule(string dep, string arr)
    : departureTime(dep), arrivalTime(arr) {
    // Body intentionally empty — initialization done via initializer list
}

/**
 * @brief Returns the departure time.
 * @return The departure time string.
 */
string Schedule::getDepartureTime() const {
    return departureTime;
}

/**
 * @brief Returns the arrival time.
 * @return The arrival time string.
 */
string Schedule::getArrivalTime() const {
    return arrivalTime;
}
