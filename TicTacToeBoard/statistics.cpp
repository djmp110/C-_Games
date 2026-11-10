#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "landing.h"
#include "statistics.h"
#include "utils.h"

using namespace std;

landing land;
void Statistics::add_statistics(string player1, string player2, string winner)
{

    const string filename = "statistics.txt";

    ofstream outputFile(filename, ios::app);

    if (!outputFile.is_open())
    {
        cerr << "Error: Could not open the file!" << endl;
        return;
    }

    outputFile << player1 << "|"
               << player2 << "|"
               << winner << endl;

    outputFile.close();

    cout << "Statistics recorded successfully." << endl;
}

void Statistics::read_statistics()
{

    const string filename = "statistics.txt";

    ifstream inputFile(filename);

    if (!inputFile.is_open())
    {
        cerr << "Error: Could not open statistics file!" << endl;
        return;
    }

    string line;

    cout << "\n======= GAME STATISTICS =======" << endl;

    while (getline(inputFile, line))
    {
        cout << line << endl;
    }

    inputFile.close();
}

void Statistics::clear_statistics()
{

    const std::string filename = "statistics.txt";

    std::ofstream outputFile(filename, std::ios::trunc);

    if (!outputFile.is_open())
    {
        std::cerr << "Error: Could not clear statistics!\n";
        return;
    }

    int user_response;

    cout << "Are You sure You want to clear Statistics?\n1. Yes\n2. No" << endl;
    cin >> user_response;
    if (user_response == 1)
    {
        outputFile.close();

        std::cout << "Statistics cleared successfully.\n";
    }
    else
    {
        cout << "Statistics are not cleared" << endl;
    }
}

void Statistics::search_player_statistics(std::string playerName)
{

    const std::string filename = "statistics.txt";

    std::ifstream inputFile(filename);

    if (!inputFile.is_open())
    {
        std::cerr << "Error: Could not open statistics file!\n";
        return;
    }

    std::string player1, player2, winner;
    std::string line;

    bool found = false;

    std::cout << "\n======= SEARCH RESULTS =======\n";

    std::cout << "Player 1\tPlayer 2\tWinner\n";
    std::cout << "-------------------------------------\n";

    while (std::getline(inputFile, line))
    {

        std::stringstream ss(line);

        std::getline(ss, player1, '|');
        std::getline(ss, player2, '|');
        std::getline(ss, winner, '|');

        if (player1 == playerName || player2 == playerName)
        {

            std::cout << player1 << "\t\t"
                      << player2 << "\t\t"
                      << winner << '\n';

            found = true;
        }
    }

    if (!found)
    {
        std::cout << "No statistics found for "
                  << playerName << ".\n";
    }

    inputFile.close();
}

void Statistics::statistics_menu()
{

    int choice;

    do
    {

        clearScreen();

        std::cout << "\n========== STATISTICS MENU ==========\n";
        std::cout << "1. See All Statistics\n";
        std::cout << "2. Search User in Statistics\n";
        std::cout << "3. Clear Statistics\n";
        std::cout << "4. Return to Home\n";
        std::cout << "=====================================\n";

        std::cout << "Enter your choice: ";
        std::cin >> choice;
        // Check if input is a number
        if (std::cin.fail())
        {
            clearScreen();
            std::cout << "\nInvalid input! Please enter a number.\n";

            std::cin.clear();
            std::cin.ignore(10000, '\n');

            std::cout << "Press Enter to continue...";
            std::cin.get();
            continue;
        }

        std::cin.ignore(10000, '\n');
        if (choice < 1 || choice > 4)
        {
            clearScreen();
            std::cout << "\nInvalid choice! Please enter a number between 1 and 4.\n";

            std::cout << "Press Enter to continue...";
            std::cin.get();
            continue;
        }

        switch (choice)
        {

        case 1:
        {
            clearScreen();
            read_statistics();

            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            break;
        }

        case 2:
        {
            std::string playerName;
            clearScreen();

            std::cout << "Enter player name: ";
            std::getline(std::cin, playerName);

            search_player_statistics(playerName);

            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            break;
        }

        case 3:
        {
            char confirm;
            clearScreen();
            std::cout << "Are you sure you want to clear all statistics? (y/n): ";
            std::cin >> confirm;
            std::cin.ignore(10000, '\n');

            if (confirm == 'y' || confirm == 'Y')
            {

                clear_statistics();
            }
            else
            {

                std::cout << "Operation cancelled.\n";
            }

            std::cout << "\nPress Enter to continue...";
            std::cin.get();

            break;
        }

        case 4:
        {
            clearScreen();
            land.main_menu();
            break;
        }
    }

    } while (choice != 4);
}