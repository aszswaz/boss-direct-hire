#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <string.h>
#include <errno.h>

#define SYSCALL_ERR(expression) \
    if (expression) { \
        printf("%s %d: %s\n", __FILE_NAME__, __LINE__, strerror(errno)); \
        goto exception; \
    }

#endif
