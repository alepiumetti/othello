// Modulos
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Colores

#define BG_GREEN "\033[42m"
#define BG_HC_GREEN "\033[0;30;102m"
#define BG_HC_YELLOW "\033[0;30;103m"
#define BG_BLUE "\033[44m"
#define BG_WHITE "\033[1;30;47m"
#define BG_BLACK "\033[1;37;40m"
#define BG_WHITE_RED "\033[1;31;40m"
#define COLOR_END "\033[0m"

// TABLERO

#define ANCHO 8 // X
#define ALTO 8  // Y

#define SIN_SELECCION -1

// ANCHO
#define X_A 0
#define X_B 1
#define X_C 2
#define X_D 3
#define X_E 4
#define X_F 5
#define X_G 6
#define X_H 7

// ALTO
#define Y_1 0
#define Y_2 1
#define Y_3 2
#define Y_4 3
#define Y_5 4
#define Y_6 5
#define Y_7 6
#define Y_8 7

// Fichas

#define FICHA_NEGRA printf("%s X %s", BG_BLACK, COLOR_END)
#define FICHA_BLANCA printf("%s O %s", BG_WHITE, COLOR_END)
#define NO_FICHA printf("%s - %s", BG_GREEN, COLOR_END)
#define CELDA_SELECCIONADA printf("%s - %s", BG_BLUE, COLOR_END)
#define CELDA_POSIBLE printf("%s - %s", BG_HC_YELLOW, COLOR_END)
#define ERROR_TEXT(X) printf("%s%s%s", BG_WHITE_RED, X, COLOR_END)
#define WARNING_TEXT(X) printf("%s%s%s", BG_HC_YELLOW, X, COLOR_END)

// Jugadores

#define NICK_SIZE 20
#define JUGADOR_BLANCO 2
#define JUGADOR_NEGRO 1
#define POSICION_BLANCO 4
#define POSICION_NEGRO 3

#define CALCULA_JUGADOR_POR_TURNO(X) ((X) % 2 == 0 ? 2 : 1)
#define CALCULA_JUGADOR_CONTRARIO_POR_TURNO(X) ((X) % 2 == 0 ? 1 : 2)
#define JUGADOR_NEGRO_TEXT(X) printf("%s%s%s", BG_BLACK, X, COLOR_END)
#define JUGADOR_BLANCO_TEXT(X) printf("%s%s%s", BG_WHITE, X, COLOR_END)

// Estados de juego

#define SIGUIENTE_TURNO 0
#define ERROR_POSICION 1
#define JUGADOR_SIN_POSICION 2
#define FINAL_DE_JUEGO -1
#define REINICIAR_JUEGO -2

// Menu

#define SALIR 0
#define JUGAR 1
#define INSTRUCTIVO 2
#define CREDITOS 3