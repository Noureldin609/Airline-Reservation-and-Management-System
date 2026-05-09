#include "../include/Reservation.h"
#include "../include/Passenger.h"
#include "../include/Flight.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include<limits>
void Reservation::displayReservation() const
{
    std::cout << "Reservation ID: " << reservationId << std::endl;
    std::cout << "Passenger Name: " << passenger->getUsername() << std::endl;
    if (auto f = flight.lock())
    {
        std::cout << "Flight: " << f->getFlightNumber() << " From " << f->getOrigin() << " to " << f->getDestination() << std::endl;
    }
    else
    {
        std::cout << "Flight expired (no longer available)." << std::endl;
    }
    std::cout << "Seat: " << seat << std::endl;
    std::cout << "Total Cost: " << flight.lock()->getPrice() << "\n";
    std::cout << "Payment Method: " << PaymentMethod << std::endl;
}

std::shared_ptr<Flight> findflightbyFlightNumber(const std::string &flightnumber)
{
    std::ifstream flightFile("../database/Flights.csv");
    if (!flightFile.is_open())
    {
        std::cerr << "Could not open flights.csv\n";
        return nullptr;
    }
    std::string line;
    std::getline(flightFile, line);
    while (std::getline(flightFile, line))
    {
        std::stringstream ss(line);
        std::string fNumber, origin, date, destination, departure, departureTime, arrivalTime, price, aircraftType, status, seats;
        std::getline(ss, fNumber, ',');
        std::getline(ss, origin, ',');
        std::getline(ss, date, ',');
        std::getline(ss, destination, ',');
        std::getline(ss, departure, ',');
        std::getline(ss, departureTime, ',');
        std::getline(ss, arrivalTime, ',');
        std::getline(ss, price, ',');
        std::getline(ss, aircraftType, ',');
        std::getline(ss, status, ',');
        std::getline(ss, seats, ',');

        if (fNumber == flightnumber)
        {
            return std::make_shared<Flight>(fNumber, origin, date, destination, departure, departureTime, arrivalTime, price, aircraftType, status, std::stoi(seats));
        }
    }
    flightFile.close();
    return nullptr;
}

std::shared_ptr<Passenger> findPassengerByID(const std::string &passengerId)
{
    std::ifstream PassFile("../database/Passengers.csv");
    if (!PassFile.is_open())
    {
        std::cerr << "Could not open\n";
        return nullptr;
    }

    std::string line;
    while (std::getline(PassFile, line))
    {
        std::stringstream ss(line);
        std::string uname, pwd, email, ageStr, address, UniqueID;
        std::getline(ss, uname, ',');
        std::getline(ss, pwd, ',');
        std::getline(ss, email, ',');
        std::getline(ss, ageStr, ',');
        std::getline(ss, address, ',');
        std::getline(ss, UniqueID, ',');

        if (UniqueID == passengerId)
        {
            int age = std::stoi(ageStr);
            PassFile.close();
            return std::make_shared<Passenger>(uname, pwd, email, age, address, UniqueID);
        }
    }
    PassFile.close();
    return nullptr;
}
std::shared_ptr<Passenger> findPassengerByUsername(const std::string &username)
{
    std::ifstream PassFile("../database/Passengers.csv");
    if (!PassFile.is_open())
    {
        std::cerr << "Could not open\n";
        return nullptr;
    }

    std::string line;
    while (std::getline(PassFile, line))
    {
        std::stringstream ss(line);
        std::string uname, pwd, email, ageStr, address, UniqueID;
        std::getline(ss, uname, ',');
        std::getline(ss, pwd, ',');
        std::getline(ss, email, ',');
        std::getline(ss, ageStr, ',');
        std::getline(ss, address, ',');
        std::getline(ss, UniqueID, ',');

        if (uname == username)
        {
            int age = std::stoi(ageStr);
            PassFile.close();
            return std::make_shared<Passenger>(uname, pwd, email, age, address, UniqueID);
        }
    }
    PassFile.close();
    return nullptr;
}

double getPriceFromReservationCSV(const std::string &reservationId)
{
    std::ifstream file("../database/Reservations.csv");
    std::string line;
    std::getline(file, line); // skip header

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string id, passengerId, flightId, seat, price, paymentMethod, paymentDetails;
        std::getline(ss, id, ',');
        std::getline(ss, passengerId, ',');
        std::getline(ss, flightId, ',');
        std::getline(ss, seat, ',');
        std::getline(ss, price, ',');
        std::getline(ss, paymentMethod, ',');
        std::getline(ss, paymentDetails, ',');

        if (id == reservationId)
            return std::stod(price);
    }

    std::cerr << "❌ Reservation ID not found in CSV: " << reservationId << "\n";
    return 0.0;
}
void Reservation_System::loadReservations()
{
    reservations.clear();
    FillReservations(reservations); // You already have FillReservations defined globally
}
void FillReservations(std::vector<std::shared_ptr<Reservation>> &reservations)
{
    reservations.clear();
    std::ifstream file("../database/Reservations.csv");

    if (!file.is_open())
    {
        std::cerr << " Error: Could not open Reservations.csv\n";
        return;
    }

    std::string line;
    std::getline(file, line); // skip header

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string reservationId, passengerId, flightNumber, seat, TC, PaymentMethod, PaymentDetails;
        std::getline(ss, reservationId, ',');
        std::getline(ss, passengerId, ',');
        std::getline(ss, flightNumber, ',');
        std::getline(ss, seat, ',');
        std::getline(ss, TC, ',');
        std::getline(ss, PaymentMethod, ',');
        std::getline(ss, PaymentDetails, ',');

        auto passenger = findPassengerByID(passengerId);
        auto flight = findflightbyFlightNumber(flightNumber);

        if (passenger && flight)
        {
            auto reservation = std::make_shared<Reservation>(
                reservationId, passenger, flight, seat, PaymentMethod, PaymentDetails);
            reservations.push_back(reservation);
        }
    }

    file.close();
}

void Reservation_System::CreateReservation(const std::shared_ptr<Reservation> &reservation)
{
    // Step 1: Load all current reservations to check for duplicates
    FillReservations(reservations);

    for (const auto &r : reservations)
    {
        if (r->reservationId == reservation->reservationId)
        {
            std::cout << " Reservation with ID " << reservation->reservationId << " already exists.\n";
            return;
        }
    }

    // Step 2: Add to vector and append to file
    reservations.push_back(reservation);
    std::ofstream file(filePath, std::ios::app);

    if (!file.is_open())
    {
        std::cerr << " Failed to open file for writing.\n";
        return;
    }

    if (auto f = reservation->flight.lock())
    {
        file << reservation->reservationId << ","
             << reservation->passenger->getPassengerId() << ","
             << f->getFlightNumber() << ","
             << reservation->seat << ","
             << f->getPrice() << ","
             << reservation->PaymentMethod << ","
             << reservation->PaymentDetails << "\n";
    }

    file.close();
    std::cout << " Reservation added successfully: " << reservation->reservationId << "\n";
}

std::string Reservation::getReservationId() const { return reservationId; }
std::string Reservation::getPaymentMethod() const { return PaymentMethod; }

void Reservation_System::CancelReservation(const std::string &reservationId)
{

    std::ifstream inFile(filePath);
    if (!inFile.is_open())
    {
        std::cerr << " Error: Could not open file for reading.\n";
        return;
    }

    std::ofstream outFile("../database/TempReservations.csv");
    if (!outFile.is_open())
    {
        std::cerr << " Error: Could not open temp file for writing.\n";
        return;
    }

    std::string line;
    bool found = false;

    // Copy the header line as is
    if (std::getline(inFile, line))
        outFile << line << "\n";

    // Go through all reservations
    while (std::getline(inFile, line))
    {
        std::stringstream ss(line);
        std::string id;
        std::getline(ss, id, ','); // first field is reservation ID

        if (id == reservationId)
        {
            found = true;
            std::cout << " Deleting reservation " << reservationId << "\n";
            continue; // skip writing this line
        }

        outFile << line << "\n"; // keep all others unchanged
    }

    inFile.close();
    outFile.close();

    // Replace the original file with the new one
    std::remove(filePath.c_str());
    std::rename("../database/TempReservations.csv", filePath.c_str());

    if (found)
        std::cout << " Reservation " << reservationId << " removed successfully.\n";
    else
        std::cout << " Reservation ID not found.\n";
}

void Reservation_System::updateReservation(const std::string &reservationId)
{
    std::ifstream inFile("../database/Reservations.csv");
    if (!inFile.is_open())
    {
        std::cerr << "Error: Could not open Reservations.csv\n";
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    bool found = false;

    while (getline(inFile, line))
    {
        std::stringstream ss(line);
        std::string id;
        getline(ss, id, ',');

        if (id == reservationId)
        {
            found = true;
            std::string PassengerID, FlightID, Seatno, Totalcost, PaymentMethod, PaymentDetails;
            getline(ss, PassengerID, ',');
            getline(ss, FlightID, ',');
            getline(ss, Seatno, ',');
            getline(ss, Totalcost, ',');
            getline(ss, PaymentMethod, ',');
            getline(ss, PaymentDetails, ',');
            std::cout << "\n--- Update Reservation ---\n";
            std::cout << "1. Seat Number\n";
            std::cout << "2. Payment Method\n";
            std::cout << "3. Payment Details\n";
            std::cout << "Enter the number of the field you want to update: ";

            int choice;
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer

            switch (choice)
            {
            case 1:
                std::cout << "Enter new Seat number: ";
                std::getline(std::cin, Seatno);
                break;

            case 2:
                std::cout << "Enter new Payment Method: ";
                std::getline(std::cin, PaymentMethod);
                break;
            case 3:
                std::cout << "Enter new Payment Details: ";
                std::getline(std::cin, PaymentDetails);
                break;
            default:
                std::cout << "Invalid option. No changes made.\n";
                break;
            }

            std::ostringstream updated;
            updated << id << "," << PassengerID << "," << FlightID << "," << Seatno << "," << Totalcost << "," << PaymentMethod << "," << PaymentDetails;
            lines.push_back(updated.str());
        }
        else
        {
            lines.push_back(line);
        }
    }

    inFile.close();

    if (!found)
    {
        std::cout << "Reservation not found.\n";
        return;
    }

    std::ofstream outFile("../database/Reservations.csv", std::ios::trunc);
    for (auto &l : lines)
        outFile << l << "\n";
    outFile.close();

    std::cout << "Reservation details updated successfully.\n";
}

void Reservation_System::showReservations() const
{
    std::cout << "Reservations: " << std::endl;
    for (auto &reservation : reservations)
    {
        reservation->displayReservation();
    }
}

std::shared_ptr<Reservation> findReservationByID(const std::string &reservationId)
{
    std::ifstream file("../database/Reservations.csv");
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open Reservations.csv\n";
        return nullptr;
    }

    std::string line;
    std::getline(file, line); // skip header

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string resId, passengerId, flightNumber, seat, totalCost, paymentMethod, paymentDetails;

        std::getline(ss, resId, ',');
        std::getline(ss, passengerId, ',');
        std::getline(ss, flightNumber, ',');
        std::getline(ss, seat, ',');
        std::getline(ss, totalCost, ',');
        std::getline(ss, paymentMethod, ',');
        std::getline(ss, paymentDetails, ',');

        if (resId == reservationId)
        {
            auto passenger = findPassengerByID(passengerId);
            auto flight = findflightbyFlightNumber(flightNumber);
            if (passenger && flight)
            {
                return std::make_shared<Reservation>(resId, passenger, flight, seat, paymentMethod, paymentDetails);
            }
        }
    }

    return nullptr;
}
