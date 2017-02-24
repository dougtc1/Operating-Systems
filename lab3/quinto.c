#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
// Se crea una linea de procesos.
void main() {
	int status, i,nprocesos;
	pid_t hijo1,hijo2;
	nprocesos = 4;
	for (i = 0; i < nprocesos; ++i) {
		hijo1=fork();
		if (hijo1 > 0) {
			hijo2=fork();
			if (hijo2>0){
				break;
			} 
		}

		if (hijo1>0 && hijo2>0){
			break;
		}

	} //fork
} // main
