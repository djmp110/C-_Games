#include "Transaction.h"
#include <iostream>

Transaction::Transaction(const Book& book, const Patron& patron, std::string activity, std::string date)
    : book(book),
      patron(patron),
      Activity(activity),
      Date(date) {
}

std::string Transaction::activity_selector() {

    int user_choice;

    std::cout << "Choose action:\n";
    std::cout << "1. Checkout Book\n";
    std::cout << "2. Checkin Book\n";

    std::cin >> user_choice;

    while (user_choice != 1 && user_choice != 2) {
        std::cout << "Invalid choice. Choose 1 or 2: ";
        std::cin >> user_choice;
    }

    if (user_choice == 1) {
        return "Checkout Book";
    }

    return "Checkin Book";
}