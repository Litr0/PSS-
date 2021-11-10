#include <string.h>

void sort(unsigned int *nums, int n) {
  unsigned int *ult= &nums[n-1];
  unsigned int *p= nums;
  while (p<ult) {
    // No modifique nada arriba de esta linea
    // Inicio de la parte que debe cambiar
    int a=0;
    int b=0;
    unsigned int a1=p[0];
    unsigned int b1=p[1];
   do{
      if((a1&1)==1){
        a++;
      }
      a1=a1>>1;
    } while (a1!=0);
    do{
      if ((b1&1)==1){
        b++;
      }
      b1=b1>>1;
    } while (b1!=0);
    int t1=a>=b ? 0:1;
    // Fin de la parte que debe cambiar
    // No Cambie nada mas a partir de aca
    if (t1 <= 0)
      p++;
    else {
      unsigned int tmp= p[0];
      p[0]= p[1];
      p[1]= tmp;
      p= nums;
    }
  }
}
