#ifndef CASELLA_H
#define CASELLA_H

#include <iostream>
#include <vector>
#include "Posizione.h"

class Casella {
private:
    int type; // Type è un intero che va da 0 a 4 {0 = vuota, 1 = partenza, 2 = economica, 3 = standard, 4 = lusso}
    int lvl;  // Lvl è un intero che va da 0 a 3 {0 = casella angolare, 1= terreno , 2 = con casa, 3 = con albergo}
    Posizione position; //Indica la posizione della casella
    int owner=0; //Variabile che indica il proprietario della cella, il valore equivale all'indice del giocatore proprietario
public:

    Casella();       // Costruttore che potrebbe anche non servire
    Casella(int t,int l, Posizione pos); //Costruttore che assegna anche la posizione a una casella

    int get_type() const { return type; } // Restituisce il livello della casella
    int get_lvl() const { return lvl; }   // Restituisce il livello della casella

    void set_type(int new_type) { type = new_type; } // Assegna un tipo nuovo alla casella (forse non servirà)
    void upgrade(); // Migliora, se possibile, il livello della casella

    int price() const;   // Restituisce il prezzo per l'acquisto del terreno e se gia acquistato per miglioramento a casa e albergo
    int revenue() const; // Restituisce il costo del pernottamento, 0 se solo terreno
    bool is_start() const; //Verifica se una cella è una cella di inizio
    bool vuota() const; //Verifica se una cella PERCORRIBILE è vuota
    bool is_central_cell() const; //Verifica che una cella NON sia percorribile
    Casella& operator=(const Casella& other);// Overloading Operatore =
    bool operator==(const Casella& other);//Overloading Operatore ==
    int length() const; //Restituisce la lunghezza della Casella
    void print_position(); //Stampa la posizione della cella usando come indice della ascissa un numero da 1 a 8, mentre come indice dell'ordinata una lettera da A a H
    Posizione get_position() const {return position;}; //Restituisce la posizione della cella
    void set_position(Posizione pos) {position=pos;}

    void set_owner(int player_index);//Assegna alla cella l'indice del proprietario
    int get_owner() {return owner;};//Resitituisce l'indice del giocatore proprietario della cella

};
std::ostream& operator<<(std::ostream& os, const Casella& c);//Overloading operatore<<

#endif
