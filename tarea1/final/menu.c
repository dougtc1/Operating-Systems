// Tarea 1 - Sistemas Operativos
//Integrantes:
//Ricardo Churion, carnet:11-10200
//Douglas Torres, carnet: 11-11027

//Importamos las librerias

#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

int main ( int argc, char *argv[] ) {
	 if ( argc != 2 ) {
	 	printf("Falto el archivo al lado del nombre del programa");
	 	return 0 ;
	 }

	FILE *fp = NULL;
	int opcion = 0;
	char archivo[50];
	char dif;
	PREGUNTA *preguntas;
	int save =0;

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
					strcpy(archivo, argv[1]);
					
					fp = fopen(archivo,"rw");

				 	preguntas = leer(fp);

				}

				break;
		
			case 2:

				if (fp != NULL) {

					mostrartodas(preguntas);

				} else {
					printf("Aun no se ha cargado ningun archivo en memoria.\n");
				}

				break;

			case 3:

				if (fp != NULL) {

					mostraralgunas(preguntas);

				} else {
					printf("Aun no se ha cargado ningun archivo en memoria.\n");
				}

				break;

			case 4:

				if (fp != NULL) {

					eliminar(preguntas);
					save = 0;

				} else {
					printf("Aun no se ha cargado ningun archivo en memoria.\n");
				}

				break;

			case 5:

				if (fp != NULL) {

					agregar(preguntas);
					save = 0;

				} else {
					printf("Aun no se ha cargado ningun archivo en memoria.\n");
				}

				break;
			case 6:


				if (fp != NULL) {

					guardar(archivo,preguntas);
					save = 1;

				} else {
					printf("Aun no se ha cargado ningun archivo en memoria.\n");
				}

				break;			
	}

	if (opcion == 7) {

		if (save == 1) {
			printf ("Fin del programa,\n");
			break;
		}

		else {
			printf("Aun no ha guardado su base de datos.\n");
			printf("Se guardara por usted antes de finalizar el programa.\n");
			guardar(archivo,preguntas);
			printf("Se ha guardado su base de datos, fin del programa.\n");
			break;
		}
		
	}
}

return 0;
}