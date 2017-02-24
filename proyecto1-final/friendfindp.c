// Proyecto 1 - Sistemas Operativos
// Integrantes:
// Ricardo Churion, carnet:11-10200
// Douglas Torres, carnet: 11-11027

//Importamos las librerias a usar

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "funcionesh.h"
#include <semaphore.h>
#include <fcntl.h>


/*  Declaracion de funcion que agrega elementos a la estructura mapeados que 
	contiene a todas las parejas resultantes del map. Recibe como argumentos
	listaAmigos que contiene a todas las parejas de amigos que resultan del map
	y estructura que es a donde son agregadas. */


struct LISTA *leer(FILE *file) {

	char *linea = NULL;
	char *token;
	int longitud;
	size_t tamano = 0;
	const char delimitador[3] = " -\n";

	LISTA *tmp, *ultimo, *salida;
	AMIGOS *tmpA1, *ultimoA1;
	COMPARACION *mapeados;
	FILE *archivo;

	archivo = file;

	// Caso base, se crea un cuadro de estructura vacia

	tmp = (LISTA *)malloc(sizeof(LISTA));

	salida = tmp;

	printf("vuelvo al leer \n");

	printf("%d \n",getline(&linea, &tamano, archivo));

	// Linea por linea del archivo de entrada

	while ((getline(&linea, &tamano, archivo)) != EOF) {

		printf("ENTRE AL WHILE \n");

		ultimo = (LISTA *)malloc(sizeof(LISTA));

	    // Aqui el token te sirve para llegar hasta - en linea

	    token = strtok(linea, delimitador);
	    longitud = strlen(token);
		tmp->nombre = (char *)malloc(sizeof(char)*longitud);
	    strcpy(tmp->nombre, token);
	    printf("%s \n",tmp->nombre);

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

	fclose(archivo);

	return salida;
};

struct COMPARACION *agregar(LISTA *listaAmigos, COMPARACION *estructura) {

	LISTA *tmp1;

	COMPARACION *tmp2, *ultimo1;

	tmp1 = (LISTA *)malloc(sizeof(LISTA));

	tmp2 = (COMPARACION *)malloc(sizeof(COMPARACION));

	tmp1 = listaAmigos;

	tmp2 = estructura;

	while(tmp1->nombre != NULL) {

		if (tmp2->tupla == NULL) {
				
			tmp2->tupla = (char *)malloc(sizeof(strlen(tmp1->nombre)));

			strcpy(tmp2->tupla,tmp1->nombre);

			tmp2->primero = tmp1->friends;

			tmp2->sig = NULL;

			tmp2 = estructura;

		} else {

			while (tmp2 != NULL) {

					if (strcmp(tmp2->tupla,tmp1->nombre) == 0) {
						
						tmp2->segundo = tmp1->friends;

						tmp2 = estructura;

						break;

					} else {

						ultimo1 = tmp2;
						tmp2 = tmp2->sig;

						}
			}

			if (tmp2 == NULL) {
				
			tmp2 = (COMPARACION *)malloc(sizeof(COMPARACION));

			tmp2->tupla = (char *)malloc(sizeof(strlen(tmp1->nombre)));

			strcpy(tmp2->tupla,tmp1->nombre);

			tmp2->primero = tmp1->friends;

			tmp2->sig = NULL;

			ultimo1->sig = tmp2;

			tmp2 = estructura;
				
			}
		}

		tmp1 = tmp1->sig;

	}

	return estructura;

};

/*  Declaracion de funcion que agrega las parejas de amigos y sus amigos en 
	comun, proveniente del reduce, en la estructura definitivo. Recibe como
	argumentos el nombre de la tupla que voy a agregar, los amigos comunes
	de dicha tupla y la estructura definitivo que es a donde se agregan.
*/

LISTA *agregarLista (char *nombre, AMIGOS *comunes, LISTA *definitivo) {

	LISTA *aux;

	aux = definitivo;

	if (definitivo->nombre == NULL) {

		definitivo->nombre = (char *)malloc(sizeof(strlen(nombre)));

		strcpy(definitivo->nombre,nombre);

		definitivo->friends = comunes;

	} else {

		while (definitivo->sig != NULL) {

			definitivo = definitivo->sig;
		}

		definitivo->sig = (LISTA *)malloc(sizeof(LISTA));

		definitivo->sig->nombre = (char *)malloc(sizeof(strlen(nombre)));

		strcpy(definitivo->sig->nombre,nombre);

		definitivo->sig->friends = comunes;

	}

	return aux;

};

/*  Declaracion de funcion map que recibe como argumentos a la estructura hilos,
	donde se ubica como argumento1 la lista de amigos de la primera tupla y
	como argumento2 la estructura mapeados, a la que se van a agregar al salir
	del map. En dicha estructura mapeados, tendria como mapeados->primero los
	amigos de la primera vez que se consigue la tupla, y al volverla a encontrar,
	se agregan en mapeados->segundo.
*/

void *map(LISTA *lista, COMPARACION *estructura) {

	char *nom_tupla, *primero, *segundo, *filename;

	int prueba;

	LISTA *temporal, *pareja, *ultimo;

	AMIGOS *auxiliar;

	COMPARACION *resultado;

	auxiliar = lista->friends;

	temporal = (LISTA*)malloc(sizeof(LISTA));
	
	pareja = temporal;
		
	if (strcmp(lista->friends->amigo,"None") == 0) {
		
			;

	} else {

		while (auxiliar != NULL) {

			ultimo = (LISTA *)malloc(sizeof(LISTA));
			ultimo->nombre = NULL;
			ultimo->friends = NULL;
			ultimo->sig = NULL;


			if (strcmp(lista->nombre,auxiliar->amigo) < 0) {

				primero = (char *)malloc(sizeof(strlen(lista->nombre)));
				segundo = (char *)malloc(sizeof(strlen(auxiliar->amigo)));

				strcpy(primero, lista->nombre);
				strcpy(segundo,auxiliar->amigo);				


			} else {

				primero = (char *)malloc(sizeof(strlen(auxiliar->amigo)));
				segundo = (char *)malloc(sizeof(strlen(lista->nombre)));

				strcpy(primero,auxiliar->amigo);
				strcpy(segundo,lista->nombre);	

			}

			nom_tupla = (char *)malloc(sizeof(strlen(primero)+strlen(segundo)+5));

			strcpy(nom_tupla, "(");
			strcat(nom_tupla,primero);
			strcat(nom_tupla," ");
			strcat(nom_tupla,segundo);
			strcat(nom_tupla, ")");

			temporal->nombre = (char *)malloc(sizeof(strlen(nom_tupla)));

			strcpy(temporal->nombre,nom_tupla);
	
			temporal->friends = lista->friends;

			temporal->sig = ultimo;

			ultimo->sig = NULL;

	    	temporal = ultimo;

	    	auxiliar = auxiliar->sig;

			}

		}
	
	filename = (char *)malloc(sizeof(strlen((char *)getpid() + 4)));

	prueba = getpid();

	sprintf(filename,"%d",prueba);

	strcat(filename,".txt");

	escribir(pareja,filename);

	exit(0);

};

/*  Declaracion de funcion reduce que se encarga de verificar si en cada
	elemento de estructura tiene ambas lista de amigos llenas,
	estructura->primero y estructura->segundo, en caso de tenerlas ambas,
	verifica si hay nombres en comun y los guarda en comunes, en caso
	contrario, se le agrega a la pareja como comunes->amigo "-None-" 
*/


void *reduce (COMPARACION *estructura, char * salida) {

	char *nombre, *semaforo;

	LISTA *definitivo;

	AMIGOS *comunes, *temporal1, *temporal2, *auxiliar;

	semaforo=(char *)malloc(sizeof(strlen("semaforo")));

	strcpy(semaforo,"semaforo");

	sem_open(semaforo,O_CREAT);

	definitivo = (LISTA *)malloc(sizeof(LISTA));
	definitivo->nombre = NULL;
	definitivo->friends = NULL;

	nombre = (char *)malloc(sizeof(strlen(estructura->tupla)));

	comunes = (AMIGOS *)malloc(sizeof(AMIGOS));

	comunes->amigo = NULL;

	comunes->sig = NULL;

	auxiliar = comunes;

	strcpy(nombre,estructura->tupla);

	temporal1 = estructura->primero;

	temporal2 = estructura->segundo;


	if (estructura->segundo != NULL) {

		while(temporal1 != NULL) {

			while(temporal2 != NULL){

				if (strcmp(temporal1->amigo,temporal2->amigo) == 0) {

					comunes->amigo = (char *)malloc(sizeof(strlen(temporal1->amigo)));

					strcpy(comunes->amigo, temporal1->amigo);

					comunes->sig = (AMIGOS *)malloc(sizeof(AMIGOS));

					comunes = comunes->sig;

					break;
				
				} else {

					temporal2 = temporal2->sig;

				}

			}

			if (temporal1->sig == NULL)	{
				break;
			}

			temporal1 = temporal1->sig;
			temporal2 = estructura->segundo;

		}

		if (comunes == NULL) {

			comunes->amigo = (char *)malloc(sizeof(strlen("-None-")));

			strcpy(comunes->amigo,"-None-");

			comunes->sig = NULL;

			definitivo->nombre = (char *)malloc(sizeof(strlen(nombre)));

			strcpy(definitivo->nombre,nombre);

			definitivo->friends = comunes;

			printf("ANTES SALIDA \n");

			sem_wait(&semaforo);

			escribir(definitivo, salida);

			printf("DESPUES SALIDA \n");

			sem_post(&semaforo);


		} else {

			definitivo->nombre = (char *)malloc(sizeof(strlen(nombre)));

			strcpy(definitivo->nombre,nombre);

			definitivo->friends =  comunes;

			printf("ANTES SALIDA \n");

			sem_wait(&semaforo);

			escribir(definitivo, salida);

			printf("DESPUES SALIDA \n");

			sem_post(&semaforo);

		}

	} else { 

		comunes->amigo = (char *)malloc(sizeof(strlen("-None-")));

		strcpy(comunes->amigo,"-None-");

		comunes->sig = NULL;

		definitivo->nombre = (char *)malloc(sizeof(strlen(nombre)));

		strcpy(definitivo->nombre,nombre);

		definitivo->friends = comunes;

		printf("ANTES SALIDA \n");

		sem_wait(&semaforo);

		escribir(definitivo, salida);

		printf("DESPUES SALIDA \n");

		sem_post(&semaforo);

	}

};

/*  Funcion que se encarga de escribir en un archivo la salida del programa,
	esta consiste en el nombre de la tupla (temp->nombre) -> nombre(s) de
	amigo(s) en comun (temp->friends->amigo).
*/

void escribir(LISTA *definitivo, char *salida) {

   LISTA *temp;

   const char flecha[4] = " ->"; 
   temp = definitivo;

   printf("%s \n",salida);

   FILE *fp = fopen(salida, "w");
   
   printf("EN ESCRIBIR 5 \n");

   printf("%s \n",temp->nombre);

   while (temp->nombre != NULL){

   		printf("PRIMER WHILE \n");

		fprintf(fp,temp->nombre);
      
		fprintf(fp,flecha);

		while (temp->friends != NULL) {
      
      		fprintf(fp," ");

			fprintf(fp,temp->friends->amigo);
			
			temp->friends = temp->friends->sig;
    		
		}

		if (temp->sig->nombre != NULL) {
			
			fprintf(fp,"\n");

		}

		temp = temp->sig;

   }

   fclose(fp);

};


/*  Funcion main del programa, en ella se encarga de leer el archivo de entrada,
	crear los hilos, llamar a las funciones map y reduce de forma concurrente a
	traves de hilos y tambien llama a salida para imprimir el resultado del programa.
*/

void main(int argc, char const *argv[]) {

	FILE *file;
	char *filename;
	char *salida = NULL;
	int longitud;

	pid_t child;
	
	// Cantidad de hilos y/o procesos a usar

	int n = 0;

	LISTA *facelook, *tmp, *ultimo, *definitivo, *auxtmp;
	AMIGOS *tmpA1, *ultimoA1;
	COMPARACION *mapeados;
	
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

	// Se declara el arreglo que va a contener los hijos del proceso

	pid_t hijos[n];

	// Se reserva el espacio de la estructura mapeados

	mapeados = (COMPARACION *)malloc(sizeof(COMPARACION));
	mapeados->tupla=NULL;
	mapeados->primero=NULL;
	mapeados->segundo=NULL;
	mapeados->sig=NULL;

	//Llamada a la funcion que lee lineas de archivo de entrada

	facelook = leer(file);

	auxtmp = facelook;

	int i = 0;

	
	while(auxtmp->nombre != NULL) {

		for (i = 0; i < n; ++i) {

			child =fork();

			if (child==0) {

				map(auxtmp,mapeados);
					
			} else {

				hijos[i] = child;
			}

		}
		
		auxtmp = auxtmp->sig;
	}

	int *status;

	for (i = 0; i < n; ++i) {
		wait(&status);
	}

	i = 0;

	char *filehijos;

	for (i = 0; i < n; ++i) {
		
		child = hijos[i];

		sprintf(filehijos,"%d",child);

		strcat(filehijos,".txt");

		printf("%s \n",filehijos);

		file = fopen(filehijos, "r");

		auxtmp = leer(file);

		mapeados = agregar(auxtmp,mapeados);
	}

	i = 0;

	while (mapeados != NULL) {
		
		for (i = 0; i < n; ++i) {

			child = fork();

			if (child==0) {

				printf("ANTES DEL REDUCE \n");
				reduce(mapeados,salida);
				
			} else {

				;
			}

			printf("EN EL WHILE DE REDUCE \n");

			mapeados = mapeados->sig;
	    		
		}
	 
	}

	free(facelook);
	free(mapeados);
	free(definitivo);
}

/*	

	printf("LLEGUE AL FINAL \n");
	printf("%s \n",definitivo->nombre);
	printf("%s \n",definitivo->friends->amigo);

	//Hay que liberar "facelook" despues de escribir todos los MAPS

	//Hay que liberar "mapeados" despues de hacer todo el reduce

	// Por ultimo hay que liberar "definitivo" despues de escribir la salida



	//PRINTS DE RESULTADO DEL MAP

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