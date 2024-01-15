// Lovato Emanuele
#include "../include/Player.h"
#include "../include/Casella.h"

Player::Player(int n)
    : nome{n}, budget{100}, vivo{true}, proprie{nullptr} {

}

bool Player::povero() {
    return (budget < 1);
}

void Player::paga(int monete) {
    budget -= monete;
}

void Player::ricevi(int monete) {
    budget += monete;
}

void Player::add_steps(int n){
    passi +=n;
}

void Player::print_proprie(){
    if(proprie[0]== nullptr){
        std::cout<<"---"<<std::endl;
    }
    else{
        std::vector<Casella*> celle= get_proprie();
        for(int i=0; i<celle.size(); i++){
            celle[i]->print_position();
            std::cout<<" ";
        }
        std::cout<<std::endl;
    }

}


bool Player::compra_casella(Casella* c) {
    int costo = c->price();     // Costo della casella da acquistare
    if((budget - costo) > 0) {
        proprie.push_back(c);   // Inserisco tale casella tra quelle possedute.
        c->set_owner(nome);     // Assegno all'elemento owner nella casella il nome del player.
        paga(costo);            // Pago il costo della casella.
        return true;    // Casella acquistata
    }
    else return false;   // In caso il budget non sia sufficiente, non si acquista e ritorna falso.
}
