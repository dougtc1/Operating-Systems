#include <stdlib.h>
#include <stdio.h>

typedef struct punto {
   int x;
   int y;
   struct punto *sigpunto;
}PUNTO;

int main() {

int i=0;
PUNTO *primero;
PUNTO *ultimo;
PUNTO *tmp;

primero = (PUNTO *) malloc(sizeof(PUNTO));

primero->x=0;

primero->y=0;

primero->sigpunto=NULL;

ultimo = primero;

printf("Valor del punto = (%d,%d) \n", primero->x, primero->y);

for (i=1;i<20;i++){

    tmp = (PUNTO *) malloc(sizeof(PUNTO));

    tmp->x=i;
    
    tmp->y=i;

    tmp->sigpunto=NULL;

    ultimo->sigpunto=tmp;

    ultimo = tmp;

    printf("Valor del punto = (%d,%d) \n", tmp->x, tmp->y);

}
}
