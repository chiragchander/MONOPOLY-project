//chirag chander
#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include "Casella.h"

class Board {
private:
	std::vector<std::vector<Casella>> board;
    std::vector<std::pair<int , int >> angles;
    int row_size=8;
    int col_size=8;
    int current_row;
    int current_col;
	int count=0;

public:
	Board();
    void print_board() const;
    void movement();
    void move(int n);
    int get_current_row() {return current_row;};
    int get_current_col() {return current_col;};
    int laps(){return (count/28);}
};//Board


std::ostream& operator<<(std::ostream& os, Board valore);

#endif //BOARD_H
