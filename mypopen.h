/*
 * -------------------------------------------------------------- includes --
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h> /* wird für wait(4) gebraucht */
#include <errno.h>
#include <sys/wait.h> /* wird für wait(4) gebraucht */
#include <assert.h>
#include <sys/time.h> /* wird für wait(4) gebraucht */
#include <sys/resource.h> /* wird für wait(4) gebraucht */

/*
 * ------------------------------------------------------------- prototypes--
 */
 
extern FILE *mypopen (const char *p_cCommand, const char *p_cType);

int pclose(FILE *stream);

