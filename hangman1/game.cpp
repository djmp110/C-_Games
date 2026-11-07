
#include <iostream>
#include <string>
#include <utility>
#include <limits>

#include "game.h"
#include "wordselector.h"
#include "draw.h"

using namespace std;

int Game::choose_option()
{
    int user_choice;

    while (true)
    {
        cout << "Choose an option between 1 - 3\n";
        cout << "1. Play Game" << endl;
        cout << "2. See Statistics" << endl;
        cout << "2. Exit" << endl;

        if (cin >> user_choice &&
            user_choice >= 1 && user_choice <= 3)
        {
            return user_choice;
        }

        cout << "Please enter 1, 2, or 3.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
int Game::difficulty_option()
{
    int user_choice;

    while (true)
    {
        cout << "\nChoose the mode you want to play\n"
             << "1. Easy\n"
             << "2. Medium\n"
             << "3. Hard\n"
             << "4. Return Back\n";

        if (cin >> user_choice &&
            user_choice >= 1 && user_choice <= 4)
        {
            return user_choice;
        }

        cout << "Please enter a number from 1 to 4.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int Game::hint_choice()
{
    int user_choice;

    while (true)
    {
        cout << "Do you want hints?\n"
             << "Enter 1 for hints\n"
             << "Enter 0 for no hints\n";

        if (cin >> user_choice &&
            (user_choice == 0 || user_choice == 1))
        {
            return user_choice;
        }

        cout << "Please enter 0 or 1.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
// Declaring variable game mode global for being used in return mode, same_mode.
int game_mode;
// Return to mode! This is for user who wants to change mode ! It is called when game ends
void Game::return_to_mode()
{
    game_mode = difficulty_option();

    if (game_mode == 4)
    {
        cout << "Returning to the main menu.\n";
        return;
    }

    pair<string, string> random_selected =
        word_selector(game_mode);

    int want_hints = hint_choice();

    if (game_mode == 1)
    {
        trials = 8;
    }
    else if (game_mode == 2)
    {
        trials = 5;
    }
    else
    {
        trials = 4;
    }

    if (want_hints == 0)
    {
        Enter_Characters(random_selected, trials);
    }
    else
    {
        Enter_Characters(random_selected, trials, 1);
    }
}

void Game::same_mode()
{
    pair<string, string> random_selected =
        word_selector(game_mode);

    int want_hints = hint_choice();

    if (game_mode == 1)
    {
        trials = 8;
    }
    else if (game_mode == 2)
    {
        trials = 5;
    }
    else
    {
        trials = 4;
    }

    if (want_hints == 0)
    {
        Enter_Characters(random_selected, trials);
    }
    else
    {
        Enter_Characters(random_selected, trials, 1);
    }
}
void Game::AfterGame()
{
    int user_choice;
    cout << "---------------------------------\n";
    cout << "1. Replay in same mode\n2. Go to change mode\n3. Return to Home\n4. Exit" << endl;
    cin >> user_choice;
    switch (user_choice)
    {
    case 1:
        same_mode();
        break;
    case 2:
        return_to_mode();
        break;

    case 3:
        Game();
        break;
    }
}

// For a game without hints
void Game::Enter_Characters(pair<string, string> selected,
                            int trials)
{
    int word_length = selected.first.length();

    cout << "The word has " << word_length
         << " characters, and you have "
         << trials << " wrong guesses available.\n";

    cout << "Enter one character at a time.\n";

    string spaces(word_length, '_');
    int fails = 0;

    while (fails < trials && spaces != selected.first)
    {
        cout << "\nWord: " << spaces << '\n';
        cout << "Enter a character: ";

        string typed_char;
        cin >> typed_char;

        if (typed_char.length() != 1)
        {
            cout << "Please enter exactly one character.\n";
            continue;
        }

        int char_returns = 0;

        for (int i = 0; i < word_length; i++)
        {
            if (typed_char[0] == selected.first[i])
            {
                spaces[i] = typed_char[0];
                char_returns++;
            }
        }

        if (char_returns == 0)
        {
            fails++;
            HangmanDrawing(fails, trials);
            cout << "Wrong guess! Attempts remaining: "
                 << trials - fails << '\n';
        }
        else
        {
            cout << "Correct guess!\n";
        }
    }

    if (spaces == selected.first)
    {
        cout << "Congratulations! You guessed the word: "
             << selected.first << '\n';
             AfterGame();
    }
    else
    {
        cout << "Game over! The word was: "
             << selected.first << '\n';
             AfterGame();
    }
}

// For a game with hints
void Game::Enter_Characters(pair<string, string> selected,
                            int trials, int wants_hints)
{
    cout << "Hint: " << selected.second << '\n';

    Enter_Characters(selected, trials);
    
}

// Game constructor
Game::Game()
{
    cout << "-------------------------\n";
    cout << "Welcome to Hangman!\n";
    cout << "-------------------------\n";

    int user_option = choose_option();

    if (user_option == 2)
    {
        cout << "This feature will come later.\n";
        return;
    }

    if (user_option == 3)
    {
        cout << "Thanks for playing with us!\n";
        return;
    }

    return_to_mode();
}
