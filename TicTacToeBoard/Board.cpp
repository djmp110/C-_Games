#include "Board.h"
#include <iostream>
#include <algorithm>
#include <cctype>

namespace {
constexpr int lines[8][3] = {
    {0,1,2},{3,4,5},{6,7,8},
    {0,3,6},{1,4,7},{2,5,8},
    {0,4,8},{2,4,6}
};
}

Board::Board() { reset(); }

void Board::reset() {
    cells_.fill(' ');
    history_.clear();
}

bool Board::isValidMove(int position) const {
    return position >= 1 && position <= 9 && cells_[position-1] == ' ' && winner() == ' ';
}

bool Board::makeMove(int position, char symbol) {
    symbol = static_cast<char>(std::toupper(static_cast<unsigned char>(symbol)));
    if ((symbol != 'X' && symbol != 'O') || !isValidMove(position)) return false;
    cells_[position-1] = symbol;
    history_.push_back({position,symbol});
    return true;
}

bool Board::undoMove() {
    if (history_.empty()) return false;
    cells_[history_.back().first - 1] = ' ';
    history_.pop_back();
    return true;
}

char Board::winner() const {
    for (const auto& line : lines) {
        char c = cells_[line[0]];
        if (c != ' ' && c == cells_[line[1]] && c == cells_[line[2]]) return c;
    }
    return ' ';
}

std::vector<int> Board::winningCells() const {
    for (const auto& line : lines) {
        char c = cells_[line[0]];
        if (c != ' ' && c == cells_[line[1]] && c == cells_[line[2]])
            return {line[0]+1,line[1]+1,line[2]+1};
    }
    return {};
}

bool Board::isFull() const {
    return std::none_of(cells_.begin(),cells_.end(),[](char c){return c == ' ';});
}

bool Board::isDraw() const { return isFull() && winner() == ' '; }

std::vector<int> Board::availableMoves() const {
    std::vector<int> moves;
    if (winner() != ' ') return moves;
    for (int i=0;i<9;++i) if(cells_[i]==' ') moves.push_back(i+1);
    return moves;
}

char Board::at(int position) const {
    return position>=1 && position<=9 ? cells_[position-1] : '\0';
}

const std::vector<std::pair<int,char>>& Board::history() const { return history_; }

void Board::display(bool color) const {
    const auto wins = winningCells();
    std::cout << "\n       TIC-TAC-TOE\n\n";
    for(int row=0;row<3;++row) {
        std::cout << "     ";
        for(int col=0;col<3;++col) {
            int i=row*3+col;
            char c=cells_[i];
            bool highlighted=std::find(wins.begin(),wins.end(),i+1)!=wins.end();
            if(color && highlighted) std::cout << "\033[1;42;30m";
            else if(color && c=='X') std::cout << "\033[1;36m";
            else if(color && c=='O') std::cout << "\033[1;35m";
            std::cout << (c==' '?static_cast<char>('1'+i):c);
            if(color) std::cout << "\033[0m";
            if(col<2) std::cout << "  |  ";
        }
        std::cout << '\n';
        if(row<2) std::cout << "     ---+-----+---\n";
    }
    std::cout << '\n';
}
