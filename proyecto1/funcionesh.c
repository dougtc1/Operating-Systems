#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct lista {
	char *nombre;
	struct amigos *friends;
	struct lista *sig;
}LISTA;

typedef struct amigos {
	char *amigo;
	struct amigos *sig;
}AMIGOS;

typedef struct comparacion {

	char *tupla;
	struct amigos *primero;
	struct amigos *segundo;
	struct comparacion *sig;

}COMPARACION;

typedef struct hilos {

	struct lista *argumento1;
	
	struct comparacion *argumento2;
	
}HILOS;

// Declaracion de mutex a ser usado en funcion map
pthread_mutex_t mutexmap;

// Declaracion de mutex a ser usado en funcion reduce
pthread_mutex_t mutexreduce;


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

			//printf("%s \n",tmp2->tupla);

			tmp2 = estructura;
				
			}
		}

		tmp1 = tmp1->sig;

	}

	return estructura;

};


LISTA *agregarLista (char *nombre, AMIGOS *comunes, LISTA *definitivo) {

	LISTA *aux;

	aux = definitivo;

	//printf("En agregarLista \n");

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

struct COMPARACION *map(HILOS *argumento) {

	char *nom_tupla, *primero, *segundo;

	LISTA *temporal, *pareja, *ultimo, *lista;

	AMIGOS *auxiliar;

	COMPARACION *resultado;

	lista = argumento->argumento1;

	auxiliar = argumento->argumento1->friends;

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

	pthread_mutex_lock(&mutexmap);

	resultado = agregar(pareja, argumento->argumento2);

	pthread_mutex_unlock(&mutexmap);

	return resultado;

};


struct LISTA *reduce (HILOS *argumento) {

	char *nombre;

	AMIGOS *comunes, *temporal1, *temporal2, *auxiliar;

	LISTA *definitivo;

	COMPARACION *estructura;

	definitivo = argumento->argumento1;

	estructura = argumento->argumento2;

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

			pthread_mutex_lock(&mutexreduce);

			definitivo = agregarLista(nombre,comunes,definitivo);
			
			pthread_mutex_unlock(&mutexreduce);

		} else {

			pthread_mutex_lock(&mutexreduce);

			definitivo = agregarLista(nombre,auxiliar,definitivo);

			pthread_mutex_unlock(&mutexreduce);
		}

	} else { 

		comunes->amigo = (char *)malloc(sizeof(strlen("-None-")));

		strcpy(comunes->amigo,"-None-");
		comunes->sig = NULL;

		pthread_mutex_lock(&mutexreduce);

		definitivo = agregarLista(nombre,comunes,definitivo);

		pthread_mutex_unlock(&mutexreduce);
	}

	return definitivo;

};	