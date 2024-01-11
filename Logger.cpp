#include <iostream>
#include <fstream>
#include "Logger.h"
using namespace std;

Logger::Logger(string s) {
fn = s;
fout.open(fn);
fout.close();
}

Logger::Logger(){
fn = "log.txt";
fout.open(fn);
fout.close();
}

void Logger::lan_dadi(int g, int d) {
string s;
s = "- Giocatore " + to_string(g) + " ha tirato i dadi ottenendo un valore di " + to_string(d);
cout<<s<<endl;
fout.open(fn, ios::app);
fout<<s<<endl;
fout.close();
return;
}

void Logger::posizione(int g, int c) {
string s;
s = "- Giocatore " + to_string(g) + " è arrivato alla casella " + to_string(c);
cout<<s<<endl;
fout.open(fn, ios::app);
fout<<s<<endl;
fout.close();
return;
}

void Logger::acq_ter(int g, int c) {
string s;
s = "- Giocatore " + to_string(g) + " ha acquistato il terreno " + to_string(c);
cout<<s<<endl;
fout.open(fn, ios::app);
fout<<s<<endl;
fout.close();
return;
}

void Logger::costr_casa(int g, int c) {
string s;
s = "- Giocatore " + to_string(g) + " ha costruito una casa sul terreno " + to_string(c);
cout<<s<<endl;
fout.open(fn, ios::app);
fout<<s<<endl;
fout.close();
return;
}

void Logger::costr_alb(int g, int c) {
string s;
s = "- Giocatore " + to_string(g) + " migliorato una casa in albergo sul terreno " + to_string(c);
cout<<s<<endl;
fout.open(fn, ios::app);
fout<<s<<endl;
fout.close();
return;
}

void Logger::pag_ped(int g1, int g2, int f, int c) {
string s;
s = "- Giocatore " + to_string(g1) + " ha pagato " + to_string(f) + " fiorini a giocatore " + to_string(g2) + " per pernottamento nella casella " + to_string(c);
cout<<s<<endl;
fout.open(fn, ios::app);
fout<<s<<endl;
fout.close();
return;
}

void Logger::vince(int g) {
string s;
s = "- Giocatore " + to_string(g) + " ha vinto la partita";
cout<<s<<endl;
fout.open(fn, ios::app);
fout<<s<<endl;
fout.close();
return;
}

void Logger::elimin(int g) {
string s;
s = "- Giocatore " + to_string(g) + " è stato eliminato";
cout<<s<<endl;
fout.open(fn, ios::app);
fout<<s<<endl;
fout.close();
return;
}

void Logger::fine_turno(int g) {
string s;
s = "- Giocatore " + to_string(g) + " ha finito il turno";
cout<<s<<endl;
fout.open(fn, ios::app);
fout<<s<<endl;
fout.close();
return;
}

void Logger::inizio_turno(int g) {
string s;
s = "- Giocatore " + to_string(g) + " ha iniziato il turno";
cout<<s<<endl;
fout.open(fn, ios::app);
fout<<s<<endl;
fout.close();
return;
}

void Logger::pas_via(int g) {
string s;
s = "- Giocatore " + to_string(g) + " è passato dal via e ha ritirato 20 fiorini";
cout<<s<<endl;
fout.open(fn, ios::app);
fout<<s<<endl;
fout.close();
return;
}

