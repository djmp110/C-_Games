
#ifndef PATRON_H
#define PATRON_H

#include <iostream>
#include <string>
using namespace std;

class Patron {
    public:
    string username;
    string cardNumber;
    int owedFees;


    // Default constructor
    Patron();

    // Parameterized constructor
    Patron(string username, string cardNumber, int owedFees);

    // Getter functions
    string getUsername() const;
    string getCardNumber() const;
    int getOwedFees() const;

    // Check whether the patron owes fees
    bool owesFees() const;

    // Setter function for fees
    void setFees(int fees);
};

#endif
