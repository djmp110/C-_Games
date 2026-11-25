#ifndef GAME_H
#define GAME_H

#include <string>
#include <utility>

class Game {
public:
    Game();

    int trials = 0;
    int difficulty_option();
    int choose_option();
    int hint_choice();
    void return_to_mode();
    void AfterGame();
    void same_mode();
    void Enter_Characters(std::pair<std::string, std::string> selected, int trials);
    void Enter_Characters(std::pair<std::string, std::string> selected, int trials, int wants_hints);

private:
    struct Statistics {
        int games_played = 0;
        int games_won = 0;
        int games_lost = 0;
        int total_wrong_guesses = 0;
    } statistics;

    int game_mode = 0;
    void show_statistics();
    void load_statistics();
    void save_statistics() const;
};

#endif
