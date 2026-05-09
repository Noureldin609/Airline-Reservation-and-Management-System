#include "../include/Maintenance.h"
#include "../include/Flight.h"
#include "../include/Aircraft.h"
#include "../include/Passenger.h"
#include "../include/Reservation.h"
#include "../include/BookingAgent.h"
#include "../include/User.h"
#include "../include/Administrator.h"
#include "../include/Payment.h"
#include <algorithm>
#include<limits>
#include <iostream>
#include <sstream>
std::string getRoleFromFile(const std::string &username)
{
    std::ifstream file("../database/users.csv");
    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open users.csv\n";
        return "";
    }

    std::string line;
    std::getline(file, line); // Skip header if any
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string uname, pwd, email, age, address, role;
        std::getline(ss, uname, ',');
        std::getline(ss, pwd, ',');
        std::getline(ss, email, ',');
        std::getline(ss, age, ',');
        std::getline(ss, address, ',');
        std::getline(ss, role, ',');

        if (uname == username)
            return role;
    }
    return "";
}
int main()
{

    Authentication a;
    std::cout << "Welcome to Airline Reservation and Management System\n";
    bool running = true;
    while (running)
    {

        std::cout << "Please select your role:\n";
        std::cout << "1. Administrator\n";
        std::cout << "2. Booking Agent\n";
        std::cout << "3. Passenger\n";
        int role;
        std::cout << "Enter your role: ";
        std::cin >> role;
        std::string username, password;
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;
        std::string RealRole = getRoleFromFile(username);
        if (a.login(username, password) && RealRole == "0")
        {
            std::cout << "Login successful\n";
            int choice;
            bool session = true;

            do
            {

                Administrator admin(username, password, "email", 20, "address");
                std::cout << "\n--- Administrator Menu ---\n";
                std::cout << "1. Manage Users\n";
                std::cout << "2. Manage Flights\n";
                std::cout << "3. Manage Aircraft\n";
                std::cout << "4. Generate Reports\n";
                std::cout << "5. Logout\n";
                std::cout << "6. Exit\n";
                std::cout << "Enter choice: ";
                std::cin >> choice;

                switch (choice)
                {
                case 1:
                    std::cout << "1. Add User\n2. Remove User\n3. Update User\n4.Back to Administrator Menu\n";
                    int uChoice;
                    std::cin >> uChoice;
                    if (uChoice == 1)
                    {
                        std::string uname, pwd, email, addr;
                        int age, role;
                        std::cout << "Enter username: ";
                        std::cin >> uname;
                        std::cout << "Enter password: ";
                        std::cin >> pwd;
                        std::cout << "Enter email: ";
                        std::cin >> email;
                        std::cout << "Enter age: ";
                        std::cin >> age;
                        std::cout << "Enter address: ";
                        std::cin >> addr;
                        std::cout << "Enter role (0=Admin,1=BookingAgent,2=Passenger): ";
                        std::cin >> role;
                        if (role == 2)
                        {
                            std::string uniqueID;
                            std::cout << "Enter unique ID: ";
                            std::cin >> uniqueID;
                            DummyUser user(uname, pwd, email, age, addr, static_cast<User::Role>(role));
                            admin.createUser(user);
                            Passenger p(uname, pwd, email, age, addr, uniqueID);
                            std::ofstream passengerFile("../database/passengers.csv", std::ios::app);
                            std::hash<std::string> hasher;
                            pwd = std::to_string(hasher(pwd));
                            passengerFile << p.getUsername() << "," << pwd << "," << p.getEmail() << "," << p.getAge() << "," << p.getAddress() << "," << p.getPassengerId() << std::endl;
                            passengerFile.close();
                        }
                        else
                        {

                            DummyUser user(uname, pwd, email, age, addr, static_cast<User::Role>(role));
                            admin.createUser(user);
                        }
                    }
                    else if (uChoice == 2)
                    {
                        std::string uname;
                        std::cout << "Enter username to remove: ";
                        std::cin >> uname;
                        admin.removeUser(uname);
                    }
                    else if (uChoice == 3)
                    {
                        std::string oldName, newName;
                        std::cout << "Enter username to update: ";
                        std::cin >> oldName;
                        std::cout << "Enter new username: ";
                        std::cin >> newName;
                        admin.updateUser(newName, oldName);
                    }

                    break;

                case 2:

                    std::cout << "1. Add flight\n2. Remove flight\n3. Update flight\n4.View all flights\n5.Back to Administrator Menu\n";
                    int secchoice;
                    std::cin >> secchoice;
                    if (secchoice == 1)
                    {
                        admin.addFlight();
                    }
                    else if (secchoice == 2)
                    {
                        admin.removeFlight();
                    }
                    else if (secchoice == 3)
                    {
                        admin.updateFlight();
                    }
                    else if (secchoice == 4)
                    {
                        admin.viewFlights();
                    }
                    else if (secchoice == 5)
                    {
                        break;
                    }
                    else if (secchoice == 6)
                    {
                        return 0;
                    }
                    break;

                case 3:
                    std::cout << "1. Add aircraft\n2. Remove aircraft\n3. Update aircraft\n4. Add Maintence Record\n5. Update Maintence Record\n6. remove Maintence Record\n7.Back to Administrator Menu\n";
                    int thirdchoice;
                    std::cin >> thirdchoice;
                    if (thirdchoice == 1)
                    {
                        admin.addAircraft();
                    }
                    else if (thirdchoice == 2)
                    {
                        admin.removeAircraft();
                    }
                    else if (thirdchoice == 3)
                    {
                        admin.updateAircraft();
                    }
                    else if (thirdchoice == 4)
                    {
                        admin.addreport();
                    }
                    else if (thirdchoice == 5)
                    {
                        std::string recordId;
                        std::cout << "Enter record ID to update: " << std::endl;
                        std::cin >> recordId;
                        admin.updatereport(recordId);
                    }
                    else if (thirdchoice == 6)
                    {
                        std::string recordId;
                        std::cout << "Enter record ID to remove: " << std::endl;
                        std::cin >> recordId;
                        admin.removereport(recordId);
                    }
                    else if (thirdchoice == 7)
                    {
                        break;
                    }

                    break;

                case 4:
                    std::cout << "--- Generate Reports ---\n";
                    std::cout << "1. Operational Reports\n2. Maintenance Reports\n3. User Activity Reports\n4. Back to Main Menu\n";
                    int fourthchoice;
                    std::cin >> fourthchoice;
                    if (fourthchoice == 1)
                    {
                        admin.generateOperationalReport();
                    }
                    else if (fourthchoice == 2)
                    {
                        admin.generateMaintenanceReport();
                    }
                    else if (fourthchoice == 3)
                    {
                        admin.generateUserActivityReports();
                    }
                    else if (fourthchoice == 4)
                    {
                        break;
                    }
                    break;
                case 5:
                    session = false;
                    break;
                case 6:
                    running = false;
                    return 0;
                }

            } while (choice != 5 && session);
        }
        else if (a.login(username, password) && RealRole == "1")
        {

            std::cout << "Login successful\n";
            int choice;
            bool session = true;
            do
            {

                BookingAgent agent(username, password, "email", 20, "address", "office", "9:00-17:00");
                std::cout << "\n--- Booking agent Menu ---\n";
                std::cout << "1. Search Flights\n";
                std::cout << "2. Book a Flight\n";
                std::cout << "3. Modify Reservation\n";
                std::cout << "4. Cancel Reservation\n";
                std::cout << "5. Logout\n";
                std::cout << "6. Exit\n";
                std::cout << "Enter choice: ";
                std::cin >> choice;
                switch (choice)
                {
                case 1:
                {
                    auto results = agent.SearchFlight();
                    printResults("Search Results", results);
                }
                break;
                case 2:
                {

                    std::string passid, Flightnum, seatnum, paymethod, paydetails, resID;
                    std::cout << "--- Book a Flight ---\n";

                    std::cout << "Enter Reservation ID: \n";
                    std::cin >> resID;
                    std::cout << "Enter Passenger ID: \n";
                    std::cin >> passid;
                    std::cout << "Enter Flight Number\n";
                    std::cin >> Flightnum;
                    std::cout << "Enter Seat Number (e.g., 12A):\n";
                    std::cin >> seatnum;
                    std::cout << "Enter Payment Method (Credit Card/Cash/PayPal):\n";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    std::getline(std::cin, paymethod);
                    std::cout << "Enter Payment Details:\n";
                    std::cin >> paydetails;
                    auto flight = findflightbyFlightNumber(Flightnum);
                    auto passenger = findPassengerByID(passid);
                    if (!flight || !passenger)
                    {
                        std::cout << "Invalid Flight Number or Passenger ID.\n";
                        break;
                    }
                    auto reservation = std::make_shared<Reservation>(resID, passenger, flight, seatnum, paymethod, paydetails);
                    double amount = std::stod(flight->getPrice());
                    Payment payment("P101", reservation->getReservationId(), amount, paymethod);
                    if (payment.processPayment())
                    {

                        agent.BookFlight(reservation);
                        std::cout << "---------------------------\n";
                        std::cout << "Flight Booked Successfully\n";
                        reservation->displayReservation();
                        std::cout << "---------------------------\n";
                    }
                    else
                    {
                        std::cout << "Booking failed due to payment error.\n";
                    }
                }
                break;
                case 3:
                {
                    std::string reservationId;
                    std::cout << "Enter reservation ID to modify: ";
                    std::cin >> reservationId;
                    agent.UpdateFlight(reservationId);
                }
                break;
                case 4:
                {
                    Reservation_System system;
                    std::string reservationId, transID;
                    std::cout << "Enter reservation ID to cancel: ";
                    std::cin >> reservationId;

                    double refundAmount = getPriceFromReservationCSV(reservationId);
                    Payment refundPayment("transID", reservationId, refundAmount, "Refund");
                    refundPayment.refund();
                    agent.CancelFlight(reservationId);
                }
                break;
                case 5:
                    session = false;
                    break;

                case 6:
                    running = false;
                    return 0;
                }
            } while (choice != 6 && session);
        }
        else if (a.login(username, password) && RealRole == "2")
        {

            std::cout << "Login successful\n";
            int choice;
            bool session = true;
            do
            {
                auto ps = findPassengerByUsername(username);
                if (!ps)
                {
                    std::cout << "Passenger not found\n";
                    break;
                }
                Passenger passenger(username, password, "email", 20, "cairo", ps->getPassengerId());
                std::cout << "\n--- Passengers Menu ---\n";
                std::cout << "1. Search Flights\n";
                std::cout << "2. filter Flight\n";
                std::cout << "3. View My Reservations\n";
                std::cout << "4. Check-In\n";
                std::cout << "5. Logout\n";
                std::cout << "Enter choice: ";
                std::cin >> choice;
                switch (choice)
                {
                case 1:
                {

                    auto results = passenger.SearchFlight();
                    printResults("Search Results", results);
                    if (results.empty())
                    {
                        break;
                    }

                    std::string flightNumber;
                    std::cout << "\nEnter the Flight Number you wish to book (or '0' to cancel): ";
                    std::cin >> flightNumber;
                    if (flightNumber == "0")
                    {
                        std::cout << "Booking cancelled.\n";
                        break;
                    }

                    std::string seatNumber, paymentMethod, paymentDetails;
                    std::cout << "Enter Seat Number (e.g., 14C): ";
                    std::cin >> seatNumber;
                    std::cout << "Enter Payment Method (Credit Card/Cash/PayPal): ";
                    std::cin >> paymentMethod;
                    std::cout << "Enter Payment Details: ";
                    std::cin >> paymentDetails;

                    auto flight = findflightbyFlightNumber(flightNumber);
                    if (!flight)
                    {
                        std::cout << " Flight not found.\n";
                        break;
                    }

                    auto foundPassenger = findPassengerByID(passenger.getPassengerId());
                    if (!foundPassenger)
                    {
                        std::cout << "Passenger not found.\n";
                        break;
                    }

                    std::string reservationId;
                    std::cout << "Enter reservation ID: ";
                    std::cin >> reservationId;

                    auto booking = std::make_shared<Reservation>(
                        reservationId, foundPassenger, flight,
                        seatNumber, paymentMethod, paymentDetails);

                    passenger.wishToBook(booking);
                }

                break;
                case 2:
                {
                    auto result = passenger.FilterFlight();
                    printResults("Filtered Results", result);
                }
                break;
                case 3:
                {
                    auto results = passenger.viewMyReservations();
                    if (results.empty())
                    {
                        std::cout << "No reservations found for you.\n";
                    }
                    else
                    {
                        std::cout << "\n--- Your Reservations ---\n";
                        for (const auto &r : results)
                        {
                            std::cout << "Reservation ID: " << r.reservationId << "\n";
                            std::cout << "Passenger ID: " << r.passengerId;
                            if (!r.passengerName.empty())
                                std::cout << " (" << r.passengerName << ")";
                            std::cout << "\n";

                            std::cout << "Flight Number: " << r.flightNumber;
                            if (r.flightPtr)
                            {

                                std::cout << "  [" << r.flightPtr->getOrigin() << " -> " << r.flightPtr->getDestination() << "]";
                            }
                            else
                            {
                                std::cout << " (Details not found)";
                            }
                            std::cout << "\n";

                            std::cout << "Seat: " << r.seat << "\n";
                            std::cout << "Total Cost: " << r.totalCost << "\n";
                            std::cout << "Payment: " << r.paymentMethod << " (" << r.paymentDetails << ")\n";
                            std::cout << "-----------------------------\n";
                        }
                    }
                }
                break;
                case 4:
                {
                    std::string reservationId;
                    std::cout << "Enter reservation ID to check-in: ";
                    std::cin >> reservationId;

                    CheckIn checkin;
                    if (checkin.loadReservation(reservationId))
                    {
                        checkin.checkIn();
                    }
                    else
                    {
                        std::cout << " Reservation not found.\n";
                    }
                }

                break;

                case 5:
                    session = false;
                    break;
                }
            } while (session);
        }
        else
        {
            std::cout << "Invalid choice or login credentials.\n";
            return 0;
        }
    }
    return 0;
}
