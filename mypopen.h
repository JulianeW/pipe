/*
 * -------------------------------------------------------------- includes --
 */
#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/*
 * ------------------------------------------------------------- prototypes--
 */
FILE *popen(const char *command, const char *type);

int pclose(FILE *stream);

