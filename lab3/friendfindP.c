#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main (int argc, char *argv[]) {


	leer(FILE *fp) {

	   PREGUNTA *preguntas, *temp, *ult;

	   char ch;
	 
	   char *linea = (char *)malloc(sizeof(char) * MaximoLinea);

	   ch = getc(fp);
	   int count = 0;

	      while ((ch != '\n') && (ch != EOF)) {

	         linea[count] = ch;
	         count++;

	         ch = getc(fp);
	      }

	      linea[count] = '\0';
	      
	      const char quote[2]="\"";
	      const char e[2]=" ";
	      char *token;
	      char *espacio;
	      
	 
	      preguntas=(PREGUNTA *)malloc(sizeof(PREGUNTA));

	      token = strtok(linea , e);
	      strcpy(preguntas->codigo, token);
	      
	      token = strtok(NULL , e);
	      strcpy(preguntas->nivel, token);

	      token = strtok(NULL , e);
	      strcpy(preguntas->area, token);

	      token = strtok(NULL , quote);
	      strcpy(preguntas->question, token);

	      espacio = strtok(NULL , quote);

	      token = strtok(NULL , quote);
	      strcpy(preguntas->answer1, token);

	      espacio = strtok(NULL , quote);

	      token = strtok(NULL , quote);
	      strcpy(preguntas->answer2, token);

	      espacio = strtok(NULL , quote);

	      token = strtok(NULL , quote);
	      strcpy(preguntas->answer3, token);

	      token = strtok(NULL , e);
	      strcpy(preguntas->answer, token);

	      preguntas->sig = NULL;

	      ult = preguntas;

	      ch = getc(fp); 
	      while (ch != EOF) {
	   
	      int count = 0;

	         while ((ch != '\n') && (ch != EOF)) {

	            linea[count] = ch;
	            count++;

	            ch = getc(fp);
	         }
	      linea[count] = '\0';

	      temp=(PREGUNTA *)malloc(sizeof(PREGUNTA));

	      token = strtok(linea , e);
	      strcpy(temp->codigo, token);
	      
	      token = strtok(NULL , e);
	      strcpy(temp->nivel, token);

	      token = strtok(NULL , e);
	      strcpy(temp->area, token);

	      token = strtok(NULL , quote);
	      strcpy(temp->question, token);

	      espacio = strtok(NULL , quote);

	      token = strtok(NULL , quote);
	      strcpy(temp->answer1, token);

	      espacio = strtok(NULL , quote);

	      token = strtok(NULL , quote);
	      strcpy(temp->answer2, token);

	      espacio = strtok(NULL , quote);

	      token = strtok(NULL , quote);
	      strcpy(temp->answer3, token);

	      token = strtok(NULL , e);
	      strcpy(temp->answer, token);

	      ult->sig = temp;

	      ult = temp;

	      ch = getc(fp);
	   }
	   ult->sig = NULL;
	//temp = preguntas;

	return preguntas;
};
}