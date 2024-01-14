//chirag chander
#include "../include/Board.h"
#include "../include/Casella.h"
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
    //scelta casuale di un indice che sar� il punto di partenza
    int start_index = std::rand() % angles.size();
    std::pair<int, int> start = angles[start_index];
    board[start.first][start.second] = Casella(1,0, Posizione(start.first, start.second));
    starting_cell= board[start.first][start.second];

    for(int i=0; i<4; i++){
        if(angles[i] != angles[start_index]){
            board[angles[i].first][angles[i].second] = Casella(0,0, Posizione(angles[i].first, angles[i].second) );
        }
    }
    //riempimento caselle vuote centrali
    for(int i=1; i<row_size -1; i++){
        for(int j=1; j<col_size-1; j++)
            board[i][j] = Casella(0,-1, Posizione(i, j));
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

    //assegnamento della propriet� per ogni cella laterale
    for (const std::pair<int, int>& pos : lateral_cells) {
        int x = pos.first;
        int y = pos.second;

        if (e > 0 && board[x][y].vuota()) {
            board[x][y] = Casella(2,1, Posizione(x,y));
            e--;
        } else if (s > 0 && board[x][y].vuota()) {
            board[x][y] = Casella(3,1, Posizione(x,y));
            s--;
        } else if (l > 0 && board[x][y].vuota()) {
            board[x][y] = Casella(4,1, Posizione(x,y));
            l--;
        }
    }
}//Board

std::ostream& operator<<(std::ostream& os, Board valore){
    valore.print_board();
    return os;
    }//operator<<


void Board::move(Casella& c, int n) {
    while (n > 0) {
        c.set_position(c.get_position().next_position() );
        count++;
        n--;
    }
////////////////////////////////////////////////////////////////////////////
    //si pu� togliere il cout
    std::cout<<"fatti "<<count<<" passi"<<std::endl;
}//move

void Board::print_line(int n) {
    if(n == 0) {
        std::cout << "     " << "1" << "       " << "2" << "       " << "3" << "       " << "4" << "       " << "5" << "       " << "6" << "       " << "7" <<
        "       " << "8" << std::endl;
    }
    else {
        std::cout << alphabet[n - 1] << "   ";
        for(int i = 0; i < col_size; i++) {
            if(board[i][n-1].is_central_cell()) std::cout<<"        ";
            else {
                std::vector<int> test;
                std::vector<int> giocatori_presenti_nella_casella; //in cui faccio push_back i giocatori nella casella
                /*
                QUESTO ALGORITMO VERRA' REALIZZATO DIRETTAMENTE NELLA CLASSE GAME, IN QUESTA CLASSE BASTA CHE VENGA STAMPATO IL TABELLONE
                SENZA GIOCATORI
                -da sostituire con un vettore di Player che indica i giocatori presenti nel tabellone
                -invece di if(test.size()) devo valutare il numero di giocatori nella casella, tipo con un for
                 in cui vedo se la posizione di board[i][n-1] � uguale alla posizione del giocatore */

                if(test.size()==0){
                    switch(board[i][n-1].length()){
                    case 0:
                        std::cout <<"|      |";
                        break;
                    case 1:
                        std::cout <<"|"<< board[i][n-1]<<"     |";
                        break;
                    case 2:
                        std::cout <<"|"<< board[i][n-1]<<"    |";
                        break;
                    }
                }
                else{
                    switch(giocatori_presenti_nella_casella.size()){ /* test.size() da sostituire con una funzione che vede quanti giocatori
                         sono presenti nella cella corrente, qui usato solo per valutare la logica della funzione  */
                    case 1:
                        std::cout <<"|"<< board[i][n-1]<<test[0]<<"    |";
                        break;
                    case 2:
                        std::cout <<"|"<< board[i][n-1]<<test[0]<<test[1]<<"   |";
                        break;
                    case 3:
                        std::cout <<"|"<< board[i][n-1]<<test[0]<<test[1]<<test[2]<<"  |";
                        break;
                    case 4:
                        std::cout <<"|"<< board[i][n-1]<<test[0]<<test[1]<<test[2]<<test[3]<<" |";
                        break;
                    }
                }
        }
        }
        std::cout << std::endl;
    }
}//print_line



void Board::print_board(){
    for(int i=0; i<=row_size; i++){
        print_line(i);
    }
}//print_board


