#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "item.h"

Item **leerItemes(char *nomFile, int *pn) {
  FILE *f= fopen(nomFile,"r"); //abrimos el archivo en modo read
  fread(pn,sizeof(*pn),1,f); //leemos n elementos de f de tamaño de pn
  Item **varios= malloc(sizeof(Item*)*(*pn)); //definimos dnd vamos a almacenar varios itemes del archivo 
  int i=0; //contador de la funcion 
  while(i<*pn){
    Item *a=malloc(sizeof(Item)); //item individual con malloc 
    int len;
    fread(&len,sizeof(len),1,f); //se extrae el largo del caracter que se lee a continuación
    char *b=malloc(len+1); //almacen con malloc de un nombre
    fread(b,len,1,f); //lectura con el char b y  del largo del caracter
    a->nom=b;  //cambiamos el nombre en a por b
    double p;
    fread(&p,sizeof(a->peso),1,f); //extraemos peso
    a->peso=p; //cambiamos los pesos 
    *varios=a; //ahora vamos agregando los items de a uno 
    varios++; //avanzamos en varios
    i++; //sumamos uno a i hasta terminar la iteracion
  }
  fclose(f); //cerramos f
  return varios-*pn; //retornamos varios al principio 
}

