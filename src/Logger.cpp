//luca pianizzola
#include <iostream>
#include <vector>
#include <fstream>
#include "../include/Logger.h"
using namespace std;

Logger::Logger(string s) {
fn = s;
}

Logger::Logger(){
fn = "log.txt";
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

void Logger::posizione(int g, string c) {
string s;
s = "- Giocatore " + to_string(g) + " è arrivato alla casella " + c;
cout<<s<<endl;
fout.open(fn, ios::app);
fout<<s<<endl;
fout.close();
return;
}

void Logger::acq_ter(int g, string c) {
string s;
s = "- Giocatore " + to_string(g) + " ha acquistato il terreno " + c;
cout<<s<<endl;
fout.open(fn, ios::app);
fout<<s<<endl;
fout.close();
return;
}

void Logger::costr_casa(int g, string c) {
string s;
s = "- Giocatore " + to_string(g) + " ha costruito una casa sul terreno " + c;
cout<<s<<endl;
fout.open(fn, ios::app);
fout<<s<<endl;
fout.close();
return;
}

void Logger::costr_alb(int g, string c) {
string s;
s = "- Giocatore " + to_string(g) + " migliorato una casa in albergo sul terreno " + c;
cout<<s<<endl;
fout.open(fn, ios::app);
fout<<s<<endl;
fout.close();
return;
}

void Logger::pag_ped(int g1, int g2, int f, string c) {
string s;
s = "- Giocatore " + to_string(g1) + " ha pagato " + to_string(f) + " fiorini a giocatore " + to_string(g2) + " per pernottamento nella casella " + c;
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

void Logger::ordine_giocatori(vector<int> g) {
string s;
s = "- L'ordine dei Giocatori è: ";
for(int i=0; i<g.size()-1; i++){
    s += "Giocatore: " + to_string(g[i])+ " ,";
}
s+= "Giocatore: "+ to_string(g[3]) + ".";

cout<<s<<endl;
fout.open(fn, ios::app);
fout<<s<<endl;
fout.close();
return;
}

void Logger::set_nome_file(string s){
fn = s;
return;
}

void Logger::nuovo_f(){
fout.open(fn);
fout.close();
return;
}
