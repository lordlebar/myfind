#include "include/is_dir.h"
#include "include/is_file.h"
#include "include/myfind.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void is_dir(char *dir_path, opt *parms, struct stat hdr)
{
    struct dirent *sdir;

    DIR * dir = opendir(dir_path);
    if (dir == NULL)
    {
        fprintf(stderr, "myfind: %s %s\n", dir_path,strerror(errno));
        return;
    }

    while ((sdir = readdir(dir)) != NULL)
    {
        if (!((strcmp(sdir->d_name, ".")) == 0 || (strcmp(sdir->d_name, "..")) == 0))
        {
            size_t len_path = strlen(dir_path) + strlen(sdir->d_name);
            char concat_Path[len_path];

            if (dir_path[strlen(dir_path) - 1] == '/')
                sprintf(concat_Path, "%s%s", dir_path, sdir->d_name);
            else
                sprintf(concat_Path, "%s/%s", dir_path, sdir->d_name);

            int status = stat(concat_Path, &hdr);
            if (status == -1)
            {
                fprintf(stderr, "myfind: %s: %s\n", concat_Path, strerror(errno));
                exit(EXIT_FAILURE);
            }

            if (S_ISDIR(hdr.st_mode))
            {
                is_file(concat_Path, parms, &hdr);
                is_dir(concat_Path, parms, hdr);
            }
            else
                is_file(concat_Path, parms, &hdr);
        }
        else
            continue;
    }
    closedir(dir);
}
