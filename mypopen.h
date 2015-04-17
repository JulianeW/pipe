/**
 * @file mypopen.h
 * Betriebssysteme MyPopen File
 * Beispiel 2
 *
 * @author Claudia Baierl ic14b003 <claudia.baierl@technikum-wien.at>
 * @author Rene Elsner ic14b016 <rene.elsner@technikum-wien.at>
 * @author Juliane Winkler ic14b059 <juliane.winkler@technikum-wien-at>
 * @date 2015/04/17
 *
 * @version 1
 *
 */

#ifndef MYPOPEN_H

#define MYPOPEN_H

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
 
extern FILE *mypopen (const char * command, const char * type);
extern int pclose(FILE * stream);

#endif

