/**
 * @file ReservationSystem.cpp
 * @brief Implementation file for the ReservationSystem class.
 *
 * Contains the main loop, authentication (passenger + admin),
 * menu display, transaction creation/execution, and admin operations.
 */

#include "ReservationSystem.h"
#include "Transaction.h"
#include "SearchTransaction.h"
#include "BookingTransaction.h"
#include "CancellationTransaction.h"
#include "PNRStatusTransaction.h"
#include "HistoryTransaction.h"
#include "Screen.h"
#include "InputHandler.h"
#include "ReservationDatabase.h"
#include "Train.h"
#include "Passenger.h"
#include "Schedule.h"
#include <string>
#include <vector>

using std::to_string;
using std::vector;

/**
 * @brief Constructor. Initializes authentication state to false.
 */
ReservationSystem::ReservationSystem()
    : userAuthenticated(false), isAdmin(false), currentPassengerID(0) {
}

/**
 * @brief Runs the reservation system main loop.
 *
 * Infinite loop: displays welcome menu, routes to passenger or admin
 * login, runs operations, resets state, displays goodbye.
 */
void ReservationSystem::run() {
    while (true) {
        // Keep showing welcome until someone logs in
        while (!userAuthenticated) {
            int mode = displayWelcomeMenu();

            switch (mode) {
                case 1:
                    authenticateUser();
                    break;
                case 2:
                    authenticateAdmin();
                    break;
                default:
                    screen.displayMessageLine("Invalid choice. Please enter 1 or 2.");
                    break;
            }
        }

        // Dispatch to correct operations based on login type
        if (isAdmin) {
            performAdminOperations();
        } else {
            performOperations();
        }

        // After logout, reset state and display goodbye
        screen.displaySeparator();
        screen.displayMessageLine("Thank you for using Railway Reservation System.");
        screen.displayMessageLine("Goodbye!");
        screen.displaySeparator();
    }
}

/**
 * @brief Displays the welcome screen with login mode choice.
 * @return 1 for Passenger login, 2 for Admin login.
 */
int ReservationSystem::displayWelcomeMenu() const {
    screen.displaySeparator();
    screen.displayMessageLine("==========================================");
    screen.displayMessageLine("   WELCOME TO RAILWAY RESERVATION SYSTEM");
    screen.displayMessageLine("==========================================");
    screen.displaySeparator();
    screen.displayMessageLine("  1. Login as Passenger");
    screen.displayMessageLine("  2. Login as Admin");
    screen.displaySeparator();
    screen.displayMessage("Enter your choice (1-2): ");
    return inputHandler.getIntInput();
}

/**
 * @brief Prompts for Passenger ID and password, then authenticates.
 */
void ReservationSystem::authenticateUser() {
    screen.displayMessage("Enter Passenger ID: ");
    int id = inputHandler.getIntInput();

    screen.displayMessage("Enter Password: ");
    string password = inputHandler.getStringInput();

    if (database.authenticatePassenger(id, password)) {
        userAuthenticated = true;
        isAdmin = false;
        currentPassengerID = id;

        screen.displaySeparator();
        screen.displayMessageLine("Login Successful! Welcome, " +
                                  database.getPassengerName(id) + "!");
        screen.displayMessage("Wallet Balance: ");
        screen.displayDollarAmount(database.getWalletBalance(id));
        screen.displayMessageLine("");
        screen.displaySeparator();
    } else {
        screen.displaySeparator();
        screen.displayMessageLine("Error: Invalid Passenger ID or Password.");
        screen.displayMessageLine("Please try again.");
        screen.displaySeparator();
    }
}

/**
 * @brief Prompts for admin password and authenticates.
 *
 * Admin login requires only a password (no user ID).
 * Default admin password: admin123
 */
void ReservationSystem::authenticateAdmin() {
    screen.displayMessage("Enter Admin Password: ");
    string password = inputHandler.getStringInput();

    if (database.authenticateAdmin(password)) {
        userAuthenticated = true;
        isAdmin = true;
        currentPassengerID = 0;

        screen.displaySeparator();
        screen.displayMessageLine("Admin Login Successful! Welcome, Administrator!");
        screen.displaySeparator();
    } else {
        screen.displaySeparator();
        screen.displayMessageLine("Error: Invalid Admin Password.");
        screen.displayMessageLine("Please try again.");
        screen.displaySeparator();
    }
}

/**
 * @brief Passenger operations loop. Displays menu and processes selections.
 */
void ReservationSystem::performOperations() {
    bool running = true;

    while (running) {
        int selection = displayMainMenu();

        switch (selection) {
            case 1:  // Search Trains
            case 2:  // Book Ticket
            case 3:  // Cancel Booking
            case 4:  // PNR Status
            case 5:  // Booking History
            {
                Transaction* transaction = createTransaction(selection);
                transaction->execute();
                delete transaction;
                break;
            }
            case 6:  // Logout
            {
                screen.displaySeparator();
                screen.displayMessageLine("Logging out " +
                    database.getPassengerName(currentPassengerID) + "...");
                userAuthenticated = false;
                isAdmin = false;
                currentPassengerID = 0;
                running = false;
                break;
            }
            default:
            {
                screen.displayMessageLine("Invalid selection. Please try again.");
                break;
            }
        }
    }
}

/**
 * @brief Admin operations loop. Displays admin menu and processes selections.
 */
void ReservationSystem::performAdminOperations() {
    bool running = true;

    while (running) {
        int selection = displayAdminMenu();

        switch (selection) {
            case 1:  // View All Users
                adminViewAllUsers();
                break;
            case 2:  // View All Trains
                adminViewAllTrains();
                break;
            case 3:  // Add Train
                adminAddTrain();
                break;
            case 4:  // Remove Train
                adminRemoveTrain();
                break;
            case 5:  // Logout
            {
                screen.displaySeparator();
                screen.displayMessageLine("Logging out Administrator...");
                userAuthenticated = false;
                isAdmin = false;
                currentPassengerID = 0;
                running = false;
                break;
            }
            default:
            {
                screen.displayMessageLine("Invalid selection. Please try again.");
                break;
            }
        }
    }
}

/**
 * @brief Displays the passenger main menu and returns selection.
 */
int ReservationSystem::displayMainMenu() const {
    screen.displaySeparator();
    screen.displayMessageLine("========== MAIN MENU ==========");
    screen.displayMessageLine("  1. Search Trains");
    screen.displayMessageLine("  2. Book Ticket");
    screen.displayMessageLine("  3. Cancel Booking");
    screen.displayMessageLine("  4. PNR Status");
    screen.displayMessageLine("  5. Booking History");
    screen.displayMessageLine("  6. Logout");
    screen.displaySeparator();

    screen.displayMessage("Enter your choice (1-6): ");
    return inputHandler.getIntInput();
}

/**
 * @brief Displays the admin menu and returns selection.
 */
int ReservationSystem::displayAdminMenu() const {
    screen.displaySeparator();
    screen.displayMessageLine("========== ADMIN MENU ==========");
    screen.displayMessageLine("  1. View All Users");
    screen.displayMessageLine("  2. View All Trains");
    screen.displayMessageLine("  3. Add Train");
    screen.displayMessageLine("  4. Remove Train");
    screen.displayMessageLine("  5. Logout");
    screen.displaySeparator();

    screen.displayMessage("Enter your choice (1-5): ");
    return inputHandler.getIntInput();
}

/**
 * @brief Creates and returns a Transaction object based on menu selection.
 */
Transaction* ReservationSystem::createTransaction(int type) {
    switch (type) {
        case 1:
            return new SearchTransaction(currentPassengerID, screen,
                                         inputHandler, database);
        case 2:
            return new BookingTransaction(currentPassengerID, screen,
                                          inputHandler, database);
        case 3:
            return new CancellationTransaction(currentPassengerID, screen,
                                                inputHandler, database);
        case 4:
            return new PNRStatusTransaction(currentPassengerID, screen,
                                             inputHandler, database);
        case 5:
            return new HistoryTransaction(currentPassengerID, screen,
                                           inputHandler, database);
        default:
            return nullptr;
    }
}

// ==================== ADMIN OPERATIONS ====================

/**
 * @brief Displays all registered passenger information.
 *
 * Shows ID, Name, Email, and Wallet Balance for every passenger
 * in a formatted table.
 */
void ReservationSystem::adminViewAllUsers() {
    screen.displaySeparator();
    screen.displayMessageLine("=== ALL REGISTERED USERS ===");
    screen.displaySeparator();

    const vector<Passenger>& passengers = database.getAllPassengers();

    if (passengers.empty()) {
        screen.displayMessageLine("No registered users found.");
    } else {
        // Display header
        screen.displayMessageLine("ID       | Name                 | Email                | Wallet Balance");
        screen.displaySeparator();

        // Display each passenger's info
        for (size_t i = 0; i < passengers.size(); ++i) {
            string line = to_string(passengers[i].getPassengerID());

            // Pad ID to 9 chars
            while (line.length() < 9) line += " ";
            line += "| " + passengers[i].getName();

            // Pad name to 22 chars
            while (line.length() < 32) line += " ";
            line += "| " + passengers[i].getEmail();

            // Pad email to 22 chars
            while (line.length() < 55) line += " ";
            line += "| ";

            screen.displayMessage(line);
            screen.displayDollarAmount(passengers[i].getWalletBalance());
            screen.displayMessageLine("");
        }
    }

    screen.displaySeparator();
}

/**
 * @brief Displays all trains in the system with their details
 *        and seat availability.
 */
void ReservationSystem::adminViewAllTrains() {
    screen.displaySeparator();
    screen.displayMessageLine("=== ALL TRAINS ===");
    screen.displaySeparator();

    const vector<Train*>& trains = database.getAllTrains();

    if (trains.empty()) {
        screen.displayMessageLine("No trains in the system.");
    } else {
        screen.displayTrainHeader();
        screen.displaySeparator();

        for (size_t i = 0; i < trains.size(); ++i) {
            Train* t = trains[i];
            screen.displayTrainRow(
                t->getTrainNumber(),
                t->getTrainName(),
                t->getSourceStation(),
                t->getDestStation(),
                t->getSchedule().getDepartureTime(),
                t->getSchedule().getArrivalTime(),
                t->getAvailableSeats("General"),
                t->getAvailableSeats("Sleeper"),
                t->getAvailableSeats("AC")
            );
        }
    }

    screen.displaySeparator();
}

/**
 * @brief Prompts admin to enter details for a new train, then adds it.
 */
void ReservationSystem::adminAddTrain() {
    screen.displaySeparator();
    screen.displayMessageLine("=== ADD NEW TRAIN ===");
    screen.displaySeparator();

    screen.displayMessage("Enter Train Number: ");
    int number = inputHandler.getIntInput();

    screen.displayMessage("Enter Train Name: ");
    string name = inputHandler.getStringInput();

    screen.displayMessage("Enter Source Station: ");
    string src = inputHandler.getStringInput();

    screen.displayMessage("Enter Destination Station: ");
    string dest = inputHandler.getStringInput();

    screen.displayMessage("Enter Base Fare: ");
    double fare = inputHandler.getDoubleInput();

    screen.displayMessage("Enter Departure Time (e.g., 06:00): ");
    string dep = inputHandler.getStringInput();

    screen.displayMessage("Enter Arrival Time (e.g., 28:00): ");
    string arr = inputHandler.getStringInput();

    // Attempt to add the train
    if (database.addTrain(number, name, src, dest, fare, dep, arr)) {
        screen.displaySeparator();
        screen.displayMessageLine("Train " + to_string(number) + " (" + name +
                                  ") added successfully!");
        screen.displayMessageLine("Route: " + src + " -> " + dest);
        screen.displayMessage("Base Fare: ");
        screen.displayDollarAmount(fare);
        screen.displayMessageLine("");
    } else {
        screen.displaySeparator();
        screen.displayMessageLine("Error: Train number " + to_string(number) +
                                  " already exists.");
    }

    screen.displaySeparator();
}

/**
 * @brief Prompts admin to enter a train number, then removes that train.
 *
 * First displays all trains so the admin can see what's available,
 * then prompts for the train number to remove.
 */
void ReservationSystem::adminRemoveTrain() {
    screen.displaySeparator();
    screen.displayMessageLine("=== REMOVE TRAIN ===");
    screen.displaySeparator();

    // Show current trains first
    adminViewAllTrains();

    screen.displayMessage("Enter Train Number to remove (or 0 to cancel): ");
    int number = inputHandler.getIntInput();

    if (number == 0) {
        screen.displayMessageLine("Removal cancelled.");
        screen.displaySeparator();
        return;
    }

    // Confirm before removing
    screen.displayMessage("Are you sure you want to remove Train " +
                          to_string(number) + "? (1 = Yes, 0 = No): ");
    int confirm = inputHandler.getIntInput();

    if (confirm != 1) {
        screen.displayMessageLine("Removal cancelled.");
        screen.displaySeparator();
        return;
    }

    if (database.removeTrain(number)) {
        screen.displaySeparator();
        screen.displayMessageLine("Train " + to_string(number) +
                                  " has been removed successfully.");
    } else {
        screen.displaySeparator();
        screen.displayMessageLine("Error: Train number " + to_string(number) +
                                  " not found.");
    }

    screen.displaySeparator();
}
