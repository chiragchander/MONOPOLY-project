// Lovato Emanuele

#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "Posizione.h"
//#include "Casella.h"
class Casella;
class Player {
private:
    int nome;   // Nome è l'indice del giocatore, che stante le specifiche sarà un valore da 1 a 4.
    int budget = 100;
    std::vector<Casella*> proprie;         // Serve a legare le casella possedute al giocatore che le possiede
    bool vivo = true;   // @@@ Serve o basta povero()
    int passi; //Indica i passi effettuati dal giocatore
    Posizione position;
public:
    Player(int n);
    int get_nome() const { return nome; }       // LLL serve nel logger per stampare
    int get_budget() const { return budget; }
    bool get_vivo() const { return vivo; }
    int get_steps(){return passi;}
    void add_steps(int n);
    bool povero();          // Se budget è minore di 1 ritorna true.
    void paga(int monete);
    void ricevi(int monete);
    bool compra_casella(Casella* c);    // Ritorna true se la casella è acquistata, false se non possiede abbastanza soldi
    std::vector<Casella*> get_proprie() { return proprie; }        // LLL questo serve nel logger per stampare le caselle del giocatore
    bool operator==(const Player& other) const {return nome==other.get_nome();}
    Posizione get_position(){return position;}
    void set_position(Posizione pos){ position.set_position(pos);}
};

#endif
