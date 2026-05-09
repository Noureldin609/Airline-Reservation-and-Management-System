
#include "../include/Administrator.h"
#include <sstream>
#include <iomanip>
#include <map>
#include <algorithm>
#include <limits>
void Administrator::createUser(User &user)
{
    userManager.createUser(user);
}

void Administrator::removeUser(const std::string &username)
{
    userManager.removeUser(const_cast<std::string &>(username));
}

void Administrator::updateUser(const std::string &oldName, const std::string &newName)
{
    std::string oldCopy = oldName;
    std::string newCopy = newName;
    userManager.updateUser(newCopy, oldCopy);
}

/* ================= Flight ================== */
void Administrator::addFlight()
{
    flightManager.addFlight();
}
void Administrator::updateFlight()
{
    flightManager.updateFlight();
}
void Administrator::removeFlight()
{
    flightManager.removeFlight();
}
void Administrator::viewFlights()
{
    flightManager.viewAllFlights();
}

/* ================= Aircraft ================== */
void Administrator::addAircraft()
{
    std::string id, type, manufacturer, status, lastDate, nextDate;
    int capacity;
    std::cout << "Enter Aircraft ID: ";
    std::cin >> id;
    std::cout << "Enter Type: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, type);
    std::cout << "Enter Manufacturer: ";
    std::cin >> manufacturer;
    std::cout << "Enter Capacity: ";
    std::cin >> capacity;
    std::cout << "Enter Status: ";
    std::cin >> status;
    std::cout << "Enter Last Maintenance Date: ";
    std::cin >> lastDate;
    std::cout << "Enter Next Maintenance Date: ";
    std::cin >> nextDate;
    aircraftManager.addAircraft(id, type, manufacturer, capacity, status, lastDate, nextDate);
}

void Administrator::updateAircraft()
{
    std::string id;
    std::cout << "Enter Aircraft ID to update: ";
    std::cin >> id;
    aircraftManager.updateAircraft(id);
}

void Administrator::removeAircraft()
{
    std::string id;
    std::cout << "Enter Aircraft ID to remove: ";
    std::cin >> id;
    aircraftManager.removeAircraft(id);
}

/* ================= Display ================== */
void Administrator::displayUser()
{
    std::cout << "Admin Username: " << username << "\nEmail: " << email << "\nRole: Administrator\n";
}

bool Administrator::checkuserRoll(Role role)
{
    return role == User::ADMINISTRATOR;
}

void Administrator::generateOperationalReport()
{
    std::string monthYear;
    std::cout << "\n--- Operational Reports ---\n";
    std::cout << "Enter Month and Year for Report (MM-YYYY): ";
    std::cin >> monthYear;
    std::string inputMonth = monthYear.substr(0, 2);
std::string inputYear = monthYear.substr(3);
std::string target = inputYear + "-" + inputMonth;

    std::cout << "\nGenerating Operational Report for " << monthYear << "...\n\n";

    std::ifstream flightFile("../database/Flights.csv");
    std::ifstream resFile("../database/Reservations.csv");

    if (!flightFile.is_open() || !resFile.is_open())
    {
        std::cerr << "Error: Could not open required CSV files.\n";
        return;
    }


    int totalFlights = 0;
    int completedFlights = 0;
    int delayedFlights = 0;
    int canceledFlights = 0;
    int totalReservations = 0;
    double totalRevenue = 0.0;
    struct FlightStats
    {
        std::string flightNumber;
        int bookings = 0;
        double revenue = 0.0;
        std::string status;
    };
    std::vector<FlightStats> flightStats;

    // Read all flights
    std::string line;
    std::getline(flightFile, line); // skip header
    while (std::getline(flightFile, line))
    {
        std::stringstream ss(line);
        std::string flightNumber, origin, date, destination, departure, departureTime, arrivalTime, price, aircraftType, status, totalSeats;
        std::getline(ss, flightNumber, ',');
        std::getline(ss, origin, ',');
        std::getline(ss, date, ',');
        std::getline(ss, destination, ',');
        std::getline(ss, departure, ',');
        std::getline(ss, departureTime, ',');
        std::getline(ss, arrivalTime, ',');
        std::getline(ss, price, ',');
        std::getline(ss, aircraftType, ',');
        std::getline(ss, status, ',');
        std::getline(ss, totalSeats, ',');
        if (date.rfind(target, 0) == 0)
        {
            FlightStats fs;
            fs.flightNumber = flightNumber;
            fs.status = status;
            if (status == "Completed")
                completedFlights++;
            else if (status == "Delayed")
                delayedFlights++;
            else if (status == "Canceled")
                canceledFlights++;

            totalFlights++;
            flightStats.push_back(fs);
        }
    }
    std::getline(resFile, line); // skip header
    while (std::getline(resFile, line))
    {
        std::stringstream ss(line);
        std::string reservationId, passengerId, flightId, seat, totalCost, paymentMethod, paymentDetails;
        std::getline(ss, reservationId, ',');
        std::getline(ss, passengerId, ',');
        std::getline(ss, flightId, ',');
        std::getline(ss, seat, ',');
        std::getline(ss, totalCost, ',');
        std::getline(ss, paymentMethod, ',');
        std::getline(ss, paymentDetails, ',');

        totalReservations++;
        if (!totalCost.empty())
            totalRevenue += std::stod(totalCost);

        // Add reservation count & revenue per flight
        for (auto &fs : flightStats)
        {
            if (fs.flightNumber == flightId)
            {
                fs.bookings++;
                fs.revenue += std::stod(totalCost);
                break;
            }
        }
    }
    // Print summary
    std::cout << "Report Summary:\n";
    std::cout << "- Total Flights Scheduled: " << totalFlights << "\n";
    std::cout << "- Flights Completed: " << completedFlights << "\n";
    std::cout << "- Flights Delayed: " << delayedFlights << "\n";
    std::cout << "- Flights Canceled: " << canceledFlights << "\n";
    std::cout << "- Total Reservations Made: " << totalReservations << "\n";
    std::cout << "- Total Revenue: $" << std::fixed << std::setprecision(2) << totalRevenue << "\n";

    // Print details
    
    std::cout << "Detailed Flight Performance:\n";
    int count = 1;
    for (const auto &fs : flightStats)
    {
        std::cout << count++ << ". Flight " << fs.flightNumber << ": " << fs.status
                  << " (" << fs.bookings << " Bookings, $" << std::fixed << std::setprecision(2) << fs.revenue << ")\n";
    }
}

void Administrator::generateMaintenanceReport()
{
    std::ifstream file("../database/Maintenance.csv");
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open Maintenance.csv\n";
        return;
    }

    std::string line;
    std::getline(file, line); // skip header

    struct Record
    {
        std::string recordId, aircraftId, type, datePerformed, nextDue, technician, remarks, status;
    };

    std::vector<Record> records;
    std::map<std::string, int> technicianCount;
    int completed = 0, pending = 0;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        Record rec;
        std::getline(ss, rec.recordId, ',');
        std::getline(ss, rec.aircraftId, ',');
        std::getline(ss, rec.type, ',');
        std::getline(ss, rec.datePerformed, ',');
        std::getline(ss, rec.nextDue, ',');
        std::getline(ss, rec.technician, ',');
        std::getline(ss, rec.remarks, ',');
        std::getline(ss, rec.status, ',');

        if (rec.status == "Completed")
            completed++;
        else
            pending++;

        technicianCount[rec.technician]++;
        records.push_back(rec);
    }

    file.close();

    // --- Summary ---
    std::cout << "\n--- Maintenance Report ---\n";
    std::cout << "Total Maintenance Records: " << records.size() << "\n";
    std::cout << "Completed Maintenance Tasks: " << completed << "\n";
    std::cout << "Pending Maintenance Tasks: " << pending << "\n\n";

    std::cout << "Technician Summary:\n";
    for (const auto &[tech, count] : technicianCount)
        std::cout << "- " << tech << ": " << count << " maintenance task(s)\n";

    std::cout << "\nUpcoming Maintenance:\n";
    for (const auto &rec : records)
        std::cout << " Aircraft " << rec.aircraftId << "|   Next Due: " << rec.nextDue << "\n";

    std::cout << "\nRecent Maintenance Activities:\n";
    for (const auto &rec : records)
        std::cout << "- " << rec.recordId << " | " << rec.aircraftId << " | "
                  << rec.type << " | " << rec.datePerformed
                  << " | Status: " << rec.status << "\n";
}
void Administrator::generateUserActivityReports()
{
    std::cout << "-----User Activity Report ----\n";
    int totalUsers = 0, Administrators = 0, Agents = 0, Passengers = 0;
    std::ifstream UserFile("../database/Users.csv");
    if (!UserFile.is_open())
    {
        std::cerr << "Error: Could not open Users.csv\n";
        return;
    }

    std::string line;
    std::getline(UserFile, line); // skip header

    while (std::getline(UserFile, line))
    {
        std::stringstream ss(line);
        std::string uname, pwd, email, age, address, role;
        std::getline(ss, uname, ',');
        std::getline(ss, pwd, ',');
        std::getline(ss, email, ',');
        std::getline(ss, age, ',');
        std::getline(ss, address, ',');
        std::getline(ss, role, ',');

        if (role == "0")
            Administrators++;
        else if (role == "1")
            Agents++;
        else
            Passengers++;
        totalUsers++;
    }

    UserFile.close();
    std::ifstream ResFile("../database/Reservations.csv");
    if (!ResFile.is_open())
    {
        std::cerr << "Error: Could not open Reservations.csv\n";
        return;
    }

    std::getline(ResFile, line); // skip header
    std::map<std::string, int> passengerCount;
    std::map<std::string, int> flightBooking;
    std::map<std::string, int> PaymentUsage;

    while (std::getline(ResFile, line))
    {
        std::stringstream ss(line);
        std::string id, passengerId, flightId, Seatno, Totalcost, paymentMethod;
        std::getline(ss, id, ',');
        std::getline(ss, passengerId, ',');
        std::getline(ss, flightId, ',');
        std::getline(ss, Seatno, ',');
        std::getline(ss, Totalcost, ',');
        std::getline(ss, paymentMethod, ',');
        passengerCount[passengerId]++;
        flightBooking[flightId]++;
        PaymentUsage[paymentMethod]++;
    }
    auto maxpassenger = std::max_element(passengerCount.begin(), passengerCount.end(), [](const auto &a, const auto &b)
                                         { return a.second < b.second; });
    auto maxflight = std::max_element(flightBooking.begin(), flightBooking.end(), [](const auto &a, const auto &b)
                                      { return a.second < b.second; });
    auto maxPayment = std::max_element(PaymentUsage.begin(), PaymentUsage.end(), [](const auto &a, const auto &b)
                                       { return a.second < b.second; });

    std::cout << "Total Registered Users: " << totalUsers << "\n";
    std::cout << "- Administrators: " << Administrators << "\n";
    std::cout << "- Booking Agents: " << Agents << "\n";
    std::cout << "- Passengers: " << Passengers << "\n";
    std::cout << "Booking Summary: \n";
    std::cout << "- Total Reservations: " << passengerCount.size() << "\n";
    if (maxpassenger != passengerCount.end())
        std::cout << "- Most Active Passenger: " << maxpassenger->first << " (" << maxpassenger->second << " bookings)\n";
    if (maxflight != flightBooking.end())
        std::cout << "- Most Booked Flight: " << maxflight->first << " (" << maxflight->second << " bookings)\n";
    if (maxPayment != PaymentUsage.end())
        std::cout << "- Most Used Payment Method: " << maxPayment->first << " (" << maxPayment->second << " times)\n";
}
void Administrator::addreport()
{
    maintenanceManager.addRecord();
}

void Administrator::updatereport(const std::string &recordId)
{
    maintenanceManager.updateRecord(recordId);
}

void Administrator::removereport(const std::string &recordId)
{
    maintenanceManager.removeRecord(recordId);
}

void Administrator::viewreport()
{
    maintenanceManager.viewAllRecords();
}