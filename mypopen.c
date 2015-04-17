
#include "mypopen.h"

/* TODO: mypclose: int mypclose(FILE *stream) */
/* JPW: TODO: Überprüfen, ob popen nur einmal aufgerufen wurde */
/* JPW: TODO: wieso andere Paramenter als im Original pope bzw der Vorlage von Petrovitsch? 
FILE *mypopen(const char *command, const char *type) */

/* Initialised with -1, because it is changed if fork() is successfull */
static pid_t pid = -1;
FILE * global_pipe = NULL;

extern FILE *mypopen (const char * command, const char * type)
{
	int pipe_filedesc[2]; /* Pipe-Filedeskriptoren um festzustellen ob w oder r */
	
	/* CB: Is this to check if enough arguments have been passed? */
	assert(argc == 2);
	/* TODO: Müssen noch einbauen wenn popen zweimal ohne pclose aufgerufen wird */
	
	if (strlen(command) < 1 || (strcmp(type, "r") != 0 && strcmp(type, "w") != 0))
		{
		/* If the type argument is invalid and this is detected, the errno variable is set to EINVAL */
		errno = EINVAL;
		return NULL;
		}

	/* check if pipe() works, otherwise return NULL */
	if (pipe(pipe_filedesc) == -1)
		return NULL;

	if (strcmp(type, "r") == 0)  /* it is read mode */
	{
		switch(pid=fork())
		{ 
			case -1: /* fork did not work if -1 is returned - close filedescriptors, as they are not needed anymore */
				close(pipe_filedesc);
				return NULL;
				break;
			case 0: /* Child mode */

				if (close(pipe_filedesc[0]) == -1)
				{
					return NULL;
				}
				if (dup2(pipe_filedesc[1], 1) == -1)
				{
					return NULL;
				}
				if (close(pipe_filedesc[1]) == -1 || close(pipe_filedesc[0]) == -1) {
					return NULL;
				}
				/* richtige Fehlerbehandlung von EXECL ??? */
				if ((execl("/bin/sh", "sh", "-c", command, NULL) == -1)
				{
					return NULL;
				}
				break;
			default: /* Parent mode */
				close(pipe_filedesc[1]);
				global_pipe = fdopen(pipe_filedesc[0], type);
				break;
		}
	}
	else if (strcmp(p_cType, "w") == 0) /* it is write mode */
	{
		switch(pid=fork())
		{ 
			case -1: /* Error */
				close(pipe_fildesc);
				return NULL;
				break;
			case 0: /* Child mode */
				if (close(pipe_filedesc[1]) == -1)
				{
					return NULL;
				}
				if (dup2(pipe_filedesc[0], 0) == -1)
				{
					return NULL;
				}
				if (close(pipe_filedesc[1]) == -1 || close(pipe_filedesc[0]) == -1)
				{
					return NULL;
				}
				if ((execl("/bin/sh", "sh", "-c", command, NULL) == -1)
				{
					return NULL;
				}
				break;
			default: /* Parent mode */
				close(pipe_filedesc[0]);
				global_pipe = fdopen(pipe_filedesc[1], type);
				break;
		}
	}

	return global_pipe;
} 

/* The pclose() function waits for the associated process to terminate
       and returns the exit status of the command as returned by wait4(2). 
       wait4() can be used to select a specific child, or children, on which to wait.
       If rusage is not NULL, the struct rusage to which it points will be
       filled with accounting information about the child. */ 

int mypclose(FILE * stream)
{
	pid_t waitpid_temp;
	int status = 0;
	
	/* check if the passed pointer is empty */
	if (stream == NULL)
	{
		errno = EINVAL;
		return -1;
	}

	if (global_pipe == NULL)
	{
		errno = ECHILD;
		return -1;
	}

	if (stream != global_pipe)
	{
		errno = EINVAL;
		return -1;
	}



	/* if fork() failed */
	if (pid == -1)
	{
        errno = ECHILD;
        return -1; /* If pclose() cannot obtain the child status, errno is set to ECHILD. */
    }

	if (fclose(stream) != 0)
	{
		pid = -1;
		global_pipe = NULL;
		return -1;
	}


	while ((waitpid_temp = waitpid(pid, &status, 0)) != pid)
	{
		if (waitpid_temp == -1)
		{
			if (errno == EINTR)
			{
				continue;
			}

			return -1;
		}
	}

	pid = -1;

	if (WIFEXITED(status))
		return WEXITSTATUS(status);

	errno = ECHILD;
	return -1;

}



