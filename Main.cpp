/**
 * @file Main.cpp
 * @brief Main driver file for the Railway Reservation System.
 *
 * This file contains the main() function, which serves as the entry
 * point for the entire application. As per the specification, it does
 * nothing except instantiate a ReservationSystem object and call its
 * run() method. All logic is encapsulated within the ReservationSystem
 * and its composed/associated classes.
 */

#include "ReservationSystem.h"  // Include the top-level controller class

/**
 * @brief Entry point of the Railway Reservation System application.
 *
 * Creates a ReservationSystem object and invokes its run() method,
 * which starts the authentication and operations loop.
 *
 * @return 0 upon successful program termination.
 */
int main() {
    // Create the reservation system object (composes all subsystems)
    ReservationSystem system;

    // Start the system — enters infinite loop of auth + operations
    system.run();

    return 0;
}
