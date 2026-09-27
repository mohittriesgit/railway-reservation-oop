/**
 * @file Booking.cpp
 * @brief Implementation file for the Booking class.
 *
 * Contains definitions of all member functions declared in Booking.h.
 */

#include "Booking.h"

/**
 * @brief Constructs a Booking with all journey details.
 * Status is set to "CONFIRMED" automatically.
 */
Booking::Booking(int pnr, int passengerID, int trainNo, string trainName,
                 string src, string dest, string date, string dep,
                 string coachType, int seatNo, double fare)
    : PNR(pnr), passengerID(passengerID), trainNumber(trainNo),
      trainName(trainName), sourceStation(src), destStation(dest),
      journeyDate(date), departureTime(dep), coachType(coachType),
      seatNumber(seatNo), fare(fare), bookingStatus("CONFIRMED") {
}

/** @brief Cancels this booking. */
void Booking::cancel() {
    bookingStatus = "CANCELLED";
}

int Booking::getPNR() const { return PNR; }
int Booking::getPassengerID() const { return passengerID; }
int Booking::getTrainNumber() const { return trainNumber; }
string Booking::getTrainName() const { return trainName; }
string Booking::getSourceStation() const { return sourceStation; }
string Booking::getDestStation() const { return destStation; }
string Booking::getJourneyDate() const { return journeyDate; }
string Booking::getDepartureTime() const { return departureTime; }
string Booking::getCoachType() const { return coachType; }
int Booking::getSeatNumber() const { return seatNumber; }
double Booking::getFare() const { return fare; }
string Booking::getBookingStatus() const { return bookingStatus; }

/** @brief Returns true if booking status is "CONFIRMED". */
bool Booking::isActive() const {
    return bookingStatus == "CONFIRMED";
}
