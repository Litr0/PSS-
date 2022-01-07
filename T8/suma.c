#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "suma.h"
Set buscar(int a[], int n, int p) {
  int pids[p];
  int fds[p][2];
  for(int i=0;i<p;i++){
    pipe(fds[i]);
  }
  Set comb= ((1<<(n-1)<<1)-1); //cantidad de combinaciones
  Set por_hijo=(comb)/p;
  for(int i=0;i<p;i++){
    int hijo = fork();
    if (hijo==0){
      close(fds[i][0]);
      Set cant= (por_hijo)*(i+1);
      for (Set k=(por_hijo*i)+1; k<=cant;k++){
        long long sum=0;
        for(int j=0;j<n;j++){
          if (k&((Set)1<<j)){
            sum+=a[j];
          }
        }
        if (sum==0){
          Set res=k;
          write(fds[i][1],&res,sizeof(Set));
          exit(0);
        }
      }
      Set res=0;
      write(fds[i][1],&res,sizeof(Set));
      exit(1);
    }
    else{
      close(fds[i][1]);
      pids[i]=hijo;
    }
  }
  Set res=0;
  for (int i=0;i<p;i++){
    Set res_hijo;
    read(fds[i][0],&res_hijo,sizeof(Set));
    waitpid(pids[i],NULL,00);
    if (res_hijo!=0){
      res=res_hijo;
    }
  }
  return res;
}