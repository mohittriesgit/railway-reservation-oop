/**
 * @file Train.h
 * @brief Header file for the Train class.
 *
 * The Train class represents a train with a number, name, route,
 * base fare, schedule, and a collection of coaches (General, Sleeper, AC).
 * It owns its coaches via pointers, enabling polymorphic fare calculation.
 */

#ifndef TRAIN_H
#define TRAIN_H

#include <string>    // Required for std::string data members
#include <vector>    // Required for std::vector<Coach*> data member
#include "Schedule.h" // Required because Schedule is stored by value

using std::string;
using std::vector;

// Forward declaration: only pointers to Coach are stored
class Coach;

/**
 * @class Train
 * @brief Represents a train with coaches and schedule.
 *
 * Each Train object has a unique train number, a name, source and
 * destination stations, a base fare, a Schedule object (composition),
 * and a vector of Coach pointers (polymorphic: GeneralCoach,
 * SleeperCoach, ACCoach).
 *
 * The Train owns its Coach objects and deletes them in the destructor.
 */
class Train {
private:
    int trainNumber;           ///< Unique numeric train identifier
    string trainName;          ///< Human-readable train name
    string sourceStation;      ///< Origin station name
    string destStation;        ///< Destination station name
    double baseFarePerSeat;    ///< Base fare before coach-type multiplier
    Schedule schedule;         ///< Departure and arrival time (composition)
    vector<Coach*> coaches;    ///< Polymorphic pointers to coach objects

public:
    /**
     * @brief Constructs a Train with all route and schedule information.
     *
     * Creates one GeneralCoach (ID=1), one SleeperCoach (ID=2), and
     * one ACCoach (ID=3), pushing their pointers into the coaches vector.
     *
     * @param number The train number.
     * @param name   The train name.
     * @param src    The source station.
     * @param dest   The destination station.
     * @param fare   The base fare per seat.
     * @param dep    The departure time string.
     * @param arr    The arrival time string.
     */
    Train(int number, string name, string src, string dest,
          double fare, string dep, string arr);

    /**
     * @brief Destructor. Deletes all dynamically allocated Coach objects.
     */
    ~Train();

    /**
     * @brief Returns the train number.
     * @return The integer train number.
     */
    int getTrainNumber() const;

    /**
     * @brief Returns the train name.
     * @return The train name string.
     */
    string getTrainName() const;

    /**
     * @brief Returns the source station name.
     * @return The source station string.
     */
    string getSourceStation() const;

    /**
     * @brief Returns the destination station name.
     * @return The destination station string.
     */
    string getDestStation() const;

    /**
     * @brief Returns the base fare per seat.
     * @return The base fare as a double.
     */
    double getBaseFare() const;

    /**
     * @brief Returns a copy of the Schedule object.
     * @return The Schedule containing departure and arrival times.
     */
    Schedule getSchedule() const;

    /**
     * @brief Returns available seat count for a given coach type.
     *
     * Searches through the coaches vector for a coach matching the
     * given type string and returns its available seat count.
     *
     * @param coachType The coach type to query (e.g., "General").
     * @return The number of available seats, or 0 if coach type not found.
     */
    int getAvailableSeats(string coachType) const;

    /**
     * @brief Returns a pointer to the coach matching the given type.
     *
     * @param coachType The coach type string to search for.
     * @return Pointer to the matching Coach, or nullptr if not found.
     */
    Coach* getCoachByType(string coachType);

    /**
     * @brief Calculates the fare for a given coach type.
     *
     * Finds the coach of the given type and calls its calculateFare()
     * method with the train's baseFarePerSeat.
     *
     * @param coachType The coach type string.
     * @return The calculated fare, or 0.0 if coach type not found.
     */
    double getFareForCoachType(string coachType) const;
};

#endif // TRAIN_H
