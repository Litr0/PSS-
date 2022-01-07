#define _DEFAULT_SOURCE 1

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "dividir.h"

#pragma GCC diagnostic ignored "-Wunused-function"

// ----------------------------------------------------
// Funcion que entrega el tiempo transcurrido desde el lanzamiento del
// programa en milisegundos

static long long time0= 0;

static long long getTime0() {
#ifdef RISCV
    return 0;
#else
    struct rusage ru;
    int rc= getrusage(RUSAGE_SELF, &ru);
    if (rc!=0) {
      perror("getTime");
      exit(1);
    }
    return (long long)ru.ru_utime.tv_sec*1000000+ru.ru_utime.tv_usec;
#endif
}

static void resetTime() {
  time0= getTime0();
}

static int getTime() {
  return (getTime0()-time0+500)/1000;
}

// ----------------------------------------------------
// Funcion que construye un nodo de una lista

static Nodo *lista(char c, Nodo *prox) {
  Nodo *a= malloc(sizeof(*a));
  a->c= c;
  a->prox= prox;
  return a;
}

// ----------------------------------------------------
// Funcion que verifica que 2 listas sean iguales

static void revisar_lista(Nodo *a, Nodo *b) {
  for (;;) {
    if (a==NULL) {

      if (b==NULL) {
        return;
      }

      fprintf(stderr, "Listas distintas: a es NULL, b tiene etiqueta %c\n",
                      b->c);
      exit(1);
    }
    else if (b==NULL) {
      fprintf(stderr, "Listas distintas: b es NULL, a tiene etiqueta %c\n",
                      a->c);
      exit(1);
    }
    else {
      if (a->c!=b->c) {
        fprintf(stderr, "Etiquetas de arboles son distintas: '%c' != '%c'\n",
                        a->c, b->c);
        exit(1);
      }
      a= a->prox;
      b= b->prox;
    }
  }
}

// ----------------------------------------------------
// Funcion que verifica que 2 nodos sean los mismos

static void revisar_mismo_nodo(Nodo *a, Nodo *b) {
  if (a!=b) {
    if (a==NULL || b==NULL)
      fprintf(stderr, "No son el mismo nodo.  Uno es NULL, el otro no\n");
    else
      fprintf(stderr, "No son el mismo nodo.  Etiquetas son '%c' '%c'\n",
                      a->c, b->c);
    exit(1);
  }
}

// ----------------------------------------------------
// Libera una lista enlazada

static void liberar(Nodo *a) {
  if (a!=NULL) {
    liberar(a->prox);
    free(a);
  }
}

// ----------------------------------------------------
// Crea una copia de lista enlazada

static Nodo *copia(Nodo *a) {
  if (a==NULL)
    return NULL;
 
  Nodo *an= malloc(sizeof(Nodo));
  an->c= a->c;
  an->prox= copia(a->prox);
  return an;
}


int main(int argc, char *argv[]) {
  printf("===========================\n");
  printf("Tests de la funcion dividir\n");
  printf("===========================\n\n");
  {
    printf("Caso lista nula: pares e impares deben ser listas vacias\n");
    Nodo *a= NULL;
    Nodo *pares= (Nodo*)0x4, *impares= (Nodo*)0x8;
    dividir(a, &impares, &pares);
    revisar_lista(pares, NULL);
    revisar_lista(impares, NULL);
    printf("Test aprobado\n");
  }

  {
    printf("Caso lista de un nodo con c='g'\n");
    Nodo *a= lista('g', NULL);
    Nodo *ref= copia(a);
    Nodo *pares= (Nodo*)0x404, *impares= (Nodo*)0x300;
    dividir(a, &impares, &pares);
    revisar_lista(pares, NULL);
    revisar_lista(impares, ref);
    revisar_mismo_nodo(impares, a);
    liberar(impares);
    liberar(ref);
    printf("Test aprobado\n");
  }

  {
    printf("Caso lista de 2 nodos 'g' y 'f'\n");
    Nodo *b= lista('f', NULL);
    Nodo *a= lista('g', b);
    Nodo *ref_pares= lista('f', NULL);
    Nodo *ref_impares= lista('g', NULL);
    Nodo *pares= (Nodo*)0x4000, *impares= (Nodo*)0x3f00;
    dividir(a, &impares, &pares);
    revisar_lista(pares, ref_pares);
    revisar_mismo_nodo(pares, b);
    revisar_lista(impares, ref_impares);
    revisar_mismo_nodo(impares, a);
    liberar(pares);
    liberar(impares);
    liberar(ref_pares);
    liberar(ref_impares);
    printf("Test aprobado\n");
  }

  {
    printf("Caso del ejemplo del enunciado\n");
    Nodo *r= lista('r', NULL);
    Nodo *b= lista('b', r);
    Nodo *x= lista('x', b);
    Nodo *f= lista('f', x);
    Nodo *g= lista('g', f);
    Nodo *ref_pares= lista('f', lista('b', NULL));
    Nodo *ref_impares= lista('g', lista('x', lista('r',NULL)));
    Nodo *pares= (Nodo*)0x8a0, *impares= (Nodo*)0x2500;
    dividir(g, &impares, &pares);
    revisar_lista(pares, ref_pares);
    revisar_mismo_nodo(pares, f);
    revisar_mismo_nodo(pares->prox, b);
    revisar_lista(impares, ref_impares);
    revisar_mismo_nodo(impares, g);
    revisar_mismo_nodo(impares->prox, x);
    revisar_mismo_nodo(impares->prox->prox, r);
    liberar(pares);
    liberar(impares),
    liberar(ref_pares);
    liberar(ref_impares);
    printf("Test aprobado\n");
  }

  int tiempo= 0;

  {

#ifdef SANITIZE
#define NLISTAS 2000
#else
#define NLISTAS 6000
#endif

    printf("Benchmark con %d listas de 1, 2, ..., %d nodos c/u\n",
           NLISTAS, NLISTAS);
    Nodo **listas= malloc(NLISTAS*sizeof(Nodo*));
    Nodo ***nodos= malloc(NLISTAS*sizeof(Nodo**));
    for (int lis= 0; lis<NLISTAS; lis++) {
      nodos[lis]= malloc((lis+1)*sizeof(Nodo*));
      Nodo *h= NULL;
      for (int i= lis-1; i>=0; i--) {
        h = lista(random(), h);
        nodos[lis][i]= h;
      }
      listas[lis]= h;
    }
    Nodo **impares_arr= malloc(NLISTAS*sizeof(Nodo*));
    Nodo **pares_arr= malloc(NLISTAS*sizeof(Nodo*));
    resetTime();
    for (int lis= 0; lis<NLISTAS; lis++) {
      dividir(listas[lis], &impares_arr[lis], &pares_arr[lis]);
    }
    tiempo= getTime();
    printf("Tiempo= %d milisegundos\n", tiempo);
    for (int lis= 0; lis<NLISTAS; lis++) {
      Nodo *h_impares= impares_arr[lis];
      for (int i= 0; i<lis; i += 2) {
        if (h_impares!=nodos[lis][i]) {
          fprintf(stderr, "Nodo %d de la lista de impares %d es incorrecto\n",
                          i, lis);
          exit(1);
        }
        h_impares= h_impares->prox;
      }
      if (h_impares!=NULL) {
        fprintf(stderr, "Lista de impares %d tiene exceso de nodos\n", lis);
        exit(1);
      }
      Nodo *h_pares= pares_arr[lis];
      for (int i= 1; i<lis; i += 2) {
        if (h_pares!=nodos[lis][i]) {
          fprintf(stderr, "Nodo %d de la lista de pares %d es incorrecto\n",
                          i, lis);
          exit(1);
        }
        h_pares= h_pares->prox;
      }
      if (h_pares!=NULL) {
        fprintf(stderr, "Lista de pares %d tiene exceso de nodos\n", lis);
        exit(1);
      }
    }
    for (int lis= 0; lis<NLISTAS; lis++) {
      liberar(impares_arr[lis]);
      liberar(pares_arr[lis]);
    }

    for (int lis= 0; lis<NLISTAS; lis++) {
      free(nodos[lis]);
    }
    free(listas);
    free(nodos);
    free(impares_arr);
    free(pares_arr);
  }

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

  printf("Felicitaciones: su solucion aprobo todos los tests\n");

  return 0;
}
