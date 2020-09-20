#include    <stdlib.h>
#include    <ncurses.h>
#include    <string.h>
#include    <time.h>

#define     COROA       11
#define     ESTANDARTE  12
#define     ESCUDO      13
#define     ESPADA      14
#define     CAVALEIRO   15
#define     MARTELO     16
#define     BALANCA     17

#define 1COROA      "          /\\          "
#define 2COROA      "         /  \\         "
#define 3COROA      "|\\       \\  /       /|"
#define 4COROA      "| \\  |\\  _||_  /|  / |"
#define 5COROA      "|  \\_| \\/    \\/ |_/  |"
#define 6COROA      "\\                    /"
#define 7COROA      "/___              ___\\"
#define 8COROA      "    \\___      ___/    "
#define 9COROA      "        \\____/        "  

#define 1ESTANDARTE " /\\                   "
#define 2ESTANDARTE "/  \\                  "
#define 3ESTANDARTE "\\  /_____             "
#define 4ESTANDARTE " ||\\     \\_____       "
#define 5ESTANDARTE " || \\         \\______"
#define 6ESTANDARTE " || |             ___/"
#define 7ESTANDARTE " <> |        ____/    "
#define 8ESTANDARTE " || /  _____/         "
#define 9ESTANDARTE " ||/__/               "  

#define 1ESCUDO     " ______        ______ "
#define 2ESCUDO     "/      \\__/\\__/      \\"
#define 3ESCUDO     "\\                    /"
#define 4ESCUDO     " |                  | "
#define 5ESCUDO     " |                  | "
#define 6ESCUDO     "  \\                /  "
#define 7ESCUDO     "   |              |   "
#define 8ESCUDO     "    \\__        __/    "
#define 9ESCUDO     "       \\______/       "  

#define 1ESPADA     "          <>          "
#define 2ESPADA     "       ___||___       "
#define 3ESPADA     "       \\______/       "
#define 4ESPADA     "         |  |         "
#define 5ESPADA     "         |  |         "
#define 6ESPADA     "         |  |         "
#define 7ESPADA     "         |  |         "
#define 8ESPADA     "         \\  /         "
#define 9ESPADA     "          \\/          "

#define 1CAVALEIRO  "/\\\\\\\\\\/////\\_         "
#define 2CAVALEIRO  "\\\\\\\\\\\\\\/)\\\\\\\\\\        "
#define 3CAVALEIRO  "///       \\\\\\\\\\___    "
#define 4CAVALEIRO  "\\\\\\  /_     \\\\\\\\\\\\\\___"
#define 5CAVALEIRO  "// \\      \\    \\\\\\\\\\\\\\"
#define 6CAVALEIRO  "\\   \\     |       \\\\\\\\"
#define 7CAVALEIRO  "/    \\    |\\_       \\\\"
#define 8CAVALEIRO  "      \\.  |  \\       \\"
#define 9CAVALEIRO  "       \\__/   |______|"            

#define 1MARTELO    " _____    __    _____ "
#define 2MARTELO    "/     \\__/  \\__/     \\"
#define 3MARTELO    "|                    |"
#define 4MARTELO    "|                    |"
#define 5MARTELO    "|     ___.__.__      |"
#define 6MARTELO    "\\____/  \\|  |/ \\_____/"
#define 7MARTELO    "         |  |         "
#define 8MARTELO    "         |  |         "
#define 9MARTELO    "         |__|         "   

#define 1BALANCA    " _        <>        _ "
#define 2BALANCA    "//  ____  ||  ____  \\\\"
#define 3BALANCA    "\\\\_/  _ \\_||_/ _  \\_//"
#define 4BALANCA    " \\___/ \\_    _/ \\___/ "
#define 5BALANCA    "   |     \\  /     |   "
#define 6BALANCA    "  / \\     ||     / \\  "
#define 7BALANCA    " /___\\    ||    /___\\ "
#define 8BALANCA    " \\___/   _||_   \\___/ "
#define 9BALANCA    "        /____\\        "   

typedef struct t_peca
{
    int desenho;
    int virada;
} t_peca;

typedef struct t_tapete
{
    int ponto_verde;
    int ponto_vermelho;
    int quant_pecas;
    t_peca *linha_pecas[7];
} t_tapete;

typedef struct t_reserva
{
    int quant_pecas;
    t_peca *linha_pecas[7];
}

void inicia_jogo (t_tapete *tapete, t_reserva *reserva)
{
    tapete->ponto_verde    = 0;
    tapete->ponto_vermelho = 0;
    tapete->quant_pecas    = 0;
    reserva->quant_pecas   = 7;
    tapete->linhapecas  = malloc (t_peca *) (7*(sizeof(t_peca)));
    reserva->linhapecas = malloc (t_peca *) (7*(sizeof(t_peca)));
    int i;
    for (i=0 ; i<7 ; i++)
    {
        reserva->linha_pecas[i]->desenho = i+11;
        reserva->linha_pecas[i]->virada  = 0;
        tapete->linha_pecas[i]->desenho  = 0;
        tapete->linha_pecas[i]->virada   = 0;
    }
}

void imprime_tapete (WINDOW *wtapete, t_tapete *tapete)
{
    wclear(wtapete);
    wattron (wtapete,COLOR_PAIR(TAPETE));

    mvwaddch (wtapete, 0 , 0  , ACS_ULCORNER);   /*imprime os cantos*/
    mvwaddch (wtapete, 0 , 157, ACS_URCORNER);
    mvwaddch (wtapete, 18, 0  , ACS_LLCORNER);
    mvwaddch (wtapete, 18, 157, ACS_LRCORNER);

    int i,j;
    for (i=1 ; i<157 ; i++)
    {
        mvwaddch (wtapete, 0 , i, ACS_HLINE);
        mvwaddch (wtapete, 18, i, ACS_HLINE);
    }                                           
    for (i=1 ; i<18 ; i++)
    {
        mvwaddch (wtapete, i, 0  , ACS_VLINE);
        mvwaddch (wtapete, i, 157, ACS_VLINE);
    }

    for (i=1 ; i<157 ; i++)
    {
        for (j=1 ; j<18 ; j++)
        {
            mvwaddch (wtapete, j, i, ' ');
        }
    }                  
    wattroff(wtapete,COLOR_PAIR(TAPETE));       /*imprimiu o tapete, falta as pecas em cima dele*/

    wattron (wtapete,COLOR_PAIR(PECA));
    int comeco = 67 - 11*tapete->quant_pecas;
    for (i=0 ; i<tapete->quant_pecas ; i++)
    {
        if (tapete->linha_pecas[i]->virada == 1)        /*peca virada*/
        {
            int j;
            mvwaddch (wtapete, 5 , comeco+i*22   , ACS_ULCORNER);
            mvwaddch (wtapete, 5 , comeco+i*22+21, ACS_URCORNER);
            mvwaddch (wtapete, 13, comeco+i*22   , ACS_LLCORNER);
            mvwaddch (wtapete, 13, comeco+i*22+21, ACS_LRCORNER);
            for (j=1 ; j<21 ; j++)
            {
                mvwaddch (wtapete, 5 , comeco+i*22+j, ACS_HLINE);
                mvwaddch (wtapete, 13, comeco+i*22+j, ACS_HLINE);
            }                                                     
            for (j=1 ; j<18 ; j++)
            {
                mvwaddch (wtapete, j, comeco+i*22   , ACS_VLINE);
                mvwaddch (wtapete, j, comeco+i*22+21, ACS_VLINE);
            }                                                    
        }
        else
        {
            if (tapete->linha_pecas[i]->desenho == COROA)
            {
                mvwprintw (wtapete, 5 , comeco+i*22, "          /\\          "  );
                mvwprintw (wtapete, 6 , comeco+i*22, "         /  \\         "  );
                mvwprintw (wtapete, 7 , comeco+i*22, "|\\       \\  /       /|" );
                mvwprintw (wtapete, 8 , comeco+i*22, "| \\  |\\  _||_  /|  / |" );
                mvwprintw (wtapete, 9 , comeco+i*22, "|  \\_| \\/    \\/ |_/  |");
                mvwprintw (wtapete, 10, comeco+i*22, "\\                    /"  );
                mvwprintw (wtapete, 11, comeco+i*22, "/___              ___\\"  );
                mvwprintw (wtapete, 12, comeco+i*22, "    \\___      ___/    "  );
                mvwprintw (wtapete, 13, comeco+i*22, "        \\____/        "  );
            }
            else if (tapete->linha_pecas[i]->desenho == ESTANDARTE)
            {
                mvwprintw (wtapete, 5 , comeco+i*22, " /\\                   " );
                mvwprintw (wtapete, 6 , comeco+i*22, "/  \\                  " );
                mvwprintw (wtapete, 7 , comeco+i*22, "\\  /_____             " );
                mvwprintw (wtapete, 8 , comeco+i*22, " ||\\     \\_____       ");
                mvwprintw (wtapete, 9 , comeco+i*22, " || \\         \\______" );
                mvwprintw (wtapete, 10, comeco+i*22, " || |             ___/"  );
                mvwprintw (wtapete, 11, comeco+i*22, " <> |        ____/    "  );
                mvwprintw (wtapete, 12, comeco+i*22, " || /  _____/         "  );
                mvwprintw (wtapete, 13, comeco+i*22, " ||/__/               "  );
            }
            else if (tapete->linha_pecas[i]->desenho == ESCUDO)
            {
                mvwprintw (wtapete, 5 , comeco+i*22, " ______        ______ "   );
                mvwprintw (wtapete, 6 , comeco+i*22, "/      \\__/\\__/      \\");
                mvwprintw (wtapete, 7 , comeco+i*22, "\\                    /"  );
                mvwprintw (wtapete, 8 , comeco+i*22, " |                  | "   );
                mvwprintw (wtapete, 9 , comeco+i*22, " |                  | "   );
                mvwprintw (wtapete, 10, comeco+i*22, "  \\                /  "  );
                mvwprintw (wtapete, 11, comeco+i*22, "   |              |   "   );
                mvwprintw (wtapete, 12, comeco+i*22, "    \\__        __/    "  );
                mvwprintw (wtapete, 13, comeco+i*22, "       \\______/       "  );
            }
            else if (tapete->linha_pecas[i]->desenho == ESPADA)
            {
                mvwprintw (wtapete, 5 , comeco+i*22, "          <>          " );
                mvwprintw (wtapete, 6 , comeco+i*22, "       ___||___       " );
                mvwprintw (wtapete, 7 , comeco+i*22, "       \\______/       ");
                mvwprintw (wtapete, 8 , comeco+i*22, "         |  |         " );
                mvwprintw (wtapete, 9 , comeco+i*22, "         |  |         " );
                mvwprintw (wtapete, 10, comeco+i*22, "         |  |         " );
                mvwprintw (wtapete, 11, comeco+i*22, "         |  |         " );
                mvwprintw (wtapete, 12, comeco+i*22, "         \\  /         ");
                mvwprintw (wtapete, 13, comeco+i*22, "          \\/          ");
            }
            else if (tapete->linha_pecas[i]->desenho == CAVALEIRO)
            {
                mvwprintw (wtapete, 5 , comeco+i*22, "/\\\\\\\\\\/////\\_         "      );
                mvwprintw (wtapete, 6 , comeco+i*22, "\\\\\\\\\\\\\\/)\\\\\\\\\\        ");
                mvwprintw (wtapete, 7 , comeco+i*22, "///       \\\\\\\\\\___    "       );
                mvwprintw (wtapete, 8 , comeco+i*22, "\\\\\\  /_     \\\\\\\\\\\\\\___"  );
                mvwprintw (wtapete, 9 , comeco+i*22, "// \\      \\    \\\\\\\\\\\\\\"   );
                mvwprintw (wtapete, 10, comeco+i*22, "\\   \\     |       \\\\\\\\"      );
                mvwprintw (wtapete, 11, comeco+i*22, "/    \\    |\\_       \\\\"        );
                mvwprintw (wtapete, 12, comeco+i*22, "      \\.  |  \\       \\"         );
                mvwprintw (wtapete, 13, comeco+i*22, "       \\__/   |______|"           );
            }
            else if (tapete->linha_pecas[i]->desenho == MARTELO)
            {
                mvwprintw (wtapete, 5 , comeco+i*22, " _____    __    _____ "   );
                mvwprintw (wtapete, 6 , comeco+i*22, "/     \\__/  \\__/     \\");
                mvwprintw (wtapete, 7 , comeco+i*22, "|                    |"   );
                mvwprintw (wtapete, 8 , comeco+i*22, "|                    |"   );
                mvwprintw (wtapete, 9 , comeco+i*22, "|     ___.__.__      |"   );
                mvwprintw (wtapete, 10, comeco+i*22, "\\____/  \\|  |/ \\_____/");
                mvwprintw (wtapete, 11, comeco+i*22, "         |  |         "   );
                mvwprintw (wtapete, 12, comeco+i*22, "         |  |         "   );
                mvwprintw (wtapete, 13, comeco+i*22, "         |__|         "   );
            }
            else if (tapete->linha_pecas[i]->desenho == BALANCA)
            {
                mvwprintw (wtapete, 5 , comeco+i*22, " _        <>        _ "    );
                mvwprintw (wtapete, 6 , comeco+i*22, "//  ____  ||  ____  \\\\"  );
                mvwprintw (wtapete, 7 , comeco+i*22, "\\\\_/  _ \\_||_/ _  \\_//");
                mvwprintw (wtapete, 8 , comeco+i*22, " \\___/ \\_    _/ \\___/ " );
                mvwprintw (wtapete, 9 , comeco+i*22, "   |     \\  /     |   "   );
                mvwprintw (wtapete, 10, comeco+i*22, "  / \\     ||     / \\  "  );
                mvwprintw (wtapete, 11, comeco+i*22, " /___\\    ||    /___\\ "  );
                mvwprintw (wtapete, 12, comeco+i*22, " \\___/   _||_   \\___/ "  );
                mvwprintw (wtapete, 13, comeco+i*22, "        /____\\        "   );
            }
        }
    }
    wattroff(wtapete,COLOR_PAIR(PECA));

    /*insira aqui a parte dos pontos*/

    wrefresh(wtapete);
}

void imprime_reserva (WINDOW *wreserva, t_reserva *reserva)
{
    wclear (wreserva);
    int i,j;

    mvwaddch (wreserva, 0 , 0 , ACS_ULCORNER);
    mvwaddch (wreserva, 0 , 85, ACS_URCORNER);
    mvwaddch (wreserva, 4 , 0 , ACS_LLCORNER);
    mvwaddch (wreserva, 4 , 85, ACS_LRCORNER);
    for (i=1 ; i<85 ; i++)
    {
        mvwaddch (wreserva, 0 , i , ACS_HLINE);
        mvwaddch (wreserva, 4 , i , ACS_HLINE);
    }                                                    
    for (i=1 ; i<4 ; i++)
    {
        mvwaddch (wreserva, i, 0 , ACS_VLINE);
        mvwaddch (wreserva, i, 85, ACS_VLINE);
    }                                                  /*até aqui, imprimiu a borda da reserva*/                          

    for (i=0 ; i<reserva->quant_pecas ; i++)
    {
        mvwaddch (wreserva, 1 , 1+i*12   , ACS_ULCORNER);
        mvwaddch (wreserva, 1 , 1+i*12+11, ACS_URCORNER);
        mvwaddch (wreserva, 3 , 1+i*12   , ACS_LLCORNER);
        mvwaddch (wreserva, 3 , 1+i*12+11, ACS_LRCORNER);
        mvwaddch (wreserva, 2 , 1+i*12   , ACS_VLINE);
        mvwaddch (wreserva, 2 , 1+i*12+11, ACS_VLINE);

        for (j=1 ; j<11 ; j++)
        {
            mvwaddch (wreserva, 1 , 1+i*12+j, ACS_HLINE);
            mvwaddch (wreserva, 3 , 1+i*12+j, ACS_HLINE);
        }

        if (reserva->linha_pecas[i] == COROA)
        {
            mvwprintw (wreserva, 2, 1+i*12, "Coroa     ");
        }                                               
        else if (reserva->linha_pecas[i] == ESTANDARTE)                  
        {
            mvwprintw (wreserva, 2, 1+i*12, "Estandarte");
        }                                              
        else if (reserva->linha_pecas[i] == ESCUDO)     
        {
            mvwprintw (wreserva, 2, 1+i*12, "Escudo    ");
        }                                                 
        else if (reserva->linha_pecas[i] == ESPADA)     
        {
            mvwprintw (wreserva, 2, 1+i*12, "Espada    ");
        }                                                 
        else if (reserva->linha_pecas[i] == CAVALEIRO)     
        {
            mvwprintw (wreserva, 2, 1+i*12, "Cavaleiro ");
        }                                                 
        else if (reserva->linha_pecas[i] == MARTELO)     
        {
            mvwprintw (wreserva, 2, 1+i*12, "Martelo   ");
        }                                              
        else 
        {
            mvwprintw (wreserva, 2, 1+i*12, "Balanca   ");
        }                                                   
    }                                           
    wrefresh (wreserva);
}

int colocar_peca (t_tapete *tapete, t_reserva *reserva, WINDOW *wtapete, WINDOW *wreserva) 
{
    int i = 0;
    char tecla;
    tecla = getch ();
    imprime_reserva         (wreserva,reserva);
    /*imprime_selecao_reserva (i);*/
    while ((tecla != 'z')&&(tecla != 'x'))  /*laco para escolher qual peca da reserva o jogador deseja*/
    {
        if (tecla == KEY_RIGHT)             
        {
            if (i < reserva->quant_pecas-1)
            {   
                i++;
            }
        }
        else if (tecla == KEY_LEFT)
        {
            if (i > 0)
            {
                i--;
            }
        }
        imprime_reserva         (wreserva,reserva);
        /*imprime_selecao_reserva (i);*/
        tecla = getch();
    }
    if (tecla == 'x')   /*caso cancele a acao*/
    {
        return 1; /*retorna que a acao foi cancelada*/
    }
    else if (tecla == 'z')  /*caso decida por uma peca*/
    {
        int desenho = reserva->linha_pecas[i]->desenho;
        int virada  = reserva->linha_pecas[i]->virada;
        
        while (i < reserva->quant_pecas-1)  /*tras as pecas da direita para a esquerda a partir da peca escolhida*/
        {
            reserva->linha_pecas[i]->desenho = reserva->linha_pecas[i+1]->desenho;
            reserva->linha_pecas[i]->virada  = reserva->linha_pecas[i+1]->virada;
            i++;
        }
        reserva->linha_pecas[i]->desenho = 0;
        reserva->linha_pecas[i]->virada  = 0;
        reserva->quant_pecas--;

        i = 0;  
        
        imprime_tapete         (wtapete,tapete);
        /*imprime_selecao_tapete (i);*/
        tecla = getch();

        while ((tecla != 'z')&&(tecla != 'x'))  /*laco para escolher onde o jogador deseja por a peca*/
        {
            if (tecla == KEY_RIGHT)             
            {
                if (i < 1)
                {   
                    i++;
                }
            }
            else if (tecla == KEY_LEFT)
            {
                if (i > 0)
                {
                    i--;
                }
            }
            imprime_tapete         (wtapete,tapete);
            /*imprime_selecao_tapete (i);*/
            tecla = getch();
        }

        if (tecla == 'x')   /*caso cancele a acao depois de ja ter escolhido a peca*/
        {
            int final = reserva->quant_pecas;
            reserva->linha_pecas[final]->desenho = desenho;
            reserva->linha_pecas[final]->virada  = virada;
            reserva->quant_pecas++;
            return 1;
        }
        else if (tecla == 'z')  /*tira a peca da reserva e poe no tapete*/
        {
            i = tapete->quant_pecas;
            if (i == 1)
            {
                tapete->linha_pecas[i]->desenho = desenho;
                tapete->linha_pecas[i]->virada  = virada;
            }
            else
            {
                while (i > 0)
                {
                    tapete->linha_pecas[i+1]->desenho = tapete->linha_pecas[i]->desenho;
                    tapete->linha_pecas[i+1]->virada  = tapete->linha_pecas[i]->virada;
                    i--;
                }
                tapete->linha_pecas[0]->desenho = desenho;
                tapete->linha_pecas[0]->virada  = virada;
            }
            tapete->quant_pecas++;
            return 0;
        }
    }
}   
