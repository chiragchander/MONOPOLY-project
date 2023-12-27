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
    std::vector<char> alphabet{'A','B','C','D','E','F','G','H'};
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
    char get_current_row() {return alphabet[current_row];};
    int get_current_col() {return current_col+1;};
    int laps(){return (count/28);}
};//Board


std::ostream& operator<<(std::ostream& os, Board valore);

#endif //BOARD_H




/*

| P  || L  || L  || E  || L  || E  || S  ||    |
| S  |                                    | S  |
| L  |                                    | E  |
| E  |                                    | E  |
| S  |                                    | S  |
| E  |                                    | S  |
| L  |                                    | S  |
|    || S  || E  || L  || S  || S  || E  ||    |

*/
