//chirag chander
#include "../include/Casella.h"
#include "../include/Posizione.h"

Casella::Casella() : type(0), lvl(0) {}

Casella::Casella(int t,int l, Posizione pos):type(t), lvl(l), position(pos){}


int Casella::revenue() const {
    if (lvl == 0 || type == 1) return 0; // una casella angolare o un terreno non ha costo di pernottamento

    if (lvl == 2) {
        // costo pernottamento in casa
        if (type == 2) return 2;
        if (type == 3) return 4;
        if (type == 4) return 7;
    }

    if (lvl == 3) {
        // costo pernottamento in albergo
        if (type == 2) return 4;
        if (type == 3) return 8;
        if (type == 4) return 14;
    }

    return 0;
}//revenue

int Casella::price() const {
    if (lvl == 0) return -1; // una casella angolare non pu� essere acquistata

    if (lvl == 1) {
        // costo acquisto terreno
        if (type == 2) return 6;
        if (type == 3) return 10;
        if (type == 4) return 20;
    }

    if (lvl == 2) {
        // costo costruzione casa
        if (type == 2) return 3;
        if (type == 3) return 5;
        if (type == 4) return 10;
    }

    if (lvl == 3) {
        // costo migioramento di una casa in albergo
        if (type == 2) return 3;
        if (type == 3) return 5;
        if (type == 4) return 10;
    }

    return -1;
}//price

std::ostream& operator<<(std::ostream& os, const Casella& c) {

    if(c.get_type()==0 && (c.get_lvl()== -1 || c.get_lvl() == 0 )){
        return os<<" ";
    }
    else if(c.get_type() == 1 && c.get_lvl() == 0) {
            return os << "P";
    } else if (c.get_lvl() == 1) {
        if (c.get_type() == 2) return os << "E";
        if (c.get_type() == 3) return os << "S";
        if (c.get_type() == 4) return os << "L";
    } else if (c.get_lvl() == 2) {
        if (c.get_type() == 2) return os << "E*";
        if (c.get_type() == 3) return os << "S*";
        if (c.get_type() == 4) return os << "L*";
    } else if (c.get_lvl() == 3) {
        if (c.get_type() == 2) return os << "E^";
        if (c.get_type() == 3) return os << "S^";
        if (c.get_type() == 4) return os << "L^";
    }

    return os;
}//operator<<

bool Casella::is_start() const{
    if(type==1 && lvl==0) return true;
    return false;
}//is_start

bool Casella::vuota() const{
    if(lvl== 0 && type==0) return true;
    return false;
}//vuota

bool Casella::is_central_cell() const{
    if(lvl== -1 && type==0) return true;
    return false;
}//is_central_cell

Casella& Casella::operator=(const Casella& other) {
    if (this != &other) { // Verifica autoassegnazione
        type = other.type;
        lvl = other.lvl;
        position.set_position(other.get_position().get_x(), other.get_position().get_y() );
    }
    return *this;
}//operator=

bool Casella::operator==(const Casella& other) {
    return (position.get_x() == other.get_position().get_x()) && (position.get_y() == other.get_position().get_y());
}//operator==


void Casella::print_position(){
        const std::vector<char> alphabet{'A','B','C','D','E','F','G','H'};
        std::cout<<alphabet[position.get_x()]<<position.get_y() +1;
}//print_position

void Casella::upgrade(){
        if(lvl>=1 && lvl<3)
            lvl++;
        else std::cout<<"NON E' POSSIBILE MIGLIORARE LA CASELLA"<<std::endl;

}//upgrade


int Casella::length() const {
    if (get_lvl() == 1) {
        return 1;
    } else if (get_lvl() == 2 || get_lvl() == 3) {
        return 2;
    }
    return 0;
}//length

void Casella::set_owner(int player_index){
    owner=player_index;
}//set_owner




