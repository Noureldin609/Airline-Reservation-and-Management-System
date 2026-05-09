#ifndef BOOKINGAGENT_H
#define BOOKINGAGENT_H

#include "User.h"
#include <vector>
#include <string>
#include <iostream>
#include "Flight.h"
#include "Passenger.h"
#include "Reservation.h"
#include <algorithm>

class BookingAgent : public User
{
private:
  std::string officeLocation; // Airport/office
  std::string shiftHours;     // e.g., "09:00 - 17:00"
  Reservation_System system;

public:
  BookingAgent(std::string username, std::string password, std::string email,
               int age, std::string address, std::string office, std::string shift)
      : User(username, password, email, age, address, User::BOOKING_AGENT),
        officeLocation(office), shiftHours(shift) {}
  std::vector<Flight> SearchFlight();
  /*================Reservation System================*/
  void BookFlight(const std::shared_ptr<Reservation> &reservation);
  void CancelFlight(const std::string &reservationId);
  void UpdateFlight(const std::string &reservationId);
  void showReservations() const;

  /*================Display User================*/
  void displayUser() override;
  bool checkuserRoll(Role role) override;
};
void printResults(const std::string& title, const std::vector<Flight>& results);
#endif
/*
#ifndef BOOKINGAGENT_H
#define BOOKINGAGENT_H

#include "User.h"
#include "Reservation.h"
#include "Payment.h"
#include <vector>
#include <string>
#include <iostream>

class BookingAgent : public User {
private:
   std::string officeLocation;                  // Airport/office
   std::string shiftHours;                      // e.g., "09:00 - 17:00"
   std::vector<Reservation> reservations;       // Reservations created by this agent
   std::vector<Payment> payments;               // Payments processed by this agent

public:
   BookingAgent(std::string username, std::string password, std::string email,
                int age, std::string address, std::string office, std::string shift)
       : User(username, password, email, age, address, User::BOOKING_AGENT),
         officeLocation(office), shiftHours(shift) {}

   // Core responsibilities
   void createReservation(const std::string& reservationId, const std::string& passengerId,
                          const std::string& flightNumber, const std::string& seat);
   void processPayment(const std::string& paymentId, const std::string& reservationId,
                       double amount);

   // Display
   void showSummary();
   void displayUser() override;
};

#endif

*/