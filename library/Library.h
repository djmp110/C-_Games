
#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <vector>
#include <string>

#include "Book.h"
#include "Patron.h"
#include "Transaction.h"


using namespace std;

class Library
{
private:
    // Store all books in the library
    vector<Book> books;

    // Store all registered patrons
    vector<Patron> patrons;

    // Store all library transactions
    vector<Transaction> transactions;

public:
    // Constructor
    Library();

    // Add a book
    void addBook(const Book &book);
    void writePatron();

    // Register a patron
    void addPatron(const Patron &patron);

    // Borrow a book
    void checkOutBook(string ISBN, string cardNumber, string date);

    // Return a book
    void returnBook(string ISBN, string cardNumber, string date);

    // Return names of patrons who owe fees
    vector<string> getPatronsWithFees() const;

    // Display all books
    void displayBooks() const;

    // Display all patron
    void displayPatron() const;

    // Display all transactions
    void displayTransactions() const;
};

#endif
