#include"game.h"
#include "statistics.h"
#include<iostream>
using namespace std;
void main_menu(){
    cout << "1. Play the game\n2. Statistics\n3. Exit"<<endl;
    int user_choice;
    cin >> user_choice;
    if(user_choice == 1){
        game.game();
        
    }else if(user_choice== 2){
        stats.statistics_menu();
    }else if(user_choice == 3){
      break;  
    }
    else{
        cout<< "You write wrong number! Choose between 1, 2 or 3" << endl;
        main_menu()
    }
}
int main(){
    std::cout<<"wellcame to Tik-Tac-Toe\n";
    Statistics stats;
    Board game;
    main_menu();
    return 0;

}
