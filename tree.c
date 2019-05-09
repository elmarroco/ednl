#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct nodo_t {
  struct nodo_t * hijo_izquierdo;
  struct nodo_t * hijo_derecho;
  char valor;
} Nodo;

//Funcion para crear nodo
Nodo* creaNodo(char valor, Nodo * hijo_izquierdo, Nodo * hijo_derecho){
	Nodo *p;
	p=(Nodo*)malloc(sizeof(Nodo));
	p->valor=valor;
	p->hijo_izquierdo=hijo_izquierdo;
	p->hijo_derecho=hijo_derecho;
	return p;
}
//Funcion para obtener operador menor prioridad
int menorPrioridad(char* expresion, int inicio, int fin){
  int mul=-1, pot = -1;
  for (int i = fin; i >= inicio; i--) {
    if (expresion[i]=='+' || expresion[i]=='-')
      return i;
    if (expresion[i]=='*' && mul==-1)
      mul= i;
    if (expresion[i]=='^' && pot ==-1)
      pot=i;
  }
  if (mul!=-1)
    return mul;
  else
    return pot;
}

//Funcion para determinar si un caracter es operador
bool esOperador(char s){
  if (s=='+' || s=='-' || s=='*' || s=='^') {
    return true;
  }
  return false;
}

//Funcion para determinar si un caracter es una constante
bool esConstante(char s){
  if (s>47 && s<58) {
    return true;
  }
  return false;
}

//Funcion para determinar si un caracter es una variable
bool esVariable(char s){
  if (s=='x') {
    return true;
  }
  return false;
}

Nodo* creaArbolExp(char* expresion, int inicio, int fin){
  int pos = menorPrioridad(expresion, inicio, fin);
  if (pos!=-1)
    return creaNodo(expresion[pos], creaArbolExp(expresion,inicio,pos-1), creaArbolExp(expresion,pos+1,fin));
  return creaNodo(expresion[inicio], NULL, NULL);
}

Nodo* derivadaArbol(Nodo *p){
  char val = p->valor;
  if (val == 'x')
    return creaNodo('1', NULL, NULL);
  else if(esConstante(val))
    return creaNodo('0', NULL, NULL);
  else{
    switch (val) {
      case '+':
        return creaNodo('+', derivadaArbol(p->hijo_izquierdo), derivadaArbol(p->hijo_derecho));
      case '-':
        return creaNodo('-', derivadaArbol(p->hijo_izquierdo), derivadaArbol(p->hijo_derecho));
      case '*':
        return creaNodo('+', creaNodo('*', p->hijo_izquierdo, derivadaArbol(p->hijo_derecho)), creaNodo('*', derivadaArbol(p->hijo_izquierdo), p->hijo_derecho ));
      case '^':
        return creaNodo('*', p->hijo_derecho, creaNodo('^',creaNodo('x', NULL, NULL),creaNodo(p->hijo_derecho->valor-1, NULL, NULL)));
    }
  }
}

void simplificaArbol(Nodo *p){
  char c = p->valor;
  if (esConstante(c) || esVariable(c))
    return;
  if (c=='^' && p->hijo_derecho->valor==1) {
    p->valor=p->hijo_derecho->valor;
    free(p->hijo_derecho);
    free(p->hijo_izquierdo);
  }
  if (c=='+' && esConstante(p->hijo_izquierdo->valor) && esConstante(p->hijo_derecho->valor)) {
    p->valor = p->hijo_izquierdo->valor + p->hijo_derecho->valor;
    free(p->hijo_izquierdo);
    free(p->hijo_derecho);
  }
  if (esOperador(p->hijo_izquierdo->valor)) {
    simplificaArbol(p->hijo_izquierdo);
  }
  if (esOperador(p->hijo_derecho->valor)) {
    simplificaArbol(p->hijo_derecho);
  }
}
void recorreArbol(Nodo * n) {
  if(n!=NULL){
      recorreArbol(n->hijo_izquierdo);
      printf("%c ", n->valor);
      recorreArbol(n->hijo_derecho);
    }
}
