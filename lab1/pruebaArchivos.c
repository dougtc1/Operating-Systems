#include <stdio.h>
#include <stdlib.h>

int main () {

int numero;
FILE *f;

f = fopen("a.txt","r");

while ((fscanf(f,"%d",&numero) != EOF)) {

    printf("Valor leido = %d \n",numero);
}

fclose(f);
}
