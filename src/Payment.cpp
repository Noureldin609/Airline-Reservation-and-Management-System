#include "../include/Payment.h"
#include <iostream>
#include<fstream>
#include <sstream>
#include <vector>
Payment::~Payment() {}

bool Payment::processPayment()
{
    std::cout << "Proccessing payment for reservation " << reservationID << "\n";
    if (method == "Credit Card" || method == "PayPal" || method == "Cash" || method == "paypal" || method == "credit card" || method == "cash")
    {
        status = "success";
        std::cout << " Payment successful using " << method << ".\n";
        saveToFile();
        return true;
    }
    else
    {
        status = "Failed";
        std::cout << " Payment failed. Please try again.\n";
        saveToFile();
        return false;
    }
}

void Payment::refund()
{
    std::ifstream infile("../database/Payments.csv");
    if (!infile.is_open())
    {
        std::cerr << "Error: Could not open Payments.csv\n";
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    bool found = false;

    std::getline(infile, line); //skip first
    // Copy all lines and update the one matching this reservation
    while (std::getline(infile, line))
    {
        std::stringstream ss(line);
        std::string pid, rid, amountStr, paymentMethod,stat;
        std::getline(ss, pid, ',');
        std::getline(ss, rid, ',');
        std::getline(ss, amountStr, ',');
        std::getline(ss, paymentMethod, ',');
        std::getline(ss, stat, ',');

        if (rid == reservationID && stat == "success")
        {
            std::cout<<"Processing refund to "<<paymentMethod<< " account: "<<std::endl;
            stat = "Refunded";
            found = true;
            line = pid + "," + rid + "," + amountStr + ","+ paymentMethod + "," + stat;
            std::cout<<"Refund Amount: "<<amountStr<<" has been credited to your "<<paymentMethod<< " account."<<std::endl;
        }

        lines.push_back(line);
    }
    infile.close();

    if (!found)
    {
        std::cout << " No successful payment found for reservation " << reservationID << ".\n";
        return;
    }

    // Rewrite file
    std::ofstream outfile("../database/Payments.csv", std::ios::trunc);
    outfile << "transactionID,reservationID,amount,paymentMethod,status\n";
    for (const auto &l : lines)
        outfile << l << "\n";

    outfile.close();

    std::cout << " Refund recorded successfully.\n";
}

void Payment::saveToFile()
{
    std::ofstream file;
    file.open("../database/Payments.csv", std::ios::app);
    file << transactionID << "," << reservationID << "," << amount << "," << method << "," << status << "\n";
    file.close();
}
    std::string Payment::getTransactionID() const { return transactionID; }
    std::string Payment::getReservationID() const { return reservationID; }
    std::string Payment::getPaymentMethod() const { return paymentMethod; }
    double Payment::getAmount() const { return amount; }
    std::string Payment::getstatus() const { return status; }