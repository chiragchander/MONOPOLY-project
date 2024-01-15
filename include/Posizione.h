//chirag chander
#ifndef POSIZIONE_H
#define POSIZIONE_H
#include <iostream>

class Posizione {
private:
    int x;  //Indica la posizione x
    int y;  //Indica la posizione y
public:
    Posizione();    //Costruttore generico
    Posizione(int pos_x,int pos_y);   //Costruttore con assegnamento della posizione
    int get_x() const {return x;};    //Restituisce la posizione x
    int get_y() const {return y;};    //Restituisce la posizione y
    void set_position(int pos_x, int pos_y); //Assegna una nuova posizione dati due valori interi
    void set_position(Posizione pos);        //Assegna una nuova posizione data una variabile di tipo Posizione
    void print_position() const;  //Stampa la posizione nel formato (x,y)
    std::string position_to_string();   //Restituisce una stringa che rappresenta la posizione espressa usando come indice della ascissa un numero da 1 a 8, mentre come indice dell'ordinata una lettera da A a H
    Posizione next_position();   //Restituisce la posizione successiva
    Posizione& operator=(const Posizione& other);  //Overloading Operatore =
    bool operator==(const Posizione other);  //Overloading Operatore ==
};//Posizione
    std::ostream& operator<<(std::ostream& os, Posizione pos);  //Overloading Operatore <<

#endif //POSIZIONE_H
