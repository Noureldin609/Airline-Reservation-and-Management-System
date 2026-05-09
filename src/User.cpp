#include "../include/User.h"
#include "../include/Administrator.h"
#include "../include/BookingAgent.h"
#include "../include/Passenger.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
User::User(std::string username, std::string password, std::string email, int age, std::string address, Role role)
{
    this->username = username;
    this->password = password;
    this->email = email;
    this->age = age;
    this->address = address;
    this->role = role;
}
std::string User::getUsername()
{
    return this->username;
}
std::string User::getPassword()
{
    return this->password;
}
std::string User::getEmail()
{
    return this->email;
}
int User::getAge()
{
    return this->age;
}
std::string User::getAddress()
{
    return this->address;
}
User::Role User::getRole()
{
    return this->role;
}
Authentication::Authentication()
{
    file.open("../database/Users.csv", std::ios::in | std::ios::out | std::ios::app);
}
Authentication::~Authentication()
{
    file.close();
}
void Authentication::registeration(User &user)
{
    std::cout << "Enter the username:\n ";
    std::cin >> user.username;
    std::cout << "Enter the password:\n ";
    std::cin >> user.password;
    std::cout << "Enter the email:\n ";
    std::cin >> user.email;
    std::cout << "Enter the age:\n ";
    std::cin >> user.age;
    std::cout << "Enter the address:\n ";
    std::cin >> user.address;
    std::cout << "Enter the role (0 for Admin, 1 for Booking Agent, 2 for Passenger):\n ";
    int roleInput;
    std::cin >> roleInput;
    std::hash<std::string> hasher;
    user.password = std::to_string(hasher(user.password));
    user.role = static_cast<User::Role>(roleInput);
    file << user.username << "," << user.password << "," << user.email << "," << user.age << "," << user.address << "," << roleInput << std::endl;
}
bool Authentication::login(std::string username, std::string password)
{
    file.clear();  // clear EOF flags
    file.seekg(0); // rewind to start of file
    std::string line;
    getline(file, line);
    while (getline(file, line))
    {
        std::string username1, password1, email1, age1, address1, role1;
        std::stringstream ss(line);
        getline(ss, username1, ',');
        getline(ss, password1, ',');
        getline(ss, email1, ',');
        getline(ss, age1, ',');
        getline(ss, address1, ',');
        getline(ss, role1, ',');
        std::hash<std::string> hasher;
        std::string hashedInput = std::to_string(hasher(password));

        if (username1 == username && password1 == hashedInput)
        {
            return true;
        }
    }
    return false;
}
/* han7dd han3ml object mn eh*/
//---------------------------LESSSAAAA HATKMLLL----------------------------
User *Authentication::RoleBaseAccessControl(const std::string &username, const std::string &password,
                                            const std::string &email, int age, const std::string &address,
                                            User::Role role)
{

    switch (role)
    {
    case User::ADMINISTRATOR:
        return new Administrator(username, password, email, age, address);
    case User::BOOKING_AGENT:
        return new BookingAgent(username, password, email, age, address, "MainOffice", "09:00-17:00");
    case User::PASSENGER:
        return new Passenger(username, password, email, age, address, "1");
    default:
        return nullptr;
    }
}

UserManager::UserManager()
{
    file.open("../database/Users.csv", std::ios::in | std::ios::out | std::ios::app);
}
UserManager::~UserManager()
{
    file.close();
}
void UserManager::createUser(User &user)
{
    std::ofstream outFile("../database/Users.csv", std::ios::app);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Cannot write Users.csv\n";
        return;
    }
    std::hash<std::string> hasher;
    user.password = std::to_string(hasher(user.password));
    outFile << user.username << "," << user.password << "," << user.email << "," << user.age << "," << user.address << "," << user.role << std::endl;
}
/*
void UserManager::removeUser(User &user)
{
    // Step 1: Read all lines from the file
    std::ifstream inFile("../database/Users.csv");
    if (!inFile.is_open())
    {
        std::cerr << "Error: Cannot open Users.csv\n";
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    bool found = false;
    while (getline(inFile, line))
    {
        std::stringstream ss(line);
        std::string username1;
        getline(ss, username1, ',');

        // Keep all lines except the one we want to remove
        if (username1 == user.username)
        {
            found = true;
            continue;
        }
        lines.push_back(line);
    }
    inFile.close();

    // Step 2: Rewrite file with remaining lines
    std::ofstream outFile("../database/Users.csv", std::ios::trunc);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Cannot write Users.csv\n";
        return;
    }

    for (const auto &l : lines)
    {
        outFile << l << "\n";
    }
    outFile.close();

    if (found)
    {
        std::cout << "User removed successfully.\n";
    }
    else
    {
        std::cout << "User not found.\n";
    }
}
    */

void UserManager::removeUser(std::string &username)
{
    // Step 1: Read all lines from the file
    std::ifstream inFile("../database/Users.csv");
    if (!inFile.is_open())
    {
        std::cerr << "Error: Cannot open Users.csv\n";
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    bool found = false;
    while (getline(inFile, line))
    {
        std::stringstream ss(line);
        std::string username1;
        getline(ss, username1, ',');

        // Keep all lines except the one we want to remove
        if (username1 == username)
        {
            found = true;
            continue;
        }
        lines.push_back(line);
    }
    inFile.close();

    // Step 2: Rewrite file with remaining lines
    std::ofstream outFile("../database/Users.csv", std::ios::trunc);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Cannot write Users.csv\n";
        return;
    }

    for (const auto &l : lines)
    {
        outFile << l << "\n";
    }
    outFile.close();

    if (found)
    {
        std::cout << "User removed successfully.\n";
    }
    else
    {
        std::cout << "User not found.\n";
    }
}

void UserManager::updateUser(std::string &updated_user, std::string &olduser)
{
    file.clear();  // clear EOF flags
    file.seekg(0); // rewind to start of file
    std::string line;
    getline(file, line);
    while (getline(file, line))
    {
        std::string username1, password1, email1, age1, address1, role1;
        std::stringstream ss(line);
        getline(ss, username1, ',');
        getline(ss, password1, ',');
        getline(ss, email1, ',');
        getline(ss, age1, ',');
        getline(ss, address1, ',');
        getline(ss, role1, ',');
        if (username1 == olduser)
        {
            UserManager::removeUser(username1);
            username1 = updated_user;
            file << username1 << "," << password1 << "," << email1 << "," << age1 << "," << address1 << "," << role1 << std::endl;
            std::cout << "User updated successfully." << std::endl;
            return;
        }
    }
    std::cout << "user not found" << std::endl;
}

// class DummyUser : public User
// {
// public:
//     DummyUser(std::string username, std::string password, std::string email,
//               int age, std::string address, Role role)
//         : User(username, password, email, age, address, role) {}

//     void displayUser() override
//     {
//         std::cout << "Username: " << username
//                   << " | Email: " << email
//                   << " | Age: " << age
//                   << " | Address: " << address
//                   << " | Role: " << role << std::endl;
//     }

//     bool checkuserRoll(Role r) override
//     {
//         return role == r;
//     }
// };
/*
int main()
{
    UserManager manager;
    int choice;

    do
    {
        std::cout << "\n=== User Manager Menu ===\n";
        std::cout << "1. Create User\n";
        std::cout << "2. Remove User\n";
        std::cout << "3. Update User\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (choice == 1)
        {
            std::string uname, pwd, email, addr;
            int age, role;
            std::cout << "Enter username: ";
            std::cin >> uname;
            std::cout << "Enter password: ";
            std::cin >> pwd;
            std::cout << "Enter email: ";
            std::cin >> email;
            std::cout << "Enter age: ";
            std::cin >> age;
            std::cout << "Enter address: ";
            std::cin >> addr;
            std::cout << "Enter role (0=Admin,1=BookingAgent,2=Passenger): ";
            std::cin >> role;

            DummyUser newUser(uname, pwd, email, age, addr, static_cast<User::Role>(role));
            manager.createUser(newUser);
            std::cout << " User created successfully.\n";
        }
        else if (choice == 2)
        {
            std::string uname;
            std::cout << "Enter username to remove: ";
            std::cin >> uname;
            manager.removeUser(uname);
        }
        else if (choice == 3)
        {
            std::string oldName, newName;
            std::cout << "Enter username to update: ";
            std::cin >> oldName;
            std::cout << "Enter new username: ";
            std::cin >> newName;

            // DummyUser temp(oldName, "", "", 0, "", User::PASSENGER); // minimal user
            manager.updateUser(newName, oldName);
            // std::cout << " User updated (if existed).\n";
        }

    } while (choice != 4);

    std::cout << "Exiting User Manager.\n";
    return 0;
}
    */
//    int main(){
//     UserManager manager;
//     DummyUser user("user1", "password1", "email1", 20, "address1", User::ADMINISTRATOR);
//     manager.createUser(user);
//    }