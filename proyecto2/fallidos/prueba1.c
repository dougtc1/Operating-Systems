#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

void main(int argc, char *argv[]) {
    DIR *dirp;
    struct dirent *direntp;
 
    if (argc !=2) {
        fprintf(stderr,"Usage: %s directory_name\n", argv[0]);
        exit(1);
    }
    if ((dirp = opendir(argv[1]))==NULL) { 
        fprintf(stderr,"No se puede abrir el directorio %s: %s\n", argv[1],
        strerror(errno));
        exit(1);
    }
    while ((direntp=readdir(dirp))!= NULL) {
        
        printf("%d \n", direntp->d_type);

    }

    closedir(dirp);
    exit(0);

}