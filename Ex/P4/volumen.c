#define _DEFAULT_SOURCE 1

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "volumen.h"

// Importante
// Al inicio de cada hijo Ud. debe cambiar la semilla usada
// para generar los numeros aleatorios.  Esto se logra invocando esta
// funcion:
//          srandom(getUSecsOfDay()*getpid());
// Si no lo hace, todos los procesos hijos generaran los mismos puntos,
// con lo que la precision lograda sera la misma que con n/p puntos.
// La función srandom hace que los hijos generen puntos distintos.
//pasa los test
double volumen(double (*f)(double x, double y),
    double xi, double xf, double yi, double yf,
    int n, int p) {
  int pids[p]; //arreglo de los hijos 
  int fds [p][2]; //matriz de los hijos 
  for (int i=0;i<p;i++){
    pipe(fds[i]); //pipe entre los hijos 
  }
  int puntos=n/p; //puntos por hijo 
  for(int i=0;i<p;i++){ 
    int hijo=fork(); //llamamos al hijo
    if (hijo==0){
      srandom(getUSecsOfDay()*getpid()); //para evitar que los hijos evaluen en los mismos puntos  
      close(fds[i][0]);
      double suma=0;
      for(int k=(puntos*i);k<puntos*(i+1);k++){ //aplicamos la funcion del enunciado 
        double x=double_random(xi,xf);
        double y=double_random(yi,yf);
        suma+=(*f)(x,y); 
      }
      write(fds[i][1],&suma,sizeof(double));//escribimos la suma
      exit(0);
    }
    else{
      close(fds[i][1]);
      pids[i]=hijo;
    }  
  }
  double res=0;
  for (int i=0;i<p;i++){
    waitpid(pids[i],NULL,00); //esperamos a que terminen los hijos
    double res_hijo; 
    read(fds[i][0],&res_hijo,sizeof(double)); //padre lee las respuestas de los hijos
    res+=res_hijo; 
  } //retornamos respuesta
  double total=(xf-xi)*(yf-yi)*(res/n);
  return total;
}
