#define _DEFAULT_SOURCE 1

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <math.h>

#include "volumen.h"

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

long long getUSecsOfDay() {
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
// Generacion de numeros aleatorios
// Puede usar esta funcion en su solucion.

static double rand_sum= 0;
static double rand_cnt= 0;

double double_random(double a, double b) {
  double r01= (double)random()/RAND_MAX;
  double r= (b-a)*r01+a;
  if (a<=r && r<=b) {
    rand_sum += r01;
    rand_cnt++;
    return r;
  }
  else {
    fprintf(stderr, "Error en numero aleatorio\n");
    exit(1);
  }
}

// ----------------------------------------------------
// Version secuencial de volumen
// (Puede usarla en su solucion pero es mas facil si copia parte
// de este codigo en su solucion.)

#if 1

// El algoritmo del enunciado
double volumenSec(double (*f)(double x, double y),
    double xi, double xf, double yi, double yf,
    int n, int p) {
  double suma= 0;
  for (int k= 0; k<n; k++) {
    double x= double_random(xi, xf);
    double y= double_random(yi, yf);
    double z= (*f)(x, y);
    suma += z;
  }
  return (xf-xi)*(yf-yi)*(suma/n);
}

#else

// Probe este otro algoritmo para averiguar si da mejor precision
// pero los resultados no son concluyentes.

static double sumaSec(double (*f)(double x, double y),
    double xi, double xf, double yi, double yf,
    int n) {
  if (n<=10) {
    double suma= 0;
    for (int k= 0; k<n; k++) {
      double x= double_random(xi, xf);
      double y= double_random(yi, yf);
      double z= (*f)(x, y);
      suma += z;
    }
    return suma;
  }
  else {
    int h= (n+1)/2;
    return sumaSec(f, xi, xf, yi, yf, h) + sumaSec(f, xi, xf, yi, yf, n-h);
  }
}
    
double volumenSec(double (*f)(double x, double y),
    double xi, double xf, double yi, double yf,
    int n, int p) {
  return (xf-xi)*(yf-yi)*(sumaSec(f, xi, xf, yi, yf, n)/n);
}

#endif

// ----------------------------------------------------
// Programa principal
// No puede usar esta funcion en su solucion!
// Debe usar el puntero f suministrado como parametro.

static double sin_2x_y(double x, double y) {
  return sin(2*x + y);
}

static double ii_sin_2x_y(double xi, double xf, double yi, double yf) {
  return sin(xi-xf)*(cos(xi+xf+yf)-cos(xi+xf+yi));
}

static double f2x_y(double x, double y) {
  return 2*x+y;
}

static double ii_f2x_y(double a, double b, double c, double d) {
  return ( -a*a*d - a*d*d/2 + b*b*d + b*d*d/2 ) -
         ( -a*a*c - a*c*c/2 + b*b*c + b*c*c/2 );
}

int main() {

  srandom(getUSecsOfDay()*getpid());

  {
    int n= 80000, p=8;
    printf("Test: volumen bajo 2x+y sobre cuadrado (0,0) a (1,1)\n");
    printf("n=%d p=%d\n", n, p);
    double a= 0, b= 1, c= 0, d= 1;
    double volSim= ii_f2x_y(a, b, c, d);
    printf("Resultado exacto: %f\n", volSim);
    double volSec= volumenSec(f2x_y, a, b, c, d, n, p);
    double errSec= fabs(volSec-volSim);
    printf("Estimacion secuencial: %f   error: %f\n", volSec, errSec);
    fflush(stdout);
    double volPar= volumen(f2x_y, a, b, c, d, n, p);
    double errPar= fabs(volPar-volSim);
    printf("Estimacion paralela: %f   error: %f\n", volPar, errPar);
    if (errPar>0.4) {
      fprintf(stderr, "Estimacion incorrecta\n");
      exit(1);
    }
    printf("Aprobado\n");
  }
  
  {
    double xi= -2.5, xf= 3, yi= -6, yf= 5;
    int n= 80000, p= 8;
    printf("Test: volumen bajo sin(2x+y)\n"
           "      sobre cuadrado (%f,%f) a (%f,%f)\n", xi, yi, xf, yf);
    printf("n=%d p=%d\n", n, p);
    double volSim= ii_sin_2x_y(xi, xf, yi, yf);
    printf("Resultado exacto: %f\n", volSim);
    double volSec= volumenSec(sin_2x_y, xi, xf, yi, yf, n, p);
    double errSec= fabs(volSec-volSim);
    printf("Estimacion secuencial: %f   error: %f\n", volSec, errSec);
    fflush(stdout);
    double volPar= volumen(sin_2x_y, xi, xf, yi, yf, n, p);
    double errPar= fabs(volPar-volSim);
    printf("Estimacion paralela: %f   error: %f\n", volPar, errPar);
  
    if (errPar>0.5) {
      fprintf(stderr, "Estimacion incorrecta\n");
      exit(1);
    }
    printf("Aprobado\n");

    n= 16000000; p= 4;
    printf("Benchmark: El ejemplo del enunciado con n=%d y p=%d\n", n, p);
    int i= 0;
    while (i<N_INTENTOS) {
      printf("Intento: %d\n", i+1);
      resetTime();
      volSec= volumenSec(sin_2x_y, xi, xf, yi, yf, n, p);
      int seq_time= getTime();
      double errSec= fabs(volSec-volSim);
      printf("Estimacion secuencial: %f   error: %f\n", volSec, errSec);
      printf("Tiempo secuencial es %d milisegundos\n", seq_time);
      resetTime();
      fflush(stdout);
      volPar= volumen(sin_2x_y, xi, xf, yi, yf, n, p);
      int par_time= getTime();
      double errPar= fabs(volPar-volSim);
      printf("Estimacion paralela: %f   error: %f\n", volPar, errPar);
      printf("Tiempo en paralelo es %d milisegundos\n", par_time);
      if (errPar>0.5) {
        fprintf(stderr, "Resultado incorrecto\n");
        exit(1);
      }
      double speedUp= (double)seq_time/par_time;
      printf("Speed up= %f\n", speedUp);
      if (speedUp>=1.3)
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
  }

  // printf("Promedio random= %f\n", (double)rand_sum/rand_cnt);

  printf("Felicitaciones, su solucion paso todos los tests\n");
  return 0;
}
