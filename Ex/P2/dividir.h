typedef struct nodo {
  char c;
  struct nodo *prox;
} Nodo;
void dividir(Nodo *lista, Nodo **pimpares, Nodo **ppares);
