// Lovato Emanuele

#include "../include/Dadi.h"
#include <random>

// Nel costruttore, inserisco il seme per la randomizzazione basata sul tempo.
// Altrimenti i numeri sono pseudo-casuali, ogni ripetizione si giungerebbe al medesimo risultato.
Dadi::Dadi() : gen(std::random_device()()), distribution(1, 6) {

}

// Lancia e genera un nuovo valore attuale, ritornando nel caso possa servire, la somma del nuovo lancio.
int Dadi::lancio() {
    dado1 = distribution(gen);
    dado2 = distribution(gen);
    somma = dado1 + dado2;
    return somma;
}


// Funzione che può essere utilizzata per un output graficamente accettabile in-game.
// Tale stampa va differenziata lievemente tra somme ad una o a due cifre.
void Dadi::stampa_quadro() {
    if(somma/10 < 1) {
        std::cout << "╔═══╗╔═══╗ ╔═══╗\n";
        std::cout << "║ " << dado1 << "+║║+" << dado2 << " ║=║ " << somma << " ║\n";
        std::cout << "╚═══╝╚═══╝ ╚═══╝\n";
    }
    else {
        std::cout << "╔═══╗╔═══╗ ╔════╗\n";
        std::cout << "║ " << dado1 << "+║║+" << dado2 << " ║=║ " << somma << " ║\n";
        std::cout << "╚═══╝╚═══╝ ╚════╝\n";
    }
}

// Overloading operatore <<
std::ostream& operator<<(std::ostream& os, const Dadi& d) {
    return os << "[" << d.get_dado1() << "+" << d.get_dado2() << "]=" << d.attuale() << "\n";
}

// Scelta per giocatore computer in base alla percentuale.
// Al 25% compra il terreno.
bool Dadi::scelta_percento() {
    int percento;
    percento = rand() % 4;
    if(percento == 0) return true;
    else return false;
}
