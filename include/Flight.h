#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>
#include <fstream>
class Flight
{
private:
    std::string flightNumber;
    std::string origin;
    std::string date;
    std::string destination;
    std::string departure;
    std::string departureTime;
    std::string arrivalTime;
    std::string price;
    std::string aircraft_type;
    std::string status;
    int totalSeats;

public:
    /*Constructor*/
    Flight(std::string flightNumber, std::string origin, std::string date, std::string destination,
           std::string departure, std::string departureTime, std::string arrivalTime,
           std::string price, std::string aircraft_type,
           std::string status = "On Time", int totalSeats = 100)
    {
        this->flightNumber = flightNumber;
        this->origin = origin;
        this->date = date;
        this->destination = destination;
        this->departure = departure;
        this->departureTime = departureTime;
        this->arrivalTime = arrivalTime;
        this->price = price;
        this->aircraft_type = aircraft_type;
        this->status = status;
        this->totalSeats = totalSeats;
    }
    /*Setters and Getters*/
    std::string getFlightNumber() const;
    void setFlightNumber(const std::string &flightNumber);

    std::string getOrigin() const;
    void setOrigin(const std::string &origin);

    std::string getDate() const;
    void setDate(const std::string &date);
    std::string getDestination() const;
    void setDestination(const std::string &destination);

    std::string getDeparture() const;
    void setDeparture(const std::string &departure);

    std::string getDepartureTime() const;
    void setDepartureTime(const std::string &departureTime);

    std::string getArrivalTime() const;
    void setArrivalTime(const std::string &arrivalTime);

    std::string getPrice() const;
    void setPrice(const std::string &price);

    std::string getAircraftType() const;
    void setAircraftType(const std::string &aircraft_type);
    std::string getStatus() const { return status; }
    int getTotalSeats() const { return totalSeats; }

    void setStatus(const std::string &newStatus) { status = newStatus; }
    void setTotalSeats(int seats) { totalSeats = seats; }
    /*Display flight*/
    void displayFlight() const;
    friend class FlightManagment;
};
class FlightManagment
{
private:
    std::fstream file;
    void updateFlightDetails(const std::string &flightNumber);
    void updateCrewAssignment(const std::string &flightNumber);

public:
    FlightManagment();
    ~FlightManagment();
    void ManageFlightsMenu();
    void addFlight();
    void updateFlight();
    void removeFlight();
    void viewAllFlights();
};
#endif