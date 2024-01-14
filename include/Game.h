// Lovato Emanuele

#ifndef GAME_H
#define GAME_H
#include <vector>
#include "Player.h"

class Game {
protected:
    int turno = 1;
    std::vector<Player> giocatori;
    // LLL aggiungerei un oggetto Logger per dare in gestione gli eventi da stampare
public:
    Game();
    int get_turno() const { return turno; }
    void next_turno();
    void intro();
    void add_giocatore(Player* pippo);
    void del_giocatore(Player* pippo);
    void giocatore_over(Player* pippo);
    bool fine_gioco();
    Player* vincitore();
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