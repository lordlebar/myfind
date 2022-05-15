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


