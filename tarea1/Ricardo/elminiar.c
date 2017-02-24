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

	PREGUNTA *preguntas,*temp, *ult;
	char ch, code;
  
 	temp = preguntas;
	printf("Cual es el codigo de la pregunta que va a eliminar?\n");
	gets(code);

	while (temp->sig.codigo != code) {
		temp = temp->sig;
	}
	ult = temp->sig->sig;
	free(temp->sig);
	temp->sig = ult;
	return(0)}
