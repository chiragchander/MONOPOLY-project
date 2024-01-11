#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
#include <fstream>
using namespace std;

class Logger{
ofstream fout;
string fn;
public:
Logger();
Logger(string s);
void lan_dadi(int g, int d);
void posizione(int g, int c);
void acq_ter(int g, int c);
void costr_casa(int g, int c);
void costr_alb(int g, int c);
void pag_ped(int g1, int g2, int f, int c);
void vince(int g);
void elimin(int g);
void fine_turno(int g);
void inizio_turno(int g);
void pas_via(int g);

};//Logger

#endif //LOGGER_H
