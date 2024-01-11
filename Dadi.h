// Lovato Emanuele

#ifndef DADI_H
#define DADI_H
#include <iostream>
#include <cstdlib>  // rand() & srand()
#include <ctime>    // time()

class Dadi {
private:
    int dado1 = 1;
    int dado2 = 1;
    int somma = 0;
public:
    Dadi();
    int lancio();
    int attuale() const { return somma; }
    int get_dado1() const { return dado1; }
    int get_dado2() const { return dado2; }
    void stampa_quadro();
};
std::ostream& operator<<(std::ostream& os, const Dadi& d);

#endif
