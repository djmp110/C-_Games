#include <iostream>
using namespace std;

int main(){
    int user_choice;
    cout << "_________________________________________"<<endl;
    cout << "Gikondo Campus Library Management System"<<endl;
    cout << "_________________________________________\n"<<endl;
    cout << "1. Here there is what you can do\n"<< "1. Add New Book\n2. Check out Book\n3. Check in Book\n4. Sell Book\n5. Close app\n";
    cin >> user_choice;
    switch(user_choice){
        case 1:
        cout << "Add New Book";
        case 2:
        cout << "Check out Book";
        case 3:
        cout << "Check in book";
    }
    return 0;
}