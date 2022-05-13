#include "include/is_dir.h"
#include "include/is_file.h"
#include "include/myfind.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <libgen.h>
#include <fnmatch.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

void is_file(char *path, opt *parms, struct stat *hdr)
{
    int print = 1;

    while (parms != NULL)
    {
        if (parms->name)
        {
            char *f = basename(path);
            int res = fnmatch(parms->name, f, 0);
            if (res != 0)
                return;
        }
        if (parms->print)
        {
            printf("%s\n", path);
            print = 0;
        }
        if (parms->newer)
        {
            struct stat hdr2;

            int status = stat(parms->newer, &hdr2);
            
            if (status == -1)
            {
                fprintf(stderr, "myfind: %s: %s\n", path, strerror(errno));
                return;
            }
            else
            {
                if (hdr->st_mtimespec.tv_sec > hdr2.st_mtimespec.tv_sec)
                {
                    printf("%s\n", path);
                    return;
                }
            }
            return;
        }
        parms = parms->next;
    }

    if (print)
        printf("%s\n", path);
}
