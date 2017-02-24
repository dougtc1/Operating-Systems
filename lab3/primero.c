#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
void main() {
      pid_t childpid;	
      childpid = fork();
      if (childpid==0)
        printf("Soy el hijo con ID= %ld\n",(long)getpid());
	
      else
        printf("Soy el Padre con ID= %ld, mi hijo es %ld\n",(long)getpid(),childpid);

}

