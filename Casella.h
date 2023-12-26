#ifndef CASELLA_H
#define CASELLA_H

#include <iostream>

class Casella {
private:
    int type; // Type è un intero che va da 0 a 4 {0 = vuota, 1 = partenza, 2 = economica, 3 = standard, 4 = lusso}
    int lvl;  // Lvl è un intero che va da 0 a 3 {0 = casella angolare, 1= terreno , 2 = con casa, 3 = con albergo}

public:
    Casella();       // Costruttore che potrebbe anche non servire
    Casella(int t);  // Cotruttore
    Casella(int t,int l); //Costruttore generico

    int get_type() const { return type; } // Restituisce il livello della casella
    int get_lvl() const { return lvl; }   // Restituisce il livello della casella

    void set_type(int new_type) { type = new_type; } // Assegna un tipo nuovo alla casella (forse non servirà)
    void set_lvl(int new_lvl) { lvl = new_lvl; }      // Assegna un livello nuovo alla casella

    int price() const;   // Restituisce il prezzo per l'acquisto del terreno e se gia acquistato per miglioramento a casa e albergo
    int revenue() const; // Restituisce il costo del pernottamento, 0 se solo terreno
    bool is_start() const; //Verifica se una cella è una cella di inizio
    bool vuota() const;
    bool is_central_cell() const;
    Casella& operator=(const Casella& other);// Overloading Operatore =
    Casella operator==(const Casella other);//Overloading Operatore ==
};
std::ostream& operator<<(std::ostream& os, const Casella& c);

#endif
