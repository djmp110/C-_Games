
#include "Library.h"
#include <iostream>
#include <algorithm>

Book BOOK;

// Constructor
Library::Library() {
}

// Add a book to the library
void Library::addBook(const Book& book) {

    // Check whether the book already exists
    for (const Book& b : books) {

        if (b == book) {
            cout << "Error: Book already exists!" << endl;
            return;
        }
    }

    // Add book to vector
    books.push_back(book);

    cout << "Book added successfully!" << endl;
}
// write patron information
//patron object creation
Patron newPatron;
void writePatron() {
    string user;
    string usedID;
    int money;

    

    cin >> newPatron.username;
    cin >> newPatron.cardNumber;
    cin >> newPatron.owedFees;
}

// Register a patron
void Library::addPatron(const Patron& newPatron) {

    // Check whether patron is already registered
    for (const Patron& p : patrons) {

        if (p.getCardNumber() == newPatron.getCardNumber()) {
            cout << "Error: Patron already registered!" << endl;
            return;
        }
    }

    // Add patron to vector
    patrons.push_back(newPatron);

    cout << "Patron registered successfully!" << endl;
}


// Check out a book
// Check out a book
void Library::checkOutBook(string ISBN,
                           string cardNumber,
                           string date) {

    // 1. Find the requested book in the library's 'books' vector
    auto it = std::find_if(books.begin(), books.end(), [&ISBN](const Book& b) {
        return b.get_ISBN() == ISBN;
    });

    // 2. Check whether book exists
    if (it == books.end()) {
        cout << "Error: Book not found!" << endl;
        return;
    }

    // 3. Find the patron
    auto patron = std::find_if(patrons.begin(), patrons.end(), [&cardNumber](const Patron& p) {
        return p.getCardNumber() == cardNumber;
    });

    // 4. Check whether patron exists
    if (patron == patrons.end()) {
        cout << "Error: Patron not registered!" << endl;
        return;
    }

    // 5. Check whether patron owes fees
    if (patron->owesFees()) {
        cout << "Error: Patron owes library fees!" << endl;
        return;
    }

    // 6. Check whether book is available
    // (Use it->isCheckedOut() if you have a getter like in returnBook, or it->Checked_out)
    if (it->Checked_out) {
        cout << "Error: Book is already borrowed!" << endl;
        return;
    }

    // 7. Mark book as borrowed
    // Note: If Checked_out is a bool variable, use: it->Checked_out = true;
    // If it is a method in Book.h (like checkIn() in returnBook), use: it->checkOut();
    it->Checked_out = true;

    // 8. Create transaction using *it (the found Book) and *patron (the found Patron)
    Transaction transaction(
        *it,
        *patron,
        "Check Out",
        date
    );

    // 9. Save transaction
    transactions.push_back(transaction);

    cout << "Book borrowed successfully!" << endl;
}



// Return a book
void Library::returnBook(string ISBN,
                         string cardNumber,
                        string date) {

    // Find the book
    auto book = books.end();

    for (auto it = books.begin(); it != books.end(); ++it) {

        if (it->get_ISBN() == ISBN) {
            book = it;
            break;
        }
    }

    // Find the patron
    auto patron = patrons.end();

    for (auto it = patrons.begin(); it != patrons.end(); ++it) {

        if (it->getCardNumber() == cardNumber) {
            patron = it;
            break;
        }
    }

    // Check whether book exists
    if (book == books.end()) {
        cout << "Error: Book not found!" << endl;
        return;
    }

    // Check whether patron exists
    if (patron == patrons.end()) {
        cout << "Error: Patron not registered!" << endl;
        return;
    }

    // Check whether book is borrowed
    if (!book->Checked_out) {
        cout << "Error: Book is not currently borrowed!" << endl;
        return;
    

    // Verify that this patron borrowed this book
    bool borrowedByPatron = false;

    for (const Transaction& t : transactions) {

        // Check the transaction history for the latest
        // checkout or return of this book
        if (t.get_Book().getISBN() == ISBN &&
            t.get_Patron().getCardNumber() == cardNumber) {

            borrowedByPatron = (t.getActivity() == "Check Out");
        }
    }

    if (!borrowedByPatron) {
        cout << "Error: This patron did not borrow this book!" << endl;
        return;
    }

    // Mark book as returned
    book->checkIn();

    // Create return transaction
    Transaction transaction(
        *book,
        *patron,
        "Check In",
        date
    );

    // Save transaction
    transactions.push_back(transaction);

    cout << "Book returned successfully!" << endl;
    }

                        }
// Get names of patrons who owe fees
vector<string> Library::getPatronsWithFees() const {

    vector<string> names;

    for (const Patron& patron : patrons) {

        if (patron.owesFees()) {
            names.push_back(patron.getUsername());
        }
    }

    return names;
}


// Display all books
void Library::displayBooks() const {

    cout << "\n===== LIBRARY BOOKS =====" << endl;

    for (const Book& book : books) {
        cout << book << endl;
    }
}


// Display all patrons



// Display all transactions
void Library::displayTransactions() const {

    cout << "\n===== TRANSACTION HISTORY =====" << endl;

    for (const Transaction& transaction : transactions) {
        transaction.displayTransaction();
        cout << "-------------------" << endl;
    }
}
