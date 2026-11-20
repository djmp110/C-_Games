
#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
using namespace std;

class User {
private:
    string username;
    string password;
    string role;

public:
    // Default constructor
    User();

    // Parameterized constructor
    User(string username, string password, string role);

    // Getter functions
    string getUsername() const;
    string getPassword() const;
    string getRole() const;

    // Login function
    bool login(string username, string password) const;

    // Display user information
    void displayUser() const;
};

#endif
