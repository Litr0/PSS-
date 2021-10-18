#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "pss.h"
#include "grafo.h"

// guardarNodo: recorre en profundidad el grafo accesible desde nodo,
// grabando en el archivo arch el nombre de cada nodo, precedido por su largo.
// En idMap queda registrado un identificador entero para cada nodo.
// *pid es la variable que almacena el proximo identificador por asignar.
// Al leer secuencialmente del archivo los nodos n1, n2, n3, etc.,
// sus identificadores seran 1, 2, 3, etc.
void guardarNodos(Nodo *nodo, Map *idMap, int *pid, FILE *arch) {
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

  int len= strlen(nodo->nom);  // Largo del nombre
  // Guardamos el largo del nombre
  fwrite(&len, sizeof(int), 1, arch);
  // Guardamos el nombre sin la terminacion del string
  fwrite(nodo->nom, len, 1, arch);

  // Recorremos recursivamente los nodos adyacentes
  for (int i= 0; i<nodo->nady; i++) {
    guardarNodos(nodo->adyacentes[i], idMap, pid, arch);
  }
}

// guardarGrafo: guarda todo el grafo accesible desde nodo en un archivo de
// nombre nomFile.  Para lograrlo, se recorre en profundidad el grafo usando
// la funcion recursiva guardarNodos.  guardarNodos graba los nombres
// encontrados en cada nodo en el formato largo en binario, seguido de los
// caracters del nombre, sin incluir la terminacion del string.
// Si el largo es -1, quiere decir que ya no hay mas nodos.
//
// A continuacion, la funcion guardarGrafo graba los nodos adyacentes
// a cada nodo.  Como no se pueden guardar punteros en el archivo, los nodos
// se identifican como 1, 2, 3, ..., etc., siendo el nodo i, el i-esimo nodo
// guardado en el archivo.  Entonces, para cada nodo en el grafo se
// guardan sus nodos adyacentes en el siguiente formato binario: primero
// viene el numero del nodo en 4 bytes en binario, luego viene el numero
// de nodos adyacentes k en 4 bytes en binario, y finalmente vienen k enteros
// de 4 bytes cada uno, en binario, con los identificadores de los nodos
// adyacentes.
//
// Cuando lea el grafo, debera traducir los identificadores enteros de los
// nodos a punteros a nodos.
void guardarGrafo(char *nomFile, Nodo *nodo) {
  printf("Grafo en el archivo %s\n\n", nomFile);
  FILE *arch= fopen(nomFile, "w");
  if (arch==NULL) {
    perror(nomFile);
    exit(1);
  }
  // Primero se guarda en el archivo los nombres en los nodos
  // y se asigna un identificador entero a cada nodo
  Map *idMap= makeHashMap(100, hash_ptr, pointer_equals);
  int nextId= 1;
  // Recorrido en profundidad del grafo a partir de nodo
  guardarNodos(nodo, idMap, &nextId, arch);
  // Ahora (intptr_t)query(idMap, nodo) entrega el entero que identifica a nodo.
  // En el archivo ya estan grabados los nombres de los nodos, pero no los
  // nodos adyacentes.

  // Guardamos un entero con -1 para marcar el fin de los nodos.
  // Al leer el archivo, si el largo del nombre del proximo nodo es -1,
  // quiere decir que ya no hay mas nodos.
  int marca= -1;
  fwrite(&marca, sizeof(int), 1, arch);

  // Luego grabamos los datos de los nodos adyacentes
  MapIterator *iter= getMapIterator(idMap);
  void *keyPtr, *valPtr;
  while (mapNext(iter, &keyPtr, &valPtr)) {
    Nodo *nodo= keyPtr;
    // Los nodos se recorren en desorden.  El primer nodo no necesariamente
    // el el nodo 1.
    int id= (intptr_t)valPtr; // El id esta disfrazado de puntero (unboxing)
    // Creamos un arreglo para los identificadores de los nodos adyacentes
    int idAdy[nodo->nady];

    for (int j= 0; j<nodo->nady; j++) {
      // En la posicion j del arreglo asignamos el identificador de j-esimo
      // nodo adyacente del nodo id
      idAdy[j]= (intptr_t)query(idMap, nodo->adyacentes[j]);
    }

    // Guardamos el identificador en el archivo
    fwrite(&id, sizeof(int), 1, arch);
    // Guardamos el numero de nodos adyacentes en el archivo
    fwrite(&nodo->nady, sizeof(nodo->nady), 1, arch);
    // Guardamos el arreglo de identificadores de los nodos adyacentes
    // al nodo id, en formato binario
    fwrite(&idAdy[0], sizeof(int), nodo->nady, arch);
  }
  destroyMapIterator(iter);
  destroyHashMap(idMap);
  fclose(arch);
  printf("--------------------------------------------\n");
}

int main() {
  FILE *grafos= fopen("grafos.txt", "w");
  // Se grabaran 4 grafos, cada vez mas complejos

  // Primero un grafo de un solo nodo, sin nodos adyacentes
  Nodo coquimbo= {"Coquimbo", 0, NULL};
  Nodo *ady_coquimbo[]= { NULL };
  coquimbo.adyacentes= ady_coquimbo;

  guardarGrafo("coquimbo.gf", &coquimbo);
  fprintf(grafos, "coquimbo.gf\n");

  // Ahora un grafo de 2 nodos: la raiz tiene un nodo adyacente, pero el
  // segundo nodo no tiene nodos adyacentes
  Nodo algarrobo= {"Algarrobo", 1, NULL};
  Nodo casablanca= {"Casablanca", 0, NULL};
  Nodo *ady_algarrobo[]= { &casablanca };
  Nodo *ady_casablanca[]= { NULL };
  algarrobo.adyacentes= ady_algarrobo;
  casablanca.adyacentes= ady_casablanca;

  guardarGrafo("algarrobo.gf", &algarrobo);
  fprintf(grafos, "algarrobo.gf\n");

  // El tercer grafo tiene 3 nodos y hay un ciclo
  Nodo antofagasta= {"antofagasta", 1, NULL};
  Nodo calama= {"calama", 2, NULL};
  Nodo iquique= {"iquique", 1, NULL};

  Nodo *ady_antofagasta[]= { &calama };
  Nodo *ady_calama[]= { &antofagasta, &iquique };
  Nodo *ady_iquique[]= { &antofagasta };

  antofagasta.adyacentes= ady_antofagasta;
  calama.adyacentes= ady_calama;
  iquique.adyacentes= ady_iquique;

  guardarGrafo("antofagasta.gf", &antofagasta);
  fprintf(grafos, "antofagasta.gf\n");

  // El cuarto grafo tiene 10 nodos y hay 2 nodos con el mismo nombre, no es
  // un error
  Nodo las_cruces= { "Las Cruces", 3, NULL };
  Nodo llolleo= { "Llolleo", 4, NULL };
  Nodo santo_domingo= {"Santo Domingo", 2, NULL};
  Nodo rapel= {"Rapel", 5, NULL};
  Nodo pichilemu= {"Pichilemu", 3, NULL};
  Nodo chillan= {"Chillan", 5, NULL};
  Nodo ancud= {"Ancud", 2, NULL};
  Nodo chacao= {"Chacao", 2, NULL};
  Nodo ahui= {"Ahui", 1, NULL};
  Nodo rapel2= {"Rapel", 2, NULL};
  
  Nodo *ady_las_cruces[] = {&llolleo, &santo_domingo, &rapel};
  Nodo *ady_llolleo[] = {&las_cruces, &santo_domingo, &rapel, &pichilemu};
  Nodo *ady_santo_domingo[] = {&llolleo, &rapel};
  Nodo *ady_rapel[] = {&llolleo, &rapel2, &pichilemu, &chillan, &las_cruces};
  Nodo *ady_pichilemu[] = {&llolleo, &rapel, &chillan};
  Nodo *ady_chillan[] = {&pichilemu, &rapel, &chacao, &las_cruces, &llolleo};
  Nodo *ady_ancud[] = {&ahui, &chacao};
  Nodo *ady_chacao[] = {&chillan, &ancud};
  Nodo *ady_ahui[] = {&ancud};
  Nodo *ady_rapel2[] = {&rapel, &pichilemu};

  las_cruces.adyacentes= ady_las_cruces;
  llolleo.adyacentes= ady_llolleo;
  santo_domingo.adyacentes= ady_santo_domingo;
  rapel.adyacentes= ady_rapel;
  pichilemu.adyacentes= ady_pichilemu;
  chillan.adyacentes= ady_chillan;
  ancud.adyacentes= ady_ancud;
  chacao.adyacentes= ady_chacao;
  ahui.adyacentes= ady_ahui;
  rapel2.adyacentes= ady_rapel2;

  guardarGrafo("las-cruces.gf", &las_cruces);
  fprintf(grafos, "las-cruces.gf\n");

  fclose(grafos);

  return 0;
}
