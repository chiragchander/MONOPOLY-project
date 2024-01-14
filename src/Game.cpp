// Lovato Emanuele

#include "../include/Game.h"
#include "../include/Board.h"
#include "../include/Player.h"
#include "../include/Dadi.h"        // Serve solo nella funzione intro()
#include <algorithm>



Game::Game(): turno {1} {
    board= tabellone.get_board();
    Player* giocatore1 = new Player(1);
    Player* giocatore2 = new Player(2);
    Player* giocatore3 = new Player(3);
    Player* giocatore4 = new Player(4);
    add_giocatore(giocatore1);
    add_giocatore(giocatore2);
    add_giocatore(giocatore3);
    add_giocatore(giocatore4);

}

void Game::add_giocatore(Player* pippo) {
    pippo->set_position(tabellone.get_starting_cell().get_position());
    giocatori.push_back(pippo);
}

void Game::del_giocatore(Player* pippo) {
    auto it = std::find_if(giocatori.begin(), giocatori.end(), [pippo](const Player* player) {
        return *player == *pippo;
    });
    if (it != giocatori.end()) {
        giocatori.erase(it);
        std::vector<Casella*> caselle= pippo->get_proprie();
        if(!caselle.empty()){
            for(int i=0; i<caselle.size(); i++){
                caselle[i]->set_owner(0);
                caselle[i]->set_lvl(1);
            }
        }
    }
    // @@@ controllare che elimini correttamente

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
        if(giocatori[i]->get_budget() > giocatori[temp]->get_budget()) {
            temp = i;
        }
    }
    return giocatori[temp];
    // @@@ il problema è quando vi saranno due primi ex-equo, che va implementato.
}

void Game::print_gameboard(){
    for(int i=0; i<=8; i++){
        print_gameboard_line(i);
    }
}

void Game::print_gameboard_line(int n){
    if(giocatori.empty()) tabellone.print_line(n);
    else{

                tabellone.print_line(0);
                std::vector<Casella*> caselle_giocatore1 = giocatori[0]->get_proprie();
                std::vector<Casella*> caselle_giocatore2 = giocatori[1]->get_proprie();
                std::vector<Casella*> caselle_giocatore3 = giocatori[2]->get_proprie();
                std::vector<Casella*> caselle_giocatore4 = giocatori[3]->get_proprie();
                std::vector<int> giocatori_presenti_nella_casella;

                            std::cout << alphabet[n-1] << "   ";
                            for(int i = 0; i < 8; i++) {
                            if(board[i][n-1].is_central_cell()) std::cout<<"        ";

                            else{

                                // Verifica la presenza per il primo giocatore
                                for (const auto& casella : caselle_giocatore1) {
                                    if (casella->get_position() == board[i][n-1].get_position()) {
                                    giocatori_presenti_nella_casella.push_back(1);
                                    break;
                                    }
                                }

                                // Verifica la presenza per il secondo giocatore
                                for (const auto& casella : caselle_giocatore2) {
                                    if (casella->get_position() == board[i][n-1].get_position()) {
                                    giocatori_presenti_nella_casella.push_back(2);
                                    break;
                                    }
                                }

                                // Verifica la presenza per il terzo giocatore
                                for (const auto& casella : caselle_giocatore3) {
                                    if (casella->get_position() == board[i][n-1].get_position()) {
                                    giocatori_presenti_nella_casella.push_back(3);
                                    break;
                                    }
                                }

                                // Verifica la presenza per il quarto giocatore
                                for (const auto& casella : caselle_giocatore4) {
                                    if (casella->get_position() == board[i][n-1].get_position()) {
                                    giocatori_presenti_nella_casella.push_back(4);
                                    break;
                                    }
                                }

                                switch(giocatori_presenti_nella_casella.size()){
                                case 0:
                                    std::cout <<"|"<< board[i][n-1]<<"     |";
                                    break;
                                case 1:
                                    std::cout <<"|"<< board[i][n-1]<<giocatori_presenti_nella_casella[0]<<"    |";
                                    break;
                                case 2:
                                    std::cout <<"|"<< board[i][n-1]<<giocatori_presenti_nella_casella[0]<<giocatori_presenti_nella_casella[1]<<"   |";
                                    break;
                                case 3:
                                    std::cout <<"|"<< board[i][n-1]<<giocatori_presenti_nella_casella[0]<<giocatori_presenti_nella_casella[1]<<giocatori_presenti_nella_casella[2]<<"  |";
                                    break;
                                case 4:
                                    std::cout <<"|"<< board[i][n-1]<<giocatori_presenti_nella_casella[0]<<giocatori_presenti_nella_casella[1]<<giocatori_presenti_nella_casella[2]<<giocatori_presenti_nella_casella[3]<<" |";
                                    break;

                                }
                             }
                            }
                            std::cout << std::endl;

                }
    }


void Game::move_player(Player* pippo){
    Dadi dado;
    int passi= dado.lancio();
    while(passi>0){
        pippo->set_position(pippo->get_position().next_position());
        pippo->add_steps(1);
        passi--;
    }
}

/*
Game_Umano::Game_Umano() : Game(n) {
}
*/

