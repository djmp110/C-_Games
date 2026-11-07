#include <iostream>
#include "statistics.h"
using namespace std;
 
int main(){
    Statistics stats;

std::string playerName;

std::cout << "Enter player name to search: ";
std::getline(std::cin, playerName);

stats.search_player_statistics(playerName);
}