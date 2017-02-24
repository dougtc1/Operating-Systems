// Tarea 1 - Sistemas Operativos
//Integrantes:
//Ricardo Churion, carnet:11-10200
//Douglas Torres, carnet: 11-11027

//Importamos las librerias

#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

int main () {

	FILE *fp = NULL;
	int opcion = 0;
	char archivo[50];
	char dif;
	PREGUNTA *preguntas1;

	//preguntas = (PREGUNTA *)malloc(sizeof(PREGUNTA));

	while (1) {

		printf("\n");
		printf("Seleccione el numero correspondiente a la accion que desea realizar: \n");
		printf("\n");
		printf("Opcion 1) Leer base de datos. \n");
		printf("Opcion 2) Consultar preguntas en la base de datos. \n");
		printf("Opcion 3) Consultar las preguntas de cierta dificultad. \n");
		printf("Opcion 4) Eliminar una pregunta. \n");
		printf("Opcion 5) Insertar una pregunta. \n");
		printf("Opcion 6) Salvar la base de datos. \n");
		printf("Opcion 7) Salir. \n");
		printf("\n");
		
		scanf("%d", &opcion);

		printf("\n");

		switch(opcion) {

			case 1:

				if (fp != NULL) {

					printf("Ya los datos estan en memoria \n");

				} else {

					printf("Que archivo desea abrir?\n");
					scanf("%s", archivo);

					fp = fopen(archivo,"rw");

				 	preguntas1 = leer(fp);

				}

				break;
		
			case 2:

				if (fp != NULL) {

					mostrartodas(preguntas1);

				} else {
					printf("Aun no se ha cargado ningun archivo en memoria.\n");
				}

				break;

			case 3:

				mostraralgunas(preguntas1);

				break;

			case 4:

				eliminar(preguntas1);

			case 5:

				agregar(preguntas1);
		
	}

	if (opcion == 7) {

		break;
	}
}

return 0;
}