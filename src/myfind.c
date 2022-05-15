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
    if (path[i] == NULL) 
        path[i] = ".";
}

opt *Parsing_args(int len, char **spath, char **parms)
{
    int y = 0;
    int opts = 0;
    int memUsed = 0;

    opt *op = malloc(sizeof(*op));
    opt *res = op;

    int i = 1;
    while (i < len) //for (int i = 1; i < len; i++)
    {
        if (opts == 1)
            op = op->next;

        if (strcmp(parms[i], "-name") == 0)
        {
            if (parms[i++])
            {
                op->name = parms[i];
                opts = 1; 
                memUsed = 1;
                i++;
                continue;
            }
            else
            {
                fprintf(stderr, "myfind: %s: requires additional arguments\n", parms[i - 1]);
                exit(EXIT_FAILURE);
            }
        } 
        else if (strcmp(parms[i], "-print") == 0)
        {
            op->print = 1;
            opts = 1; 
            memUsed = 1;
            i++;
            continue;
        }
        else if (strcmp(parms[i], "-type") == 0)
        {
            if (parms[i++])
            {
                if (strlen(parms[i]) > 1)
                {
                    fprintf(stderr, "myfind: %s: this option take one letter\n", parms[i - 1]);
                    exit(EXIT_FAILURE);
                }
                char type_of = *parms[i];
                if (type_of == 'b' || type_of == 'c' || type_of == 'd' || type_of == 'f' || type_of == 'l' || type_of == 'p' || type_of == 's')
                {
                    op->types = type_of;
                    opts = 1; 
                    memUsed = 1;
                    i++;
                    continue;
                }
                else
                {
                    fprintf(stderr, "myfind: %s: %c: unknown letter\n", parms[i - 1], type_of);
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                fprintf(stderr, "myfind: %s: requires additional arguments\n", parms[i - 1]);
                exit(EXIT_FAILURE);
            }
        }
        else if (strcmp(parms[i], "-newer") == 0)
        {
            if (parms[i++])
            {
                op->newer = parms[i];
                opts = 1;
                memUsed = 1;
                i++;
                continue;
            }
            else
            {
                fprintf(stderr, "myfind: %s: requires additional arguments\n", parms[i - 1]);
                exit(EXIT_FAILURE);
            }
        }

<<<<<<< HEAD
=======
        if (opts == 1)
        {
            op->next = malloc(sizeof(*op));
            if (op->next == NULL)
            {
                fprintf(stderr, "myfind: %s\n", strerror(errno));
                exit(EXIT_FAILURE);
            }
            op = op->next;
            op->next = NULL;
        }

>>>>>>> 08a9ced7046040176db96126f4d04a8e31cd9e10
        if (memUsed == 1) 
        {
            if (strcmp(parms[i - 1], "-print") == 0)
                fprintf(stderr,"myfind: %s: doesn't take parameters\n", parms[i]);
            fprintf(stderr,"myfind: Usage: ./myfind [starting-point ...] [expressions] ...\n");
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
            fprintf(stderr, "myfind: %s: Unknown option\nUsage: ./myfind [starting-point ...] [expressions] ...", parms[i]);
            exit(EXIT_FAILURE);
        }
        i++;
    }
    spath[y] = NULL;
    return res;
}
