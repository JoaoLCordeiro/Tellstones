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

#define COROA1      "          /\\          "
#define COROA2      "         /  \\         "
#define COROA3      "|\\       \\  /       /|"
#define COROA4      "| \\  |\\  _||_  /|  / |"
#define COROA5      "|  \\_| \\/    \\/ |_/  |"
#define COROA6      "\\                    /"
#define COROA7      "/___              ___\\"
#define COROA8      "    \\___      ___/    "
#define COROA9      "        \\____/        "  

#define ESTANDARTE1 " /\\                   "
#define ESTANDARTE2 "/  \\                  "
#define ESTANDARTE3 "\\  /_____             "
#define ESTANDARTE4 " ||\\     \\_____       "
#define ESTANDARTE5 " || \\         \\______"
#define ESTANDARTE6 " || |             ___/"
#define ESTANDARTE7 " <> |        ____/    "
#define ESTANDARTE8 " || /  _____/         "
#define ESTANDARTE9 " ||/__/               "  

#define ESCUDO1     " ______        ______ "
#define ESCUDO2     "/      \\__/\\__/      \\"
#define ESCUDO3     "\\                    /"
#define ESCUDO4     " |                  | "
#define ESCUDO5     " |                  | "
#define ESCUDO6     "  \\                /  "
#define ESCUDO7     "   |              |   "
#define ESCUDO8     "    \\__        __/    "
#define ESCUDO9     "       \\______/       "  

#define ESPADA1     "          <>          "
#define ESPADA2     "       ___||___       "
#define ESPADA3     "       \\______/       "
#define ESPADA4     "         |  |         "
#define ESPADA5     "         |  |         "
#define ESPADA6     "         |  |         "
#define ESPADA7     "         |  |         "
#define ESPADA8     "         \\  /         "
#define ESPADA9     "          \\/          "

#define CAVALEIRO1  "/\\\\\\\\\\/////\\_         "
#define CAVALEIRO2  "\\\\\\\\\\\\\\/)\\\\\\\\\\        "
#define CAVALEIRO3  "///       \\\\\\\\\\___    "
#define CAVALEIRO4  "\\\\\\  /_     \\\\\\\\\\\\\\___"
#define CAVALEIRO5  "// \\      \\    \\\\\\\\\\\\\\"
#define CAVALEIRO6  "\\   \\     |       \\\\\\\\"
#define CAVALEIRO7  "/    \\    |\\_       \\\\"
#define CAVALEIRO8  "      \\.  |  \\       \\"
#define CAVALEIRO9 "       \\__/   |______|"            

#define MARTELO1    " _____    __    _____ "
#define MARTELO2    "/     \\__/  \\__/     \\"
#define MARTELO3    "|                    |"
#define MARTELO4    "|                    |"
#define MARTELO5    "|     ___.__.__      |"
#define MARTELO6    "\\____/  \\|  |/ \\_____/"
#define MARTELO7    "         |  |         "
#define MARTELO8    "         |  |         "
#define MARTELO9    "         |__|         "   

#define BALANCA1    " _        <>        _ "
#define BALANCA2    "//  ____  ||  ____  \\\\"
#define BALANCA3    "\\\\_/  _ \\_||_/ _  \\_//"
#define BALANCA4    " \\___/ \\_    _/ \\___/ "
#define BALANCA5    "   |     \\  /     |   "
#define BALANCA6    "  / \\     ||     / \\  "
#define BALANCA7    " /___\\    ||    /___\\ "
#define BALANCA8    " \\___/   _||_   \\___/ "
#define BALANCA9    "        /____\\        "   

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
} t_reserva;

void inicia_jogo (t_tapete *tapete, t_reserva *reserva)
{
    tapete->ponto_verde    = 0;
    tapete->ponto_vermelho = 0;
    tapete->quant_pecas    = 0;
    reserva->quant_pecas   = 7;
    
    /*tapete->linha_pecas  = (t_peca *) malloc (7*(sizeof(t_peca)));
    reserva->linha_pecas = (t_peca *) malloc (7*(sizeof(t_peca)));*/
    int i;
    for (i=0 ; i<7 ; i++)
    {
        tapete->linha_pecas[i]  = (t_peca *) malloc (sizeof(t_peca));
        reserva->linha_pecas[i] = (t_peca *) malloc (sizeof(t_peca));

        reserva->linha_pecas[i]->desenho = i+11;
        reserva->linha_pecas[i]->virada  = 0;
        tapete->linha_pecas[i]->desenho  = 0;
        tapete->linha_pecas[i]->virada   = 0;
    }
}

void imprime_tapete (WINDOW *wtapete, t_tapete *tapete)
{
    wclear(wtapete);
    wattron (wtapete,COLOR_PAIR(1));

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
    wattroff(wtapete,COLOR_PAIR(1));       /*imprimiu o tapete, falta as pecas em cima dele*/

    wattron (wtapete,COLOR_PAIR(2));
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
                mvwprintw (wtapete, 5 , comeco+i*22, COROA1);
                mvwprintw (wtapete, 6 , comeco+i*22, COROA2);
                mvwprintw (wtapete, 7 , comeco+i*22, COROA3);
                mvwprintw (wtapete, 8 , comeco+i*22, COROA4);
                mvwprintw (wtapete, 9 , comeco+i*22, COROA5);
                mvwprintw (wtapete, 10, comeco+i*22, COROA6);
                mvwprintw (wtapete, 11, comeco+i*22, COROA7);
                mvwprintw (wtapete, 12, comeco+i*22, COROA8);
                mvwprintw (wtapete, 13, comeco+i*22, COROA9);
            }
            else if (tapete->linha_pecas[i]->desenho == ESTANDARTE)
            {
                mvwprintw (wtapete, 5 , comeco+i*22, ESTANDARTE1);
                mvwprintw (wtapete, 6 , comeco+i*22, ESTANDARTE2);
                mvwprintw (wtapete, 7 , comeco+i*22, ESTANDARTE3);
                mvwprintw (wtapete, 8 , comeco+i*22, ESTANDARTE4);
                mvwprintw (wtapete, 9 , comeco+i*22, ESTANDARTE5);
                mvwprintw (wtapete, 10, comeco+i*22, ESTANDARTE6);
                mvwprintw (wtapete, 11, comeco+i*22, ESTANDARTE7);
                mvwprintw (wtapete, 12, comeco+i*22, ESTANDARTE8);
                mvwprintw (wtapete, 13, comeco+i*22, ESTANDARTE9);
            }
            else if (tapete->linha_pecas[i]->desenho == ESCUDO)
            {
                mvwprintw (wtapete, 5 , comeco+i*22, ESCUDO1);
                mvwprintw (wtapete, 6 , comeco+i*22, ESCUDO2);
                mvwprintw (wtapete, 7 , comeco+i*22, ESCUDO3);
                mvwprintw (wtapete, 8 , comeco+i*22, ESCUDO4);
                mvwprintw (wtapete, 9 , comeco+i*22, ESCUDO5);
                mvwprintw (wtapete, 10, comeco+i*22, ESCUDO6);
                mvwprintw (wtapete, 11, comeco+i*22, ESCUDO7);
                mvwprintw (wtapete, 12, comeco+i*22, ESCUDO8);
                mvwprintw (wtapete, 13, comeco+i*22, ESCUDO9);
            }
            else if (tapete->linha_pecas[i]->desenho == ESPADA)
            {
                mvwprintw (wtapete, 5 , comeco+i*22, ESPADA1);
                mvwprintw (wtapete, 6 , comeco+i*22, ESPADA2);
                mvwprintw (wtapete, 7 , comeco+i*22, ESPADA3);
                mvwprintw (wtapete, 8 , comeco+i*22, ESPADA4);
                mvwprintw (wtapete, 9 , comeco+i*22, ESPADA5);
                mvwprintw (wtapete, 10, comeco+i*22, ESPADA6);
                mvwprintw (wtapete, 11, comeco+i*22, ESPADA7);
                mvwprintw (wtapete, 12, comeco+i*22, ESPADA8);
                mvwprintw (wtapete, 13, comeco+i*22, ESPADA9);
            }
            else if (tapete->linha_pecas[i]->desenho == CAVALEIRO)
            {
                mvwprintw (wtapete, 5 , comeco+i*22, CAVALEIRO1);
                mvwprintw (wtapete, 6 , comeco+i*22, CAVALEIRO2);
                mvwprintw (wtapete, 7 , comeco+i*22, CAVALEIRO3);
                mvwprintw (wtapete, 8 , comeco+i*22, CAVALEIRO4);
                mvwprintw (wtapete, 9 , comeco+i*22, CAVALEIRO5);
                mvwprintw (wtapete, 10, comeco+i*22, CAVALEIRO6);
                mvwprintw (wtapete, 11, comeco+i*22, CAVALEIRO7);
                mvwprintw (wtapete, 12, comeco+i*22, CAVALEIRO8);
                mvwprintw (wtapete, 13, comeco+i*22, CAVALEIRO9);
            }
            else if (tapete->linha_pecas[i]->desenho == MARTELO)
            {
                mvwprintw (wtapete, 5 , comeco+i*22, MARTELO1);
                mvwprintw (wtapete, 6 , comeco+i*22, MARTELO2);
                mvwprintw (wtapete, 7 , comeco+i*22, MARTELO3);
                mvwprintw (wtapete, 8 , comeco+i*22, MARTELO4);
                mvwprintw (wtapete, 9 , comeco+i*22, MARTELO5);
                mvwprintw (wtapete, 10, comeco+i*22, MARTELO6);
                mvwprintw (wtapete, 11, comeco+i*22, MARTELO7);
                mvwprintw (wtapete, 12, comeco+i*22, MARTELO8);
                mvwprintw (wtapete, 13, comeco+i*22, MARTELO9);
            }
            else if (tapete->linha_pecas[i]->desenho == BALANCA)
            {
                mvwprintw (wtapete, 5 , comeco+i*22, BALANCA1);
                mvwprintw (wtapete, 6 , comeco+i*22, BALANCA2);
                mvwprintw (wtapete, 7 , comeco+i*22, BALANCA3);
                mvwprintw (wtapete, 8 , comeco+i*22, BALANCA4);
                mvwprintw (wtapete, 9 , comeco+i*22, BALANCA5);
                mvwprintw (wtapete, 10, comeco+i*22, BALANCA6);
                mvwprintw (wtapete, 11, comeco+i*22, BALANCA7);
                mvwprintw (wtapete, 12, comeco+i*22, BALANCA8);
                mvwprintw (wtapete, 13, comeco+i*22, BALANCA9);
            }
        }
    }
    wattroff(wtapete,COLOR_PAIR(2));

    /*insira aqui a parte dos pontos*/

    wrefresh(wtapete);
}

void imprime_reserva (WINDOW *wreserva, t_reserva *reserva)
{
    wclear (wreserva);
    int i,j;

    wattron (wreserva,COLOR_PAIR(3));
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

        if (reserva->linha_pecas[i]->desenho == COROA)
        {
            mvwprintw (wreserva, 2, 1+i*12, "Coroa     ");
        }                                               
        else if (reserva->linha_pecas[i]->desenho == ESTANDARTE)                  
        {
            mvwprintw (wreserva, 2, 1+i*12, "Estandarte");
        }                                              
        else if (reserva->linha_pecas[i]->desenho == ESCUDO)     
        {
            mvwprintw (wreserva, 2, 1+i*12, "Escudo    ");
        }                                                 
        else if (reserva->linha_pecas[i]->desenho == ESPADA)     
        {
            mvwprintw (wreserva, 2, 1+i*12, "Espada    ");
        }                                                 
        else if (reserva->linha_pecas[i]->desenho == CAVALEIRO)     
        {
            mvwprintw (wreserva, 2, 1+i*12, "Cavaleiro ");
        }                                                 
        else if (reserva->linha_pecas[i]->desenho == MARTELO)     
        {
            mvwprintw (wreserva, 2, 1+i*12, "Martelo   ");
        }                                              
        else 
        {
            mvwprintw (wreserva, 2, 1+i*12, "Balanca   ");
        }                                                   
    }               
    wattroff(wreserva,COLOR_PAIR(3));                            
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
    else  /*caso decida por uma peca*/
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
        else  /*tira a peca da reserva e poe no tapete*/
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

int main ()
{
    initscr();
    noecho();
    curs_set(FALSE);
    
    start_color();
    init_pair (1,COLOR_WHITE,COLOR_BLUE );
    init_pair (2,COLOR_BLUE ,COLOR_WHITE);
    init_pair (3,COLOR_BLUE ,COLOR_BLACK);

    WINDOW *wtapete  = newwin (19,158,0,0);
    WINDOW *wreserva = newwin (5,86,22,0);

    t_tapete  *tapete;
    t_reserva *reserva;
    tapete = malloc(sizeof(t_tapete));
    reserva = malloc(sizeof(t_reserva));
    inicia_jogo (tapete, reserva);

    char tecla;
    tecla = getch ();
    while (tecla != 'q')
    {
        imprime_reserva (wreserva,reserva);
        imprime_tapete  (wtapete ,tapete );
        tecla = getch ();
    }
    endwin(); 
    return 0;
}      
