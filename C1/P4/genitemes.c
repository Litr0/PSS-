#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "item.h"

// Guarda en el archivo de nombre nomArch toda la informacion contenida
// en el arreglo itemes de tamano n
void guardarItemes(char *nomArch, Item **itemes, int n) {
  FILE *arch= fopen(nomArch, "w");
  if (arch==NULL) {
    perror(nomArch);
    exit(1);
  }
  // Primero se guarda en el archivo el numero de itemes
  fwrite(&n, sizeof(n), 1, arch);

  // Ahora grabamos cada item en el arreglo
  for (int i= 0; i<n; i++) {
    Item *item= itemes[i];
    int len= strlen(item->nom);
    fwrite(&len, sizeof(len), 1, arch); // Largo del nombre
    fwrite(item->nom, len, 1, arch);    // El nombre, sin terminacion
    fwrite(&item->peso, sizeof(item->peso), 1, arch); // El peso
    printf("%s %f\n", item->nom, item->peso);
  }
  fclose(arch);
}

void mostrarItemes(char *nomArch, Item **itemes, int n) {
  printf("Itemes en el archivo %s\n", nomArch);
  for (int i= 0; i<n; i++) {
    printf("%s %f\n", itemes[i]->nom, itemes[i]->peso);
  }
  printf("-----------------------------------------------------\n\n");
}

int main() {
  FILE *archivos= fopen("itemes.txt", "w");
  // Se grabaran 3 arreglos, cada vez mas complejos

  // Primero un arreglo de un item
  Item coquimbo= {"Coquimbo", 1.25};
  Item santiago= {"Santiago", 3.5};
  Item algarrobo= {"Algarrobo", 20.125};
  Item chillan= {"Chillan", -20.5};
  Item pichilemu= {"Pichilemu", -15.25};

  Item *arregloCoquimbo[]= { &coquimbo };
  guardarItemes("coquimbo.arr", arregloCoquimbo, 1);
  fprintf(archivos, "coquimbo.arr\n");
  mostrarItemes("coquimbo.arr", arregloCoquimbo, 1);

  Item *arregloAlgarrobo[]= { &algarrobo, &pichilemu};
  guardarItemes("algarrobo.arr", arregloAlgarrobo, 2);
  fprintf(archivos, "algarrobo.arr\n");
  mostrarItemes("algarrobo.arr", arregloAlgarrobo, 2);

  Item *arregloSantiago[]= { &santiago, &coquimbo, &algarrobo, &chillan,
                             &pichilemu};
  guardarItemes("santiago.arr", arregloSantiago, 5);
  fprintf(archivos, "santiago.arr\n");
  mostrarItemes("santiago.arr", arregloSantiago, 5);

  fclose(archivos);

  return 0;
}
