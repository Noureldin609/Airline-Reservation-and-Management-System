#include "../include/Aircraft.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
std::string Aircraft::getAircraftId() const { return aircraftId; }
std::string Aircraft::getType() const { return type; }
std::string Aircraft::getManufacturer() const { return manufacturer; }
int Aircraft::getCapacity() const { return capacity; }
std::string Aircraft::getStatus() const { return status; }
std::string Aircraft::getLastMaintenanceDate() { return lastMaintenanceDate; }
std::string Aircraft::getNextMaintenanceDate() { return nextMaintenanceDate; }

void Aircraft::setStatus(const std::string &newStatus) { status = newStatus; }
void Aircraft::setLastMaintenanceDate(const std::string &date) { lastMaintenanceDate = date; }
void Aircraft::setNextMaintenanceDate(const std::string &date) { nextMaintenanceDate = date; }

// Display
void Aircraft::displayAircraft() const
{
    std::cout << "Aircraft " << aircraftId << " (" << type << " - " << manufacturer << ")\n"
              << "Capacity: " << capacity << " seats\n"
              << "Status: " << status << "\n"
              << "Last Maintenance: " << lastMaintenanceDate << "\n"
              << "Next Maintenance: " << nextMaintenanceDate << "\n";
}

void AircraftManagement::addAircraft(std::string id, std::string type, std::string manufacturer,
                                     int capacity, std::string status, std::string lastMaintenanceDate,
                                     std::string nextMaintenanceDate)
{
    std::ofstream file("../database/Aircraft.csv", std::ios::app);
    if (file.is_open())
    {
        file << id << "," << type << "," << manufacturer << "," << capacity << "," << status << "," << lastMaintenanceDate << "," << nextMaintenanceDate << "\n";
        file.close();
        std::cout << "Aircraft added successfully.\n";
    }
    else
    {
        std::cerr << "Error: Could not open Aircraft.csv\n";
    }
}

void AircraftManagement::removeAircraft(std::string id)
{

    std::ifstream inFile("../database/Aircraft.csv");
    if (!inFile.is_open())
    {
        std::cerr << "Error: Could not open Aircraft.csv\n";
        return;
    }
    std::vector<std::string> lines;
    std::string line;
    bool found = false;

    while (getline(inFile, line))
    {
        std::stringstream ss(line);
        std::string toRemove;
        getline(ss, toRemove, ',');

        if (toRemove == id)
        {
            found = true;
            continue;
        }
        lines.push_back(line);
    }

    inFile.close();

    if (!found)
    {
        std::cout << "Aircraft not found.\n";
        return;
    }

    std::ofstream outFile("../database/Aircraft.csv", std::ios::trunc);
    for (auto &l : lines)
        outFile << l << "\n";
    outFile.close();

    std::cout << "Aircraft removed successfully.\n";
}
void AircraftManagement::updateAircraft(const std::string &id){
 std::ifstream inFile("../database/Aircraft.csv");
    if (!inFile.is_open())
    {
        std::cerr << "Error: Could not open Aircraft.csv\n";
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    bool found = false;

    while (getline(inFile, line))
    {
        std::stringstream ss(line);
        std::string toUpdate;
        getline(ss, toUpdate, ',');

        if (toUpdate == id)
        {
            found = true;
            std::string type,manufacturer,capacity,status,lastMaintenanceDate,nextMaintenanceDate;
            getline(ss, type, ',');
            getline(ss, manufacturer, ',');
            getline(ss, capacity, ',');
            getline(ss, status, ',');
            getline(ss, lastMaintenanceDate, ',');
            getline(ss, nextMaintenanceDate, ',');

            std::cout << "Enter new Type: ";
            std::cin.ignore();
            getline(std::cin, type);

            std::ostringstream updated;
            updated << id << "," << type << "," << manufacturer << "," << capacity << "," << status << "," << lastMaintenanceDate << "," << nextMaintenanceDate;
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
        std::cout << "Aircraft not found.\n";
        return;
    }

    std::ofstream outFile("../database/Aircraft.csv", std::ios::trunc);
    for (auto &l : lines)
        outFile << l << "\n";
    outFile.close();

    std::cout << "Aircraft details updated successfully.\n";
}

