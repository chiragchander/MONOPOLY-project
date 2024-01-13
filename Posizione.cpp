//chirag chander
#include "Posizione.h"

Posizione::Posizione():x(0),y(0) {}
Posizione::Posizione(int pos_x, int pos_y):x(pos_x), y(pos_y) {}

void Posizione::set_position(int pos_x, int pos_y){
    x=pos_x;
    y=pos_y;
}//set_position

void Posizione::print_position(){
    std::cout<<"("<<x<<","<<y<<")";
}//print_position


Posizione Posizione::next_position() {
    int nextX = x;
    int nextY = y;

    if (x == 0 && y < 7)
        nextY++;
    else if (y == 7 && x < 7)
        nextX++;
    else if (x == 7 && y > 0)
        nextY--;
    else if (y == 0 && x > 0)
        nextX--;

    return Posizione(nextX, nextY);
}//next_position

Posizione& Posizione::operator=(const Posizione& other) {
    if (this != &other) { // Verifica autoassegnazione
        x=other.get_x();
        y=other.get_y();
    }
    return *this;
}//operator=

bool Posizione::operator==(const Posizione other){
    return (x == other.get_x() && y == other.get_y());
}//operator==

std::ostream& operator<<(std::ostream& os, Posizione pos){
        return os <<"("<<pos.get_x()<<";"<<pos.get_y()<<")";
}//operator<<
