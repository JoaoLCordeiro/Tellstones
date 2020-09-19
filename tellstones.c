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

int colocar_peca (t_tapete *tapete, t_reserva *reserva) 
{
    int i=0;
    char tecla;
    tecla = getch ();
    /*imprime_reserva (reserva);*/
    /*imprime_selecao (i);*/
    while (tecla != 'z')
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
        /*imprime_reserva (reserva);*/
        /*imprime_selecao (i);*/
    }

}   
