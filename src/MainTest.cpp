#include <iostream>
#include "../include/Casella.h"
#include "../include/Board.h"
#include "../include/Dadi.h"
#include "../include/Game.h"
#include "../include/Player.h"


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

    Dadi ddd;
    cout << "Lancio: " << ddd.lancio() << "\n";
    cout << ddd;
    cout << "Attuale: " << ddd.attuale() << "\n";
    cout << "Lancio: " << ddd.lancio() << "\n";
    cout << ddd;
    ddd.stampa_quadro();
    Game g;


    g.print_gameboard();


    return 0;
}

