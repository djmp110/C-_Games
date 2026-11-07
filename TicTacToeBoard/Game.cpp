#include "Board.h"
#include <iostream>
#include <string>
using namespace std;

string enter_player_one()
{
    string player;
    cout << "Enter the player 1 name\n";
    cin >> player;
    return player;
}

string enter_player_two()
{
    string player;
    cout << "Enter the player 2 name\n";
    cin >> player;
    return player;
}

string choose_first_player(string x, string y)
{
    cout << "Choose whose to play first\n.";
    cout << "1. " << x << endl;
    cout << "2. " << y << endl;
    int user_choice;
    cin >> user_choice;
    if (user_choice < 1 || user_choice > 2)
    {
        cout << "Invalid choise! Enter 1 or 2\n";
    }
    if (user_choice == 1)
    {
        return x;
    }
    else
    {
        return y;
    }
}

int game()
{
    Board board;
    string player_one = enter_player_one();
    string player_two = enter_player_two();
    string first_player = choose_first_player(player_one, player_two);
    string second_player = first_player == player_one ? player_two: player_one;
    char player_1_token = 'X';
    bool again = true;

    while (again)
    {
        board.reset();
        player_1_token = 'X';
        while (board.winner() == ' ' && !board.isDraw())
        {
            board.display();
            std::cout << "Player " << first_player << ": choose 1-9 (u = undo, q = quit): ";
            std::string input;
            if (!std::getline(std::cin, input))
                return 0;
            if (input == "q" || input == "Q")
                return 0;
            if (input == "u" || input == "U")
            {
                if (board.undoMove())
                    player_1_token = player_1_token == 'X' ? 'O' : 'X';
                else
                    std::cout << "No move to undo.\n";
                continue;
            }
            if (input.size() != 1 || input[0] < '1' || input[0] > '9' ||
                !board.makeMove(input[0] - '0', player_1_token))
            {
                std::cout << "Invalid move. Choose an empty square 1-9.\n";
                continue;
            }
            first_player= first_player == player_one? player_two : player_one;
            player_1_token = player_1_token == 'X' ? 'O' : 'X';
        }
        board.display();
        if (board.isDraw()){
            std::cout << "It's a draw!\n";
        }
        else{
            char winner_char = board.winner();
            string winner;
            if(winner_char == 'X'){
                winner = first_player;
            }else{
                winner = second_player;
            }
            std::cout << "Player " << winner << " wins!\n";
        }
        std::cout << "Play again? (y/n): ";
        std::string answer;
        if (!std::getline(std::cin, answer))
            return 0;
        again = answer == "y" || answer == "Y";
    }
}
