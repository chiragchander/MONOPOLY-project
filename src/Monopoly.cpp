// main.cpp
// Lovato Emanuele

#include <iostream>
#include <string>       // Per conversione esplicita argv[1] e susseguente confronto.
#include "../include/Casella.h"
#include "../include/Board.h"
#include "../include/Dadi.h"
#include "../include/Game.h"
#include "../include/Player.h"
#include "../include/Logger.h"

using namespace std;

int main(int argc, char* argv[]) {
    // Controllo non vi sia più di un argomento oltre al comando dell'eseguibile.
    bool partita_umana = false;     // Variabile per valutare tipologia partita.
    if (argc != 2) {
        cout << "Argomento dell'eseguibile errato.\n";
        cout << "    <#> Cortesemente, utilizza: \n    " << argv[0] << " [tipologia_giocatore: \"computer\" o \"human\"]\n";
        return 1;       // Se non vi è uno ed uno solo argomento addizionale, esci dal programma ritornando 1.
    }

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
        cout << "    <#> Cortesemente, utilizza: \n    " << argv[0] << " [tipologia_giocatore: \"computer\" o \"human\"]\n";
        return 1;
    }

    Board board;
    Dadi dadi;
    Game game;

    // Come da consegna, due diversi file di log a seconda della tipologia di partita.
    string nome_file;
    if(partita_umana) nome_file = "log_human.txt";
    else nome_file = "log_computer.txt";
    Logger logger(nome_file);   // Logger per i vari eventi del gioco.

    // Crea l'ordine iniziale dei giocatori.
    game.intro();

    int conta_gio = 0;    // Indica vettore giocatori, da 0 a 3.
    int gio_umano = 0;      // @@@ come deciderlo?
    int totale_gio = 4;     // @@@ magari includerlo in Game?
    Player* gio_attuale = nullptr;

    // LOOP centrale e principale del gioco.
    while(!game.fine_gioco()) {
        gio_attuale = game.get_giocatori(conta_gio);
        //logger.inizio_turno(gio_attuale->get_nome());

        // MOVIMENTO con differenze in questo punto, a seconda
        // If tipologia partita human, turno umano.
        if(partita_umana && conta_gio == gio_umano) {
            // HUMAN
            // Input "show" per visualizzazioni, "roll" per proseguire lanciando il dado.
            string input_utente;
            cout << "Umano, attendo un tuo comando!\n";

            do {
                    logger.inizio_turno(gio_attuale->get_nome());
                    game.turno_human(gio_attuale);
                    break;
            } while(true);
        }
        // Else tipologia partita computer o partita human con turno giocatori computer.
        else {
            // COMPUTER
            // @@@ Decidere se visualizzare mostra board per giocatore computer e che altro visualizzare.

            // @@@ move_player e move_robot vanno cambiate radicalmente
            game.turno_robot(gio_attuale);
            game.move_player(gio_attuale);
        }

        logger.fine_turno(gio_attuale->get_nome());
        // Prossimo giocatore
        conta_gio++;

        // FINE TURNO totale, terminati i giocatori attuali.
        if(conta_gio > (totale_gio-1)) {
            game.next_turno();

            for(int i=0; i < totale_gio; i++) {
                Player* gio_temp = game.get_giocatori(i);
                // Analisi se ciascuno dei gio_temp hanno soldi, se povero() rimuoverlo ed aggiornare totale_gio.
                if(gio_temp->povero()) {
                    logger.elimin(gio_temp->get_nome());     // Segnala nel log prima di eliminare il giocatore.
                    game.del_giocatore(gio_temp);
                    i--;            // Slittato il vettore player di uno.
                    totale_gio--;   // Di conseguenza anche numero giocatori ridotto.
                }
            }
            conta_gio = 0;     // Riparte dal primo giocatore.
        }
    }

    // Calcola vincitori, che sia uno o più.
    // @@@ implementare più vincitori in caso di parità.
    vector<Player*> vincitori = game.vincitori();
    for(int i=0; i<vincitori.size(); i++){
            logger.vince(vincitori[i]->get_nome());
    }

    return 0;
}
