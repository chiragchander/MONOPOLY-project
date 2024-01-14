#include <iostream>
#include <string>       // Per conversione esplicita argv[1] e susseguente confronto.
#include "../include/Casella.h"
#include "../include/Board.h"
#include "../include/Dadi.h"
#include "../include/Game.h"
#include "../include/Player.h"

using namespace std;

int main(int argc, char* argv[]) {
    // [argc e argv -> Lovato Emanuele]
    // Controllo non vi sia più di un argomento oltre al comando dell'eseguibile.
    /*if (argc != 2) {
        cout << "Argomento dell'eseguibile errato.\n";
        cout << "    Cortesemente, utilizza: \n    " << argv[0] << " [tipologia_giocatore: \"computer\" o \"human\"]\n";
        return 1;       // Se non vi è uno ed uno solo argomento addizionale, esci dal programma ritornando 1.
    }

    bool partita_umana;     // Variabile per valutare tipologia partita.
    // Per confrontare con operatore ==, faccio conversione esplicita di argv[1] in string.
    // I valori a riga di comando vanno inseriti in minuscolo, stante la consegna del progetto.
    if(string(argv[1]) == "computer") {
        partita_umana = false;
    }
    else if(string(argv[1]) == "human") {
        partita_umana = true;
    }
    else {
        cout << "Tipologia di giocatore errata.\n";
        cout << "    Cortesemente, utilizza: \n    " << argv[0] << " [tipologia_giocatore: \"computer\" o \"human\"]\n";
        return 1;
    }
    // end [argc e argv -> Lovato Emanuele]
*/
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
