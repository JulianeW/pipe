/**
 * @file mypopen.h
 * Betriebssysteme Headerfile für mypopen
 *
 * @author Claudia Baierl ic14b003 <claudia.baierl@technikum-wien.at>
 * @author Rene Elsner ic14b016 <rene.elsner@technikum-wien.at>
 * @author Juliane Piñeiro-Winkler ic14b059 <juliane.winkler@technikum-wien-at>
 * @date 2015/04/23
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
#include <sys/types.h> 
#include <errno.h>
#include <sys/wait.h> 
#include <fcntl.h>
#include <sys/time.h> 
#include <sys/resource.h> 

/*
 * ------------------------------------------------------------- prototypes--
 */
 
extern FILE *mypopen (const char * command, const char * type);
extern int pclose(FILE * stream);

#endif

