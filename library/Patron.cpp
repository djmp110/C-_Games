
#include "Patron.h"

// Default constructor
Patron::Patron() {
    username = "";
    cardNumber = "";
    owedFees = 0;
}

// Parameterized constructor
Patron::Patron(string username, string cardNumber, int owedFees) {
    this->username = username;
    this->cardNumber = cardNumber;
    this->owedFees = owedFees;
}

// Getter for username
string Patron::getUsername() const {
    return username;
}

// Getter for card number
string Patron::getCardNumber() const {
    return cardNumber;
}

// Getter for owed fees
int Patron::getOwedFees() const {
    return owedFees;
}

// Check if patron owes fees
bool Patron::owesFees() const {
    return owedFees > 0;
}

// Setter for fees
void Patron::setFees(int fees) {
    if (fees >= 0) {
        owedFees = fees;
    } else {
        cout << "Fees cannot be negative!" << endl;
    }
}

