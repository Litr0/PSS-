#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "pss.h"
#include "grafo.h"

// leerGrafo: reconstruye el grafo almacenado en el archivo nomFile
Nodo *leerGrafo(char *nomFile) {
  FILE *f = fopen(nomFile,"r");
  int ind= 1;
  int len=1;
  Map *map = makeHashMap(100,hash_ptr,pointer_equals);
  while(1){ 
    fread(&len, sizeof(int),1,f);
    if (len==-1){
      break;
    }
    char * nom = malloc(len+1);
    Nodo *guarda_name = malloc(sizeof(Nodo));
    fread(nom,len,1,f);
    *(nom+len) = 0;
    guarda_name->nom=nom;
    define(map,(void*)(intptr_t)ind,guarda_name);
    ind++;
  }
  while(fread(&ind,sizeof(int),1,f)){
    Nodo* nodo = query(map,(void *)(intptr_t)ind);
    int c;
    fread(&c,sizeof(int),1,f);
    nodo->nady=c;
    int ady[c];
    Nodo** nady=malloc(sizeof(Nodo*)*(c)); 
    fread(ady,sizeof(int),c,f); 
    int d = 0;
    while(d<c){
      *(nady+d)=query(map,(void *)(intptr_t)ady[d]);
      d++;
    }
    nodo->adyacentes=nady;
  }
  Nodo *c=query(map,(void *)(intptr_t)1);
  destroyHashMap(map);
  fclose(f);
  return c;
}
