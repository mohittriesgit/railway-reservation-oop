/**
 * @file Train.cpp
 * @brief Implementation file for the Train class.
 *
 * Contains the definitions of all member functions declared in Train.h.
 * The Train class creates and owns three coach objects (General, Sleeper, AC).
 */

#include "Train.h"          // Include the Train class header
#include "Coach.h"           // Required for Coach method calls
#include "GeneralCoach.h"    // Required to create GeneralCoach objects
#include "SleeperCoach.h"    // Required to create SleeperCoach objects
#include "ACCoach.h"         // Required to create ACCoach objects

/**
 * @brief Constructs a Train with all required data.
 *
 * Uses a member initializer list for all value members.
 * Dynamically creates one GeneralCoach, one SleeperCoach, and one ACCoach,
 * each with a unique coach ID, and stores their pointers in the coaches vector.
 *
 * @param number The train number.
 * @param name   The train name.
 * @param src    The source station.
 * @param dest   The destination station.
 * @param fare   The base fare per seat.
 * @param dep    The departure time string.
 * @param arr    The arrival time string.
 */
Train::Train(int number, string name, string src, string dest,
             double fare, string dep, string arr)
    : trainNumber(number), trainName(name), sourceStation(src),
      destStation(dest), baseFarePerSeat(fare), schedule(dep, arr) {
    // Create one coach of each type and store in the coaches vector
    coaches.push_back(new GeneralCoach(1));   // Coach ID 1: General
    coaches.push_back(new SleeperCoach(2));   // Coach ID 2: Sleeper
    coaches.push_back(new ACCoach(3));         // Coach ID 3: AC
}

/**
 * @brief Destructor. Frees all dynamically allocated Coach objects.
 *
 * Iterates through the coaches vector and deletes each Coach pointer
 * to prevent memory leaks.
 */
Train::~Train() {
    // Delete every Coach object that was allocated in the constructor
    for (size_t i = 0; i < coaches.size(); ++i) {
        delete coaches[i];  // Free the Coach memory
    }
}

/**
 * @brief Returns the train number.
 * @return The integer train number.
 */
int Train::getTrainNumber() const {
    return trainNumber;
}

/**
 * @brief Returns the train name.
 * @return The train name string.
 */
string Train::getTrainName() const {
    return trainName;
}

/**
 * @brief Returns the source station name.
 * @return The source station string.
 */
string Train::getSourceStation() const {
    return sourceStation;
}

/**
 * @brief Returns the destination station name.
 * @return The destination station string.
 */
string Train::getDestStation() const {
    return destStation;
}

/**
 * @brief Returns the base fare per seat.
 * @return The base fare as a double.
 */
double Train::getBaseFare() const {
    return baseFarePerSeat;
}

/**
 * @brief Returns a copy of the Schedule object.
 * @return The Schedule containing departure and arrival times.
 */
Schedule Train::getSchedule() const {
    return schedule;
}

/**
 * @brief Returns available seat count for the specified coach type.
 *
 * Iterates through all coaches. When a coach's type matches the
 * requested coachType, returns the available seat count from that coach.
 *
 * @param coachType The coach type string to search for.
 * @return Number of available seats, or 0 if type not found.
 */
int Train::getAvailableSeats(string coachType) const {
    // Search through all coaches for the matching type
    for (size_t i = 0; i < coaches.size(); ++i) {
        if (coaches[i]->getCoachType() == coachType) {
            return coaches[i]->getAvailableSeatCount();
        }
    }
    return 0;  // Coach type not found
}

/**
 * @brief Returns a pointer to the coach of the given type.
 *
 * @param coachType The coach type string to match.
 * @return Pointer to the matching Coach object, or nullptr.
 */
Coach* Train::getCoachByType(string coachType) {
    // Search through all coaches for the matching type
    for (size_t i = 0; i < coaches.size(); ++i) {
        if (coaches[i]->getCoachType() == coachType) {
            return coaches[i];  // Return pointer to matching coach
        }
    }
    return nullptr;  // No matching coach found
}

/**
 * @brief Calculates the fare for a specific coach type.
 *
 * Finds the coach of the given type and invokes its polymorphic
 * calculateFare() method with the train's base fare.
 *
 * @param coachType The coach type string.
 * @return The calculated fare, or 0.0 if coach type not found.
 */
double Train::getFareForCoachType(string coachType) const {
    // Search for the matching coach and calculate fare polymorphically
    for (size_t i = 0; i < coaches.size(); ++i) {
        if (coaches[i]->getCoachType() == coachType) {
            return coaches[i]->calculateFare(baseFarePerSeat);
        }
    }
    return 0.0;  // Coach type not found
}
