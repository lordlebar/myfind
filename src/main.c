#include "include/myfind.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    struct stat *hdr = (struct stat *)malloc(sizeof(struct stat));
    int status = 0;
    
    char *path = "";
    if (argc >= 2){
        for (int i = 1; i < argc; i++)
        {
            status = stat(argv[i], hdr);
            path = argv[i];

            if (status == -1)
            {
                printf("myfind: ");
                printf("%s: No such file or directory\n", argv[i]);
            }
            else if ((hdr->st_mode & S_IFMT) == S_IFDIR)
            {
                myfind(path);
            }
            else if ((hdr->st_mode & S_IFMT) == S_IFREG)
                printf("%s\n", argv[i]);
            else
                printf("error: no directory or no regular file");
        }
    }
    else if (argc == 1)
    {
        status = stat(".", hdr);
        path = ".";

        myfind(path);
    }
    else
        printf("usage: ./myfind [path]");

    free(hdr);
    return 0;
}
