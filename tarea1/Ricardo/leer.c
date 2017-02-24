#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pregunta {
   char codigo[100];
   char nivel[100];
   char area[100];
   char question[100];
   char answer1[100];
   char answer2[100];
   char answer3[100];
   char answer[100];
   struct pregunta *sig;
}PREGUNTA;

void leer(FILE *fp, PREGUNTA *preguntas) {

   PREGUNTA *temp, *ult;

   char ch;
 
   //printf("Que archivo desea abrir?\n");
   //gets(archivo);
 
   //fp = fopen(archivo,"r"); // read mode
 
   int MaximoLinea = 500;
   char *linea = (char *)malloc(sizeof(char) * MaximoLinea);

   ch = getc(fp);
   int count = 0;

      while ((ch != '\n') && (ch != EOF)) {

         linea[count] = ch;
         count++;

         ch = getc(fp);
      }

      linea[count] = '\0';
      printf("%s\n",linea );


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


      printf("%s\n",preguntas->codigo);
      printf("%s\n",preguntas->nivel);
      printf("%s\n",preguntas->area);
      printf("%s\n",preguntas->question);
      printf("%s\n",preguntas->answer1);
      printf("%s\n",preguntas->answer2);
      printf("%s\n",preguntas->answer3);
      printf("%s\n",preguntas->answer);

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
temp = preguntas;

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

   }
