// Modulos
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

// Colores

#define BG_GREEN "\033[42m"
#define BG_BLUE "\033[44m"
#define BG_WHITE "\033[47m"
#define BG_BLACK "\033[40m"
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
#define CELDA_SELECCCIONADA printf("%s - %s", BG_BLUE, COLOR_END)

// Jugadores

#define NICK_SIZE 20
#define JUGADOR_BLANCO 2
#define JUGADOR_NEGRO 1

#define JUGADOR_NEGRO_TEXT(X) printf("%s%s%s", BG_BLACK, X, COLOR_END)
#define JUGADOR_BLANCO_TEXT(X) printf("%s%s%s", BG_WHITE, X, COLOR_END)