//Tarea 1
// Ricardo Churion, carnet:11-10200
// Douglas Torres, carnet:11-11027

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pregunta {
   char codigo[100];
   char nivel[2];
   char area[2];
   char question[100];
   char answer1[100];
   char answer2[100];
   char answer3[100];
   char answer[2];
   struct pregunta *sig;
}PREGUNTA;

struct PREGUNTA *leer(FILE *fp) {

   PREGUNTA *preguntas, *temp, *ult;

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


void mostrartodas(PREGUNTA *preguntas) {

PREGUNTA *temp;

temp = preguntas;

printf ("Estas son las preguntas que se encuentran en su base de datos. \n");
printf("\n");

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

void mostraralgunas(PREGUNTA *preguntas) {

   char dif[2];

   PREGUNTA *temp;

   temp = preguntas;

   printf("Cual es la dificultad que desea consultar?. \n");

   scanf("%s", dif);

   printf("\n");

printf ("Estimado usuario, estas son las preguntas de la dificultad escogida que se encuentran en su base de datos. \n");
printf("\n");

while (temp!=NULL){

   if (strcmp(temp->nivel,dif) == 0) {
      
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

   } else {

      temp =temp->sig;
   
   }
}
}

struct PREGUNTA *eliminar(PREGUNTA *preguntas){

   PREGUNTA *anterior, *siguiente;

   anterior=(PREGUNTA *)malloc(sizeof(PREGUNTA));

   siguiente=(PREGUNTA *)malloc(sizeof(PREGUNTA));
   
   char elim[100];
   int delete = 0;

   
   siguiente = preguntas->sig;
   anterior = preguntas;


   printf("Introduzca el codigo de la pregunta que desea eliminar. \n");

   scanf("%s", elim);

   if (strcmp(anterior->codigo,elim) == 0) {

      strcpy(anterior->codigo, siguiente->codigo);
      strcpy(anterior->nivel, siguiente->nivel);
      strcpy(anterior->area, siguiente->area);
      strcpy(anterior->question, siguiente->question);
      strcpy(anterior->answer1, siguiente->answer1);
      strcpy(anterior->answer2, siguiente->answer2);
      strcpy(anterior->answer3, siguiente->answer3);
      strcpy(anterior->answer, siguiente->answer);
      anterior->sig = siguiente->sig;
      free(siguiente);
      delete = 1;
   }  else {

      while (siguiente != NULL){

         if (strcmp(siguiente->codigo,elim) == 0) {

           anterior->sig = siguiente->sig;
           free(siguiente);
           siguiente = NULL;
           delete = 1;

         } else {

            anterior = siguiente;
            siguiente = siguiente->sig;

         }
      }
   }

   if (delete == 0) {
      printf("ERROR:Introdujo un codigo que no esta en la base de datos");
   }
}

struct PREGUNTA *agregar(PREGUNTA *preguntas){

   PREGUNTA *temporal, *auxiliar;

   char parametro[100];

   int option = 0;

   temporal = preguntas;

   while (temporal->sig != NULL){
      temporal = temporal->sig;
   }

   auxiliar = (PREGUNTA *)malloc(sizeof(PREGUNTA));
   
   temporal->sig = auxiliar;

   printf("\n");

   printf("En este menu podra agregar una nueva pregunta a la base de datos.\n");

   printf("\n");

   while (1) {


      printf("\n");
      printf("Seleccione el numero correspondiente a la opcion que desea agregar: \n");
      printf("\n");
      printf("Opcion 1) Agregar \"Codigo\". \n");
      printf("Opcion 2) Agregar \"Nivel\". \n");
      printf("Opcion 3) Agregar \"Area\". \n");
      printf("Opcion 4) Agregar \"Pregunta\". \n");
      printf("Opcion 5) Agregar \"Respuesta 1\". \n");
      printf("Opcion 6) Agregar \"Respuesta 2\". \n");
      printf("Opcion 7) Agregar \"Respuesta 3\". \n");
      printf("Opcion 8) Agregar \"Nro de respuesta correcta\".\n");
      printf("Opcion 9) Si ya termino de agregar todas las opciones deseadas, finalice con esta opcion.");
      printf("\n");

      scanf("%d", &option);

      printf("\n");

      switch(option) {

         case 1:

            printf("Introduzca el codigo de la pregunta que desea agregar.\n");
            scanf("%s", parametro);
            printf("\n");

            strcpy(auxiliar->codigo,parametro);

            break;

         case 2:

            printf("Introduzca el nivel de la pregunta que desea agregar.\n");
            scanf("%s", parametro);
            printf("\n");

            strcpy(auxiliar->nivel,parametro);

            break;

         case 3:

            printf("Introduzca el area de la pregunta que desea agregar.\n");
            scanf("%s", parametro);
            printf("\n");

            strcpy(auxiliar->area,parametro);



            break;

         case 4:

            printf("Introduzca la pregunta que desea agregar. \n");
            
            scanf(" %[^\t\n]s",&parametro);
            printf("\n");

            strcpy(auxiliar->question,parametro);

            break;

         case 5:

            printf("Introduzca la primera respuesta que desea agregar.\n");
           
            scanf(" %[^\t\n]s",&parametro);
            printf("\n");

            strcpy(auxiliar->answer1,parametro);

            break;
        
        case 6:

            printf("Introduzca la segunda respuesta que desea agregar.\n");
           
            scanf(" %[^\t\n]s",&parametro);
            printf("\n");

            strcpy(auxiliar->answer2,parametro);

            break;

        case 7:

            printf("Introduzca la tercera respuesta que desea agregar.\n");
          
            scanf(" %[^\t\n]s",&parametro);
            printf("\n");

            strcpy(auxiliar->answer3,parametro);

            break;

        case 8:

            printf("Introduzca el numero de la respuesta correcta que desea agregar.\n");
            scanf("%s", parametro);
            printf("\n");

            strcpy(auxiliar->answer,parametro);

            break;
      }

   if (option == 9) {
      
      printf("Se ha agregado su pregunta a la base de datos exitosamente.\n");

      auxiliar->sig = NULL;

      break;
   }

   }

}
void guardar(char *archivo, PREGUNTA *preguntas){

   PREGUNTA *temp;
   temp = preguntas;
   remove(archivo);

   FILE *fp = fopen(archivo, "w");
      
   while (temp!=NULL){

      fprintf(fp,temp->codigo);
      fprintf(fp," ");
      fprintf(fp,temp->nivel);
      fprintf(fp," ");
      fprintf(fp,temp->area);
      fprintf(fp," ");
      fprintf(fp,"\"");
      fprintf(fp,temp->question);
      fprintf(fp,"\"");
      fprintf(fp," ");
      fprintf(fp,"\"");
      fprintf(fp,temp->answer1);
      fprintf(fp,"\"");
      fprintf(fp," ");
      fprintf(fp,"\"");
      fprintf(fp,temp->answer2);
      fprintf(fp,"\"");
      fprintf(fp," ");
      fprintf(fp,"\"");
      fprintf(fp,temp->answer3);
      fprintf(fp,"\"");
      fprintf(fp," ");
      fprintf(fp,temp->answer);
      fprintf(fp,"\n");

      temp = temp->sig;

   }
}

   



