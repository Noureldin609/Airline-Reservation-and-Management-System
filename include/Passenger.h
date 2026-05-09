#ifndef PASSENGER_H
#define PASSENGER_H

#include "User.h"
#include "Flight.h"
#include <vector>
#include "Reservation.h"
#include "reservationview.h"
#include "Payment.h"
class Passenger : public User
{
protected:
    std::string passengerId;
    Reservation_System system;

public:
    Passenger(std::string username, std::string password, std::string email,
              int age, std::string address, std::string passengerId) : User(username, password, email, age, address, User::PASSENGER), passengerId(passengerId) {}
    std::vector<Flight> SearchFlight();
    std::vector<Flight> FilterFlight();
    std::vector<ReservationView> viewMyReservations();
    void wishToBook(const std::shared_ptr<Reservation> &reservation);
    std::string getPassengerId() const;
    void setPassengerId(const std::string &passengerId);
    void displayUser() override;
    bool checkuserRoll(Role role) override;
};


#endif