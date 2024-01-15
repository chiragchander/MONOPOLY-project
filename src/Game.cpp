// Lovato Emanuele
#include "../include/Casella.h"
#include "../include/Game.h"
#include "../include/Board.h"
#include "../include/Player.h"
#include "../include/Dadi.h"        // Serve solo nella funzione intro()
#include "../include/Logger.h"        // Serve solo nella funzione intro()
#include <algorithm>
#include <cstdlib>
#include <ctime>



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

std::vector<int> Game::order_players() {
    Dadi dadi;
    std::vector<int> tiri_dadi;
    std::vector<int> giocatori;

    // Esegui 4 tiri di dadi
    for (int i = 0; i < 4; ++i) {
        tiri_dadi.push_back(dadi.lancio());
        giocatori.push_back(i + 1);
    }

    // Trova il massimo tra i tiri
    int massimo = *std::max_element(tiri_dadi.begin(), tiri_dadi.end());

    // Trova i giocatori che hanno ottenuto il massimo
    std::vector<int> giocatori_con_massimo;
    for (int i = 0; i < 4; ++i) {
        if (tiri_dadi[i] == massimo) {
            giocatori_con_massimo.push_back(giocatori[i]);
        }
    }


    if (giocatori_con_massimo.size() > 1) {
        std::cout << "Spareggio tra i giocatori: ";
        for (int giocatore : giocatori_con_massimo) {
            std::cout << giocatore << " ";
        }
        std::cout << std::endl;

         giocatori.erase(std::remove_if(giocatori.begin(), giocatori.end(),
                          [&giocatori_con_massimo](int giocatore) {
                              return std::find(giocatori_con_massimo.begin(),
                                               giocatori_con_massimo.end(),
                                               giocatore) != giocatori_con_massimo.end();
                          }),
            giocatori.end());

        tiri_dadi.clear();
        for (int i = 0; i < giocatori_con_massimo.size(); ++i) {
            tiri_dadi.push_back(dadi.lancio());
        }

        // Trova nuovamente i giocatori che hanno ottenuto il massimo
        massimo = *std::max_element(tiri_dadi.begin(), tiri_dadi.end());
        giocatori_con_massimo.clear();
        for (int i = 0; i < giocatori.size(); ++i) {
            if (tiri_dadi[i] == massimo) {
                giocatori_con_massimo.push_back(giocatori[i]);
            }
        }
    }

    // Ordina gli indici dei giocatori in base al dado più alto
    std::sort(giocatori.begin(), giocatori.end(), [&tiri_dadi](int a, int b) {
        return tiri_dadi[a - 1] > tiri_dadi[b - 1];
    });

    return giocatori;
}


Player* Game::get_player_from_index(int n) {
    for (int i=0; i<giocatori.size();i++) {
        if (giocatori[i]->get_nome() == n) {
            return giocatori[i];
        }
    }
    return nullptr;
}//get_player_from_index

void Game::intro() {
    std::vector<int> ordine= order_players();
    std::sort(giocatori.begin(), giocatori.end(), [&](Player* a, Player* b) {
        int indice_a = a->get_nome();
        int indice_b = b->get_nome();
        return std::find(ordine.begin(), ordine.end(), indice_a) < std::find(ordine.begin(), ordine.end(), indice_b);
    });


    // LLL aggiornerei logger per avvisare dell'ordine dei giocatori
}

void Game::turno_robot(Player* pippo){
    Dadi d;
    ////////////LOGGER----->INIZIO TURNO ROBOT
    std::cout<<"giocatore "<<pippo->get_nome()<< " inizia il turno"<<std::endl ;
    move_player(pippo);
    ////////////LOGGER----->MOVIMENTO ROBOT

    //casella angolare, non faccio niente e il turno termina
    if(board[pippo->get_position().get_x()][pippo->get_position().get_y()].is_angolo()){
        //LOGGER---> FINE TURNO
    }
    //terreno senza proprietario, posso comprare il terreno
    else if(board[pippo->get_position().get_x()][pippo->get_position().get_y()].get_owner()==0 &&
            board[pippo->get_position().get_x()][pippo->get_position().get_y()].is_terreno()){
        //LOGGER-->
        if(d.scelta_percento()){
            if(pippo->get_budget()>= board[pippo->get_position().get_x()][pippo->get_position().get_y()].price()){

            pippo->paga(board[pippo->get_position().get_x()][pippo->get_position().get_y()].price());
            board[pippo->get_position().get_x()][pippo->get_position().get_y()].set_owner(pippo->get_nome());

                std::cout<<"giocatore "<<pippo->get_nome()<< " compra terreno"<<std::endl ;
            }
            else{
                ///LOGGER FINE TURNO
                std::cout<<"giocatore "<<pippo->get_nome()<< " finisce il turno"<<std::endl ;

            }
        }
        else   {
            ///LOGGER FINE TURNO
            std::cout<<"giocatore "<<pippo->get_nome()<< " finisce il turno"<<std::endl ;

        }
    }
    //terreno di proprietà, posso migliorare a casa
    else if(board[pippo->get_position().get_x()][pippo->get_position().get_y()].get_owner()== pippo->get_nome() &&
            board[pippo->get_position().get_x()][pippo->get_position().get_y()].is_terreno()){
        //LOGGER-->
        if(d.scelta_percento()){
            if(pippo->get_budget()>= board[pippo->get_position().get_x()][pippo->get_position().get_y()].price()){
                pippo->paga(board[pippo->get_position().get_x()][pippo->get_position().get_y()].price());
                board[pippo->get_position().get_x()][pippo->get_position().get_y()].upgrade();
                                std::cout<<"giocatore "<<pippo->get_nome()<< " migliora terreno in casa"<<std::endl ;

            }
            else{
                ///LOGGER FINE TURNO
                                std::cout<<"giocatore "<<pippo->get_nome()<< " finisce il turno"<<std::endl ;

            }
        }
        else   {
            ///LOGGER FINE TURNO
                            std::cout<<"giocatore "<<pippo->get_nome()<< " finisce il turno"<<std::endl ;

        }
    }
    //terreno di proprietà, posso migliorare ad albergo
    else if(board[pippo->get_position().get_x()][pippo->get_position().get_y()].get_owner()== pippo->get_nome() &&
            board[pippo->get_position().get_x()][pippo->get_position().get_y()].is_casa()){
        //LOGGER-->
        if(d.scelta_percento()){
            if(pippo->get_budget()>= board[pippo->get_position().get_x()][pippo->get_position().get_y()].price()){
            pippo->paga(board[pippo->get_position().get_x()][pippo->get_position().get_y()].price());
            board[pippo->get_position().get_x()][pippo->get_position().get_y()].upgrade();
                            std::cout<<"giocatore "<<pippo->get_nome()<< " migliora casa in albergo"<<std::endl ;

            }
            else{
                ///LOGGER FINE TURNO
                                std::cout<<"giocatore "<<pippo->get_nome()<< " finisce il turno"<<std::endl ;

            }
        }
        else   {
            ///LOGGER FINE TURNO
                            std::cout<<"giocatore "<<pippo->get_nome()<< " finisce il turno"<<std::endl ;

        }
    }
    //casa di un altro giocatore, pago il pernottamento
    else if(board[pippo->get_position().get_x()][pippo->get_position().get_y()].get_owner() != pippo->get_nome() &&
            board[pippo->get_position().get_x()][pippo->get_position().get_y()].is_casa() || board[pippo->get_position().get_x()][pippo->get_position().get_y()].is_albergo()){
        //LOGGER-->
            if(pippo->get_budget()>= board[pippo->get_position().get_x()][pippo->get_position().get_y()].price()){

            //pippo paga a giocatore 2, giocatore 2 riceve
            pippo->paga(board[pippo->get_position().get_x()][pippo->get_position().get_y()].price());
            get_player_from_index(board[pippo->get_position().get_x()][pippo->get_position().get_y()].get_owner())->ricevi(board[pippo->get_position().get_x()][pippo->get_position().get_y()].price());
                            std::cout<<"giocatore "<<pippo->get_nome()<< " paga pernottamento"<<std::endl ;

            }
            else{
                ///LOGGER GAME OVER ROBOT
                                std::cout<<"giocatore "<<pippo->get_nome()<< " eliminato"<<std::endl ;

                giocatore_over(pippo);
                get_player_from_index(board[pippo->get_position().get_x()][pippo->get_position().get_y()].get_owner())->ricevi(pippo->get_budget());

            }

    }

//LOGGER FINE TURNO

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
std::vector<Player*> Game::vincitori() {
    std::vector<Player*> vincitori;
        if (giocatori.empty()) {
        return vincitori;
    }

    int massimo = giocatori[0]->get_budget();
    for (int i = 1; i < giocatori.size(); i++) {
        if (giocatori[i]->get_budget() > massimo) {
            massimo = giocatori[i]->get_budget();
        }
    }
    for (int i = 0; i < giocatori.size(); i++) {
        if (giocatori[i]->get_budget() == massimo) {
            vincitori.push_back(giocatori[i]);
        }
    }

    return vincitori;
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
    int num=passi;
    while(passi>0){
        pippo->set_position(pippo->get_position().next_position());
        pippo->add_steps(1);
        if(pippo->get_steps()%28 ==0){
            pippo->ricevi(20);
        }
        passi--;
    }
    std::cout<<"il giocatore "<<pippo->get_nome()<<" si e' mosso di "<<num<<" passi"<<std::endl;
}

/*
Game_Umano::Game_Umano() : Game(n) {
}
*/

