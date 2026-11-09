#ifndef STATISTICS_H
#define STATISTICS_H

#include <string>

class Statistics {

public:
// This is for recording statistics into statistics file
    void add_statistics(std::string player1, std::string player2, std::string winner);

// This is for reading statistics from statistics file
    void read_statistics();

//This is for clearing statistics
    void clear_statistics();

// This is for searching the player in statistics
    void search_player_statistics(std::string playerName);

    void statistics_menu();

};

#endif