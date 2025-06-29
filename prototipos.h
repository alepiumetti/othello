#include "./header.h"

void muestraTablero(int tablero[ALTO][ANCHO], int filaSeleccionada,
                    int columnaSeleccionada);
void inicializaTablero(int tablero[ALTO][ANCHO]);
void juegaFichas(int tablero[ALTO][ANCHO], int turno, char jugador[]);
void ingresaJugador(char jugador[NICK_SIZE], int nro_jugador);
void verificaPosiciones(int tablero[ALTO][ANCHO], int turno);
void limpiaPosiciones(int tablero[ALTO][ANCHO]);