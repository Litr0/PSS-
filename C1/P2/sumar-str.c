#include <stdio.h>
#include <string.h>

#include "sumar-str.h"
//NOTAR QUE FUNCION PASA LOS TESTS
char sumarStr(char *a, char *b) {
  char *a_1=a +strlen(a)-1; //puntero que apunta al final de a
  char *b_1=b +strlen(b)-1; //puntero que apunta al final de b
  int c=strlen(a)-1; //contador para la iteración
  char r='0';
  while(c>=0){
    char sum=(*a_1)+(*b_1)-'0';
    if ('0'<=sum+r-'0' && sum+r-'0'<='9'){ //si la suma agregando r  es menor a '9' r necesariamente tiene q tener valor '0'
      *a_1=(sum) +(r)-'0'; //como esta dentro del rango basta con asignarlo al puntero
      r='0'; 
      c--; //avanzamos en la iteracion
      a_1--;
      b_1--;
    }
    else{
      *a_1=(sum)+(r)-'0'-10; //como nos pasamos restamos 10 para quedar fuera del rango 
      r='1'; //r igual 1 al pasarnos del rango
      c--; //avanzamos en la iteracion
      a_1--;
      b_1--;
    }

  }
  return r; //retornamos r

}
