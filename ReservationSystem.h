/**
 * @file ReservationSystem.h
 * @brief Header file for the ReservationSystem class.
 *
 * ReservationSystem is the top-level controller class, analogous to
 * the ATM class in the ATM case study. It owns all composite objects
 * (Screen, InputHandler, ReservationDatabase) and orchestrates the
 * authentication and operations loop.
 */

#ifndef RESERVATIONSYSTEM_H
#define RESERVATIONSYSTEM_H

#include "Screen.h"               // Stored by value (composition)
#include "InputHandler.h"         // Stored by value (composition)
#include "ReservationDatabase.h"  // Stored by value (composition)

// Forward declaration — only pointer returned by createTransaction
class Transaction;

/**
 * @class ReservationSystem
 * @brief Top-level class that runs the Railway Reservation System.
 *
 * Manages the main loop: authentication, menu display, transaction
 * creation and execution, and logout/reset.
 */
class ReservationSystem {
private:
    bool userAuthenticated;         ///< Whether a user is currently logged in
    bool isAdmin;                   ///< Whether the current session is admin
    int currentPassengerID;         ///< ID of the currently logged-in passenger
    Screen screen;                  ///< Output handler (composition)
    InputHandler inputHandler;      ///< Input handler (composition)
    ReservationDatabase database;   ///< Central database (composition)

    /** @brief Displays welcome screen and returns login mode (1=Passenger, 2=Admin). */
    int displayWelcomeMenu() const;

    /** @brief Prompts for credentials and authenticates the user. */
    void authenticateUser();

    /** @brief Prompts for admin password and authenticates. */
    void authenticateAdmin();

    /** @brief Main operations loop after successful passenger login. */
    void performOperations();

    /** @brief Admin operations loop after successful admin login. */
    void performAdminOperations();

    /** @brief Displays the main menu and returns user's selection. */
    int displayMainMenu() const;

    /** @brief Displays the admin menu and returns selection. */
    int displayAdminMenu() const;

    /** @brief Creates a Transaction object based on the menu selection. */
    Transaction* createTransaction(int type);

    // === Admin operation helpers ===

    /** @brief Displays all registered passenger information. */
    void adminViewAllUsers();

    /** @brief Displays all trains in the system. */
    void adminViewAllTrains();

    /** @brief Prompts admin to add a new train. */
    void adminAddTrain();

    /** @brief Prompts admin to remove a train. */
    void adminRemoveTrain();

public:
    /** @brief Constructor. Initializes state to not authenticated. */
    ReservationSystem();

    /** @brief Runs the reservation system main loop. */
    void run();
};

#endif // RESERVATIONSYSTEM_H
