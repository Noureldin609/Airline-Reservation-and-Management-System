#ifndef PAYMENT_h
#define PAYMENT_h
#include <string>

class Payment
{
private:
    std::string transactionID;
    std::string reservationID;
    std::string paymentMethod;
    double amount;

    std::string method;
    std::string status;

public:
    Payment(std::string tId, std::string rId, double amt, std::string meth)
        : transactionID(tId), reservationID(rId), amount(amt), method(meth), status("Pending") {}
    ~Payment();
    bool processPayment();
    void refund();
    void saveToFile();
    /*setters and getters*/
    std::string getTransactionID() const; 
    std::string getReservationID() const; 
    std::string getPaymentMethod() const; 
    double getAmount() const;
    std::string getstatus() const;
};


#endif