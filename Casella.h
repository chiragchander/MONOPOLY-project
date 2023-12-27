#ifndef CASELLA_H
#define CASELLA_H

#include <iostream>
#include <vector>

class Casella {
private:
    int type; // Type è un intero che va da 0 a 4 {0 = vuota, 1 = partenza, 2 = economica, 3 = standard, 4 = lusso}
    int lvl;  // Lvl è un intero che va da 0 a 3 {0 = casella angolare, 1= terreno , 2 = con casa, 3 = con albergo}
    int x;
    int y;
public:
    Casella();       // Costruttore che potrebbe anche non servire
    Casella(int t,int l, int row, int col);

    int get_x()const {return x;};
    int get_y() const {return y;};
    void set_position(int row, int col);
    void print_position();
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
    bool operator==(const Casella other);//Overloading Operatore ==
    int length() const;
    void movement();

};
std::ostream& operator<<(std::ostream& os, const Casella& c);

#endif
