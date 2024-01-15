//chirag chander
#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include "Casella.h"

class Board {
private:
	std::vector<std::vector<Casella>> board; //Matrice 8x8 che rappresenta il vettore
    std::vector<std::pair<int , int >> angles; //Coppie di interi che indicano le coordinate delle caselle angolari
    const std::vector<char> alphabet{'A','B','C','D','E','F','G','H'}; //Vettore di caratteri usato per la stampa degli indici delle ordinate
    const int row_size=8; //Dimensione delle righe
    const int col_size=8; //Dimensione delle righe
	Casella starting_cell; //Casella iniziale

public:
	Board(); //Costruttore tabellone
    void print_line(int n); //Stampa una singola riga del tabellone
    void print_board();  //Stampa tabellone
    Casella get_starting_cell()const {return starting_cell;}; //Restituisce la casella iniziale
    int get_starting_row(){return starting_cell.get_position().get_x();}; //Restituisce la posizione x della casella iniziale
    int get_starting_col(){return starting_cell.get_position().get_y();}; //Restituisce la posizione y della casella iniziale
    std::vector<std::vector<Casella>> get_board(){return board;}; //Restituisce una matrice che rappresenta il tabellone

};//Board

std::ostream& operator<<(std::ostream& os, Board valore);//Overloading operatore <<

#endif //BOARD_H
