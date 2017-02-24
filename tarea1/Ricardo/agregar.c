#include <stdio.h>
#include <stdlib.h>

typedef struct pregunta {
   char codigo;
   char nivel;
   char area;
   char question;
   char answer1;
   char answer2;
   char answer3;
   char answer;
   struct pregunta *sig;
}PREGUNTA;
int main() {

ult = preguntas;
while (ult->sig!=NULL){
   ult = ult->sig;
}

temp=(PREGUNTA *)malloc(sizeof(PREGUNTA));
printf("Cual es el codigo de la pregunta que agregara?\n");
gets(temp.codigo);
printf("Nivel de la pregunta?\n");
gets(temp.nivel);
printf("Area de la pregunta?\n");
gets(temp.area);
printf("Cual es la pregunta?\n");
gets(temp.question);
printf("Cual es la primera posible respuesta?\n");
gets(temp.answer1);
printf("Cual es la segunda posible respuesta?\n");
gets(temp.answer2);
printf("Cual es la tercera posible respuesta?\n");
gets(temp.answer3);
printf("Cual es la respuesta correcta(introduza 1,2 o 3)?\n");
gets(temp.answer);
ult->sig = temp;
temp->sig = NULL;

return(0)}