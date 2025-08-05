#include "./header.h"

// Funciones de interfaz e interaccion
int menu();
void ingresaJugador(char jugador[NICK_SIZE], int nro_jugador);

// Funciones inializadoras o de muestra
void inicializaTablero(int tablero[ALTO][ANCHO]);
void limpiaPosiciones(int tablero[ALTO][ANCHO]);
void muestraTablero(int tablero[ALTO][ANCHO], int filaSeleccionada, int columnaSeleccionada);

// Logica de juego de fichas
int juegaFichas(int tablero[ALTO][ANCHO], int turno, char jugador[]);

// Verificaciones y calculos
void convierteFichas(int tablero[ALTO][ANCHO], int turno, int y, int x);
int calculaCantidadFichas(int tablero[ALTO][ANCHO]);
int verificaPosiciones(int tablero[ALTO][ANCHO], int turno);
int verificaFinalDeJuego(int tablero[ALTO][ANCHO]);

// Funciones utilitarias
void pausa();
void clearConsole();
void clearBuffer();
void printTitle();