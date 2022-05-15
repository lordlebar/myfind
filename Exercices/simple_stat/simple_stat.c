#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    struct stat hdr;

    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            int status = stat(argv[i], &hdr);

            if (status == -1)
                return 1;

            printf("st_dev=%d\n", hdr.st_dev);
            printf("st_ino=%llu\n", hdr.st_ino);
            printf("st_mode=0%o\n", hdr.st_mode);
            printf("st_nlink=%d\n", hdr.st_nlink);
            printf("st_uid=%d\n", hdr.st_uid);
            printf("st_gid=%d\n", hdr.st_gid);
            printf("st_rdev=%d\n", hdr.st_rdev);
            printf("st_size=%lld\n", hdr.st_size);
            printf("st_atime=%ld\n", hdr.st_atime);
            printf("st_mtime=%ld\n", hdr.st_mtime);
            printf("st_ctime=%ld\n", hdr.st_ctime);
            printf("st_blksize=%d\n", hdr.st_blksize);
            printf("st_blocks=%lld\n", hdr.st_blocks);
        }
        return 0;
    }
    return 1;
}