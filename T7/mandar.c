#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
long int size=0;
char big[1001];
void masgrande(int indent,char *name){
  DIR *current_dir;
  struct dirent *this_entry;
  char ruta[1001];
  struct stat status;
  char slash='/';
  if (stat(name, &status)!=0) {
    perror(name);
    exit(1);
  }
  if(!S_ISDIR(status.st_mode)){
    if (status.st_size>size){
      size=status.st_size;
      strncpy(big,ruta,1001);
    }
    return;
  }   
  if ((current_dir=opendir(name))==NULL) {
    perror(name);
    return;
  }    
  while ((this_entry=readdir(current_dir))!=NULL) {
    if (strcmp(this_entry->d_name, ".")==0 || 
        strcmp(this_entry->d_name, "..")==0)
      continue;
    strncpy(ruta,name,1001);
    strncat(ruta,&slash,1);
    strncat(ruta,this_entry->d_name,strlen(this_entry->d_name));   
    masgrande(indent+1,ruta);
  }               
  closedir(current_dir);
} 
int main(int argc, char *argv[]){
    for (int i=1;i<argc;i++){
        masgrande(0,argv[i]);
    }
    printf("mas grande: %s de %ld bytes\n", big, size);

}