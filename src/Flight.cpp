#include "../include/Flight.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
// Setters and getters
void Flight::setFlightNumber(const std::string &flightNumber)
{
    this->flightNumber = flightNumber;
}

void Flight::setOrigin(const std::string &origin)
{
    this->origin = origin;
}
void Flight::setDate(const std::string &date)
{
    this->date = date;
}

void Flight::setDestination(const std::string &destination)
{
    this->destination = destination;
}

void Flight::setDeparture(const std::string &departure)
{
    this->departure = departure;
}

void Flight::setDepartureTime(const std::string &departureTime)
{
    this->departureTime = departureTime;
}

void Flight::setArrivalTime(const std::string &arrivalTime)
{
    this->arrivalTime = arrivalTime;
}

void Flight::setPrice(const std::string &price)
{
    this->price = price;
}

void Flight::setAircraftType(const std::string &aircraft_type)
{
    this->aircraft_type = aircraft_type;
}

std::string Flight::getFlightNumber() const
{
    return this->flightNumber;
}

std::string Flight::getOrigin() const
{
    return this->origin;
}
std::string Flight::getDate() const
{
    return this->date;
}
std::string Flight::getDestination() const
{
    return this->destination;
}

std::string Flight::getDeparture() const
{
    return this->departure;
}

std::string Flight::getDepartureTime() const
{
    return this->departureTime;
}

std::string Flight::getArrivalTime() const
{
    return this->arrivalTime;
}

std::string Flight::getPrice() const
{
    return this->price;
}

std::string Flight::getAircraftType() const
{
    return this->aircraft_type;
}
void Flight::displayFlight() const
{
    std::cout << "Flight Number: " << this->flightNumber << std::endl;
    std::cout << "Origin: " << this->origin << std::endl;
    std::cout << "Date: " << this->date << std::endl;
    std::cout << "Destination: " << this->destination << std::endl;
    std::cout << "Departure: " << this->departure << std::endl;
    std::cout << "Departure Time: " << this->departureTime << std::endl;
    std::cout << "Arrival Time: " << this->arrivalTime << std::endl;
    std::cout << "Price: " << this->price << std::endl;
    std::cout << "Aircraft Type: " << this->aircraft_type << std::endl;
    std::cout << "Status: " << this->status << std::endl;
    std::cout << "Total Seats: " << this->totalSeats << std::endl;
}

/*Flight Management*/
FlightManagment::FlightManagment()
{
}

FlightManagment::~FlightManagment()
{
    if (file.is_open())
        file.close();
}

void FlightManagment::ManageFlightsMenu()
{
    int choice;
    do
    {
        std::cout << "--- Manage Flights ---\n";
        std::cout << "1. Add Flight\n";
        std::cout << "2. Update Existing Flight\n";
        std::cout << "3. Remove Flight\n";
        std::cout << "4. View All Flights\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            addFlight();
            break;
        case 2:
            updateFlight();
            break;
        case 3:
            removeFlight();
            break;
        case 4:
            viewAllFlights();
            break;
        }
    } while (choice != 5);
}
void FlightManagment::addFlight()
{
    std::string flightNumber, origin, date, destination, departure, departureTime, arrivalTime, price, aircraft_type, status;
    int totalSeats;

    std::cin.ignore(); // clear leftover newline from previous input

    std::cout << "Enter flight number: ";
    std::getline(std::cin, flightNumber);
    std::cout << "Enter origin: ";
    std::getline(std::cin, origin);
    std::cout << "Enter date: (YYYY-MM-DD): ";
    std::getline(std::cin, date);
    std::cout << "Enter destination: ";
    std::getline(std::cin, destination);
    std::cout << "Enter departure: ";
    std::getline(std::cin, departure);
    std::cout << "Enter departure time (HH:MM): ";
    std::getline(std::cin, departureTime);
    std::cout << "Enter arrival time (HH:MM): ";
    std::getline(std::cin, arrivalTime);
    std::cout << "Enter price: ";
    std::getline(std::cin, price);
    std::cout << "Enter aircraft type: ";
    std::getline(std::cin, aircraft_type);
    std::cout << "Enter flight status (On Time/Delayed/Canceled): ";
    std::getline(std::cin, status);
    std::cout << "Enter total seats: ";
    std::cin >> totalSeats;

    // Create a Flight object from entered data
    Flight flight(flightNumber, origin, date, destination, departure, departureTime, arrivalTime, price, aircraft_type, status, totalSeats);

    // Open file for append
    std::ofstream outFile("../database/flights.csv", std::ios::app);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Could not open flights.csv\n";
        return;
    }

    // Save flight details to file
    outFile << flight.getFlightNumber() << ","
            << flight.getOrigin() << ","
            << flight.getDate() << ","
            << flight.getDestination() << ","
            << flight.getDeparture() << ","
            << flight.getDepartureTime() << ","
            << flight.getArrivalTime() << ","
            << flight.getPrice() << ","
            << flight.getAircraftType() << ","
            << flight.getStatus() << ","
            << flight.getTotalSeats() << "\n";

    outFile.close();

    std::cout << "Flight " << flight.getFlightNumber() << " added successfully.\n";
}
void FlightManagment::updateFlight()
{
    std::string flightNumber;
    std::cout << "--- Update Existing Flight ---\n";
    std::cout << "Enter Flight Number to Update: ";
    std::cin >> flightNumber;

    int choice;
    do
    {
        std::cout << "\nSelect information to update:\n";
        std::cout << "1. Flight Details\n";
        std::cout << "2. Crew Assignments\n";
        std::cout << "3. Back to Manage Flights\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            updateFlightDetails(flightNumber);
            break;
        case 2:
            updateCrewAssignment(flightNumber);
            break;
        case 3:
            std::cout << "Returning to Manage Flights...\n";
            break;
        default:
            std::cout << "Invalid choice.\n";
        }
    } while (choice != 3);
}
void FlightManagment::updateFlightDetails(const std::string &flightNumber)
{
    std::ifstream inFile("../database/flights.csv");
    if (!inFile.is_open())
    {
        std::cerr << "Error: Could not open flights.csv\n";
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

        if (id == flightNumber)
        {
            found = true;
            std::string origin, date, destination, departure, departureTime, arrivalTime, price, aircraft_type, status, totalSeats;
            getline(ss, origin, ',');
            getline(ss, date, ',');
            getline(ss, destination, ',');
            getline(ss, departure, ',');
            getline(ss, departureTime, ',');
            getline(ss, arrivalTime, ',');
            getline(ss, price, ',');
            getline(ss, aircraft_type, ',');
            getline(ss, status, ',');
            getline(ss, totalSeats, ',');

            std::cout << "Enter new Destination: ";
            std::cin.ignore();
            getline(std::cin, destination);

            std::ostringstream updated;
            updated << id << "," << origin << "," << date << "," << destination << ","
                    << departure << "," << departureTime << "," << arrivalTime << ","
                    << price << "," << aircraft_type << "," << status << "," << totalSeats;
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
        std::cout << "Flight not found.\n";
        return;
    }

    std::ofstream outFile("../database/flights.csv", std::ios::trunc);
    for (auto &l : lines)
        outFile << l << "\n";
    outFile.close();

    std::cout << "Flight details updated successfully.\n";
}
void FlightManagment::updateCrewAssignment(const std::string &flightNumber)
{
    std::string pilotId, attendantId;

    std::cout << "\n--- Crew Assignments ---\n";
    std::cout << "Available Pilots:\n";
    std::cout << "1. PL001 - Captain Sarah Connor\n";
    std::cout << "2. PL002 - Captain James Kirk\n";
    std::cout << "Select Pilot by ID: ";
    std::cin >> pilotId;

    std::cout << "\nAvailable Flight Attendants:\n";
    std::cout << "1. FA001 - Emma Watson\n";
    std::cout << "2. FA002 - John Cena\n";
    std::cout << "Select Flight Attendant by ID: ";
    std::cin >> attendantId;

    std::ofstream outFile("../database/flight_crew.csv", std::ios::app);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Could not open flight_crew.csv\n";
        return;
    }

    outFile << flightNumber << "," << pilotId << "," << attendantId << "\n";
    outFile.close();

    std::cout << "Crew assigned successfully to Flight " << flightNumber << ".\n";
}
void FlightManagment::removeFlight()
{

    std::ifstream inFile("../database/flights.csv");
    if (!inFile.is_open())
    {
        std::cerr << "Error: Could not open flights.csv\n";
        return;
    }
    std::string flightNumber;
    std::cout << "Enter Flight Number to remove " << std::endl;
    std::cin >> flightNumber;
    std::vector<std::string> lines;
    std::string line;
    bool found = false;

    while (getline(inFile, line))
    {
        std::stringstream ss(line);
        std::string id;
        getline(ss, id, ',');

        if (id == flightNumber)
        {
            found = true;
            continue;
        }
        lines.push_back(line);
    }

    inFile.close();

    if (!found)
    {
        std::cout << "Flight not found.\n";
        return;
    }

    std::ofstream outFile("../database/flights.csv", std::ios::trunc);
    for (auto &l : lines)
        outFile << l << "\n";
    outFile.close();

    std::cout << "Flight removed successfully.\n";
}
void FlightManagment::viewAllFlights()
{
    std::ifstream inFile("../database/flights.csv");
    if (!inFile.is_open())
    {
        std::cerr << "Error: Could not open flights.csv\n";
        return;
    }
    std::vector<Flight> lines;
    std::string line;
    std::getline(inFile, line);
    while (std::getline(inFile, line))
    {
        std::stringstream ss(line);
        std::string flightNumber, origin, date, destination, departure, departureTime, arrivalTime, price, aircraft_type, status, totalSeats;
        getline(ss, flightNumber, ',');
        getline(ss, origin, ',');
        getline(ss, date, ',');
        getline(ss, destination, ',');
        getline(ss, departure, ',');
        getline(ss, departureTime, ',');
        getline(ss, arrivalTime, ',');
        getline(ss, price, ',');
        getline(ss, aircraft_type, ',');
        getline(ss, status, ',');
        getline(ss, totalSeats, ',');
        
        lines.emplace_back(flightNumber, origin, date, destination, departure, departureTime, arrivalTime, price, aircraft_type, status, std::stoi(totalSeats));
    }
    inFile.close();
    std::cout << "All Flights are: " << std::endl;
    std::cout << "-------------------------------------------------------------\n";
    for (auto &f : lines)
    {
        f.displayFlight();
        std::cout << "-------------------------------------------------------------\n";
    }
}
