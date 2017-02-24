#include <stdlib.h>
#include <stdio.h>


typedef struct arbol {
    int nodo;
    struct arbol *izq;
    struct arbol *der;
} ARBOL;

int main(){
ARBOL *miarbol;
ARBOL *hijoizq;
ARBOL *hijoder;

miarbol = (ARBOL *) malloc(sizeof(ARBOL));

miarbol->nodo=0;

hijoizq = (ARBOL *) malloc(sizeof(ARBOL));

hijoder = (ARBOL *) malloc(sizeof(ARBOL));

miarbol->izq=hijoizq;

miarbol->der=hijoder;

hijoizq->nodo=1;

hijoizq->izq=NULL;

hijoizq->der=NULL;

hijoder->nodo=2;

hijoder->izq=NULL;

hijoder->der=NULL;

printf("Valor del Nodo = %d \n", miarbol->nodo);
printf("Valor del NodoIzq = %d \n", miarbol->izq->nodo);
printf("Valor del NodoDer = %d \n", miarbol->der->nodo);

}
