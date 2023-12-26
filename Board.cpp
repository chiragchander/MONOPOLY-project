//chirag chander
#include "Board.h"
#include "Casella.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>

Board::Board(){
    srand((unsigned) time(NULL));//generatore numeri casuali
    board.resize(row_size, std::vector<Casella>(col_size));/*inizializzazione tabellone
                                               con posizione iniziale casuale*/
    //angles rappresenta le posizioni angolari
    std::vector<std::pair<int , int >> angles = {{0, 0}, {0, 7}, {7, 0}, {7, 7}};
    //scelta casuale di un indice che sarà il punto di partenza
    int start_index = std::rand() % angles.size();
    std::pair<int, int> start = angles[start_index];
    board[start.first][start.second] = Casella(1,0);
    for(int i=0; i<4; i++){
        if(angles[i] != angles[start_index]){
            board[angles[i].first][angles[i].second] = Casella();
        }
    }
    //riempimento caselle vuote centrali
    for(int i=1; i<row_size -1; i++){
        for(int j=1; j<col_size-1; j++)
            board[i][j] = Casella(0,-1);
    }
    //riempimento caselle laterali, escluse le caselle angolari
    std::vector<std::pair<int, int>> lateral_cells = {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6},
                                                      {7, 1}, {7, 2}, {7, 3}, {7, 4}, {7, 5}, {7, 6},
                                                      {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0},
                                                      {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}, {6, 7}};
    //funzione che "mescola" il vettore in modo casuale
    std::random_shuffle(lateral_cells.begin(), lateral_cells.end());
    int e = 8;
    int s = 10;
    int l = 6;
    //assegnamento della proprietà per ogni cella laterale
    for (const auto& pos : lateral_cells) {
        int x = pos.first;
        int y = pos.second;

        if (e > 0 && board[x][y].vuota()) {
            board[x][y] = Casella(2);
            e--;
        } else if (s > 0 && board[x][y].vuota()) {
            board[x][y] = Casella(3);
            s--;
        } else if (l > 0 && board[x][y].vuota()) {
            board[x][y] = Casella(4);
            l--;
        }
    }
}//Board

void Board::print_board() const {
    for (int i = 0; i < row_size; ++i) {
        for (int j = 0; j < col_size; ++j) {
                if(board[i][j].is_central_cell()){
                    std::cout<<"     ";
                }
                else {
                    //metto un if, se player position uguale a board[i][j] stampa anche index player
                    std::cout <<"|"<< board[i][j]<<"  |";
                }
            }
        std::cout<<std::endl;
        }
}//print_board



