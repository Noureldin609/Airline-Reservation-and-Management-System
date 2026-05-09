#include "../include/Maintenance.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

// =========================
// Display Maintenance Record
// =========================
void MaintenanceRecord::displayRecord() const
{
    std::cout << "\n--- Maintenance Record ---\n";
    std::cout << "Record ID: " << recordId << "\n";
    std::cout << "Aircraft ID: " << aircraftId << "\n";
    std::cout << "Type: " << maintenanceType << "\n";
    std::cout << "Date Performed: " << datePerformed << "\n";
    std::cout << "Next Due Date: " << nextDueDate << "\n";
    std::cout << "Technician: " << technicianName << "\n";
    std::cout << "Remarks: " << remarks << "\n";
    std::cout << "Status: " << status << "\n";
}


// Constructor

MaintenanceManagement::MaintenanceManagement()
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::ofstream newFile(filePath);
        newFile << "RecordID,AircraftID,Type,DatePerformed,NextDue,Technician,Remarks,Status\n";
        newFile.close();
    }
    else
    {
        file.close();
    }
}

// =========================
// Add New Maintenance Record
// =========================
void MaintenanceManagement::addRecord()
{
    std::string recordId, aircraftId, maintenanceType, datePerformed,
        nextDueDate, technicianName, remarks, status;

    std::cin.ignore();
    std::cout << "Enter Record ID: ";
    std::getline(std::cin, recordId);
    std::cout << "Enter Aircraft ID: ";
    std::getline(std::cin, aircraftId);
    std::cout << "Enter Maintenance Type: ";
    std::getline(std::cin, maintenanceType);
    std::cout << "Enter Date Performed (YYYY-MM-DD): ";
    std::getline(std::cin, datePerformed);
    std::cout << "Enter Next Due Date (YYYY-MM-DD): ";
    std::getline(std::cin, nextDueDate);
    std::cout << "Enter Technician Name: ";
    std::getline(std::cin, technicianName);
    std::cout << "Enter Remarks: ";
    std::getline(std::cin, remarks);
    std::cout << "Enter Status (Scheduled / In Progress / Completed): ";
    std::getline(std::cin, status);

    std::ofstream outFile(filePath, std::ios::app);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Could not open maintenance.csv\n";
        return;
    }

    outFile << recordId << "," << aircraftId << "," << maintenanceType << ","
            << datePerformed << "," << nextDueDate << ","
            << technicianName << "," << remarks << "," << status << "\n";

    outFile.close();
    std::cout << "Maintenance record added successfully.\n";
}

// =========================
// Update Maintenance Record
// =========================
void MaintenanceManagement::updateRecord(const std::string &recordId)
{
    std::ifstream inFile(filePath);
    if (!inFile.is_open())
    {
        std::cerr << "Error: Could not open maintenance.csv\n";
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    bool found = false;

    while (std::getline(inFile, line))
    {
        std::stringstream ss(line);
        std::string id;
        std::getline(ss, id, ',');

        if (id == recordId)
        {
            found = true;
            std::string newStatus, nextDue;
            std::cout << "Enter new Status (Scheduled / In Progress / Completed): ";
            std::getline(std::cin >> std::ws, newStatus);
            std::cout << "Enter new Next Due Date (YYYY-MM-DD): ";
            std::getline(std::cin, nextDue);

            std::string restOfLine;
            std::getline(ss, restOfLine);
            std::stringstream record(line);
            std::vector<std::string> fields;
            std::string field;
            while (std::getline(record, field, ','))
                fields.push_back(field);

            // Update fields (NextDueDate and Status)
            if (fields.size() >= 8)
            {
                fields[4] = nextDue;
                fields[7] = newStatus;
            }

            std::ostringstream updatedLine;
            for (size_t i = 0; i < fields.size(); ++i)
            {
                updatedLine << fields[i];
                if (i < fields.size() - 1)
                    updatedLine << ",";
            }
            lines.push_back(updatedLine.str());
        }
        else
        {
            lines.push_back(line);
        }
    }
    inFile.close();

    std::ofstream outFile(filePath, std::ios::trunc);
    for (auto &l : lines)
        outFile << l << "\n";
    outFile.close();

    if (found)
        std::cout << "Record " << recordId << " updated successfully.\n";
    else
        std::cout << " Record not found.\n";
}

// =========================
// Remove Maintenance Record
// =========================
void MaintenanceManagement::removeRecord(const std::string &recordId)
{
    std::ifstream inFile(filePath);
    if (!inFile.is_open())
    {
        std::cerr << "Error: Could not open maintenance.csv\n";
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    bool found = false;

    while (std::getline(inFile, line))
    {
        std::stringstream ss(line);
        std::string id;
        std::getline(ss, id, ',');

        if (id != recordId)
        {
            lines.push_back(line);
        }
        else
        {
            found = true;
        }
    }
    inFile.close();

    std::ofstream outFile(filePath, std::ios::trunc);
    for (auto &l : lines)
        outFile << l << "\n";
    outFile.close();

    if (found)
        std::cout << "Record deleted successfully.\n";
    else
        std::cout << "Record not found.\n";
}

// =========================
// View All Maintenance Records
// =========================
void MaintenanceManagement::viewAllRecords() const
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open maintenance.csv\n";
        return;
    }

    std::string line;
    std::getline(file, line); // skip header
    std::cout << "\n--- Maintenance Records ---\n";

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string recordId, aircraftId, type, datePerformed, nextDue, technician, remarks, status;
        getline(ss, recordId, ',');
        getline(ss, aircraftId, ',');
        getline(ss, type, ',');
        getline(ss, datePerformed, ',');
        getline(ss, nextDue, ',');
        getline(ss, technician, ',');
        getline(ss, remarks, ',');
        getline(ss, status, ',');

        MaintenanceRecord record(recordId, aircraftId, type, datePerformed, nextDue, technician, remarks, status);
        record.displayRecord();
    }
    file.close();
}

// =========================
// Update Aircraft Status
// =========================
void MaintenanceManagement::updateAircraftStatus(Aircraft &aircraft, const std::string &newStatus)
{
    aircraft.setStatus(newStatus);
    std::cout << "Aircraft " << aircraft.getAircraftId() << " status updated to " << newStatus << "\n";
}
