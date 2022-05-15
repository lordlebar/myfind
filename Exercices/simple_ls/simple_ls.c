#include <dirent.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        fprintf(stderr, "simple_is: take zero or one path");
        return 1;
    }

    char *path;

    if (argv[1] != NULL)
        path = argv[1];
    else
        path = ".";

    DIR *dir = opendir(path);

    if (dir != NULL)
    {
        struct dirent *sdir;

        while ((sdir = readdir(dir)) != NULL)
        {
            if (!((strcmp(sdir->d_name, ".")) == 0
                || (strcmp(sdir->d_name, "..")) == 0))
            {
                printf("%s\n", sdir->d_name);
            }
        }
        closedir(dir);
    }
    else
    {
        fprintf(stderr, "simple_ls: %s: No such file or directory\n", path);
        return 1;
    }
    return 0;
}
