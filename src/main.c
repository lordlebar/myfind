#include "include/myfind.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    char *list_path[argc];

    opt *args = Parsing_args(argc, list_path, argv);

    myfind(list_path, args);

    opt *first = args;
    while (first)
    {
        opt *temp = first->next;
        free(first);
        first = temp;
    }

    return 0;
}

opt *Parsing_args(int len, char **spath, char **parms)
{
    int y = 0;
    int opts = 0;
    int memUsed = 0;

    opt *op = malloc(sizeof(*op));
    opt *first = op;

    for (int i = 1; i < len; i++)
    {
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

        if (opts == 1)
        {
            op->next = calloc(1, sizeof(*op));
            if (op->next == NULL)
            {
                fprintf(stderr, "myfind: %s\n", strerror(errno));
                exit(EXIT_FAILURE);
            }
            op = op->next;
            op->next = NULL;
        }

        if (memUsed != 0) 
        {
            if (parms[i][0] == '-')
            {
                fprintf(stderr, "myfind: %s: Unknown option\n", parms[i]);
                exit(EXIT_FAILURE);
            }
            fprintf(stderr, "%s\n", "myfind: Usage: ./myfind [starting-point...] [expressions] ...");
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

    return first;
}