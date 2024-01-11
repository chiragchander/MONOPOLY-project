//chirag chander
#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include "Casella.h"
// #include "Player.h"

class Board {
private:
	std::vector<std::vector<Casella>> board;
    std::vector<std::pair<int , int >> angles;
    const std::vector<char> alphabet{'A','B','C','D','E','F','G','H'};
    int row_size=8;
    int col_size=8;
	int count=0;

	Casella starting_cell;
	// std::vector<Player> players;
	void print_line(int n) ;

public:
	Board();
    void print_board();
    void move(Casella& c, int n);
    Casella get_starting_cell()const {return starting_cell;};
    int get_starting_row(){return starting_cell.get_x();};
    int get_starting_col(){return starting_cell.get_y();};
    int laps(){return (count/28);};

    /*
    void add_player(Player& p)  {players.push_back(p)};

    */
    void print_test();

};//Board


std::ostream& operator<<(std::ostream& os, Board valore);

#endif //BOARD_H
