#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "suma-dec.h"

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
// revisar_int: verifica que un entero es un valor especifico

static void revisar_dec(Decimal n, Decimal nref) {
  if (n!=nref) {
    fprintf(stderr, "El valor retornado debio ser %llx, no %llx\n", nref, n);
    exit(1);
  }
}

int main(int argc, char *argv[]) {
  printf("===============================\n");
  printf("Tests de la funcion sumaDecimal\n");
  printf("===============================\n\n");

  printf("Test: 2+4 = 6\n");
  Decimal dec6= sumaDecimal(0x2, 0x4);
  revisar_dec(dec6, 0x6);

  printf("Test: 25+14 = 39\n");
  Decimal dec39= sumaDecimal(0x25, 0x14);
  revisar_dec(dec39, 0x39);

  printf("Test: 9+9 = 18\n");
  Decimal dec18= sumaDecimal(0x9, 0x9);
  revisar_dec(dec18, 0x18);

  printf("Test: 37+45 = 82\n");
  Decimal dec82= sumaDecimal(0x37, 0x45);
  revisar_dec(dec82, 0x82);

  printf("Test: 68+45 = 113\n");
  Decimal dec113= sumaDecimal(0x68, 0x45);
  revisar_dec(dec113, 0x113);

  printf("Test: 9999+1 = 10000\n");
  Decimal dec10000= sumaDecimal(0x9999, 0x1);
  revisar_dec(dec10000, 0x10000);

  printf("Test: 5542372939610024 + 4019389412089123 = 9561762351699147\n");
  Decimal dec_big= sumaDecimal(0x5542372939610024, 0x4019389412089123);
  revisar_dec(dec_big, 0x9561762351699147);

  printf("Felicitaciones: su solucion es correcta\n\n");

  return 0;
}
