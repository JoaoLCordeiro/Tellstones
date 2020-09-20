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
    
}

int colocar_peca (t_tapete *tapete, t_reserva *reserva) 
{
    int i = 0;
    char tecla;
    tecla = getch ();
    /*imprime_reserva         (reserva);*/
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
        /*imprime_reserva         (reserva);*/
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
        
        /*imprime_tapete         (tapete);*/
        /*imprime_selecao_tapete (i);*/
        tecla = getch();

        while ((tecla != 'z')&&(tecla != 'x'))  /*laco para escolher onde o jogador deseja por a peca*/
        {
            if (tecla == KEY_RIGHT)             
            {
                if (i < tapete->quant_pecas-1)
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
            /*imprime_tapete         (tapete);*/
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
            int j = tapete->quant_pecas-1;
            while (j > i)
            {
                tapete->linha_pecas[j+1]->desenho = tapete->linha_pecas[j]->desenho;
                tapete->linha_pecas[j+1]->virada  = tapete->linha_pecas[j]->virada;
                j--;
            }
            tapete->linha_pecas[j]->desenho = desenho;
            tapete->linha_pecas[j]->virada  = virada;
            tapete->quant_pecas++;
        
            return 0;
        }
    }
}   
