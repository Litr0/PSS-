#include <string.h>
#include <stdlib.h>

#include "corregir.h"
//pasa los test
void corregir(char *s) {
  char *p=s; //puntero que apunta al principio 
  char *sig=s; // puntero que se mueve por el char
  while(*sig!='\0'){ //iteracion hasta que lleguemos al final del string
    if(*sig==' '){ //si encontramos un espacio
      for(s=sig;*s==' ';s++){ //avanzamos s hasta llegar a algo distinto a un espacio 
      }
      if (*s==','){ //si encontramos una coma 
        sig=s; 
      }
    }
    *p=*sig; //ahora p debe apuntar al sig 
    p++; //avanzamos en las variables
    s++;
    sig++;
  }
  *p='\0'; //agregamos \0 a p
}   
