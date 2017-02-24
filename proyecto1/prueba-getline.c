#include <stdio.h>
#include <stdlib.h>

typedef struct amigos {
	char *amigo;
	struct amigos *sig;
}AMIGOS;

typedef struct lista {
	char *nombre;
	struct amigos *friends;
	struct lista *sig;
}LISTA;

int main(int argc, char const *argv[]) {

	FILE *file;
	char *linea = NULL;
	size_t tamano = 0;
	char read;
	char *salida = NULL;
	int longitud;
	int n =0;
	

	LISTA *facelook, *tmp, *ultimo;
	AMIGOS *tmpA1, *ultimoA1;
	
	const char delimitador[3] = " -\n";
	char *token;

	if (argc == 4) {

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


	// Caso base, se crea un cuadro de estructura vacia

	tmp = (LISTA *)malloc(sizeof(LISTA));

	facelook = tmp;

	// Linea por linea del archivo de entrada

	while ((read = getline(&linea, &tamano, file)) != EOF) {

		ultimo = (LISTA *)malloc(sizeof(LISTA));

	    printf("Retrieved line of length %d:\n", read);

	    printf("%s", linea);


	    // Aqui el token te sirve para llegar hasta arrow en linea

	    token = strtok(linea, delimitador);
	    longitud = strlen(token);
		tmp->nombre = (AMIGOS *)malloc(sizeof(char)*longitud);
	    strcpy(tmp->nombre, token);

	    // Aqui el token pasa a ser null y te sirve para llegar hasta espacio
	    
	    char basura = strtok(NULL,delimitador);

	    // Primer tokenizado y agregado a la estructura

		token = strtok(NULL,delimitador);

		tmp->friends = (AMIGOS *)malloc(sizeof(AMIGOS));

		printf("TOKEN = %s \n",token);

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

	    	printf("Else \n");
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

	printf("%d \n",n);
	printf("%s \n", salida);
/*
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
