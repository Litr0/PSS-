#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "item.h"

void mostrarItemes(char *nomArch, Item **itemes, int n) {
  printf("Itemes en el archivo %s\n", nomArch);
  for (int i= 0; i<n; i++) {
    printf("%s %f\n", itemes[i]->nom, itemes[i]->peso);
  }
  printf("-----------------------------------------------------\n\n");
}

void liberarItemes(Item **itemes, int n) {
  for (int i= 0; i<n; i++) {
    free(itemes[i]->nom);
    free(itemes[i]);
  }
  free(itemes);
}

int main(int argc, char **argv) {
  if (argc<=1) {
    fprintf(stderr, "Uso: %s <archivos de entrada> ...\n", argv[0]);
    exit(1);
  }

  for (int i= 1; i<argc; i++) {
    char *nomArch= argv[i];
    int n;
    Item **itemes= leerItemes(nomArch, &n);
    mostrarItemes(nomArch, itemes, n);
    liberarItemes(itemes, n);
  }

  return 0;
}
