#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

void main(int argc, char const *argv[]) {

	struct stat statbuf;

	int directorios[10] = {1,2,3,4,5,6,7,8,9,10};
	int archivos[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

	int tmp;
	int random;
	int contador=0;

	char *direccion = NULL;

	char *salida = NULL;

	int n,m,i,j,fd1;

	time_t t;

	pid_t child;

	char *cmd=NULL;

	FILE *fp, *fp2;

	int status,bytes;

	if (argc == 5) {

		direccion = (char *) malloc(sizeof(strlen(argv[1]) + 1));

		direccion = argv[1];

		n = atoi(argv[2]);

		m = atoi(argv[3]);

		salida = argv[4];

	} else if (argc == 4) {

		char cwd[1024];

		direccion = getcwd(cwd,sizeof(cwd));

		n = atoi(argv[1]);

		m = atoi(argv[2]);

		salida = argv[3];

	} else {

			exit(0);
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

	// Se comienzan a agregar los directorios a acceder en aux_dir, esta solo contiene el numero en cuestion

	// Se iteran n veces, es decir, la cantidad de procesos y carpetas que queria crear/acceder el usuario

	for (i = 0; i < n; i++) {

		char buffer[1];

		char *aux_dir = NULL;

		sprintf(buffer, "%d",directorios[i]);

		aux_dir = (char *) malloc(sizeof(strlen(buffer) + 1));

		strcpy(aux_dir,buffer);

		strcat(aux_dir,"/");

		// Se crea el pipe por donde se van a comunicar padre e hijo

		int fd[2];
	
		pipe(fd);

		// Se hace fork para crear a los hijos

		if ((child = fork())==0) {
		

				char *auxiliar_direccion = NULL;

				auxiliar_direccion = (char *) malloc(sizeof(strlen(direccion) + strlen(aux_dir) + 1));

				strcpy(auxiliar_direccion,direccion);

				//	auxiliar_direccion = (char *) realloc(auxiliar_direccion,strlen(auxiliar_direccion)+strlen(aux_dir));

				strcat(auxiliar_direccion,aux_dir);

				cmd = (char *)malloc(sizeof("cat "));

				strcpy(cmd,"cat ");

				for (j = 0; j < m; ++j) {

					char *aux_arch = NULL;

					char buffer_extra[1];

					aux_arch = (char *) malloc(sizeof(strlen(archivos[j]) + 1));

					sprintf(buffer_extra, "%d",archivos[j]);

					strcpy(aux_arch,buffer_extra);

					char *temporal=NULL;

					temporal=(char *) malloc(sizeof(strlen(auxiliar_direccion) + strlen(aux_arch) + 1));

					strcpy(temporal, auxiliar_direccion);

					strcat(temporal, aux_arch);

					stat(temporal,&statbuf);

					if (access(temporal, F_OK) != -1) {
						

						if (S_ISREG(statbuf.st_mode)){

							cmd =(char *) realloc(cmd,strlen(cmd) + strlen(temporal) + 1);

		    				strcat(cmd,temporal);

		    				strcat(cmd," ");

		    				//printf("ESTE ES CMD %s \n",cmd);

		    				contador++;

						}
					}

	    			free(aux_arch);
	    			free(temporal);
	    		}

	    		free(auxiliar_direccion);
					
				//printf("HIJO %d %s \n",i,cmd);

				close(fd[0]); /* Se cierran el descriptor que no se usa */

				write(fd[1], cmd, strlen(cmd) + 1);

				close(fd[1]);

				exit(0);

		} else {

			close(fd[1]); /* Se cierran los descriptores que no se usan */

			char buf[500];

			bytes = read(fd[0],buf,500);

			system(buf);

			strcat(buf,">> ");

			strcat(buf,salida);

			system(buf);

			printf("%s \n",buf);

			close(fd[0]);
		
			wait(n);
 			
 		}

	}

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