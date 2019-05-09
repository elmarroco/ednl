#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char * String;
void leerCadena(String *cadena);
String buffer;

void leerCadena(String *cadena) {
  char c; //Almacena el caracter leido
  int i; //Controla el tamaño de la cadena
  String auxiliar = NULL; //Almacena cadena antes de ser copiada a la direccion

  if ((*cadena)!=NULL) {
    free(*cadena);
    (*cadena)=NULL;
  }
  i=1; //Inicializa i en uno (para almacenar primer caracter)
  while ((c=getchar())!='\n') {
    auxiliar=(String)realloc(auxiliar, (i+2)*sizeof(char));
    if (auxiliar == NULL) {
      printf("Memoria Insuficiente!\n");
      return;
    }
    auxiliar[i-1]=c;
    auxiliar[i]='\0';
    i++;
  }
  if (auxiliar == NULL) {
    auxiliar = (String)malloc(5*sizeof(char));
    strcpy(auxiliar,"NULO");
  }
  (*cadena)=(String)realloc((*cadena),(strlen(auxiliar)+1)*sizeof(char));
  strcpy((*cadena), auxiliar);
  free(auxiliar);
}
