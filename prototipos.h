#include "./header.h"

void muestraTablero(int tablero[ALTO][ANCHO], int filaSeleccionada,
                    int columnaSeleccionada);
void inicializaTablero(int tablero[ALTO][ANCHO]);
int juegaFichas(int tablero[ALTO][ANCHO], int turno, char jugador[]);
void ingresaJugador(char jugador[NICK_SIZE], int nro_jugador);
int verificaPosiciones(int tablero[ALTO][ANCHO], int turno);
void limpiaPosiciones(int tablero[ALTO][ANCHO]);
void convierteFichas(int tablero[ALTO][ANCHO],int turno,int y, int x);
void pausa();
int verificaFinalDeJuego(int tabler[ALTO][ANCHO]);