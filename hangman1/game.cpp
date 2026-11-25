#include "game.h"

#include "draw.h"
#include "wordselector.h"

#include <cctype>
#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#ifdef _WIN32
#include <cstdlib>
#else
#include <iostream>
#endif

namespace {
void clear_screen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::cout << "\033[2J\033[H" << std::flush;
#endif
}

int read_integer(const std::string& prompt, int minimum, int maximum) {
    while (true) {
        std::cout << prompt;
        int value;
        if (std::cin >> value && value >= minimum && value <= maximum) return value;
        if (std::cin.eof()) return minimum;
        std::cout << "Please enter a number from " << minimum << " to " << maximum << ".\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
}

int Game::choose_option() {
    return read_integer("\n1. Play Game\n2. See Statistics\n3. Exit\nChoose an option: ", 1, 3);
}

int Game::difficulty_option() {
    return read_integer("\nChoose a mode:\n1. Easy\n2. Medium\n3. Hard\n4. Return to main menu\nChoose: ", 1, 4);
}

int Game::hint_choice() {
    return read_integer("Do you want a hint? (1 yes, 0 no): ", 0, 1);
}

void Game::return_to_mode() {
    game_mode = difficulty_option();
    if (game_mode == 4) return;
    same_mode();
}

void Game::same_mode() {
    if (game_mode < 1 || game_mode > 3) return;
    const auto selected = word_selector(game_mode);
    const int hints = hint_choice();
    trials = game_mode == 1 ? 8 : (game_mode == 2 ? 5 : 4);
    Enter_Characters(selected, trials, hints);
}

void Game::AfterGame() {
    const int choice = read_integer("\n1. Replay in same mode\n2. Change mode\n3. Main menu\n4. Exit\nChoose: ", 1, 4);
    if (choice == 1) same_mode();
    else if (choice == 2) return_to_mode();
    else if (choice == 3) {
        const int option = choose_option();
        if (option == 1) return_to_mode();
        else if (option == 2) show_statistics();
        else std::cout << "Thanks for playing!\n";
    } else std::cout << "Thanks for playing!\n";
}

void Game::load_statistics() {
    std::ifstream file("hangman_statistics.txt");
    Statistics loaded;
    if (file >> loaded.games_played >> loaded.games_won >> loaded.games_lost >> loaded.total_wrong_guesses) {
        statistics = loaded;
    } else {
        statistics = {};
    }
}

void Game::save_statistics() const {
    std::ofstream file("hangman_statistics.txt");
    if (!file) {
        std::cerr << "Could not save statistics to hangman_statistics.txt.\n";
        return;
    }
    file << statistics.games_played << '\n'
         << statistics.games_won << '\n'
         << statistics.games_lost << '\n'
         << statistics.total_wrong_guesses << '\n';
    if (!file) std::cerr << "Failed while writing hangman statistics.\n";
}

void Game::show_statistics() {
    load_statistics();
    std::cout << "\n--- Hangman statistics ---\n"
              << "Games played: " << statistics.games_played << '\n'
              << "Wins: " << statistics.games_won << '\n'
              << "Losses: " << statistics.games_lost << '\n'
              << "Wrong guesses: " << statistics.total_wrong_guesses << '\n';
}

void Game::Enter_Characters(std::pair<std::string, std::string> selected, int maximum_mistakes) {
    std::string answer = selected.first;
    for (char& letter : answer) letter = static_cast<char>(std::tolower(static_cast<unsigned char>(letter)));
    std::string revealed(answer.size(), '_');
    std::string guessed;
    int mistakes = 0;
    std::cout << "The word has " << answer.size() << " characters; you have " << maximum_mistakes << " wrong guesses.\n";

    while (mistakes < maximum_mistakes && revealed != answer) {
        clear_screen();
        std::cout << "Hangman\n\n";
        HangmanDrawing(mistakes, maximum_mistakes);
        std::cout << "\nWord: " << revealed << "\nGuessed: " << (guessed.empty() ? "(none)" : guessed) << "\nEnter a letter: ";
        std::string input;
        if (!(std::cin >> input)) {
            std::cin.clear();
            std::cout << "Input ended.\n";
            return;
        }
        if (input.size() != 1 || !std::isalpha(static_cast<unsigned char>(input[0]))) {
            std::cout << "Enter one letter.\n";
            continue;
        }
        const char letter = static_cast<char>(std::tolower(static_cast<unsigned char>(input[0])));
        if (guessed.find(letter) != std::string::npos) {
            std::cout << "You already guessed that letter.\n";
            continue;
        }
        guessed += letter;
        bool found = false;
        for (std::size_t index = 0; index < answer.size(); ++index) {
            if (answer[index] == letter) { revealed[index] = letter; found = true; }
        }
        if (!found) {
            ++mistakes;
            ++statistics.total_wrong_guesses;
            HangmanDrawing(mistakes, maximum_mistakes);
            std::cout << "Wrong guess. Attempts remaining: " << maximum_mistakes - mistakes << '\n';
        } else std::cout << "Correct guess!\n";
    }
    if (revealed == answer) {
        std::cout << "You won! The word was: " << answer << '\n';
    } else {
        std::cout << "Game over. The word was: " << answer << '\n';
    }
    load_statistics();
    ++statistics.games_played;
    if (revealed == answer) ++statistics.games_won;
    else ++statistics.games_lost;
    statistics.total_wrong_guesses += mistakes;
    save_statistics();
    AfterGame();
}

void Game::Enter_Characters(std::pair<std::string, std::string> selected, int maximum_mistakes, int wants_hints) {
    if (wants_hints) std::cout << "Hint: " << selected.second << '\n';
    Enter_Characters(std::move(selected), maximum_mistakes);
}

Game::Game() {
    std::cout << "-------------------------\nWelcome to Hangman!\n-------------------------\n";
    while (true) {
        const int option = choose_option();
        if (option == 1) { return_to_mode(); break; }
        if (option == 2) show_statistics();
        else { std::cout << "Thanks for playing!\n"; break; }
    }
}
