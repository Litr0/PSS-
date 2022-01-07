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
  char cwd[1001];
  char ruta[1001];
  struct stat status;
  char slash='/';
  strncat(ruta,name,strlen(name));
  if (stat(name, &status)!=0) {
    perror(name);
    exit(1);
  }
  if(S_ISDIR(status.st_mode)){
    strncat(ruta,&slash,1); 
  }  
  if(!S_ISDIR(status.st_mode)){
    if (status.st_size>size){
      size=status.st_size;
      strncpy(big,ruta,1001);[]
    }
    return;
  }   
  if ((current_dir=opendir(name))==NULL) {
    perror(name);
    return;
  }
      
  if (getcwd(cwd, 1001)==NULL) {
    perror("getcwd");
    return;
  }
  if (chdir(name)!=0) {
    perror(name);
    return;
  }       
  while ((this_entry= readdir(current_dir))!=NULL) {
    if (strcmp(this_entry->d_name, ".")==0 || 
        strcmp(this_entry->d_name, "..")==0)
      continue;   
    masgrande(indent+1, this_entry->d_name);
  }             
  closedir(current_dir);
  chdir(cwd);
} 
int main(int argc, char *argv[]){
    for (int i=1;i<argc;i++){
        masgrande(0,argv[i]);
    }
    printf("mas grande: %s de %ld bytes\n", big, size);
}