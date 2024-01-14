// Lovato Emanuele

#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "Casella.h"

class Player {
private:
    int nome;   // Nome è l'indice del giocatore, che stante le specifiche sarà un valore da 1 a 4.
    int budget = 100;
    std::vector<Casella*> proprie;         // serve a legare le casella possedute al giocatore che le possiede
    bool vivo = true;
public:
    Player(int n);
    int get_nome() const { return nome; }       // LLL serve nel logger per stampare
    int get_budget() const { return budget; }
    bool get_vivo() const { return vivo; }
    bool povero();          // Se budget è minore di 1 ritorna true.
    void paga(int monete);
    void ricevi(int monete);
    bool compra_casella(Casella* c);    // Ritorna true se la casella è acquistata, false se non possiede abbastanza soldi
    std::vector<Casella*> get_proprie() { return proprie; }        // LLL questo serve nel logger per stampare le caselle del giocatore
};

#endif