#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "statistics.h"

using namespace std;

void Statistics::add_statistics(string player1, string player2, string winner) {

    const string filename = "statistics.txt";

    ofstream outputFile(filename, ios::app);

    if (!outputFile.is_open()) {
        cerr << "Error: Could not open the file!" << endl;
        return;
    }

    outputFile << player1 << "|" 
               << player2 << "|" 
               << winner << endl;

    outputFile.close();

    cout << "Statistics recorded successfully." << endl;
}

void Statistics::read_statistics() {

    const string filename = "statistics.txt";

    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error: Could not open statistics file!" << endl;
        return;
    }

    string line;

    cout << "\n======= GAME STATISTICS =======" << endl;

    while (getline(inputFile, line)) {
        cout << line << endl;
    }

    inputFile.close();
}

void Statistics::clear_statistics() {

    const std::string filename = "statistics.txt";

    std::ofstream outputFile(filename, std::ios::trunc);

    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not clear statistics!\n";
        return;
    }

    outputFile.close();

    std::cout << "Statistics cleared successfully.\n";
}

void Statistics::search_player_statistics(std::string playerName) {

    const std::string filename = "statistics.txt";

    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open statistics file!\n";
        return;
    }

    std::string player1, player2, winner;
    std::string line;

    bool found = false;

    std::cout << "\n======= SEARCH RESULTS =======\n";

    std::cout << "Player 1\tPlayer 2\tWinner\n";
    std::cout << "-------------------------------------\n";

    while (std::getline(inputFile, line)) {

        std::stringstream ss(line);

        std::getline(ss, player1, '|');
        std::getline(ss, player2, '|');
        std::getline(ss, winner, '|');

        if (player1 == playerName || player2 == playerName) {

            std::cout << player1 << "\t\t"
                      << player2 << "\t\t"
                      << winner << '\n';

            found = true;
        }
    }

    if (!found) {
        std::cout << "No statistics found for " 
                  << playerName << ".\n";
    }

    inputFile.close();
}