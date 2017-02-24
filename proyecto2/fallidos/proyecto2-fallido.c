#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char const *argv[]) {

	printf("ESTOY EMPEZANDO \n");

	struct stat statbuf;

	int directorios[10] = {1,2,3,4,5,6,7,8,9,10};
	int archivos[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

	int tmp;
	int random;
	int contador=0;

	char *direccion = NULL;

	char *salida = NULL;

	int n,m,i,j;

	time_t t;

	pid_t child;

	char *cmd=NULL;

	if (argc == 5) {

		direccion = (char *) malloc(sizeof(strlen(argv[1]) + 1));

		direccion = argv[1];

		n = atoi(argv[2]);

		m = atoi(argv[3]);

		salida = argv[4];

	    printf("HAY 5 ARGUMENTOS %s \n",direccion);


	} else if (argc == 4) {

		char cwd[1024];

		direccion = getcwd(cwd,sizeof(cwd));

		printf("HAY 4 ARGUMENTOS %s \n",direccion );

		n = atoi(argv[1]);

		m = atoi(argv[2]);

		salida = argv[3];

	} else {

			return 1;
	}

	// Se randomiza el arreglo directorios

	srand((unsigned) time(&t));

	for (i = 0; i < 10; i++) {    // shuffle array

	    tmp = directorios[i];
	    random = rand() % 10;

	    directorios[i] = directorios[random];
	    directorios[random] = tmp;
	}	

	srand((unsigned) time(&t));

	// Se randomiza el arreglo de archivos

	for (i = 0; i < 20; i++) {

	    tmp = archivos[i];
	    random = rand() % 20;
	    archivos[i] = archivos[random];
	    archivos[random] = tmp;

	}

	// Se seleccionan los numeros aleatorios de los arreglos

	printf("IMPRIMO LOS ARRAYS \n");


	for (i = 0; i < 20; i++) {    // print array
	    printf("%d,",archivos[i]);
	}

	printf("\n");
	for (i = 0; i < 10; i++) {    // print array
	    printf("%d,",directorios[i]);
	}
	printf("\n");

	// Se comienzan a agregar los directorios a acceder en aux_dir, esta solo contiene el numero en cuestion

	// Se iteran n veces, es decir, la cantidad de procesos y carpetas que queria crear/acceder el usuario

	for (i = 0; i < n; i++) {

		char buffer[1];

		char *aux_dir = NULL;

		sprintf(buffer, "%d",directorios[i]);

		aux_dir = (char *) malloc(sizeof(strlen(buffer) + 1));

		strcpy(aux_dir,buffer);

		strcat(aux_dir,"/");

		printf(" JUSTO ANTES DEL FORK ESTE ES aux_dir: %s \n",aux_dir);

		// Se hace fork para crear a los hijos

		child = fork();
		
		if (child == 0) {

				char *auxiliar_direccion = NULL;

				auxiliar_direccion = (char *) malloc(sizeof(strlen(direccion) + strlen(aux_dir) + 1));

				strcpy(auxiliar_direccion,direccion);

				printf("1 EN EL HIJO, ESTE ES auxiliar_direccion SOLO CON DIRECCION ACTUAL: %s \n",auxiliar_direccion);

				//	auxiliar_direccion = (char *) realloc(auxiliar_direccion,strlen(auxiliar_direccion)+strlen(aux_dir));

				strcat(auxiliar_direccion,aux_dir);

				printf("2 EN EL HIJO, ESTE ES auxiliar_direccion CON LA DIRECCION DE LA CARPETA A ACCEDER: %s \n",auxiliar_direccion);

				cmd = (char *)malloc(sizeof("cat "));

				strcpy(cmd,"cat ");

				for (j = 0; j < m; ++j) {

					char *aux_arch = NULL;

					char buffer_extra[1];

					printf("3 ESTE ES auxiliar_direccion ANTES DE AGREGAR EL ARCHIVO A LEER: %s \n",auxiliar_direccion);

					aux_arch = (char *) malloc(sizeof(strlen(archivos[j]) + 1));

					sprintf(buffer_extra, "%d",archivos[j]);

					printf("4 ESTE ES auxiliar_direccion ANTES DE AGREGAR EL ARCHIVO A LEER:  %s \n",auxiliar_direccion);

					printf("5 ESTE ES buffer: %s \n",buffer_extra);

					strcpy(aux_arch,buffer_extra);

					printf("6 ESTE ES aux_arch DESPUES DE AGREGAR buffer: %s \n",aux_arch);

					char *temporal=NULL;

					temporal=(char *) malloc(sizeof(strlen(auxiliar_direccion) + strlen(aux_arch) + 1));

					strcpy(temporal, auxiliar_direccion);

					printf("7 ESTE ES temporal DESPUES DE COPIARLE auxiliar_direccion: %s \n",temporal);

					strcat(temporal, aux_arch);

					printf("8 ESTE ES temporal DESPUES DE COPIARLE auxiliar_direccion Y aux_arch: %s \n",temporal);

					printf("ANTES DE VERIFICAR QUE ES REGULAR \n");

					if (!(statbuf.st_mode & S_IFREG)){

						cmd =(char *) realloc(cmd,strlen(cmd) + strlen(temporal) + 1);

	    				strcat(cmd,temporal);

	    				strcat(cmd," ");

	    				printf("ESTE ES CMD %s \n",cmd);

	    				contador++;

					}

	    			free(aux_arch);
	    			free(temporal);
	    		}
					
					printf("HIJO %d %s \n",i,cmd);

					exit(1);

		} else {

			wait();

		}

	}
					
 	printf("El padre termina \n");

	return 0;
}


/*

    char *cmd=NULL;

	cmd = (char *)malloc(sizeof("cd "));

    strcpy(cmd,"cd ");

    cmd =(char *)realloc(cmd, strlen(cmd)+strlen(direccion));

    strcat(cmd,direccion);

    printf("%s \n",cmd);

    system(cmd);



    auxiliar_direccion = (char *) realloc(auxiliar_direccion,strlen(auxiliar_direccion)+strlen(aux_dir));
	
	cmd =                (char *)realloc(cmd, strlen(cmd)+strlen(temporal) + 1);

	*/