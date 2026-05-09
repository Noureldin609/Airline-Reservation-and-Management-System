#ifndef MAINTENANCE_H
#define MAINTENANCE_H

#include <string>
#include <vector>
#include <memory>
#include "Aircraft.h"

class MaintenanceRecord
{
private:
    std::string recordId;        // Unique ID for maintenance record
    std::string aircraftId;      // Associated aircraft
    std::string maintenanceType; // e.g., "Engine Check", "Routine Inspection"
    std::string datePerformed;   // When it was done
    std::string nextDueDate;     // When the next one is due
    std::string technicianName;  // Who performed it
    std::string remarks;         // Notes or issues found
    std::string status;          // Completed / Pending / Scheduled

public:
    MaintenanceRecord(std::string recordId, std::string aircraftId, std::string maintenanceType,
                      std::string datePerformed, std::string nextDueDate,
                      std::string technicianName, std::string remarks, std::string status)
        : recordId(recordId), aircraftId(aircraftId), maintenanceType(maintenanceType),
          datePerformed(datePerformed), nextDueDate(nextDueDate),
          technicianName(technicianName), remarks(remarks), status(status) {}

    // Getters
    std::string getRecordId() const { return recordId; }
    std::string getAircraftId() const { return aircraftId; }
    std::string getMaintenanceType() const { return maintenanceType; }
    std::string getDatePerformed() const { return datePerformed; }
    std::string getNextDueDate() const { return nextDueDate; }
    std::string getTechnicianName() const { return technicianName; }
    std::string getRemarks() const { return remarks; }
    std::string getStatus() const { return status; }

    // Setters
    void setNextDueDate(const std::string &date) { nextDueDate = date; }
    void setStatus(const std::string &newStatus) { status = newStatus; }

    void displayRecord() const;
};

class MaintenanceManagement
{
private:
    std::vector<std::shared_ptr<MaintenanceRecord>> records; 
    std::string filePath = "../database/Maintenance.csv";

public:
    MaintenanceManagement();

    void addRecord();
    void updateRecord(const std::string &recordId);
    void removeRecord(const std::string &recordId);
    void viewAllRecords() const;

    void updateAircraftStatus(Aircraft &aircraft, const std::string &newStatus);
};

#endif
