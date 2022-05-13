#ifndef IS_FILE_H
#define IS_FILE_H

#include "myfind.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void is_file(char *fp_path, opt *p, struct stat *hdr);

#endif /* ! IS_FILE_H */
