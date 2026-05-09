#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "User.h"
#include "Flight.h"
#include "Aircraft.h"
#include "Maintenance.h"
#include <vector>
#include <string>
#include <iostream>

class Administrator : public User
{
private:
    UserManager userManager;              //manage users
    FlightManagment flightManager;        //manage flights
    AircraftManagement aircraftManager;   //manage aircraft
    MaintenanceManagement maintenanceManager; // manage maintenance

public:
    Administrator(std::string username, std::string password, std::string email,
                  int age, std::string address)
        : User(username, password, email, age, address, User::ADMINISTRATOR)
    {
    }

    /* ==== User Management ==== */
    void createUser(User &user);
    void removeUser(const std::string &username);
    void updateUser(const std::string &oldName, const std::string &newName);

    /* ==== Flight Management ==== */
    void addFlight();
    void updateFlight();
    void removeFlight();
    void viewFlights();

    /* ==== Aircraft Management ==== */
    void addAircraft();
    void updateAircraft();
    void removeAircraft(); 

     /*Maintenance Management*/
     void addreport();
     void updatereport(const std::string &recordId);
     void removereport(const std::string &recordId);
     void viewreport();

    /* ==== Display ==== */
    void displayUser() override;
    bool checkuserRoll(Role role) override;

    /* ==== Reports ==== */
    void generateOperationalReport();
    void generateMaintenanceReport();
    void generateUserActivityReports();

};

#endif
