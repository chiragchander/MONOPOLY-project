// Lovato Emanuele

#include "../include/Game.h"
#include "../include/Dadi.h"        // Serve solo nella funzione intro()

Game::Game() 
    : turno {1} {
}

void Game::add_giocatore(Player* pippo) {
    giocatori.push_back(pippo);
}

void Game::del_giocatore(Player* pippo) {
    giocatori.erase(pippo);     // @@@ controllare che elimini correttamente
    // CCC rimuovere dal tabellone tutte le caselle e proprietà del giocatore
}

void Game::next_turno() {
    turno++;
    // @@@ Eventualmente aggiungere qui i 20 fiorni del player.
}

void Game::intro() {
    // Come richiesto dalla consegna, ordine i giocatori con nome 1, 2, 3, 4 nell'ordine determianto dai dadi.
//    Dadi dadolata;
/*    for(int i = 1; i <= 4; i++) {
        Player temp(i);
    }
WORK IN PROGRESS, stavo facendola ora @@@.
*/

    // LLL aggiornerei logger per avvisare dell'ordine dei giocatori
}

void Game::giocatore_over(Player* pippo) {
    // Se il giocatore in questione pippo è da rimuovere, va tolto dalla lista
    if(pippo->povero() || !pippo->get_vivo()) {
        del_giocatore(pippo);
        // CCC vanno inserite tutte da Board le modalità per liberare le caselle possedute dal giocatore
    }
}

bool Game::fine_gioco() {
    // Stabiliamo che si finisca quando i turni arrivano oltre il 500 o quando rimane un solo giocatore.
    if(turno > 500 || giocatori.size() == 1) {
        return true;
    }
    else return false;
}

Player* Game::vincitore() {
    int temp = 0;
    for(int i = 0; i < giocatori.size(); i++) {
        if(giocatori[i].get_budget() > giocatori[temp].get_budget()) {
            temp = i;
        }
    }
    return giocatori[temp];
    // @@@ il problema è quando vi saranno due primi ex-equo, che va implementato.
}


/*
Game_Umano::Game_Umano() : Game(n) {
}
*/