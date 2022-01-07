#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>

#include "suma.h"

#ifdef OPT
#define N_INTENTOS 5
#define N 29
#else
#define N_INTENTOS 1
#define N 27
#endif

// ----------------------------------------------------
// Funcion que entrega el tiempo transcurrido desde el lanzamiento del
// programa en milisegundos

static long long getUSecsOfDay() {
  struct timeval Timeval;
  gettimeofday(&Timeval, NULL);
  return (long long)Timeval.tv_sec*1000000+Timeval.tv_usec;
}

static int time0= 0;

static int getTime0() {
    return getUSecsOfDay()/1000;
}

static void resetTime() {
  time0= getTime0();
}

static int getTime() {
  return getTime0()-time0;
}

// ----------------------------------------------------
// La funcion leer para recibir n bytes de un pipe

int leer(int fd, void *vbuf, int n) {
  char *buf= vbuf;
  do {
    int rc= read(fd, buf, n);
    if (rc<=0)
      return 1; /* fracaso: error o fin del archivo/pipe/socket */
    n-= rc; /* descontamos los bytes leídos */
    buf+= rc; /* avanzamos el buffer para no reescribir lo leido previamente */
  } while (n>0); /* mientras no leamos todo lo que esperamos */
  return 0; /* exito */
}

// ----------------------------------------------------
// Version secuencial buscar

Set buscarSeq(int a[], int n) {
  Set comb= (1<<(n-1)<<1)-1; // 2n-1: nro. de combinaciones
  for (Set k= 1; k<=comb; k++) {
    // k es el mapa de bits para el subconjunto { a[i] | bit ki de k es 1 }
    long long sum= 0;
    for (int i= 0; i<n; i++) {
      if ( k & ((Set)1<<i) ) // si bit ki de k es 1
        sum+= a[i];
    }
    if (sum==0) {  // exito: el subconjunto suma 0
      return k;    // y el mapa de bits para el subconjunto es k
  } }
  return 0;        // no existe subconjunto que sume 0
}

// ----------------------------------------------------
// Funcion que muestra la solucion

void mostrar(int a[], Set k, int n) {
  long long sum= 0;
  if (k==0) {
    printf("subconjunto no existe\n");
    return;
  }
  for (int i= 0; i<n; i++) {
    if ( k & ((Set)1<<i) ) {
      printf("%d ", a[i]);
      sum+= a[i];
    }
  }
  if (sum!=0) {
    fprintf(stderr, "El subconjunto suma %lld, no 0\n", sum);
    exit(1);
  }
  printf("\n");
}

// ----------------------------------------------------
// Programa principal

int main() {
  printf("Test: El ejemplo del enunciado\n");
  int a[]= { -7, -3, -2, 5, 8};
  Set kSeq= buscarSeq(a, 5);
  mostrar(a, kSeq, 5);
  fflush(stdout);
  Set k= buscar(a, 5, 8);
  mostrar(a, k, 5);
  if (k!=kSeq) {
    fprintf(stderr, "La solucion debio ser %lld, no %lld\n", kSeq, k);
    exit(1);
  }
  printf("Aprobado\n");

  printf("Uno ejemplo mas grande con n=26, sin solucion\n");
  int b[]= { 122737, -37364, 287373, -27267, 967923, -25383, 924973, -28973,
             278363, 28272, 98734, -26735, -983267, 674998, 72537, 116725,
             72537, 27263, 82739, 829276, -5383715, 675483, -28334, 38495,
             374943, 278367};
  int i= 0;
  while (i<N_INTENTOS) {
    printf("Intento: %d\n", i+1);
    resetTime();
    k= buscarSeq(b, 26);
    int seq_time= getTime();
    if (k!=0) {
      mostrar(b, k, 26);
      fprintf(stderr, "Bug del profesor: la solucion debio ser %d, no %lld\n",
                      0, k);
      exit(1);
    }
    printf("Tiempo secuencial es %d milisegundos\n", seq_time);
    fflush(stdout);
    resetTime();
    k= buscar(b, 26, 8);
    int par_time= getTime();
    if (k!=0) {
      mostrar(b, k, 26);
      fprintf(stderr, "La solucion debio ser %d, no %lld\n", 0, k);
      exit(1);
    }
    printf("Tiempo en paralelo es %d milisegundos\n", par_time);
    double speedUp= (double)seq_time/par_time;
    printf("Speed up= %f\n", speedUp);
    if (speedUp>=1.5)
      break;
    i++;
  }
#ifdef OPT
  if (i>=N_INTENTOS) {
      fprintf(stderr, "Su solucion no es suficientemente eficiente\n");
      fprintf(stderr, "Verifique que el procesador es dual-core al menos\n");
      exit(1);
  }
#endif

  printf("Aprobado\n");
  
  printf("Uno ejemplo mas grande aun con n=%d, con solucion\n", N);
  int c[]= { -3, -2, 5,
             122737, -37364, 287373, 27267, 967923, -25383, 924973, -28973,
             278363, 28272, 98734, -26735, 983267, 674998, 72537, 116725,
             72537, 27263, 82739, 829276, 5383715, 675483, -28334, 38495,
             374943, 278367};
  fflush(stdout);
  k= buscar(c, N, 4);
  mostrar(c, k, N);

  printf("Aprobado\n");

  printf("Felicitaciones, su tarea paso todos los tests\n");
  return 0;
}
