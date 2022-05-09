#include "include/myfind.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

void myfind(char *s){
    char *Path = malloc(sizeof(char));
    struct dirent *dir;

    DIR *d = opendir(s);
    if (d != NULL)
    {
           printf("%s\n", s);
        while ((dir = readdir(d))!=NULL)
        {
            if (dir->d_type == DT_DIR)
            {
                if (strcmp(dir->d_name, ".")!=0 && strcmp(dir->d_name, "..")!=0)
                { 
                    strcpy(Path, s);
                    strcat(Path,"/");
                    strcat(Path, dir->d_name);
                    myfind(Path);
                }
            }
            else
                printf("%s/%s\n", s,dir->d_name);
    }
    closedir(d);
    }
    else
        perror("myfind");
}

