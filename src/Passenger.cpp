#include "../include/passenger.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
#include <ctime>
std::vector<Flight> Passenger::SearchFlight()
{
    std::vector<Flight> Flights;
    std::vector<Flight> result;
    std::ifstream file("../database/flights.csv");
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open flights.csv\n";
        return result;
    }
    std::string origin, destination, Date;
    std::cout << "Enter Origin: ";
    std::cin >> origin;
    std::cout << "Enter Destination: ";
    std::cin >> destination;
    std::cout << "Enter Date: ";
    std::cin >> Date;
    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string flightNumber, origin, date, destination, departure, departureTime, arrivalTime, price, aircraft_type;
        getline(ss, flightNumber, ',');
        getline(ss, origin, ',');
        getline(ss, date, ',');
        getline(ss, destination, ',');
        getline(ss, departure, ',');
        getline(ss, departureTime, ',');
        getline(ss, arrivalTime, ',');
        getline(ss, price, ',');
        getline(ss, aircraft_type, ',');
        Flights.emplace_back(flightNumber, origin, date, destination, departure, departureTime, arrivalTime, price, aircraft_type);
    }
    file.close();
    std::copy_if(Flights.begin(), Flights.end(), std::back_inserter(result),
                 [&](const Flight &flight)
                 {
                     bool dateMatch = (flight.getDate() == Date);
                     bool destMatch = (flight.getDestination() == destination);
                     bool originMatch = (flight.getOrigin() == origin);

                     return dateMatch && destMatch && originMatch;
                 });

    return result;
}

std::vector<Flight> Passenger::FilterFlight()
{
    std::vector<Flight> Flights;
    std::vector<Flight> result;
    int option;
    std::string origin, destination, Date, line;
    std::ifstream file("../database/flights.csv");
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open flights.csv\n";
        return result;
    }
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string flightNumber, origin, date, destination, departure, departureTime, arrivalTime, price, aircraft_type;
        getline(ss, flightNumber, ',');
        getline(ss, origin, ',');
        getline(ss, date, ',');
        getline(ss, destination, ',');
        getline(ss, departure, ',');
        getline(ss, departureTime, ',');
        getline(ss, arrivalTime, ',');
        getline(ss, price, ',');
        getline(ss, aircraft_type, ',');
        Flights.emplace_back(flightNumber, origin, date, destination, departure, departureTime, arrivalTime, price, aircraft_type);
    }
    file.close();
    std::cout << "Enter Filter Criteria: \n";
    std::cout << "1. Origin\n2. Destination\n3. Date\n";
    std::cin >> option;
    switch (option)
    {
    case 1:
    {

        std::cout << "Enter Origin: ";
        std::cin >> origin;
        auto FilterByOrigin = [&]()
        {
            std::vector<Flight> temp;
            for (auto &flight : Flights)
            {
                if (flight.getOrigin() == origin)
                {
                    temp.push_back(flight);
                }
            }
            return temp;
        };

        result = FilterByOrigin();
        break;
    }
    case 2:
    {

        std::cout << "Enter Destination: ";
        std::cin >> destination;
        auto FilterByDestination = [&]()
        {
            std::vector<Flight> temp;
            for (auto &flight : Flights)
            {
                if (flight.getDestination() == destination)
                {
                    temp.push_back(flight);
                }
            }
            return temp;
        };
        result = FilterByDestination();
        break;
    }

    case 3:
    {

        std::cout << "Enter Date (YYYY-MM-DD) :";
        std::cin >> Date;
        auto FilterByDate = [&]()
        {
            std::vector<Flight> temp;
            for (auto &flight : Flights)
            {
                if (flight.getDate() == Date)
                {
                    temp.push_back(flight);
                }
            }
            return temp;
        };
        result = FilterByDate();
        break;
    }

    default:
        break;
    }
    return result;
}

void Passenger::displayUser()
{
    std::cout << "Username: " << username << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Role: " << "Passenger" << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Address: " << address << std::endl;
    std::cout << "Passenger ID: " << passengerId << std::endl;
}

std::string Passenger::getPassengerId() const
{
    return passengerId;
}

void Passenger::setPassengerId(const std::string &passengerId)
{
    this->passengerId = passengerId;
}

bool Passenger::checkuserRoll(Role role)
{
    return role == PASSENGER;
}
void Passenger::wishToBook(const std::shared_ptr<Reservation> &reservation)
{
    auto f = reservation->flight.lock();
    if (!f)
    {
        std::cerr << " Invalid flight information.\n";
        return;
    }

    //  Save reservation to file
    std::ofstream file("../database/Reservations.csv", std::ios::app);
    if (!file.is_open())
    {
        std::cerr << " Failed to open file for writing.\n";
        return;
    }

    file << reservation->reservationId << ","
         << reservation->passenger->getPassengerId() << ","
         << f->getFlightNumber() << ","
         << reservation->seat << ","
         << f->getPrice() << ","
         << reservation->PaymentMethod << ","
         << reservation->PaymentDetails << "\n";
    file.close();

    //  Simulate payment successs
    std::string transac = "T" + std::to_string(rand() % 1000 + 100);
    Payment payment(transac, reservation->reservationId,
                    std::stod(f->getPrice()), reservation->PaymentMethod);
    payment.processPayment();

    //  Display confirmation summary
    std::cout << "\n Booking successful!\n";
    std::cout << "-------------------------------------------\n";
    std::cout << "Reservation ID: " << reservation->reservationId << "\n";
    std::cout << "Flight: " << f->getFlightNumber()
              << " from " << f->getOrigin()
              << " to " << f->getDestination() << "\n";
    std::cout << "Seat: " << reservation->seat << "\n";
    std::cout << "Total Cost: $"
              << std::stod(f->getPrice()) << "\n";
    std::cout << "Payment Method: " << reservation->PaymentMethod << "\n";
    std::cout << "-------------------------------------------\n";
}

std::vector<ReservationView> Passenger::viewMyReservations()
{
    std::vector<ReservationView> results;


    std::ifstream file("database/Reservations.csv");
    if (!file.is_open())
    {
        std::cerr << " Failed to open Reservations.csv (path: database/Reservations.csv)\n";
        return results;
    }

    std::string line;
    if (!std::getline(file, line)) return results; // nothing in file
    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string reservationId, passid, flightNumber, seat, totalCost, paymentMethod, paymentDetails;

        std::getline(ss, reservationId, ',');
        std::getline(ss, passid, ',');
        std::getline(ss, flightNumber, ',');
        std::getline(ss, seat, ',');
        std::getline(ss, totalCost, ',');
        std::getline(ss, paymentMethod, ',');
        std::getline(ss, paymentDetails, ',');

        auto trim = [](std::string &s) {
            while (!s.empty() && (s.back() == '\r' || s.back() == '\n' || s.back() == ' ' || s.back() == '\t')) s.pop_back();
            size_t i = 0;
            while (i < s.size() && (s[i] == ' ' || s[i] == '\t')) ++i;
            if (i) s.erase(0, i);
        };
        trim(reservationId); trim(passid); trim(flightNumber);
        trim(seat); trim(totalCost); trim(paymentMethod); trim(paymentDetails);


        if (passid != passengerId) continue;

        ReservationView rv;
        rv.reservationId = reservationId;
        rv.passengerId = passid;
        rv.flightNumber = flightNumber;
        rv.seat = seat;
        rv.totalCost = totalCost;
        rv.paymentMethod = paymentMethod;
        rv.paymentDetails = paymentDetails;


        rv.passengerPtr = findPassengerByID(passid);      
        if (rv.passengerPtr) rv.passengerName = rv.passengerPtr->getUsername();

        std::string fn = flightNumber;
        rv.flightPtr = findflightbyFlightNumber(fn);    

        results.push_back(std::move(rv));
    }

    file.close();
    return results;
}