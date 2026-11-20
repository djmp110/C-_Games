
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "Book.h"
#include "Patron.h"

class Transaction {

private:
    Book book;
    Patron patron;
    std::string Activity;
    std::string Date;

public:

    // Constructor
    Transaction(const Book& book, const Patron& patron, std::string activity, std::string date);

    // This is the  Function to select an activity
    static std::string activity_selector();

};

#endif
