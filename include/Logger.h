//luca pianizzola
#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
#include <fstream>
using namespace std;

class Logger{
ofstream fout;
string fn;  //Stringa per contenere il nome del file di log
public:
Logger();  //Costruttore generico
Logger(string s);  //Costruttore con nome del file di log
void lan_dadi(int g, int d); //Log del lancio dei dadi
void posizione(int g, string c);  //Log dello spostamento
void acq_ter(int g, string c); //Log dell'acquisto di un terreno
void costr_casa(int g, string c);  //Log della costruzione di una casa
void costr_alb(int g, string c);  //Log della costruzione di un albergo
void pag_ped(int g1, int g2, int f, string c);  //Log del pagamento di un pernottamento
void vince(int g); //Log del vincitore
void elimin(int g); //Log di un giocatore eliminato
void fine_turno(int g);  //Log della fine di un turno
void inizio_turno(int g);  //Log dell'inizio di un turno
void pas_via(int g);  //Log del passaggio dal via
void ordine_giocatori(vector<int> g);  //Log dell'ordine di gioco
void set_nome_file(string s);  //Funzione per impostare successivamente il nome del file su cui scrivere
void nuovo_f();  //Funzione per ricreare il file di log azzerandone il contenuto

};//Logger

#endif //LOGGER_H
