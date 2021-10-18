#include <stdio.h>

#include "suma-dec.h"
//PASA TODOS LOS TESTS
Decimal sumaDecimal(Decimal x, Decimal y) {
Decimal sum=0; //Resultado final
Decimal cont=15; //variable que sirve como contador y mascara con 4 unos 
Decimal mask10=10; //mascara con 1010
Decimal a1=1; //utilizado para sumar
Decimal a0=0; //valor que va a cambiar dependiendo de lo que de 
while (cont!=0){
  Decimal agr= (x & cont) + (y & cont); //parte de lo que vamos a agregar 
  if (agr<mask10-(a1&a0)){
    sum+= agr+(a1&a0); //si no se sobrepasa lo anterior solo se agrega a1&a0 y se
    a0=0; //define a0=0
    }
  else{
    sum+= agr-mask10+(a1&a0); //si se se sobrepasa o es igual ademas de sumar se le resta mask10 
    a0=-1; //a0=-1 ya que sobrepasamos el 10 
    }
  a1=a1<<4; //se desplaza todo 4 bits a la izq
  mask10=mask10<<4;
  cont=cont<<4;
  }
  return sum;
}
