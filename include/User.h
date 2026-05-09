#ifndef USER_H
#define USER_H
#include <string>
#include <fstream>
#include <iostream>
class User
{
public:
    enum Role
    {
        ADMINISTRATOR,
        BOOKING_AGENT,
        PASSENGER
    };
    User(std::string username, std::string password, std::string email, int age, std::string address, Role role);
    std::string getUsername();
    std::string getPassword();
    std::string getEmail();
    int getAge();
    std::string getAddress();
    Role getRole();
    virtual void displayUser() = 0;
    virtual bool checkuserRoll(Role role) = 0;

protected:
    std::string username;
    std::string password;
    std::string email;
    int age;
    std::string address;
    Role role;
    friend class Authentication;
    friend class UserManager;
};
class Authentication
{
    std::fstream file;

public:
    Authentication();
    ~Authentication();
    void registeration(User &user);
    bool login(std::string username, std::string password);
    User *RoleBaseAccessControl(const std::string& username, const std::string& password,
                                            const std::string& email, int age, const std::string& address,
                                            User::Role role);
};
class DummyUser : public User {
public:
    DummyUser(std::string username, std::string password, std::string email,
              int age, std::string address, Role role)
        : User(username, password, email, age, address, role) {}

    void displayUser() override {
        std::cout << "Username: " << username << "\nEmail: " << email
                  << "\nRole: " << role << "\n";
    }

    bool checkuserRoll(Role r) override {
        return role == r;
    }
};

class UserManager
{
private:
    std::fstream file;

public:
    UserManager();
    ~UserManager();
    void createUser(User &user);
    void removeUser(std::string &username);
    void updateUser(std::string &updated_user, std::string &olduser);
};
#endif