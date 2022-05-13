#include "include/myfind.h"
#include "include/is_file.h"
#include "include/is_dir.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

void myfind(char **path, opt *args)
{
    struct stat hdr;
    int i = 0;

    if (path[i] == NULL) 
        path[i] = ".";

    while (path[i] != NULL)
    {
        int status = stat(path[i], &hdr);
        if (status == -1)
            fprintf(stderr, "myfind: %s: %s\n", path[i], strerror(errno));
        else 
        {
            is_file(path[i], args, &hdr);

            if (S_ISDIR(hdr.st_mode))
                is_dir(path[i], args, hdr);
        }
        i++;
    }
}
