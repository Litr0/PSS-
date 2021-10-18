#include <stddef.h>

#include "prev.h"
//PASA TODOS LOS TESTS
void asignarPrev(Nodo *t, Nodo **pprev) {
  if (t==NULL){ //caso base si t es NULL no se hace nada 
    return;
  }
  asignarPrev(t->izq,pprev); //recursividad hacia la izq cm se lee primero
  t->prev=*pprev; //el leido previamente es pprev y se asigna
  t->prox=NULL; //mientras se asigna el prox como NULL
  if (t->prev!=NULL){ //si prev distinto de vacio el prox del prev va a ser t
    t->prev->prox=t; 
  }
  *pprev=t; //a pprev se le asigna t 
  asignarPrev(t->der,pprev); //finalmente aplicamos la recursividad hacia la der como es lo ultimo que se debería leer por el orden
}
