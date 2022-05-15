#include <stdlib.h>

#include "include/myfind.h"

int main(int argc, char *argv[])
{
    char *list_path[argc];

    opt *args = Parsing_args(argc, list_path, argv);

    myfind(list_path, args);

    opt *first = args;
<<<<<<< HEAD
    while (first) // clean
=======
    while (first)
>>>>>>> 57c7e38d7260535f278d95362d73e6eac20da9cd
    {
        opt *temp = first->next;
        free(first);
        first = temp;
    }
    return 0;
}


