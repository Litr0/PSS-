#define _DEFAULT_SOURCE 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "corregir.h"

// ----------------------------------------------------
// Funcion que entrega el tiempo de CPY usado desde
// que se invoco resetTime()

static long long time0= 0;

static long long getTime0() {
#ifndef RISCV
    struct rusage ru;
    int rc= getrusage(RUSAGE_SELF, &ru);
    if (rc!=0) {
      perror("getTime");
      exit(1);
    }
    return (long long)ru.ru_utime.tv_sec*1000000+ru.ru_utime.tv_usec;
#else
    return 0;
#endif
}

static void resetTime() {
  time0= getTime0();
}

static int getTime() {
  return (getTime0()-time0+500)/1000;
}

// ----------------------------------------------------
// mistrncpy
//

void mistrncpy(char *dest, char *src, int n) {
  char *top= dest+n;
  while (*src!=0 && dest<top)
    *dest++ = *src++;
  if (dest<top)
    *dest++= 0;
}

// ----------------------------------------------------
// verificar: chequea que str y res sean iguales.  De lo contrario diagnostica
// un resultado incorrecto.

void verificar(char *str, char *ref) {
  char *p= str, *q= ref;
  while (*p!=0 && *p==*q) {
    p++;
    q++;
  }
  if (*p==0 && *q==0)
    printf("Test aprobado\n");
  else if (strlen(ref)<80) {
    fprintf(stderr, "Resultado incorrecto: \"%s\"\n", str);
    fprintf(stderr, "Resultado debio ser: \"%s\"\n", ref);
    fprintf(stderr, "La diferencia esta en la posicion %ld: '%c' != '%c'\n",
                    p-str, *p, *q);
    fprintf(stderr, "Lo siento, su solucion no aprueba este test\n");
    exit(1);
  }
  else {
    fprintf(stderr, "Resultado incorrecto\n");
    fprintf(stderr, "Largo resultado= %ld   largo correcto= %ld\n",
                    strlen(str), strlen(ref));
    fprintf(stderr, "La diferencia esta en la posicion %ld: '%c' != '%c'\n",
                    p-str, *p, *q);
    fprintf(stderr, "Lo siento, su solucion no aprueba este test\n");
    exit(1);
  }
}

int main(int argc, char *argv[]) {
  printf ("Test unitarios\n");
  char test1[]= "";
  corregir(test1);
  verificar(test1, "");

  char test2[]= " ";
  corregir(test2);
  verificar(test2, " ");

  char test3[]= ",";
  corregir(test3);
  verificar(test3, ",");

  char test4[]= " ,";
  corregir(test4);
  verificar(test4, ",");

  char test5[]= "   ,";
  corregir(test5);
  verificar(test5, ",");

  char test6[]= "hola   que tal   ,  como estas";
  corregir(test6);
  verificar(test6, "hola   que tal,  como estas");

  char test7[]= "hola que tal,  como estas";
  corregir(test7);
  verificar(test7, "hola que tal,  como estas");

  char test8[]= "  h o, l  a  ,  q   , u  e t     ,a  l";
  corregir(test8);
  verificar(test8, "  h o, l  a,  q, u  e t,a  l");

  printf("Benchmark\n");

#define TAM 200000000
  char *pals[]= {"los", "cuatro", "puntos", "cardinales", "son", "4", ":",
                 "el", "norte", "y", "el", "sur", NULL };
  char *str= malloc(TAM+1);
  char *dest= str;
  char *fin= str+TAM;
  char *ref= malloc(TAM+1);
  char *ref_dest= ref;
  int espacios= 0;
  int i= 0;
  do {
    int len= strlen(pals[i]);
    mistrncpy(dest, pals[i], fin-dest);
    mistrncpy(ref_dest, pals[i], fin-dest);
    dest += len;
    ref_dest += len;
    char *ref_dest_orig= ref_dest;
    for (int j= 0; j<espacios && dest<fin ; j++) {
      *dest++= ' ';
      *ref_dest++= ' ';
    }
    if (dest<fin && (random()&1)==0) {
      *dest++= ',';
      ref_dest= ref_dest_orig;
      *ref_dest++= ',';
    }
    espacios++;
    i++;
    if (pals[i]==NULL)
      i= 0;
  } while (dest<fin);

  *dest++ = 0;
  *ref_dest++ = 0;

  resetTime();
  corregir(str);
  corregir(str);
  int tiempo= getTime();
  printf("Tiempo= %d milisegundos\n", tiempo);

  if (argc==2) {
    if (strcmp(argv[1], "ref")==0) {
      FILE *out= fopen("tiempo-ref.txt", "w");
      if (out==NULL) {
        perror("tiempo-ref.txt");
        exit(1);
      }
      fprintf(out, "%d\n", tiempo);
      fclose(out);
    }
    else {
      int tiempo_ref= atoi(argv[1]);
      printf("Tiempo de la solucion del profesor: %d milisegundos\n",
             tiempo_ref);
    }
  }

  verificar(str, ref);

  free(str);
  free(ref);

  printf("Felicitaciones: su solucion aprobo todos los tests\n");
  return 0;
}
