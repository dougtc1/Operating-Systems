// Proyecto 2 - Sistemas Operativos
// Integrantes:
// Ricardo Churion, carnet:11-10200
// Douglas Torres, carnet: 11-11027

//Importamos las librerias a usar

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>

void main(int argc, char const *argv[]) {

	// Se declaran los arreglos con los nombres de carpetas y archivos

	int directorios[10] = {1,2,3,4,5,6,7,8,9,10};
	int archivos[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};


	// Declaracion de estructura que permite verificar existencia de un archivo

	struct stat statbuf;

	int tmp;
	int random;
	int contador=0;

	char *direccion = NULL;

	char *salida = NULL;

	int n,m,i,j;

	time_t t;

	pid_t child;

	char *cmd=NULL;

	FILE *fp, *fp2;

	int status;

	// Lectura de los argumentos pasados al momento de ejecutar el programa

	if (argc == 6) {

		direccion = (char *) malloc(sizeof(strlen(argv[1]) + 1));

		direccion = argv[2];

		n = atoi(argv[3]);

		m = atoi(argv[4]);

		salida = argv[5];

	} else if (argc == 4) {

		char cwd[1024];

		direccion = getcwd(cwd,sizeof(cwd));

		n = atoi(argv[1]);

		m = atoi(argv[2]);

		salida = argv[3];

	} else {

		exit(0);
	}

	// Arreglo donde se guardan la cantidad de archivos leidos por cada hijo

	int archleidos[n];

	// Se randomiza el arreglo directorios usando a time como seed

	srand((unsigned) time(&t));

	for (i = 0; i < 10; i++) {    // shuffle array

	    tmp = directorios[i];
	    random = rand() % 10;

	    directorios[i] = directorios[random];
	    directorios[random] = tmp;
	}	

	srand((unsigned) time(&t));

	// Se randomiza el arreglo archivos usando a time como seed

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

		// Se hace fork para crear a los hijos, se verifica si no hubo problemas

		if ((child = fork()) == 0) { // Codigo que ejecutan los hijos
		
			contador = 0;  // Cantidad de archivos leidos por el hijo

			char *auxiliar_direccion = NULL;
			
			auxiliar_direccion = (char *) malloc(sizeof(strlen(direccion) + strlen(aux_dir) + 1));
			
			strcpy(auxiliar_direccion,direccion);
			
			strcat(auxiliar_direccion,aux_dir);
			
			// Comando que se ejecutara para concatenar los archivos

			cmd = (char *)malloc(sizeof("cat "));
			
			strcpy(cmd,"cat ");

			// Se itera m veces para verificar si existen los archivos regulares que seran leidos por cada hijo
			
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

				// Se pregunta si existe el archivo
				
				if (access(temporal, F_OK) != -1) {

					// Se pregunta si es un archivo regular

					if (S_ISREG(statbuf.st_mode)){
				
						// En caso afirmativo se procede a concatenar dicho archivo a "cmd"

						cmd =(char *) realloc(cmd,strlen(cmd) + strlen(temporal) + 1);
	    		
	    				strcat(cmd,temporal);
	    		
	    				strcat(cmd," ");

	    				// Se suma 1 al contador debido a que se puede leer el archivo especificado
	    		
	    				contador++;
					}
				}

				// Se libera el espacio de variables que ya no seran usadas durante la siguiente iteracion
	    		
	    		free(aux_arch);
	    		
	    		free(temporal);
	    	}

    		char entero[1];
    		
    		sprintf(entero,"%d",i);

    		// Se redirecciona la salida estandar a un archivo temporal llamado "entero" 
    		
    		freopen(entero, "w", stdout);

    		// Se ejecuta "cmd" y su salida es escrita en el archivo temporal "entero"
    		
    		system(cmd);
			
			close(fd[0]); /* Se cierra el descriptor que no se usa */

			// Se pasa por el pipe el nombre del archivo temporal que creo el hijo
			
			write(fd[1], entero, 3);
			
			close(fd[1]);

			free(auxiliar_direccion);

			free(cmd);
			
			exit(contador); // En "contador" se pasa la cantidad de archivos que han sido leidos por el hijo

		} else {  // Codigo que ejecuta el padre

			char auxiliar[1];
			
			char auxiliar2[2];
			
			char *cat=NULL;
			
			cat = (char *)malloc(sizeof(strlen("cat ") + 2));
			
			char ch;
			
			close(fd[1]); /* Se cierra el descriptor que no se usa */
			
			stat(fp2,&statbuf);

			// Se lee el pipe que comunica el padre con el hijo, auxiliar toma el nombre del archivo temporal
			
			read(fd[0], auxiliar, 3);
			
			strcpy(cat,"cat ");
			
			strcat(cat,auxiliar);
			
			system(cat); // Se ejecuta cat del archivo temporal para mostrar en salida estadar el contenido de dicho archivo
			
			strcpy(auxiliar2, auxiliar);

			// Se crea el archivo de salida que tendra el contenido final
			
			fp = fopen(salida, "wa");
			
			fp2 = fopen(auxiliar, "ra");

			// Se itera para tomar del file descriptor fp2 el contenido del archivo temporal, que se guarda en ch
			
			while ((ch = fgetc(fp2)) != EOF){
        	
				// Se escribe en "salida" a traves del file descriptor fp

        		fputc(ch, fp);
        	
        	}
			
        	// Se borra el archivo temporal creado por el hijo

	       	remove(auxiliar2);

	       	// Se obtiene el valor de "contador" y se almacena en el archivo "archleidos"

	       	wait(&status);

	       	archleidos[i]=status>>8;

	       	free (cat);
 				
		}

	free(aux_dir);

	}

	// Se cierran los file descriptors activos
	
	fclose(fp);
    
    fclose(fp2);

}