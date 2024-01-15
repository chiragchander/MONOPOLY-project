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
    int turno = 1; //Contatore turno
    std::vector<Player*> giocatori;  //Vettore di giocatori
    Board tabellone;    //Tabellone
    std::vector<std::vector<Casella>> board;    //Matrice che rappresenza il tabellone
    const std::vector<char> alphabet{'A','B','C','D','E','F','G','H'}; //Vettore di caratteri usato per gli indici delle ordinate
    void print_gameboard_line(int n);  //Stampa una singola riga del tabellone
    Logger log;//Logger
public:
    Game();//Costruttore
    Game(std::string s);
    int get_turno() const { return turno; }//Restituisce il numero del turno corrente
    void next_turno();//Aumenta di uno il contatore di turni
    void intro();//Inizializza il gioco
    void add_giocatore(Player* pippo);//Aggiunge un giocatore
    void del_giocatore(Player* pippo);//Rimuovi un giocatore
    void giocatore_over(Player* pippo);//Elimina un giocatore
    bool fine_gioco();//Verifica se il gioco è terminato
    std::vector<Player*> vincitori();//Restituisce i giocatori vincitori, se più di uno
    Player* get_giocatori(int n) const { return giocatori[n]; } //Restituisce un giocatore
    void print_gameboard();//Stampa tabellone
    void move_player(Player* pippo);//Movimento giocatore umano
    void move_robot(Player* pippo);//MOvimento giocatore computer
    std::vector<int> order_players();//Restituisce un Vettore di indici di giocatori ordinati casualmente
    Player* get_player_from_index(int n);//Restituisce un giocatore a partire dall'indice
    void turno_robot(Player* pippo);//Regola il turno di un giocatore computer
    void turno_human(Player* pippo);//regoila il turno di un giocatore umano
    std::string centr(std::string s); //Funzione per centrare le caselle nelle stringhe

};

#endif
