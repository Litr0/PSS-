#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "pss.h"
#include "grafo.h"

// leerGrafo: reconstruye el grafo almacenado en el archivo nomFile
Nodo *leerGrafo(char *nomFile) {
  FILE *f = fopen(nomFile,"r");
  int x = 0;
  int l=0;
  Map *m = makeHashMap(100,hash_ptr,pointer_equals);
  while((l)!=-1){
    Nodo *n = malloc(sizeof(Nodo));
    int len; 
    fread(&len, sizeof(len),1,f);
    char * nom = malloc(sizeof(len+1));
    printf(nom);
    fread(nom,len,1,f);
    n->nom=nom;
    define(m,(void*)(intptr_t)x,n);
    len=l;
    l--;
  }
  while(fread(&x,sizeof(int),1,f)){
    Nodo* node = query(m,(void *)(intptr_t)x);
    int a;
    fread(&a,sizeof(int),1,f);
    node->nady=a;
    int *ady[a];
    fread(ady,sizeof(int),a,f);
    Nodo** nady=malloc(sizeof(Nodo*)*(a));  
    int b = 0;
    while(b<a){
      *(nady+b)=query(m,(void *)(intptr_t)ady[b]);
      b++;
    }
    node->adyacentes=nady;
  }
  Nodo *c = query(m,(void *)(intptr_t)1);
  destroyHashMap(m);
  fclose(f);
  return c;
}