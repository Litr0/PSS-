#include <stdlib.h>
#include "descomponer.h"
void descomponer(Nodo *t, int z, Nodo **pinf, Nodo **psup) {
  if (t == NULL){
    *pinf=NULL;
    *psup=NULL;
    return;
  }
  if (t->x <= z){
    descomponer((t->der),z,pinf,psup);
    t->der=*pinf;
    *pinf=t;
  }
  if(t->x>z){
    descomponer((t->izq),z,pinf,psup);
    t->izq=*psup;
    *psup=t;
  }
}
void descomposicion(Nodo *t, int z, Nodo **pinf, Nodo **psup) {
  Nodo *c;
  if(t==NULL){
    c=NULL;
    *pinf=NULL;
    *psup=NULL;
    return;
  }
  c=(Nodo*)malloc(sizeof(Nodo));
  c->x=t->x;
  if (t->x<=z){
    c->izq=t->izq;
    descomposicion(t->der,z,pinf,psup);
    c->der=*pinf;
    *pinf=c;
  }
  else{
    c->der=t->der;
    descomposicion(t->izq,z,pinf,psup);
    c->izq=*psup;
    *psup=c;
  }  
  return;
}
