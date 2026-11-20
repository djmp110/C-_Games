
#include "User.h"

// Default constructor
User::User() {
    username = "";
    password = "";
    role = "Librarian";
}

// Parameterized constructor
User::User(string username, string password, string role) {
    this->username = username;
    this->password = password;
    this->role = role;
}

// Get username
string User::getUsername() const {
    return username;
}

// Get password
string User::getPassword() const {
    return password;
}

// Get role
string User::getRole() const {
    return role;
}

// Login function
bool User::login(string username, string password) const {
    return this->username == username &&
           this->password == password;
}

// Display user information
void User::displayUser() const {
    cout << "Username: " << username << endl;
    cout << "Role: " << role << endl;
}
