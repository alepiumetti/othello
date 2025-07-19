#include "./header.h"
#include "./prototipos.h"
#include <stdio.h>

void pausa() {
  // Limpia el búfer de entrada
  printf("Presione Enter para continuar...");
  while (getchar() != '\n')
    ;
  while (getchar() != '\n')
    ; // Espera hasta que se presione Enter
}

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

  while (turno != -1) {

    int estado_de_juego = juegaFichas(
        tablero, turno,
        CALCULA_JUGADOR_POR_TURNO(turno) == 2 ? jugadorBlanco : jugadorNegro);

    switch (estado_de_juego) {
    case SIGUIENTE_TURNO:
      turno++;
      break;
    case ERROR_POSICION:
      printf("\nERROR: Posicion invalida, seleccione una posicion de las "
             "opciones con fondo amarillo.\n");
      pausa();
      break;
    case JUGADOR_SIN_POSICION:
      printf("\nAVISO:Este turno no tiene una posicion valida de juego\n");
      turno++;
      pausa();
      break;
    case FINAL_DE_JUEGO:
      turno = -1;
      printf("\n\nLLEGO EL FINAL DEL JUEGO!\n\n");
      break;
    default:
      turno++;
      break;
    }
  }
  return 0;
}

int juegaFichas(int tablero[ALTO][ANCHO], int turno, char jugador[]) {

  limpiaPosiciones(tablero);
  int fila, columna;
  // do {

  fila = 1;
  columna = 65;
  int posiciones_posibles = verificaPosiciones(tablero, turno);

  if (posiciones_posibles == 0) {
    // Si no hay posiciones posibles verifica que todavia haya posiciones
    // jugables
    if (verificaFinalDeJuego == FINAL_DE_JUEGO) {
      return FINAL_DE_JUEGO;
    } else {
      return JUGADOR_SIN_POSICION;
    }
  }

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
    // Limpia el buffer de entrada
    while (getchar() != '\n')
      ;
    scanf("%c", &letra);

    // Convierte la letra a entero

    columna = letra;

  } while (columna < 65 || columna > 72);

  // Formatea el valor de la letra en una posicion entendible para la matriz
  columna = columna - 65;

  // } while (tablero[fila][columna] != (CALCULA_JUGADOR_POR_TURNO(turno) + 2));

  // Muestra aviso de ingreso de posicion erroneo
  if (tablero[fila][columna] != (CALCULA_JUGADOR_POR_TURNO(turno) + 2) ||
      tablero[fila][columna] == 0) {
    return ERROR_POSICION;
  }

  // Verifica que la posicion en la que quiere poner el jugador sea valida
  tablero[fila][columna] = CALCULA_JUGADOR_POR_TURNO(turno);

  convierteFichas(tablero, turno, fila, columna);

  return SIGUIENTE_TURNO;
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
          } else if (tablero[y][x] == POSICION_BLANCO ||
                     tablero[y][x] == POSICION_NEGRO) {
            CELDA_POSIBLE;
          } else {
            if (y == filaSeleccionada) {
              // En el caso de que una posicion vertical este seleccionada
              // muestra toda la fila celeste para mostrar las opciones que
              // tiene de posicionar una ficha.
              CELDA_SELECCIONADA;
            } else if (x == columnaSeleccionada) {
              // En caso de que la columna este seleccionada, muestra todas sus
              // celdas seleccionadas
              CELDA_SELECCIONADA;
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

int verificaPosiciones(int tablero[ANCHO][ALTO], int turno) {

  // Cuenta las cantidad de posiciones posibles

  int posiciones_posibles = 0;

  // busca las fichas del turno

  for (int y = 0; y < ALTO; y++) {
    for (int x = 0; x < ANCHO; x++) {

      if (CALCULA_JUGADOR_POR_TURNO(turno) == tablero[y][x]) {

        int valDEBUG = tablero[y][x];

        // busca fichas contrarias
        //  verifica derecha
        if (CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno) == tablero[y][x + 1]) {
          // Empieza a buscar por un espacio libre
          int x_temp = x + 1;

          while (x_temp < ANCHO &&
                 tablero[y][x_temp] ==
                     CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno)) {
            x_temp++;
          }

          if (x_temp < ANCHO && tablero[y][x_temp] == 0 &&
              tablero[y][x_temp - 1] ==
                  CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno)) {
            tablero[y][x_temp] = CALCULA_JUGADOR_POR_TURNO(turno) + 2;
            posiciones_posibles++;
          }
        }
        // verifica izquierda

        if (CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno) == tablero[y][x - 1]) {
          // Empieza a buscar por un espacio libre
          int x_temp = x - 1;

          while (x_temp > 0 && tablero[y][x_temp] ==
                                   CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno)) {
            x_temp--;
          }

          if (x_temp >= 0 && tablero[y][x_temp] == 0 &&
              tablero[y][x_temp + 1] ==
                  CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno)) {
            tablero[y][x_temp] = CALCULA_JUGADOR_POR_TURNO(turno) + 2;
            posiciones_posibles++;
          }
        }

        // verifica abajo

        if (CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno) == tablero[y + 1][x]) {
          // Empieza a buscar por un espacio libre
          int y_temp = y + 1;

          while (y_temp < ALTO &&
                 tablero[y_temp][x] ==
                     CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno)) {
            y_temp++;
          }

          if (y_temp < ALTO && tablero[y_temp][x] == 0 &&
              tablero[y_temp - 1][x] ==
                  CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno)) {
            tablero[y_temp][x] = CALCULA_JUGADOR_POR_TURNO(turno) + 2;
            posiciones_posibles++;
          }
        }

        // verifica arriba

        if (CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno) == tablero[y - 1][x]) {
          // Empieza a buscar por un espacio libre
          int y_temp = y - 1;

          while (y_temp > 0 && tablero[y_temp][x] ==
                                   CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno)) {
            y_temp--;
          }

          if (y_temp >= 0 && tablero[y_temp][x] == 0 &&
              tablero[y_temp + 1][x] ==
                  CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno)) {
            tablero[y_temp][x] = CALCULA_JUGADOR_POR_TURNO(turno) + 2;
            posiciones_posibles++;
          }
        }

        // verifica abajo - derecha

        if (CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno) ==
            tablero[y + 1][x + 1]) {
          // Empieza a buscar por un espacio libre
          int y_temp = y + 1;
          int x_temp = x + 1;

          while (y_temp < ALTO && x_temp < ANCHO &&
                 tablero[y_temp][x_temp] ==
                     CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno)) {
            y_temp++;
            x_temp++;
          }

          if (y_temp < ALTO && x_temp < ANCHO && tablero[y_temp][x_temp] == 0 &&
              tablero[y_temp - 1][x_temp - 1] ==
                  CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno)) {
            tablero[y_temp][x_temp] = CALCULA_JUGADOR_POR_TURNO(turno) + 2;
            posiciones_posibles++;
          }
        }

        // verifica arriba - izquierda

        if (CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno) ==
            tablero[y - 1][x - 1]) {
          // Empieza a buscar por un espacio libre
          int y_temp = y - 1;
          int x_temp = x - 1;

          while (y_temp > 0 && x_temp > 0 &&
                 tablero[y_temp][x_temp] ==
                     CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno)) {
            y_temp--;
            x_temp--;
          }

          if (y_temp >= 0 && x_temp >= 0 && tablero[y_temp][x_temp] == 0 &&
              tablero[y_temp + 1][x_temp + 1] ==
                  CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno)) {
            tablero[y_temp][x_temp] = CALCULA_JUGADOR_POR_TURNO(turno) + 2;
            posiciones_posibles++;
          }
        }

        // verifica arriba - derecha
        if (CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno) ==
            tablero[y - 1][x + 1]) {
          // Empieza a buscar por un espacio libre
          int y_temp = y - 1;
          int x_temp = x + 1;

          while (y_temp > 0 && x_temp > 0 &&
                 tablero[y_temp][x_temp] ==
                     CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno)) {
            y_temp--;
            x_temp++;
          }

          if (y_temp >= 0 && x_temp < ANCHO && tablero[y_temp][x_temp] == 0 &&
              tablero[y_temp + 1][x_temp - 1] ==
                  CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno)) {
            tablero[y_temp][x_temp] = CALCULA_JUGADOR_POR_TURNO(turno) + 2;
            posiciones_posibles++;
          }
        }

        // verifica abajo - izquierda
        if (CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno) ==
            tablero[y + 1][x - 1]) {
          // Empieza a buscar por un espacio libre
          int y_temp = y + 1;
          int x_temp = x - 1;

          while (y_temp > 0 && x_temp > 0 &&
                 tablero[y_temp][x_temp] ==
                     CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno)) {
            y_temp++;
            x_temp--;
          }

          if (y_temp < ALTO && x_temp >= 0 && tablero[y_temp][x_temp] == 0 &&
              tablero[y_temp - 1][x_temp + 1] ==
                  CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno)) {
            tablero[y_temp][x_temp] = CALCULA_JUGADOR_POR_TURNO(turno) + 2;
            posiciones_posibles++;
          }
        }
      }
    }
  }

  return posiciones_posibles;
}

void limpiaPosiciones(int tablero[ALTO][ANCHO]) {
  for (int y = 0; y < ALTO; y++) {
    for (int x = 0; x < ANCHO; x++) {
      if (tablero[y][x] == POSICION_BLANCO || tablero[y][x] == POSICION_NEGRO) {
        tablero[y][x] = 0;
      }
    }
  }
}

int verificaFinalDeJuego(int tablero[ALTO][ANCHO]) {

  int posiciones_jugables = 0;

  for (int y = 0; y < ALTO; y++) {
    for (int x = 0; x < ANCHO; x++) {
      if (tablero[y][x] == 0) {
        posiciones_jugables++;
      }
    }
  }

  if (posiciones_jugables > 0) {
    return FINAL_DE_JUEGO;
  } else {
    return SIGUIENTE_TURNO;
  }
}

void convierteFichas(int tablero[ALTO][ANCHO], int turno, int y, int x) {
  // Toma la ultima ficha puesta
  // Verifica para todos lados donde tiene que convertir las fichas intermedias

  int x_temp, y_temp;

  // Verifica y convierte arriba

  y_temp = y - 1;

  // verifica si en una posicion arriba hay una ficha contraria

  if (tablero[y_temp][x] == CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno)) {

    // busca la siguiente ficha del jugador o el borde superior del tablero

    while (tablero[y_temp][x] == CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno) &&
           y_temp > 0) {
      y_temp--;
    }

    // si la ultima posicion que encontro es la de un jugador convierte las
    // fichas
    if (tablero[y_temp][x] == CALCULA_JUGADOR_POR_TURNO(turno) && y_temp != 0) {
      for (int index = y; index > y_temp; index--) {
        tablero[index][x] = CALCULA_JUGADOR_POR_TURNO(turno);
      }
    }
  }

  // verifica y convierte abajo

  y_temp = y + 1;

  // Verifica si hay una ficha contraria en la posicion de abajo

  if (tablero[y_temp][x] == CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno)) {

    // Busca la ficha mas proxima o el borde inferior

    while (tablero[y_temp][x] == CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno) &&
           y_temp < ALTO) {
      y_temp++;
    }

    // si la ficha que encontro es propia
    // cambia todas las fichas entre la jugada y la mas proxima encontrada

    if (tablero[y_temp][x] == CALCULA_JUGADOR_POR_TURNO(turno) &&
        y_temp != ALTO) {
      for (int index = y; index < y_temp; index++) {
        tablero[index][x] = CALCULA_JUGADOR_POR_TURNO(turno);
      }
    }
  }

  // verifica y convierte derecha

  x_temp = x + 1;

  if (tablero[y][x_temp] == CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno)) {
    while (tablero[y][x_temp] == CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno) &&
           x_temp < ANCHO) {
      x_temp++;
    }

    if (tablero[y][x_temp] == CALCULA_JUGADOR_POR_TURNO(turno) &&
        x_temp != ANCHO) {
      for (int index = x; index < x_temp; index++) {
        tablero[y][index] = CALCULA_JUGADOR_POR_TURNO(turno);
      }
    }
  }

  // verifica y convierte izquierda

  x_temp = x - 1;

  if (tablero[y][x_temp] == CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno)) {
    while (tablero[y][x_temp] == CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno) &&
           x_temp > 0) {
      x_temp--;
    }

    if (tablero[y][x_temp] == CALCULA_JUGADOR_POR_TURNO(turno) && x_temp != 0) {
      for (int index = x; index > x_temp; index--) {
        tablero[y][index] = CALCULA_JUGADOR_POR_TURNO(turno);
      }
    }
  }

  // verifica y convierte abajo

  y_temp = y + 1;

  if (tablero[y_temp][x] == CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno)) {
    while (tablero[y_temp][x] == CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno) &&
           y_temp < ALTO) {
      y_temp++;
    }

    if (tablero[y_temp][x] == CALCULA_JUGADOR_POR_TURNO(turno) &&
        y_temp != ALTO) {
      for (int index = y; index < y_temp; index++) {
        tablero[index][x] = CALCULA_JUGADOR_POR_TURNO(turno);
      }
    }
  }

  // verifica y convierte arriba

  y_temp = y - 1;

  if (tablero[y_temp][x] == CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno)) {
    while (tablero[y_temp][x] == CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno) &&
           y_temp > 0) {
      y_temp--;
    }

    if (tablero[y_temp][x] == CALCULA_JUGADOR_POR_TURNO(turno) && y_temp != 0) {
      for (int index = y; index > y_temp; index--) {
        tablero[y_temp][x] = CALCULA_JUGADOR_POR_TURNO(turno);
      }
    }
  }


  // verifica y convierte arriba - izquierda

  y_temp = y - 1;
  x_temp = x - 1;

  if (tablero[y_temp][x_temp] == CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno)) {
    while (tablero[y_temp][x_temp] ==
               CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno) &&
           y_temp > 0 && x_temp > 0) {
      x_temp--;
      y_temp--;
    }

    if (tablero[y_temp][x_temp] == CALCULA_JUGADOR_POR_TURNO(turno) &&
        x_temp != 0 && y_temp != 0) {
      // Variables temporales creadas para el bucle
      int i = y - 1;
      int j = x - 1;

      while (i > y_temp && j > x_temp) {
        tablero[i][j] = CALCULA_JUGADOR_POR_TURNO(turno);
        i--;
        j--;
      }
    }
  }

  // verifica y convierte arriba - derecha

  y_temp = y - 1;
  x_temp = x + 1;

  if (tablero[y_temp][x_temp] == CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno)) {
    while (tablero[y_temp][x_temp] ==
               CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno) &&
           y_temp > 0 && x_temp < ANCHO) {
      x_temp++;
      y_temp--;
    }

    if (tablero[y_temp][x_temp] == CALCULA_JUGADOR_POR_TURNO(turno) &&
        x_temp != ANCHO && y_temp != 0) {
      // Variables temporales creadas para el bucle
      int i = y - 1;
      int j = x + 1;

      while (i > y_temp && j < x_temp) {
        tablero[i][j] = CALCULA_JUGADOR_POR_TURNO(turno);
        i--;
        j++;
      }
    }
  }

  // verifica y convierte abajo - izquierda

  y_temp = y + 1;
  x_temp = x - 1;

  if (tablero[y_temp][x_temp] == CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno)) {
    while (tablero[y_temp][x_temp] ==
               CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno) &&
           y_temp < ALTO && x_temp > 0) {
      x_temp--;
      y_temp++;
    }

    if (tablero[y_temp][x_temp] == CALCULA_JUGADOR_POR_TURNO(turno) &&
        x_temp != 0 && y_temp != ALTO) {
      // Variables temporales creadas para el bucle
      int i = y + 1;
      int j = x - 1;

      while (i < y_temp && j > x_temp) {
        tablero[i][j] = CALCULA_JUGADOR_POR_TURNO(turno);
        i++;
        j--;
      }
    }
  }

  // verifica y convierte abajo - derecha
  y_temp = y + 1;
  x_temp = x + 1;

  if (tablero[y_temp][x_temp] == CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno)) {
    while (tablero[y_temp][x_temp] ==
               CALCULA_JUGADOR_CONTRARIO_POR_TURNO(turno) &&
           y_temp < ALTO && x_temp < ANCHO) {
      x_temp++;
      y_temp++;
    }

    if (tablero[y_temp][x_temp] == CALCULA_JUGADOR_POR_TURNO(turno) &&
        x_temp != ANCHO && y_temp != ALTO) {
      // Variables temporales creadas para el bucle
      int i = y + 1;
      int j = x + 1;

      while (i < y_temp && j < x_temp) {
        tablero[i][j] = CALCULA_JUGADOR_POR_TURNO(turno);
        i++;
        j++;
      }
    }
  }
}