
typedef struct nodo {
  char *nom;
  int nady;
  struct nodo **adyacentes;
} Nodo;

Nodo *leerGrafo(char *nomFile);
