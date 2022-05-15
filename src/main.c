#include <stdlib.h>

#include "include/myfind.h"

int main(int argc, char *argv[])
{
    char *list_path[argc];

    opt *args = Parsing_args(argc, list_path, argv);

    myfind(list_path, args);

    opt *first = args;
    while (first) // clean
    {
        opt *temp = first->next;
        free(first);
        first = temp;
    }
    return 0;
}


