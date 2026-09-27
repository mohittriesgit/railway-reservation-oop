/**
 * @file Booking.h
 * @brief Header file for the Booking class.
 *
 * Represents a single ticket booking in the Railway Reservation System.
 */

#ifndef BOOKING_H
#define BOOKING_H

#include <string>

using std::string;

/**
 * @class Booking
 * @brief Represents one ticket booking with all journey details and status.
 */
class Booking {
private:
    int PNR;                ///< Unique booking ID
    int passengerID;        ///< ID of the passenger who made the booking
    int trainNumber;        ///< Number of the booked train
    string trainName;       ///< Name of the booked train
    string sourceStation;   ///< Departure station
    string destStation;     ///< Arrival station
    string journeyDate;     ///< Date of journey
    string departureTime;   ///< Scheduled departure time
    string coachType;       ///< Type of coach (General/Sleeper/AC)
    int seatNumber;         ///< Assigned seat number
    double fare;            ///< Ticket fare
    string bookingStatus;   ///< "CONFIRMED" or "CANCELLED"

public:
    /** @brief Constructs a Booking. Status is set to "CONFIRMED". */
    Booking(int pnr, int passengerID, int trainNo, string trainName,
            string src, string dest, string date, string dep,
            string coachType, int seatNo, double fare);

    /** @brief Cancels this booking. */
    void cancel();

    int getPNR() const;
    int getPassengerID() const;
    int getTrainNumber() const;
    string getTrainName() const;
    string getSourceStation() const;
    string getDestStation() const;
    string getJourneyDate() const;
    string getDepartureTime() const;
    string getCoachType() const;
    int getSeatNumber() const;
    double getFare() const;
    string getBookingStatus() const;

    /** @brief Returns true if booking status is "CONFIRMED". */
    bool isActive() const;
};

#endif // BOOKING_H
