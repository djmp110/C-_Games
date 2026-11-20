#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <array>
#include <vector>
#include <utility>

class Board {
public:
   int game();
    static constexpr int SIZE = 3;
    Board();
    void reset();
    void player(std::string player1,std::string player2);
    bool makeMove(int position, char symbol);
    bool undoMove();
    bool isValidMove(int position) const;
    bool isFull() const;
    char winner() const;
    bool isDraw() const;
    std::vector<int> availableMoves() const;
    std::vector<int> winningCells() const;
    char at(int position) const;
    void display(bool color = true) const;
    const std::vector<std::pair<int,char>>& history() const;
private:
    std::array<char,9> cells_{};
    std::vector<std::pair<int,char>> history_;
};
#endif
