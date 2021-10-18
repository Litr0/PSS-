#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "pss.h"
#include "grafo.h"

// mostrarNodos: recorre en profundidad el grafo accesible desde nodo,
// mostrando nombre y nodos adyacentes de cada nodo visitado.
void mostrarNodos(Nodo *nodo, Map *idMap, int *pid) {
  // Si el nodo ya esta presente en idMap, ya fue visitado, se ignora
  if (contains(idMap, nodo))
    return;

  int id= (*pid)++; // Es el identificador asignado a este nodo
  // Registramos su id en idMap disfrazandolo como puntero (unboxing)
  define(idMap, nodo, (void*)(intptr_t)id);

  // Mostramos el nombre e identificador en el terminal
  printf("%s -> %d :", nodo->nom, id);
  if (nodo->nady>0)
    printf(" %s", nodo->adyacentes[0]->nom);
  for (int i= 1; i<nodo->nady; i++) {
    // y los nombres en los nodos adyacentes
    printf(", %s", nodo->adyacentes[i]->nom);
  }
  printf("\n");
  // Visitamos recursivamente los nodos adyacentes
  for (int i= 0; i<nodo->nady; i++) {
    // y los nombres en los nodos adyacentes
    mostrarNodos(nodo->adyacentes[i], idMap, pid);
  }
}

int main(int argc, char **argv) {
  if (argc<=1) {
    fprintf(stderr, "Uso: %s <archivos de entrada> ...\n", argv[0]);
    exit(1);
  }

  for (int i= 1; i<argc; i++) {
    char *nomFile= argv[i];
    Nodo *nodo= leerGrafo(nomFile);
    Map *idMap= makeHashMap(100, hash_ptr, pointer_equals);
    int nextId= 1;
    printf("Grafo en el archivo %s\n\n", nomFile);
    mostrarNodos(nodo, idMap, &nextId);
    MapIterator *iter=getMapIterator(idMap);
    void *keyPtr, *valPtr;
    while (mapNext(iter, &keyPtr, &valPtr)) {
      Nodo *nodo= keyPtr;
      free(nodo->nom);
      free(nodo->adyacentes);
      free(nodo);
    }
    destroyMapIterator(iter);
    destroyHashMap(idMap);
    printf("--------------------------------------------\n");
  }

  return 0;
}
