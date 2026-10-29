
#include "draw.h"
#include <iostream>
#include <algorithm>

    HangmanDrawing::HangmanDrawing(int mistakes, int trials) {
    mistakes = std::clamp(mistakes, 0, trials);

    std::cout << "\n";
    std::cout << "  +-------+\n";
    std::cout << "  |       |\n";

    // Head
    std::cout << "  |       "
              << (mistakes >= 1 ? "O" : " ")
              << "\n";

    // Arms and body
    std::cout << "  |      "
              << (mistakes >= 3 ? "/" : " ")
              << (mistakes >= 2 ? "|" : " ")
              << (mistakes >= 4 ? "\\" : " ")
              << "\n";

    // Legs
    std::cout << "  |      "
              << (mistakes >= 5 ? "/" : " ")
              << " "
              << (mistakes >= 6 ? "\\" : " ")
              << "\n";

    std::cout << "  |\n";
    std::cout << "  ==========\n";

    std::cout << "\nMistakes: "
              << mistakes << "/" << trials
              << "\n";
}