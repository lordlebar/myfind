#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void is_dir(char *dir_path);

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        fprintf(stderr, "simple_is: take zero or one path");
        return 1;
    }

    struct stat hdr;
    char *path;

    if (argv[1] != NULL)
        path = argv[1];
    else
        path = ".";

    int status = stat(path, &hdr);
    if (status == -1)
    {
        fprintf(stderr, "simple_ls: %s: No such file or directory", argv[1]);
        return 1;
    }
    if (S_ISDIR(hdr.st_mode))
        is_dir(path);
    else
        printf("%s\n", path);
    return 0;
}

void is_dir(char *dir_path)
{
    DIR *dir = opendir(dir_path);

    if (dir != NULL)
    {
        struct dirent *sdir;

        while ((sdir = readdir(dir)) != NULL)
        {
            if (!(((strcmp(sdir->d_name, ".")) == 0 || (strcmp(sdir->d_name, "..")) == 0)))
                printf("%s\n", sdir->d_name);
        }
        closedir(dir);
    }
}
