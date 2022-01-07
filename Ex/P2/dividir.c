#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "dividir.h"
//pasa todos los tests
void dividir(Nodo *nodo, Nodo **pimpares, Nodo **ppares) {
  if (nodo==NULL){ //caso base
    *pimpares=NULL;
    *ppares=NULL;
    return;
  } //si en la recursividad anterior usamos impar ahora sigue par y viceversa
  dividir(nodo->prox,ppares,pimpares);//agregamos siempre a pimpares y damos vuelta los parametros en la recursividad
  nodo->prox=*pimpares;
  *pimpares=nodo;
}
