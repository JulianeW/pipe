/* JPW: Wieso wird das hier inkludiert? Was ist das? Unser Headerfile heißt mypopen.h */
#include "mypopcl.h"

/* TODO: mypclose: int mypclose(FILE *stream) */
/* JPW: TODO: Überprüfen, ob popen nur einmal aufgerufen wurde */
/* JPW: TODO: wieso andere Paramenter als im Original pope bzw der Vorlage von Petrovitsch? 
FILE *mypopen(const char *command, const char *type) */

/* JPW: TODO: Wieso wird das hier deklariert? */
static pid_t pid;

extern FILE *mypopen (const char *p_cCommand, const char *p_cType) 
{
	int Pipe_FileDesc[2];
	FILE *p_PipeEnd = NULL;
	
	assert(argc == 2);
	
	if (strlen(p_cCommand) < 1 || (strcmp(p_cType, "r") != 0 && strcmp(p_cType, "w") != 0)) return NULL;

	if (pipe(Pipe_FileDesc) == -1) return NULL;

	if (strcmp(p_cType, "r") == 0)  /* it is read mode */
	{
		switch(pid=fork())
		{ 
			case -1: /* Error */
							 return NULL;
							 break;
			case 0: /* Child mode */
							if (close(0) == -1 || close(1) == -1) {
								return NULL;
							}
							if (dup2(Pipe_FileDesc[1], 1) == -1) {
								return NULL;
							}
							if (close(Pipe_FileDesc[1]) == -1 || close(Pipe_FileDesc[0]) == -1) {
								return NULL;
							}
							execlp("/bin/sh", "sh", "-c", p_cCommand, NULL);
							break;
			default: /* Parent mode */
							close(Pipe_FileDesc[1]);
							p_PipeEnd = fdopen(Pipe_FileDesc[0], p_cType);
							break;
		}
	}
	else if (strcmp(p_cType, "w") == 0) /* it is write mode */
	{
		switch(pid=fork())
		{ 
			case -1: /* Error */
							 return NULL;
							 break;
			case 0: /* Child mode */
							if (close(0) == -1) {
								return NULL;
							}
							if (dup2(Pipe_FileDesc[0], 0) == -1) {
								return NULL;
							}
							if (close(Pipe_FileDesc[1]) == -1 || close(Pipe_FileDesc[0]) == -1) {
								return NULL;
							}
							execlp("/bin/sh", "sh", "-c", p_cCommand, NULL);
							break;
			default: /* Parent mode */
							 close(Pipe_FileDesc[0]);
							 p_PipeEnd = fdopen(Pipe_FileDesc[1], p_cType);
							 break;
		}
	}

	return p_PipeEnd;
} 

/* The pclose() function waits for the associated process to terminate
       and returns the exit status of the command as returned by wait4(2). 
       wait4() can be used to select a specific child, or children, on which to wait.
       If rusage is not NULL, the struct rusage to which it points will be
       filled with accounting information about the child. */ 

/* JPW: TODO: Woher kommt der Parameter stream? Müssen wir den umbenennen? */
extern int mypclose(FILE *stream)
{
	pid_t Variable1 = 0; /* Initialisierung der Variable für waitpid */
	/* The pid_t data type represents process IDs.
	You can get the process ID of a process by calling getpid.
	The function getppid returns the process ID of the parent of the current process
	(this is also known as the parent process ID). */
	/* ist die pid_t Variable in popen dieselbe, die man hier braucht? */
	
	if (stream == NULL)
	{
		errno = EINVAL; /*  Im Falle von mypopen() ist auch errno passend zu erhalten 
		(falls ein System-Call einen Fehler meldet) bzw. direkt zu setzen (z.B. falls 
		unerwartete/falsche Parameter übergeben werden ist EINVAL ein guter Wert dafür). */
		
		return -1; /* The pclose() function returns -1 if wait4(2) returns an error, 
		or some other error is detected.
		In the event of an error, these functions set errno to indicate the cause of the error.*/
	}
	
	if (pid == -1) /* JPW: TODO: Was ist das für eine Variable? */
	{
        errno = ECHILD;
        return (-1); /* If pclose() cannot obtain the child status, errno is set to ECHILD. */
        }

	pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);
	return pclose(stream);
}



