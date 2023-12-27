//chirag chander
#include "Casella.h"

Casella::Casella() : type(0), lvl(0) {}

Casella::Casella(int t,int l, int row, int col):type(t), lvl(l), x(row), y(col){}

void Casella::set_position(int row, int col) {
        x=row;
        y=col;
    }//set_position

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
    if (lvl == 0) return -1; // una casella angolare non può essere acquistata

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
        x=other.get_x();
        y=other.get_y();
    }
    return *this;
}//operator=

bool Casella::operator==(const Casella other){
    return (lvl== other.get_lvl() && type==other.get_type());
}//operator==


void Casella::print_position(){
        const std::vector<char> alphabet{'A','B','C','D','E','F','G','H'};
        std::cout<<alphabet[get_x()]<<get_y()+1;
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
    return 0; // Default
}

void Casella::movement(){
    int current_row= x;
    int current_col= y;
     if(current_row==0 && current_col==0)
        current_row=1;
     else if(current_row==1 && current_col==0)
        current_row=2;
     else if(current_row==2 && current_col==0)
        current_row=3;
     else if(current_row==3 && current_col==0)
        current_row=4;
     else if(current_row==4 && current_col==0)
        current_row=5;
     else if(current_row==5 && current_col==0)
        current_row=6;
     else if(current_row==6 && current_col==0)
        current_row=7;
     else if(current_row==7 && current_col==0)
        current_col=1;
     else if(current_row==7 && current_col==1)
        current_col=2;
     else if(current_row==7 && current_col==2)
        current_col=3;
     else if(current_row==7 && current_col==3)
        current_col=4;
     else if(current_row==7 && current_col==4)
        current_col=5;
     else if(current_row==7 && current_col==5)
        current_col=6;
     else if(current_row==7 && current_col==6)
        current_col=7;
     else if(current_row==7 && current_col==7)
        current_row=6;
     else if(current_row==6 && current_col==7)
        current_row=5;
     else if(current_row==5 && current_col==7)
        current_row=4;
     else if(current_row==4 && current_col==7)
        current_row=3;
     else if(current_row==3 && current_col==7)
        current_row=2;
     else if(current_row==2 && current_col==7)
        current_row=1;
     else if(current_row==1 && current_col==7)
        current_row=0;
     else if(current_row==0 && current_col==7)
        current_col=6;
     else if(current_row==0 && current_col==6)
        current_col=5;
     else if(current_row==0 && current_col==5)
        current_col=4;
     else if(current_row==0 && current_col==4)
        current_col=3;
     else if(current_row==0 && current_col==3)
        current_col=2;
     else if(current_row==0 && current_col==2)
        current_col=1;
     else if(current_row==0 && current_col==1)
        current_col=0;
}//movement





