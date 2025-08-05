void clearConsole() {
  if (system("clear") != 0) {
    fprintf(stderr, "Error al ejecutar 'clear'\n");
  }
}

void clearBuffer() {
  while (getchar() != '\n')
    ;
}

void pausa() {
  // Limpia el búfer de entrada
  WARNING_TEXT("Presione Enter para continuar...");
  clearBuffer(); // Espera hasta que se presione Enter
}

void printTitle() {
  printf("----");
  SUCCESS_TEXT("Othello");
  printf(" / ");
  SUCCESS_TEXT("Reversi");
  printf("----\n\n");
}