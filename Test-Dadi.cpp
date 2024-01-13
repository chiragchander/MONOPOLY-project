// Lovato Emanuele

#include "Dadi.h"

int main(void) {
    Dadi ddd;
    std::cout << "Lancio: " << ddd.lancio() << "\n";
    std::cout << ddd;
    std::cout << "Attuale: " << ddd.attuale() << "\n";
    std::cout << "Lancio: " << ddd.lancio() << "\n";
    std::cout << ddd;
    ddd.stampa_quadro();

    return 0;
}



