
#include <iostream>
#include "Book.h"
#include <vector>
#include <string>

// Available genres
std::string genres[5] = {
    "fiction",
    "nonfiction",
    "periodical",
    "biography",
    "Children"
};

// Function to choose a genre
std::string genre() {
    int user_choice;

    std::cout << "Choose the genre\n"
              << "1. fiction\n"
              << "2. nonfiction\n"
              << "3. periodical\n"
              << "4. biography\n"
              << "5. children\n";

    std::cin >> user_choice;

    while (user_choice < 1 || user_choice > 5) {
        std::cout << "Choose number 1 to 5: ";
        std::cin >> user_choice;
    }

    return genres[user_choice - 1];
}
std::vector<std::vector<std::string>> Books ={};
// Collection of all books


// Book constructor
Book::Book(std::string isbn, std::string title, std::string author, int copyright_date,std::string genre, bool checked_out) {

    ISBN = isbn;
    Title = title;
    Author = author;
    Copyright_Date = copyright_date;
    Genre = genre;
    Checked_out = checked_out;

    std::vector<std::string> book_details = {
        ISBN,
        Title,
        Author,
        std::to_string(Copyright_Date),
        Genre,
        std::to_string(Checked_out)
    };

    Books.push_back(book_details);
}

void Book::check_out_book() {
    if (Checked_out == false) {
        Checked_out = true;
        std::cout << "Book checked out successfully!\n";
    }
    else {
        std::cout << "This book is already checked out.\n";
    }
}

void Book::check_in_book() {
    if (Checked_out == true) {
        Checked_out = false;
        std::cout << "Book checked in successfully!\n";
    }
    else {
        std::cout << "This book is already available.\n";
    }
}

bool Book::operator==(const Book& other) const {
    return ISBN == other.ISBN;
}

bool Book::operator!=(const Book& other) const {
    return ISBN != other.ISBN;
}

Book Transaction::get_Book() const {
    return book;
}

Patron Transaction::get_Patron() const {
    return patron;
}

std::string Transaction::get_Activity() const {
    return Activity;
}

std::string Transaction::get_Date() const {
    return Date;
}