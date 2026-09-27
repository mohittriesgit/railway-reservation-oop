/**
 * @file Schedule.h
 * @brief Header file for the Schedule class.
 *
 * The Schedule class stores the departure and arrival times
 * for a train journey. It is used as a composition member
 * within the Train class.
 */

#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <string>  // Required for std::string data members

using std::string;

/**
 * @class Schedule
 * @brief Stores departure and arrival time information for a train.
 *
 * This is a simple value class used by the Train class to encapsulate
 * timing information. Times are stored as strings (e.g., "06:00", "28:00").
 */
class Schedule {
private:
    string departureTime;  ///< The scheduled departure time (e.g., "06:00")
    string arrivalTime;    ///< The scheduled arrival time (e.g., "28:00")

public:
    /**
     * @brief Constructs a Schedule with the given departure and arrival times.
     * @param dep The departure time string.
     * @param arr The arrival time string.
     */
    Schedule(string dep, string arr);

    /**
     * @brief Returns the departure time.
     * @return The departure time string.
     */
    string getDepartureTime() const;

    /**
     * @brief Returns the arrival time.
     * @return The arrival time string.
     */
    string getArrivalTime() const;
};

#endif // SCHEDULE_H
