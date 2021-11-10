#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sort.h"

// El arreglo de nombres de personas

void printBin(uint x) {
  printf("0b");
  int bits[sizeof(uint)*8];
  int i= 0;
  for (;;) {
    bits[i]= x&1;
    x >>= 1;
    if (x==0)
      break;
    i++;
  }
  do {
    printf("%d", bits[i--]);
  } while (i>=0);
}

void resultados(uint x, uint y) {
  printf("Resultado: ");
  printBin(x);
  printf(" ");
  printBin(y);
  printf("\n");
}

int main(int argc, char *argv[]) {
  if (argc==1) {

    printf("Un arreglo bien ordenado: 0b11 0b1\n");
    uint nums2[]= {0b11, 0b1};
    sort(nums2, 2);
    resultados(nums2[0], nums2[1]);
    if (nums2[0]!=0b11 || nums2[1]!=0b1) {
      fprintf(stderr, "El resultado es incorrecto\n");
      exit(1);
    }

    printf("Otro arreglo bien ordenado: 0b11 0b1000\n");
    uint nums2b[]= {0b11, 0b1000};
    sort(nums2b, 2);
    resultados(nums2b[0], nums2b[1]);
    if (nums2b[0]!=0b11 || nums2b[1]!=0b1000) {
      fprintf(stderr, "El resultado es incorrecto\n");
      exit(1);
    }

    printf("Un arreglo desordenado: 0b1000100100 0b110011 \n");
    uint nums3[]= {0b1000100100, 0b110011};
    sort(nums3, 2);
    resultados(nums3[0], nums3[1]);
    if (nums3[0]!=0b110011 || nums3[1]!=0b1000100100) {
      fprintf(stderr, "El resultado es incorrecto\n");
      exit(1);
    }

    printf("Otro arreglo desordenado: 0b1001 0b11001000\n");
    uint nums3b[]= {0b1001, 0b11001000};
    sort(nums3b, 2);
    resultados(nums3b[0], nums3b[1]);
    if (nums3b[0]!=0b11001000 || nums3b[1]!=0b1001) {
      fprintf(stderr, "El resultado es incorrecto\n");
      exit(1);
    }

    printf("Arreglo con numero grande ordenado: "
           "0b10000000000000000000000000000000  0b0\n");
    uint nums4[]= {0b10000000000000000000000000000000, 0b0};
    sort(nums4, 2);
    resultados(nums4[0], nums4[1]);
    if (nums4[0]!=0b10000000000000000000000000000000 || nums4[1]!=0b0) {
      fprintf(stderr, "El resultado es incorrecto\n");
      exit(1);
    }

    printf("Arreglo con numero grande desordenado: 0b0   "
           "0b10000000000000000000000000000000\n");
    uint nums4b[]= {0b0, 0b10000000000000000000000000000000};
    sort(nums4b, 2);
    resultados(nums4b[0], nums4b[1]);
    if (nums4b[0]!=0b10000000000000000000000000000000 || nums4b[1]!=0b0) {
      fprintf(stderr, "El resultado es incorrecto\n");
      exit(1);
    }
  
    printf("Arreglo con 3 numeros desordenados: 0b1000000000 0b10100 0b111\n");
    uint nums5[]= {0b1000000000, 0b10100, 0b111};
    sort(nums5, 3);
    printf("Resultado: ");
    printBin(nums5[0]); printf(" ");
    printBin(nums5[1]); printf(" ");
    printBin(nums5[2]); printf("\n");
    if (nums5[0]!=0b111 || nums5[1]!=0b10100 || nums5[2]!=0b1000000000) {
      fprintf(stderr, "El resultado es incorrecto\n");
      exit(1);
    }
  }

  printf("Ahora un arreglo de 12 numeros\n");
  // 0, 3, 5, 11, 1, 2, 7, 10, 9, 8, 4, 6
  uint nums[]= {
                 0b0,
                 0b10101,
                 0b11111,
                 0b11111111111,
                 0b10000000000000000000000000000000,
                 0b10000000000000000000000000000001,
                 0b1010101010101,
                 0b10010010010010011111,
                 0b1111111101,
                 0b01111000000000000000000000001111,
                 0b11100000000000000000000000000001,
                 0b11111100000000000000000000000000
               };

  int refs[]= {
                 0b11111111111,
                 0b10010010010010011111,
                 0b1111111101,
                 0b01111000000000000000000000001111,
                 0b1010101010101,
                 0b11111100000000000000000000000000,
                 0b11111,
                 0b11100000000000000000000000000001,
                 0b10101,
                 0b10000000000000000000000000000001,
                 0b10000000000000000000000000000000,
                 0b0,
               };

  printf("El arreglo desordenado es:\n");
  printf("--------------------------\n");
  for (int i= 0; i<12; i++) {
    printBin(nums[i]);
    printf("\n");
  }
  sort(nums, 12);
  printf("\n");
  printf("El arreglo ordenado es:\n");
  printf("-----------------------\n");
  for (int i= 0; i<12; i++) {
    printBin(nums[i]);
    printf("\n");
  }
  for (int i= 0; i<12; i++) {
    if (nums[i]!=refs[i]) {
      fprintf(stderr, "El %d-esimo elemento es incorrecto\n", i);
      exit(1);
    }
  }

  printf("Felicitaciones: test de prueba aprobado\n");
  return 0;
}
