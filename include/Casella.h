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
    int owner=0; //Variabile che indica il proprietario della casella, il valore equivale all'indice del giocatore proprietario
public:

    Casella();  // Costruttore che potrebbe anche non servire
    Casella(int t,int l, Posizione pos); //Costruttore che assegna anche la posizione a una casella
    int get_type() const { return type; } // Restituisce il tipo della casella
    int get_lvl() const { return lvl; }   // Restituisce il livello della casella
    void set_type(int new_type) { type = new_type; } // Assegna un tipo nuovo alla casella
    void set_lvl(int new_lvl) { lvl = new_lvl; } // Assegna un tipo nuovo alla casella
    void upgrade(); // Migliora, se possibile, il livello della casella
    void set_owner(int player_index);//Assegna alla casella l'indice del proprietario
    int get_owner() {return owner;};//Resitituisce l'indice del giocatore proprietario della casella
    int price() const;   // Restituisce il prezzo per l'acquisto del terreno e se gia acquistato per miglioramento a casa e albergo
    int revenue() const; // Restituisce il costo del pernottamento, 0 se solo terreno
    bool is_start() const; //Verifica se una casella è una casella di inizio
    bool vuota() const; //Verifica se una casella PERCORRIBILE è vuota
    bool is_central_cell() const; //Verifica che una casella NON sia percorribile
    bool is_terreno() {return lvl==1;}  //Restituisce true se la casella è un terreno
    bool is_casa() {return lvl==2;}     //Restituisce true se la casella è una casa
    bool is_albergo()  {return lvl==3;} //Restituisce true se la casella è un albergo
    bool is_angolo()  {return lvl==0;}  //Restituisce true se la casella è angolare
    int length() const; //Restituisce la lunghezza della Casella, 1 se terreno, 2 se casa o albergo
    std::string position_to_string();
    void print_position(); //Stampa la posizione della casella usando come indice della ascissa un numero da 1 a 8, mentre come indice dell'ordinata una lettera da A a H
    Posizione get_position() const {return position;}; //Restituisce la posizione della casella
    void set_position(Posizione pos) {position= pos;}  //Assegna una nuova posizione alla casella
    std::string to_string(); //Restituisce una stringa che rappresenta la posizione della casella
    Casella& operator=(const Casella& other);// Overloading Operatore =
    bool operator==(const Casella& other);//Overloading Operatore ==
};//Casella
std::ostream& operator<<(std::ostream& os, const Casella& c);//Overloading operatore<<

#endif
