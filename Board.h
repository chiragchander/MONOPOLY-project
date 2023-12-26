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
	int count;/* servirà per la funzione move per
	tener conto dei passi fatti e incrementare i fiorini
	quando si fa un giro completo */

public:
	Board();
    void print_board() const;

};//Board


std::ostream& operator<<(std::ostream& os, Board valore);

#endif //BOARD_H
