//Tarea 1
// Ricardo Churion, carnet:11-10200
// Douglas Torres, carnet:11-11027

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