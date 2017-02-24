#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

int main(int argc, char const *argv[]) {

	FILE *file;
	char *linea = NULL;
	size_t tamano = 0;
	char *salida = NULL;
	int longitud;
	
	// Cantidad de hilos y/o procesos a usar

	int n = 0;
	

	LISTA *facelook, *tmp, *ultimo, *auxtmp, *definitivo;
	AMIGOS *tmpA1, *ultimoA1;
	COMPARACION *mapeados;
	
	const char delimitador[3] = " -\n";
	char *token;

	if (argc == 4) {

		//Casting para intrepetar el flag de cantidad de procesos/hilos

		n = atoi(argv[1]);

		file = fopen(argv[2], "r");

		salida = argv[3];


	} else if (argc == 3) {

		file = fopen(argv[1], "r");

		salida = argv[2];

		n = 1;

	} else {

		return 1;
	}

	if (file == NULL) {
	    return 1;
	}

	// Se reserva el espacio de la estructura mapeados

	mapeados = (COMPARACION *)malloc(sizeof(COMPARACION));
	mapeados->tupla=NULL;
	mapeados->primero=NULL;
	mapeados->segundo=NULL;
	mapeados->sig=NULL;


	// Caso base, se crea un cuadro de estructura vacia

	tmp = (LISTA *)malloc(sizeof(LISTA));

	facelook = tmp;

	// Linea por linea del archivo de entrada

	while ((getline(&linea, &tamano, file)) != EOF) {

		ultimo = (LISTA *)malloc(sizeof(LISTA));

	    //printf("%s", linea);

	    // Aqui el token te sirve para llegar hasta - en linea

	    token = strtok(linea, delimitador);
	    longitud = strlen(token);
		tmp->nombre = (char *)malloc(sizeof(char)*longitud);
	    strcpy(tmp->nombre, token);

	    // Aqui el token pasa a ser null y se desecha el ">"
	    
	    char basura = strtok(NULL,delimitador);

	    // Primer tokenizado y agregado a la estructura

		token = strtok(NULL,delimitador);

		tmp->friends = (AMIGOS *)malloc(sizeof(AMIGOS));

		if (strcmp(token,"None") != 0) {
		
			longitud = strlen(token);
		    tmp->friends->amigo = (char *) malloc(sizeof(char)*longitud);
		    strcpy(tmp->friends->amigo, token);
		    tmp->friends->sig = NULL;
		    ultimoA1 = tmp->friends;

		    token = strtok(NULL,delimitador);

			// Iteracion de los amigos de cada linea. 

		    while (token != NULL) {

		    	longitud = strlen(token);
		    	tmpA1 = (AMIGOS*) malloc(sizeof(AMIGOS));
		    	tmpA1->amigo = (char *) malloc(sizeof(char)*longitud);
		    	strcpy(tmpA1->amigo, token);
		    	tmpA1->sig = NULL;
		    	ultimoA1->sig = tmpA1;
		    	ultimoA1 = tmpA1;

		    	token = strtok(NULL,delimitador);

			}
	    
	    } else {

	    	longitud = strlen(token);
	    	tmp->friends->amigo = (char *) malloc(sizeof(char)*longitud);
	    	strcpy(tmp->friends->amigo,token);

	    }

	    tmp->sig = ultimo;

	    tmp = ultimo;

	}

	printf("\n");
	
		if (linea) {
	    	free(linea);
		}

	fclose(file);

	auxtmp = facelook;

	while(auxtmp->nombre != NULL) {

		mapeados = map(auxtmp,mapeados);

		auxtmp = auxtmp->sig;
	}

	definitivo = (LISTA *)malloc(sizeof(LISTA));
	definitivo->nombre = NULL;
	definitivo->friends = NULL;

	while (mapeados != NULL) {

		//printf("%s \n",mapeados->tupla);

		definitivo = reduce(mapeados,definitivo);

		mapeados = mapeados->sig;

	}
 
// 	printf("%s \n",definitivo->nombre);
//	printf("%s \n",definitivo->friends->amigo);

	//Hay que liberar "facelook" despues de escribir todos los MAPS

	//Hay que liberar "mapeados" despues de hacer todo el reduce

	// Por ultimo hay que liberar "definitivo" despues de escribir la salida



	//PRINTS DE RESULTADO DEL MAP
/*

	printf("%s \n",mapeados->tupla);
	printf("%s \n",mapeados->primero->amigo);
	printf("%s \n",mapeados->sig->tupla);
	printf("%s \n",mapeados->sig->sig->tupla);

	//PRINTS DE LECTURA DE ARCHIVO

	printf("%d \n",n);
	printf("%s \n", salida);

	printf("Aqui comienza la prueba: \n");

	printf("%s \n",facelook->nombre);
	printf("%s \n",facelook->friends->amigo);
	printf("%s \n",facelook->sig->nombre);
	printf("%s \n",facelook->sig->friends->amigo);
	printf("%s \n",facelook->sig->sig->friends->amigo);
	printf("%s \n",facelook->sig->sig->friends->sig->sig->amigo);
*/
	return 0;
}
