// Lovato Emanuele
#ifndef GAME_H
#define GAME_H
#include <vector>
#include "Player.h"
#include "Board.h"
#include "Logger.h"
class Casella;

class Game {
private:
    int turno = 1;
    std::vector<Player*> giocatori;
    // LLL aggiungerei un oggetto Logger per dare in gestione gli eventi da stampare
    Board tabellone;
    std::vector<std::vector<Casella>> board;
    const std::vector<char> alphabet{'A','B','C','D','E','F','G','H'};
    void print_gameboard_line(int n);
    Logger log;
public:
    Game();
    int get_turno() const { return turno; }
    void next_turno();
    void intro();
    void add_giocatore(Player* pippo);
    void del_giocatore(Player* pippo);
    void giocatore_over(Player* pippo);
    bool fine_gioco();
    std::vector<Player*> vincitori();
    Player* get_giocatori(int n) const { return giocatori[n]; }
    void print_gameboard();
    void move_player(Player* pippo);
    void move_robot(Player* pippo);
    std::vector<int> order_players();
    Player* get_player_from_index(int n);
    void turno_robot(Player* pippo);

};




/*
class Game_Umano: public Game {
private:
    int play_umano; // da 0 a 3 indica il giocatore umano nell'array lista_play[4]
public:
    Game_Umano();
    int get_pos_umano() const { return play_umano; }
};
*/

#endif
