#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "recortar.h"

uint recortar(unsigned int x, int i, int j) {
uint mask = ~((-1)<<(j));
uint izq = (x>>(i+1))<<(j);
if(i==31){
  izq=0;
}
if (j==0){
  mask=0;
}
return izq|(x & mask);
}
