//chirag chander
#ifndef POSIZIONE_H
#define POSIZIONE_H
#include <iostream>

class Posizione {
private:
    int x; //Indica la posizione x
    int y; //Indica la posizione y
public:
    Posizione();
    Posizione(int pos_x,int pos_y); //Costruttore che  anche la posizione

    int get_x() const {return x;};
    int get_y() const {return y;};

    void set_position(int pos_x, int pos_y);
    void print_position();


    Posizione& operator=(const Posizione& other);// Overloading Operatore =
    bool operator==(const Posizione other);//Overloading Operatore ==
};
    std::ostream& operator<<(std::ostream& os, Posizione pos);

#endif //POSIZIONE_H
