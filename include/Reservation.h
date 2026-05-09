#ifndef RESERVATION_H
#define RESERVATION_H
#include <string>
#include <vector>
#include <sstream>
#include <ctime>
#include <memory>
#include <iostream>
#include "Flight.h"
class Passenger;
class Reservation
{

public:
    std::string reservationId;
    std::shared_ptr<Passenger> passenger;
    std::weak_ptr<Flight> flight;
    std::string seat;
    std::string PaymentMethod;
    std::string PaymentDetails;
    Reservation(std::string reservationId, std::shared_ptr<Passenger> passenger, std::weak_ptr<Flight> flight, std::string seat, std::string PaymentMethod, std::string PaymentDetails) : reservationId(reservationId), passenger(passenger), flight(flight), seat(seat), PaymentMethod(PaymentMethod), PaymentDetails(PaymentDetails) {}
    void displayReservation() const;
    std::string getReservationId() const;
    std::string getPaymentMethod() const;
};
void FillReservations(std::vector<std::shared_ptr<Reservation>> &reservations);
class Reservation_System
{
    std::vector<std::shared_ptr<Reservation>> reservations;
    std::string filePath = "../database/Reservations.csv";

public:
    void CreateReservation(const std::shared_ptr<Reservation> &reservation);
    void CancelReservation(const std::string &reservationId);
    void updateReservation(const std::string &reservationId);
    void showReservations() const;
    void loadReservations();
};

class CheckIn
{
    std::string reservationId;
    std::string passengerId;
    std::string flightId;
    std::string seat;
    std::string totalCost;
    std::string gate;
    std::string boardingTime;

public:
    CheckIn() { srand(time(0)); }

    bool loadReservation(const std::string &reservationId)
    {
        std::ifstream file("../database/Reservations.csv");
        if (!file.is_open())
        {
            std::cerr << " Error: Unable to open Reservations.csv\n";
            return false;
        }

        std::string line;
        std::getline(file, line); // skip header
        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            std::string rid, pid, fid, seatNum, cost, payM, payD;
            std::getline(ss, rid, ',');
            std::getline(ss, pid, ',');
            std::getline(ss, fid, ',');
            std::getline(ss, seatNum, ',');
            std::getline(ss, cost, ',');
            std::getline(ss, payM, ',');
            std::getline(ss, payD, ',');

            if (rid == reservationId)
            {
                this->reservationId = rid;
                this->passengerId = pid;
                this->flightId = fid;
                this->seat = seatNum;
                this->totalCost = cost;
                return true;
            }
        }
        return false;
    }

    void checkIn()
    {
        if (reservationId.empty())
        {
            std::cout << " No reservation loaded.\n";
            return;
        }

        // Random gate number
        int gateNum = rand() % 20 + 1;
        gate = "B" + std::to_string(gateNum);

        // Random boarding time (just simulate)
        int hour = rand() % 12 + 1;
        int minute = (rand() % 2) ? 0 : 30;
        boardingTime = (hour < 10 ? "0" : "") + std::to_string(hour) + ":" +
                       (minute == 0 ? "00" : "30");

        displayBoardingPass();
    }

    void displayBoardingPass() const
    {
        std::cout << "\nCheck-In Successful!\n";
        std::cout << "Boarding Pass:\n";
        std::cout << "-----------------------------\n";
        std::cout << "Reservation ID: " << reservationId << "\n";
        std::cout << "Passenger ID:   " << passengerId << "\n";
        std::cout << "Flight:         " << flightId << "\n";
        std::cout << "Seat:           " << seat << "\n";
        std::cout << "Total Cost:     $" << totalCost << "\n";
        std::cout << "Gate:           " << gate << "\n";
        std::cout << "Boarding Time:  " << boardingTime << "\n";
        std::cout << "-----------------------------\n";
    }
};
std::shared_ptr<Flight> findflightbyFlightNumber(const std::string &flightnumber);
std::shared_ptr<Passenger> findPassengerByID(const std::string &passengerId);
std::shared_ptr<Reservation> findReservationByID(const std::string &reservationId);
std::shared_ptr<Passenger> findPassengerByUsername(const std::string &username);
double getPriceFromReservationCSV(const std::string &reservationId);
#endif