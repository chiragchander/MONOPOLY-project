// Lovato Emanuele
#include "../include/Casella.h"
#include "../include/Game.h"
#include "../include/Board.h"
#include "../include/Player.h"
#include "../include/Dadi.h"   // Serve solo nella funzione intro()
#include "../include/Logger.h" // Serve solo nella funzione intro()
#include <algorithm>
#include <random>

Game::Game() : turno{1}
{
    board = tabellone.get_board();
    Player *giocatore1 = new Player(1);
    Player *giocatore2 = new Player(2);
    Player *giocatore3 = new Player(3);
    Player *giocatore4 = new Player(4);
    add_giocatore(giocatore1);
    add_giocatore(giocatore2);
    add_giocatore(giocatore3);
    add_giocatore(giocatore4);
    log.set_nome_file("log_computer.txt");
    log.nuovo_f();
}

Game::Game(std::string s) : turno{1}
{
    board = tabellone.get_board();
    Player *giocatore1 = new Player(1);
    Player *giocatore2 = new Player(2);
    Player *giocatore3 = new Player(3);
    Player *giocatore4 = new Player(4);
    add_giocatore(giocatore1);
    add_giocatore(giocatore2);
    add_giocatore(giocatore3);
    add_giocatore(giocatore4);
    log.set_nome_file(s);
    log.nuovo_f();

}

void Game::add_giocatore(Player *pippo)
{
    pippo->set_position(tabellone.get_starting_cell().get_position());
    giocatori.push_back(pippo);
}

void Game::del_giocatore(Player *pippo)
{
    log.elimin(pippo->get_nome());
    auto it = std::find_if(giocatori.begin(), giocatori.end(), [pippo](const Player *player)
                           { return *player == *pippo; });
    if (it != giocatori.end())
    {
        giocatori.erase(it);
        std::vector<Casella *> caselle = pippo->get_proprie();
        if (!caselle.empty())
        {
            for (int i = 0; i < caselle.size(); i++)
            {
                caselle[i]->set_owner(0);
                caselle[i]->set_lvl(1);
            }
        }
    }
    // @@@ controllare che elimini correttamente

    // CCC rimuovere dal tabellone tutte le caselle e proprietà del giocatore
}

void Game::next_turno()
{
    turno++;
    // @@@ Eventualmente aggiungere qui i 20 fiorni del player.
}

std::vector<int> Game::order_players() {
        Dadi dadi;
        std::vector<int> giocatori(4);
        for (int i = 0; i < 4; ++i) {
            giocatori[i] = i + 1;
        }

        // Ordina i giocatori a caso
        for (int i = 0; i < 4; ++i) {
            int indiceCasuale = rand() % 4;
            std::swap(giocatori[i], giocatori[indiceCasuale]);
        }

        // Trova massimo
        int massimo = 0;
        for (int i = 0; i < 4; ++i) {
            int lancio = dadi.lancio();
            std::cout << "Giocatore " << giocatori[i] << " ha lanciato: " << lancio << std::endl;
            if (lancio > massimo) {
                massimo = lancio;
            }
        }

        // Trova i giocatori che hanno  il massimo
        std::vector<int> giocatori_con_massimo;
        for (int i = 0; i < 4; ++i) {
            if (dadi.lancio() == massimo) {
                giocatori_con_massimo.push_back(giocatori[i]);
            }
        }

        // Spareggio
        if (giocatori_con_massimo.size() > 1) {
            std::cout << "Spareggio tra i giocatori: ";
            for (int i = 0; i < giocatori_con_massimo.size(); ++i) {
                giocatori_con_massimo[i] = dadi.lancio();
                std::cout << giocatori_con_massimo[i] << " ";
            }
            std::cout << std::endl;

            // Trova nuovamente i giocatori che hanno ottenuto il massimo
            massimo = *std::max_element(giocatori_con_massimo.begin(), giocatori_con_massimo.end());
            giocatori_con_massimo.erase(
                std::remove_if(giocatori_con_massimo.begin(), giocatori_con_massimo.end(),
                               [&massimo](int giocatore) { return giocatore != massimo; }),
                giocatori_con_massimo.end());
        }

        // Ordina gli indici dei giocatori in base al masismo
        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                if (dadi.lancio() > dadi.lancio()) {
                    std::swap(giocatori[i], giocatori[j]);
                }
            }
        }

        return giocatori;
    }

Player *Game::get_player_from_index(int n)
{
    for (int i = 0; i < giocatori.size(); i++)
    {
        if (giocatori[i]->get_nome() == n)
        {
            return giocatori[i];
        }
    }
    return nullptr;
} // get_player_from_index

void Game::intro()
{
    std::vector<int> ordine = order_players();
    std::sort(giocatori.begin(), giocatori.end(), [&](Player *a, Player *b)
              {
        int indice_a = a->get_nome();
        int indice_b = b->get_nome();
        return std::find(ordine.begin(), ordine.end(), indice_a) < std::find(ordine.begin(), ordine.end(), indice_b); });

    log.ordine_giocatori(ordine);
}

void Game::turno_robot(Player *pippo)
{
    log.inizio_turno(pippo->get_nome());
    Dadi d;
    move_player(pippo);

    // casella angolare, non faccio niente e il turno termina
    if (board[pippo->get_position().get_x()][pippo->get_position().get_y()].is_angolo())
    {
        // LOGGER---> FINE TURNO
    }
    // terreno senza proprietario, posso comprare il terreno
    else if (board[pippo->get_position().get_x()][pippo->get_position().get_y()].get_owner() == 0 &&
             board[pippo->get_position().get_x()][pippo->get_position().get_y()].is_terreno())
    {
        // LOGGER-->
        if (d.scelta_percento())
        {
            if (pippo->get_budget() >= board[pippo->get_position().get_x()][pippo->get_position().get_y()].price())
            {

                pippo->paga(board[pippo->get_position().get_x()][pippo->get_position().get_y()].price());
                board[pippo->get_position().get_x()][pippo->get_position().get_y()].set_owner(pippo->get_nome());

                log.acq_ter(pippo->get_nome(), pippo->get_position().position_to_string());
            }
            else
            {
            }
        }
        else
        {
        }
    }
    // terreno di proprietà, posso migliorare a casa
    else if (board[pippo->get_position().get_x()][pippo->get_position().get_y()].get_owner() == pippo->get_nome() &&
             board[pippo->get_position().get_x()][pippo->get_position().get_y()].is_terreno())
    {
        // LOGGER-->
        if (d.scelta_percento())
        {
            if (pippo->get_budget() >= board[pippo->get_position().get_x()][pippo->get_position().get_y()].price())
            {
                pippo->paga(board[pippo->get_position().get_x()][pippo->get_position().get_y()].price());
                board[pippo->get_position().get_x()][pippo->get_position().get_y()].upgrade();
                log.costr_casa(pippo->get_nome(), pippo->get_position().position_to_string());
            }
            else
            {
            }
        }
        else
        {
        }
    }
    // terreno di proprietà, posso migliorare ad albergo
    else if (board[pippo->get_position().get_x()][pippo->get_position().get_y()].get_owner() == pippo->get_nome() &&
             board[pippo->get_position().get_x()][pippo->get_position().get_y()].is_casa())
    {
        // LOGGER-->
        if (d.scelta_percento())
        {
            if (pippo->get_budget() >= board[pippo->get_position().get_x()][pippo->get_position().get_y()].price())
            {
                pippo->paga(board[pippo->get_position().get_x()][pippo->get_position().get_y()].price());
                board[pippo->get_position().get_x()][pippo->get_position().get_y()].upgrade();
                log.costr_alb(pippo->get_nome(), pippo->get_position().position_to_string());
            }
            else
            {
                /// LOGGER FINE TURNO
            }
        }
        else
        {
        }
    }
    // casa di un altro giocatore, pago il pernottamento
    else if (board[pippo->get_position().get_x()][pippo->get_position().get_y()].get_owner() != pippo->get_nome() &&
                 board[pippo->get_position().get_x()][pippo->get_position().get_y()].is_casa() ||
             board[pippo->get_position().get_x()][pippo->get_position().get_y()].is_albergo())
    {
        // LOGGER-->
        if (pippo->get_budget() >= board[pippo->get_position().get_x()][pippo->get_position().get_y()].price())
        {

            // pippo paga a giocatore 2, giocatore 2 riceve
            pippo->paga(board[pippo->get_position().get_x()][pippo->get_position().get_y()].price());
            get_player_from_index(board[pippo->get_position().get_x()][pippo->get_position().get_y()].get_owner())->ricevi(board[pippo->get_position().get_x()][pippo->get_position().get_y()].price());
            log.pag_ped(pippo->get_nome(), get_player_from_index(board[pippo->get_position().get_x()][pippo->get_position().get_y()].get_owner())->get_nome(), board[pippo->get_position().get_x()][pippo->get_position().get_y()].price(), pippo->get_position().position_to_string());
        }
        else
        {
            /// LOGGER GAME OVER ROBOT

            giocatore_over(pippo);
            get_player_from_index(board[pippo->get_position().get_x()][pippo->get_position().get_y()].get_owner())->ricevi(pippo->get_budget());
        }
    }

    log.fine_turno(pippo->get_nome());
}

void Game::turno_human(Player *pippo)
{
    log.inizio_turno(pippo->get_nome());
    Dadi d;
    ////////////LOGGER----->INIZIO TURNO ROBOT
    std::string input_utente;

    do {
        std::cout << "\nUmano, attendo un tuo comando!\n";
        std::cout << "    <#> Accetto solamente \"show\" o \"roll\".\n";
        std::cin >> input_utente;

        // Controlla il comando ed eventualmente eseguine l'azione.
        if (input_utente == "show")
        {
            // Mostra dati della partita, come da consegna.
            // tabellone
            print_gameboard();
            // lista proprieta' e fiorini
            for (int i = 0; i < 4; i++)
            {
                Player *gio_temp = get_giocatori(i);
                cout << "Giocatore " << gio_temp->get_nome() << " ha le caselle:\n";
                gio_temp->print_proprie();
                cout << "Inoltre tale Giocatore ha " << gio_temp->get_budget() << " fiorini.\n\n";
            }
        }

        else if (input_utente == "roll")
        {
            /////////////////////////////////////////////////////////DA SISTEMARE
            // Lancia i dadi e prosegui.
            move_player(pippo);
            ////////////LOGGER----->MOVIMENTO ROBOT

            // casella angolare, non faccio niente e il turno termina
            if (board[pippo->get_position().get_x()][pippo->get_position().get_y()].is_angolo())
            {
                // LOGGER---> FINE TURNO
            }
            // terreno senza proprietario, posso comprare il terreno
            else if (board[pippo->get_position().get_x()][pippo->get_position().get_y()].get_owner() == 0 &&
                    board[pippo->get_position().get_x()][pippo->get_position().get_y()].is_terreno())
            {
                // LOGGER-->
                if (pippo->get_budget() >= board[pippo->get_position().get_x()][pippo->get_position().get_y()].price())
                {
                    char answer;
                    std::cout << "Desideri comprare il terreno?" << std::endl;
                    std::cin >> answer;
                    if (answer == 'S')
                    {
                        pippo->paga(board[pippo->get_position().get_x()][pippo->get_position().get_y()].price());
                        board[pippo->get_position().get_x()][pippo->get_position().get_y()].set_owner(pippo->get_nome());
                        log.acq_ter(pippo->get_nome(), pippo->get_position().position_to_string());
                    }
                    else if (answer == 'N')
                    {
                        /// LOGGER FINE TURNO
                    }
                    // DA GESTIRE QUANDO SI INSERISCE IL CARATTERE SBAGLIATO
                }
                else
                {
                    /// LOGGER FINE TURNO
                }
            }

            // terreno di proprietà, posso migliorare a casa
            else if (board[pippo->get_position().get_x()][pippo->get_position().get_y()].get_owner() == pippo->get_nome() &&
                    board[pippo->get_position().get_x()][pippo->get_position().get_y()].is_terreno())
            {
                // LOGGER-->
                if (pippo->get_budget() >= board[pippo->get_position().get_x()][pippo->get_position().get_y()].price())
                {

                    char answer;
                    std::cout << "Desideri costruire una casa?" << std::endl;
                    std::cin >> answer;
                    if (answer == 'S')
                    {
                        pippo->paga(board[pippo->get_position().get_x()][pippo->get_position().get_y()].price());
                        board[pippo->get_position().get_x()][pippo->get_position().get_y()].upgrade();
                        log.costr_casa(pippo->get_nome(), pippo->get_position().position_to_string());
                    }
                    else if (answer == 'N')
                    {
                        /// LOGGER FINE TURNO
                    }
                }
                else
                {
                    /// LOGGER FINE TURNO
                }
            }

            // terreno di proprietà, posso migliorare ad albergo
            else if (board[pippo->get_position().get_x()][pippo->get_position().get_y()].get_owner() == pippo->get_nome() &&
                    board[pippo->get_position().get_x()][pippo->get_position().get_y()].is_casa())
            {
                // LOGGER-->

                if (pippo->get_budget() >= board[pippo->get_position().get_x()][pippo->get_position().get_y()].price())
                {
                    char answer;
                    std::cout << "Desideri costruire una casa?" << std::endl;
                    std::cin >> answer;
                    if (answer == 'S')
                    {

                        pippo->paga(board[pippo->get_position().get_x()][pippo->get_position().get_y()].price());
                        board[pippo->get_position().get_x()][pippo->get_position().get_y()].upgrade();
                        log.costr_alb(pippo->get_nome(), pippo->get_position().position_to_string());
                    }
                    else if (answer == 'N')
                    {
                        /// LOGGER FINE TURNO
                    }
                }

                else
                {
                    /// LOGGER FINE TURNO
                }
            }

            // casa di un altro giocatore, pago il pernottamento
            else if (board[pippo->get_position().get_x()][pippo->get_position().get_y()].get_owner() != pippo->get_nome() &&
                        board[pippo->get_position().get_x()][pippo->get_position().get_y()].is_casa() ||
                    board[pippo->get_position().get_x()][pippo->get_position().get_y()].is_albergo())
            {
                // LOGGER-->
                if (pippo->get_budget() >= board[pippo->get_position().get_x()][pippo->get_position().get_y()].price())
                {

                    // pippo paga a giocatore 2, giocatore 2 riceve
                    pippo->paga(board[pippo->get_position().get_x()][pippo->get_position().get_y()].price());
                    get_player_from_index(board[pippo->get_position().get_x()][pippo->get_position().get_y()].get_owner())->ricevi(board[pippo->get_position().get_x()][pippo->get_position().get_y()].price());
                    log.pag_ped(pippo->get_nome(), get_player_from_index(board[pippo->get_position().get_x()][pippo->get_position().get_y()].get_owner())->get_nome(), board[pippo->get_position().get_x()][pippo->get_position().get_y()].price(), pippo->get_position().position_to_string());
                }
                else
                {
                    /// LOGGER GAME OVER ROBOT

                    giocatore_over(pippo);
                    get_player_from_index(board[pippo->get_position().get_x()][pippo->get_position().get_y()].get_owner())->ricevi(pippo->get_budget());
                }
            }
        }
        else
        {
            std::cout << "Comando non accettato: cortesemente, ripeti l'inserimento.\n";
        }
    } while(input_utente != "roll");

    log.fine_turno(pippo->get_nome());
}

void Game::giocatore_over(Player *pippo)
{
    // Se il giocatore in questione pippo è da rimuovere, va tolto dalla lista
    if (pippo->povero() || !pippo->get_vivo())
    {
        del_giocatore(pippo);
    }
}

bool Game::fine_gioco()
{
    // Stabiliamo che si finisca quando i turni arrivano oltre il 500 o quando rimane un solo giocatore.
    if (turno > 500 || giocatori.size() == 1)
    {
        return true;
    }
    else
        return false;
}
std::vector<Player *> Game::vincitori()
{
    std::vector<Player *> vincitori;
    if (giocatori.empty())
    {
        return vincitori;
    }

    int massimo = giocatori[0]->get_budget();
    for (int i = 1; i < giocatori.size(); i++)
    {
        if (giocatori[i]->get_budget() > massimo)
        {
            massimo = giocatori[i]->get_budget();
        }
    }
    for (int i = 0; i < giocatori.size(); i++)
    {
        if (giocatori[i]->get_budget() == massimo)
        {
            vincitori.push_back(giocatori[i]);
        }
    }

    return vincitori;
}

void Game::print_gameboard()
{
    tabellone.print_line(0);
    for (int i = 1; i <= 8; i++)
    {
        print_gameboard_line(i);
    }
}

void Game::print_gameboard_line(int n)
{
    std::vector<int> giocatori_presenti_nella_casella;
    std::vector<std::pair<int, int>> posizioni_giocatori;
    for (const auto &giocatore : giocatori)
    {
        int x = giocatore->get_position().get_x();
        int y = giocatore->get_position().get_y();
        posizioni_giocatori.push_back(std::make_pair(x, y));
    }

    std::cout << alphabet[n - 1] << " ";
    for (int i = 0; i < 8; i++)
    {
        if (board[i][n - 1].is_central_cell())
        {
            std::cout << "        ";
        }
        else
        {
            giocatori_presenti_nella_casella.clear();

            // Verifica la presenza dei giocatori nella casella
            for (int giocatore_index = 0; giocatore_index < giocatori.size(); ++giocatore_index)
            {
                int x_giocatore = posizioni_giocatori[giocatore_index].first;
                int y_giocatore = posizioni_giocatori[giocatore_index].second;

                if (x_giocatore == board[i][n - 1].get_position().get_x() &&
                    y_giocatore == board[i][n - 1].get_position().get_y())
                {
                    giocatori_presenti_nella_casella.push_back(giocatori[giocatore_index]->get_nome());
                }
            }

            // Stampa la casella con i giocatori presenti
            switch (giocatori_presenti_nella_casella.size())
            {
            case 0:
            	std::cout << centr(board[i][n - 1].to_string());
                break;
            case 1:
            	if(board[i][n - 1].to_string() != " "){
                std::cout << centr(board[i][n - 1].to_string() + std::to_string(giocatori_presenti_nella_casella[0]));
                } else std::cout << centr(std::to_string(giocatori_presenti_nella_casella[0]));
                break;
            case 2:
            	if(board[i][n - 1].to_string() != " "){
                std::cout << centr(board[i][n - 1].to_string() + std::to_string(giocatori_presenti_nella_casella[0]) + std::to_string(giocatori_presenti_nella_casella[1]));
                } else std::cout << centr(std::to_string(giocatori_presenti_nella_casella[0]) + std::to_string(giocatori_presenti_nella_casella[1]));
                break;
            case 3:
            	if(board[i][n - 1].to_string() != " "){
            	std::cout << centr(board[i][n - 1].to_string() + std::to_string(giocatori_presenti_nella_casella[0]) + std::to_string(giocatori_presenti_nella_casella[1]) + std::to_string(giocatori_presenti_nella_casella[2]));
            	} else std::cout << centr(std::to_string(giocatori_presenti_nella_casella[0]) + std::to_string(giocatori_presenti_nella_casella[1]) + std::to_string(giocatori_presenti_nella_casella[2]));
                break;
            case 4:
            	if(board[i][n - 1].to_string() != " "){
            	std::cout << centr(board[i][n - 1].to_string() + std::to_string(giocatori_presenti_nella_casella[0]) + std::to_string(giocatori_presenti_nella_casella[1]) + std::to_string(giocatori_presenti_nella_casella[2]) + std::to_string(giocatori_presenti_nella_casella[3]));
            	} else std::cout << centr(std::to_string(giocatori_presenti_nella_casella[0]) + std::to_string(giocatori_presenti_nella_casella[1]) + std::to_string(giocatori_presenti_nella_casella[2]) + std::to_string(giocatori_presenti_nella_casella[3]));
                break;
            }
        }
    }
    std::cout << std::endl;
}

void Game::move_player(Player *pippo)
{
    Dadi dado;
    int passi = dado.lancio();
    int count = passi;
    log.lan_dadi(pippo->get_nome(), passi);
    while (passi > 0)
    {
        pippo->set_position(pippo->get_position().next_position());
        pippo->add_steps(1);
        if (pippo->get_steps() % 28 == 0 && pippo->get_steps() > 0)
        {
            pippo->ricevi(20);
        }
        passi--;
    }
    log.posizione(pippo->get_nome(), pippo->get_position().position_to_string());
}

std::string Game::centr(std::string s){
	std::string def;
	if((6-s.size())%2){
	int t = (6 - s.size())/2;
	for(int i = 0; i < t; i++){
		def += " ";
	}
	def += "|" + s + "|";
	for(int i = 0; i <= t; i++){
		def += " ";
	}
	return def;
	} else {
	int t = (6 - s.size())/2;
	for(int i = 0; i < t; i++){
		def += " ";
	}
	def += "|" + s + "|";
	for(int i = 0; i < t; i++){
		def += " ";
	}
	return def;
}

}
