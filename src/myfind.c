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
                is_dir(path[i], args, &hdr);
        }
        i++;
    }
}

opt *Parsing_args(int len, char **spath, char **parms)
{
    int y = 0;
    int opts = 0;
    int memUsed = 0;

    opt *op = malloc(sizeof(*op));
    opt *res = op;

    for (int i = 1; i < len; i++)
    {
        if (opts == 1)
            op = op->next;

        if (strcmp(parms[i], "-name") == 0)
        {
            if (parms[++i])
            {
                op->name = parms[i];
                opts = 1; 
                memUsed = 1;
                continue;
            }
            else
            {
                fprintf(stderr, "myfind: missing argument to %s\n", parms[i - 1]);
                exit(EXIT_FAILURE);
            }
        } 
        else if (strcmp(parms[i], "-print") == 0)
        {
            op->print = 1;
            opts = 1; 
            memUsed = 1;
            continue;
        }
        else if (strcmp(parms[i], "-type") == 0)
        {
            if (parms[++i])
            {
                if (strlen(parms[i]) > 1)
                {
                    fprintf(stderr, "myfind: Option -type take one letter\n");
                    exit(EXIT_FAILURE);
                }
                char type_of = *parms[i];
                if (type_of == 'b' || type_of == 'c' || type_of == 'd' || type_of == 'f' || type_of == 'l' || type_of == 'p' || type_of == 's')
                {
                    op->types = type_of;
                    opts = 1; 
                    memUsed = 1;
                    continue;
                }
                else
                {
                    fprintf(stderr, "myfind: %c: type not correct\n", type_of);
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                fprintf(stderr, "myfind: missing argument to %s\n", parms[i - 1]);
                exit(EXIT_FAILURE);
            }
        }
        else if (strcmp(parms[i], "-newer") == 0)
        {
            if (parms[++i])
            {
                op->newer = parms[i];
                opts = 1;
                memUsed = 1;
                continue;
            }
            else
            {
                fprintf(stderr, "myfind: missing argument to %s\n", parms[i - 1]);
                exit(EXIT_FAILURE);
            }
        }

        if (memUsed == 1) 
        {
            if (parms[i][0] == '-')
            {
                fprintf(stderr, "myfind: %s: Unknown option\n", parms[i]);
                exit(EXIT_FAILURE);
            }
            fprintf(stderr,"myfind: Usage: ./myfind [starting-point...] [expressions] ...\n");
            exit(EXIT_FAILURE);
        } 
        else
            opts = 0;

        if (!memUsed && parms[i][0] != '-')
        {
            spath[y] = parms[i];
            y++;
        }
        else
        {
            fprintf(stderr, "myfind: %s: Unknown option, file or directory\n", parms[i]);
            exit(EXIT_FAILURE);
        }
    }
    spath[y] = NULL;
    return res;
}
