#include <iostream>
#include "Casella.h"
#include "Board.h"
using namespace std;

int main() {
    Board b;
    b.print_board();
    cout<<endl;
    char row= b.get_current_row();
    int col= b.get_current_col();
    cout<<row<<" "<<col<<endl;
    b.move(28);
    cout<<b.get_current_row()<<" "<<b.get_current_col()<<endl;
    int laps=b.laps();
    cout<<"Fatti "<<laps<<" giri"<<endl;
    return 0;
}
