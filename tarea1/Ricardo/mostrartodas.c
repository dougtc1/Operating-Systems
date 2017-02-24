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

void mostratodas(PREGUNTA preguntas) {

PREGUNTA ult;

ult = preguntas;

while (temp!=NULL){

      printf("%s",temp->codigo);
      printf(" ");
      printf("%s",temp->nivel);
      printf(" ");
      printf("%s",temp->area);
      printf(" ");
      printf("%s",temp->question);
      printf(" ");
      printf("%s",temp->answer1);
      printf(" ");
      printf("%s",temp->answer2);
      printf(" ");
      printf("%s",temp->answer3);
      printf(" ");
      printf("%s\n",temp->answer);
      printf("\n");

      temp = temp->sig;

}
