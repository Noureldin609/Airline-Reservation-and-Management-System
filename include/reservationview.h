#pragma once
#include <string>
#include <memory>

struct ReservationView {
    std::string reservationId;
    std::string passengerId;
    std::string passengerName;   // optional: if you can find it
    std::string flightNumber;
    std::string seat;
    std::string totalCost;
    std::string paymentMethod;
    std::string paymentDetails;

    // optional pointers if you want to access full objects
    std::shared_ptr<class Passenger> passengerPtr; // may be nullptr
    std::shared_ptr<class Flight> flightPtr;       // may be nullptr
};