#include <string.h>
#include <stdlib.h>

#include "desplazar.h"
//Tarea 2 Gonzalo Sobarzo
void desplazar(char *str, int from, int nbytes, int by) {
  int c;
  char *a=str;
  char *b=str;
  if(by>0){
    c=nbytes-1;
    if ((from+nbytes+by)>strlen(a)){
      c-=(from+nbytes+by)-strlen(a);
    }
    a+=from+c;
    b=a+by;
    while(c>=0){
      *b=*a;
      c--;
      a--;
      b--; 
    }
  }
  else{
    c=0;
    if(from+by<0){
      c-=from+by;
      from-=from+by;
    }
    a+=from;
    b=a+by;
    while(c<=nbytes-1){
      *b=*a;
      c++;
      a++;
      b++; 
    }
  }     
}

char *desplazamiento(char *str, int from, int nbytes, int by) {
  char *str_c=malloc(strlen(str)+1);
  strcpy(str_c,str);
  desplazar(str_c,from,nbytes,by);
  return str_c;
  free(str_c);
}