
#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>
#include "Patron.h"

class Book {
private:
    std::string ISBN;
    std::string Title;
    std::string Author;
    int Copyright_Date;
    std::string Genre;
    

public:
bool Checked_out;
    // Constructor
    std::vector<std::vector<std::string>> Books;
    Book(std::string isbn,
         std::string title,
         std::string author,
         int copyright_date,
         std::string genre,
         bool checked_out = false);

    // Getters
    std::string get_ISBN() const;
    std::string get_Title() const;
    std::string get_Author() const;
    int get_Copyright_Date() const;
    std::string get_Genre() const;
    bool get_Checked_out() const;

    // Checkout and check-in
    void check_out_book();
    void check_in_book();

    // Comparison operators
    bool operator==(const Book& other) const;
    bool operator!=(const Book& other) const;

    // Output operator
    friend std::ostream& operator<<(std::ostream& out, const Book& book);

    Book get_Book() const;
    Patron get_Patron() const;
    std::string get_Activity() const;
    std::string get_Date() const;
};

#endif
