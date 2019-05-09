#include "leerCadena.c"
#include "tree.c"

int main(int argc, char const *argv[]) {
  printf("Ingresa expresion a derivar\n");
  leerCadena(&buffer);
  printf("La cadena es %s\n", buffer);
  Nodo * n = creaArbolExp(buffer, 0, strlen(buffer)-1);
  Nodo * d = derivadaArbol(n);
  //simplificaArbol(d);
  recorreArbol(d);
  return 0;
}
