#include "./header.h"
#include "./prototipos.h"

int main() {

  srand(time(NULL));

  int tablero[ALTO][ANCHO] = {0};

  // Para sortear el turno inicializarlo en 1 o 2
  // Dependiendo del nro de turno (par o impar) va a comenzar determinado
  // jugador negro = 1 y blanco = 2
  int turno = 0;

  char jugadorNegro[NICK_SIZE] = "";
  char jugadorBlanco[NICK_SIZE] = "";

  system("clear");

  // Ingresa Nombre de jugadores

  ingresaJugador(jugadorNegro, JUGADOR_NEGRO);
  ingresaJugador(jugadorBlanco, JUGADOR_BLANCO);

  // Inicializa tablero con fichas iniciales

  inicializaTablero(tablero);

  muestraTablero(tablero, SIN_SELECCION, SIN_SELECCION);

  while (turno < 10) {

    juegaFichas(tablero, turno, jugadorBlanco);
    turno++;

  }

  return 0;
}

void juegaFichas(int tablero[ALTO][ANCHO], int turno, char jugador[]) {

  int fila = 1,columna = 65;

  // Ingresa la posicion de la fila que va a seleccionar
  do {
    muestraTablero(tablero, SIN_SELECCION, SIN_SELECCION);
    printf("Turno de ");
    turno % 2 == 0 ? JUGADOR_BLANCO_TEXT(jugador) : JUGADOR_NEGRO_TEXT(jugador);
    printf("\n");
    if (fila < 1 || fila > 8) {
      printf("ERROR: Debe ingresar un numero entre 1 y 8\n");
    }
    printf("Fila (1-8):");
    scanf("%d", &fila);
  } while (fila < 1 || fila > 8);

  // Ubica correctamente la seleccion de la fila
  fila = fila - 1;

  char letra = 'A';
  
  do {
    muestraTablero(tablero, fila, SIN_SELECCION);
    printf("Turno de ");
    turno % 2 == 0 ? JUGADOR_BLANCO_TEXT(jugador) : JUGADOR_NEGRO_TEXT(jugador);
    printf("\n");
    if (columna < 65 || columna > 72) {
      printf("Error: Debe ingresar una letra entre A y H\n");
    };
    printf("Columna (A-H):");
    // Limpia el búfer de entrada
    while (getchar() != '\n'); 
    scanf("%c", &letra);

    // Convierte la letra a entero

    columna = letra;

  } while (columna < 65 || columna > 72);

  // Formatea el valor de la letra en una posicion entendible para la matriz
  columna = columna - 65;



  if (turno % 2 == 0) {
    tablero[fila][columna] = 2;
  } else {
    tablero[fila][columna] = 1;
  }
}

void ingresaJugador(char jugador[NICK_SIZE], int nro_jugador) {

  printf("Ingrese el nombre del jugador ");
  nro_jugador == JUGADOR_NEGRO ? JUGADOR_NEGRO_TEXT("color negro")
                               : JUGADOR_BLANCO_TEXT("color blanco");
  printf(": ");
  // TODO: validar input de 0 a 20 caracteres
  scanf("%19s", jugador); // Lee hasta 19 caracteres para evitar desbordamiento
}

void muestraTablero(int tablero[ALTO][ANCHO], int filaSeleccionada,
                    int columnaSeleccionada) {

  system("clear");

  printf("        TABLERO     \n");

  for (int y = 0; y <= ALTO; y++) {
    for (int x = 0; x <= ANCHO; x++) {
      if (y == ALTO) {
        if (x == ANCHO) {
          printf(" / ");
        } else {
          // Imprime la ultima fila con los nros de posicion Y
          printf(" %c ", x + 65);
        }
      } else {
        if (x == ANCHO) {
          // Imprime la ultima columna con las letras de posicion X
          printf(" %d ", y + 1);
        } else {
          if (tablero[y][x] == JUGADOR_NEGRO) {
            // En el caso de que el valor sea 1 muestra ficha negra
            FICHA_NEGRA;
          } else if (tablero[y][x] == JUGADOR_BLANCO) {
            // En caso de que el valor sea 2 muestra ficha blanca
            FICHA_BLANCA;
          } else {
            if (y == filaSeleccionada) {
              // En el caso de que una posicion vertical este seleccionada muestra toda la fila celeste para mostrar las opciones que tiene de posicionar una ficha.
              CELDA_SELECCCIONADA;
            } else if (x == columnaSeleccionada) {
              // En caso de que la columna este seleccionada, muestra todas sus celdas seleccionadas
              CELDA_SELECCCIONADA;
            } else {
              NO_FICHA;
            }
          }
        }
      }
    }
    printf("\n");
  }
  printf("\n");
}

void inicializaTablero(int tablero[ALTO][ANCHO]) {
  // Aleatoriamente inicializa el tablero en alguna de las dos formas posibles
  if (rand() % 2 == 0) {
    tablero[Y_4][X_D] = JUGADOR_BLANCO;
    tablero[Y_5][X_D] = JUGADOR_NEGRO;
    tablero[Y_4][X_E] = JUGADOR_NEGRO;
    tablero[Y_5][X_E] = JUGADOR_BLANCO;
  } else {
    tablero[Y_4][X_D] = JUGADOR_BLANCO;
    tablero[Y_5][X_D] = JUGADOR_BLANCO;
    tablero[Y_4][X_E] = JUGADOR_NEGRO;
    tablero[Y_5][X_E] = JUGADOR_NEGRO;
  }
}