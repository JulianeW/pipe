/*
 * -------------------------------------------------------------- includes --
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <assert.h>

/*
 * ------------------------------------------------------------- prototypes--
 */
 
extern FILE *mypopen (const char *p_cCommand, const char *p_cType);

int pclose(FILE *stream);

