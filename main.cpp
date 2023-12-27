#include <iostream>
#include "Casella.h"
#include "Board.h"

using namespace std;

int main() {
    Board b;
    b.print_board();
    Casella start= b.get_starting_cell();
    b.move(start,28);
    cout<<endl;
    int laps=b.laps

    cout<<"Fatti "<<laps<<" giri"<<endl;


    return 0;
}
