#ifndef AIRCRAFT_H
#define AIRCRAFT_H
#include <string>

class Aircraft
{
    std::string aircraftId;          // Unique ID for the aircraft
    std::string type;                // Model (Boeing 777, Airbus A320)
    std::string manufacturer;        // Boeing, Airbus, etc.
    int capacity;                    // Number of seats
    std::string status;              // Available, In Maintenance, Assigned
    std::string lastMaintenanceDate; // Last maintenance date
    std::string nextMaintenanceDate; // Next scheduled maintenance
public:
    Aircraft(std::string id, std::string type, std::string manufacturer,
             int capacity, std::string status, std::string lastMaintenanceDate,
             std::string nextMaintenanceDate)
        : aircraftId(id), type(type), manufacturer(manufacturer),
          capacity(capacity), status(status), lastMaintenanceDate(lastMaintenanceDate), nextMaintenanceDate(nextMaintenanceDate) {}

    std::string getAircraftId() const;
    std::string getType() const;
    std::string getManufacturer() const;
    int getCapacity() const;
    std::string getStatus() const;
    std::string getLastMaintenanceDate();
    std::string getNextMaintenanceDate();

    // Setter
    void setStatus(const std::string &newStatus);
    void setLastMaintenanceDate(const std::string &date);
    void setNextMaintenanceDate(const std::string &date);
    // Display
    void displayAircraft() const;
};
class AircraftManagement{
public:
void addAircraft(std::string id, std::string type, std::string manufacturer,
             int capacity, std::string status, std::string lastMaintenanceDate,
             std::string nextMaintenanceDate);
void removeAircraft(std::string id);
void updateAircraft(const std::string &id);

};
#endif