


#include "../include/BookingAgent.h"
#include <vector>
#include <sstream>
void BookingAgent::BookFlight(const std::shared_ptr<Reservation> &reservation)
{
    system.CreateReservation(reservation);
}
void BookingAgent::CancelFlight(const std::string &reservationId){
    system.CancelReservation(reservationId);
}
void BookingAgent::UpdateFlight(const std::string &reservationId){
    system.updateReservation(reservationId);
}
void BookingAgent::showReservations() const{
    system.showReservations();
}
// Override display
void BookingAgent::displayUser()
{
    std::cout << "Username: " << username
              << "\nEmail: " << email
              << "\nRole: Booking Agent"
              << "\nOffice: " << officeLocation
              << "\nShift: " << shiftHours << "\n";
}

bool BookingAgent::checkuserRoll(Role role)
{
    return role == User::BOOKING_AGENT;
}

/*Search Flight*/
std::vector<Flight> BookingAgent::SearchFlight()
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
                     bool destMatch =  (flight.getDestination() == destination);
                     bool originMatch =  (flight.getOrigin() == origin);

                     return dateMatch && destMatch && originMatch;
                 });

    return result;
}
void printResults(const std::string& title, const std::vector<Flight>& results) {
    std::cout << "\n--- " << title << " ---" << std::endl;
    if (results.empty()) {
        std::cout << "  No flights found matching the criteria." << std::endl;
    } else {
        std::cout << "  Found " << results.size() << " flight(s):" << std::endl;
        for (const auto& f : results) {
            std::cout<<"-------------------------------\n";
            f.displayFlight();
        }
        std::cout<<"-------------------------------\n";
    }
}


