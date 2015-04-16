#include "mypopcl.h"

/* TODO: schlafen */
/* TODO: alkohol */
/* TODO: mypclose */

static pid_t pid;

FILE *mypopen (const char *p_cCommand, const char *p_cType) 
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

int myplose(FILE *stream)
{
	/* The pclose() function waits for the associated process to terminate
       and returns the exit status of the command as returned by wait4(2). 
       wait4() can be used to select a specific child, or children, on which to wait.
       If rusage is not NULL, the struct rusage to which it points will be
       filled with accounting information about the child. */ 
	pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);
	return pclose(stream);
}

