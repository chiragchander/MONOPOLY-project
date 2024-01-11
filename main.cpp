#include <iostream>
#include "Casella.h"
#include "Board.h"

using namespace std;

int main() {
    Board b;
    b.print_board();
    Casella start= b.get_starting_cell();
    for (int i = 0; i < 28; ++i) {
    b.move(start, 1);
    cout << endl;
    start.print_position();
    cout << endl;
}
    cout<<endl;
    int laps=b.laps();


    return 0;
}

