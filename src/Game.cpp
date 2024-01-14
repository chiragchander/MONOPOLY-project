// Lovato Emanuele

#include "../include/Game.h"
#include "../include/Board.h"
#include "../include/Player.h"
#include "../include/Dadi.h"        // Serve solo nella funzione intro()
#include <algorithm>
#include <cstdlib>
#include <ctime>



Game::Game(): turno {1} {
    board= tabellone.get_board();
    Player* giocatore2 = new Player(2);
    Player* giocatore3 = new Player(3);
    Player* giocatore4 = new Player(4);
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
        tabellone.print_line(0);
    for(int i=1; i<=8; i++){
        print_gameboard_line(i);
    }
}

void Game::print_gameboard_line(int n) {
        std::vector<int> giocatori_presenti_nella_casella;
        std::vector<std::pair<int, int>> posizioni_giocatori;
        for (const auto& giocatore : giocatori) {
            int x = giocatore->get_position().get_x();
            int y = giocatore->get_position().get_y();
            posizioni_giocatori.push_back(std::make_pair(x, y));
        }

        std::cout << alphabet[n-1] << "   ";
        for (int i = 0; i < 8; i++) {
            if (board[i][n - 1].is_central_cell()) {
                std::cout << "        ";
            } else {
                giocatori_presenti_nella_casella.clear();

                // Verifica la presenza dei giocatori nella casella
                for (int giocatore_index = 0; giocatore_index < giocatori.size(); ++giocatore_index) {
                    int x_giocatore = posizioni_giocatori[giocatore_index].first;
                    int y_giocatore = posizioni_giocatori[giocatore_index].second;

                    if (x_giocatore == board[i][n - 1].get_position().get_x() &&
                        y_giocatore == board[i][n - 1].get_position().get_y()) {
                        giocatori_presenti_nella_casella.push_back(giocatori[giocatore_index]->get_nome());
                    }
                }

                // Stampa la casella con i giocatori presenti
                switch (giocatori_presenti_nella_casella.size()) {
                case 0:
                    std::cout << "|" << board[i][n - 1] << "     |";
                    break;
                case 1:
                    std::cout << "|" << board[i][n - 1] << giocatori_presenti_nella_casella[0] << "    |";
                    break;
                case 2:
                    std::cout << "|" << board[i][n - 1] << giocatori_presenti_nella_casella[0] << giocatori_presenti_nella_casella[1] << "   |";
                    break;
                case 3:
                    std::cout << "|" << board[i][n - 1] << giocatori_presenti_nella_casella[0] << giocatori_presenti_nella_casella[1] << giocatori_presenti_nella_casella[2] << "  |";
                    break;
                case 4:
                    std::cout << "|" << board[i][n - 1] << giocatori_presenti_nella_casella[0] << giocatori_presenti_nella_casella[1] << giocatori_presenti_nella_casella[2] << giocatori_presenti_nella_casella[3] << " |";
                    break;
                }
            }
        }
        std::cout << std::endl;
}



void Game::move_player(Player* pippo){
    Dadi dado;
    int passi= dado.lancio();
    while(passi>0){
        pippo->set_position(pippo->get_position().next_position());
        pippo->add_steps(1);
        if(pippo->get_steps()%28 ==0){
            pippo->ricevi(20);
        }
        passi--;
    }
}

void Game::move_robot(Player* pippo){
    std::srand(static_cast<int>(std::time(nullptr)));
    int prob= std::rand() %4;
    if(prob==1){
        Dadi dado;
    int passi= dado.lancio();
    while(passi>0){
        pippo->set_position(pippo->get_position().next_position());
        pippo->add_steps(1);
        if(pippo->get_steps()%28 ==0){
            pippo->ricevi(20);
        }
        passi--;
    }
    }
}

/*
Game_Umano::Game_Umano() : Game(n) {
}
*/

