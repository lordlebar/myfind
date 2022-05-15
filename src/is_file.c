#include "include/is_file.h"

#include <dirent.h>
#include <errno.h>
#include <fnmatch.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "include/myfind.h"

void is_file(char *path, opt *parms, struct stat *hdr)
{
    int print = 1;

    while (parms != NULL)
    {
        if (parms->name)
        {
            if (name(path, parms) == 0)
                return;
        }
        if (parms->print)
        {
            printf("%s\n", path);
            print = 0;
        }
        if (parms->types)
        {
            if (types(parms, hdr) == 0)
                return;
        }
        if (parms->newer)
        {
            if (newer(path, parms, hdr) == 0)
                return;
            
        }
        parms = parms->next;
    }

    if (print)
        printf("%s\n", path);
}

int newer(char *path, opt *parms, struct stat *hdr)
{
    struct stat hdr2;

    int status = stat(parms->newer, &hdr2);
            
    if (status == -1)
    {
        fprintf(stderr, "myfind: %s: %s\n", parms->newer, strerror(errno));
        exit(EXIT_FAILURE);
    }
    else
    {
        if (hdr->st_mtime > hdr2.st_mtime)
        {
            printf("%s\n", path);
            return 0;
        }
    }
    return 0;
}

int name(char *path, opt *parms)
{
    char *f = basename(path);
    int res = fnmatch(parms->name, f, 0);
    if (res != 0)
        return 0;
    return 1;
}

int types(opt *parms, struct stat *hdr)
{
    char letter;

    if (S_ISBLK(hdr->st_mode))
        letter = 'b';
    else if (S_ISCHR(hdr->st_mode))
        letter = 'c';
    else if (S_ISDIR(hdr->st_mode))
        letter = 'd';
    else if (S_ISREG(hdr->st_mode)) 
        letter = 'f';
    else if (S_ISLNK(hdr->st_mode))
        letter = 'l';
    else if (S_ISFIFO(hdr->st_mode))
        letter = 'p';
    else if (S_ISSOCK(hdr->st_mode))
        letter = 's';
    else
        letter = '?';

    if (letter != parms->types)
        return 0;
    return 1;
}
