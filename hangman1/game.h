#ifndef GAME_H
#define GAME_H
#include <utility>
#include <string>


class Game{
    public:
    int trials;
    int difficulty_option();
    int choose_option();
    Game();
    void return_to_mode();
    void AfterGame();
    int hint_choice();
    void same_mode();
    void Enter_Characters(std :: pair<std :: string, std :: string> selected, int trials);
    void Enter_Characters(std :: pair<std :: string, std :: string> selected, int trials, int wants_hints);
};

#endif