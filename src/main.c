#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>

#define SEM_MODE S_IRWXU /* read, write, execute/search by owner */
#define SEM_VALUE 1

const char* arg0 = NULL;

inline static void usage()
{
  fprintf(stderr, "usage: %s <semname> cmd arg0 arg1 ....\n", arg0);
}

inline static void child(int argc, char * argv[])
{
  /* TODO check argv*/
  char* e_arg0;
  char** e_argv;
  int i;
  
  e_arg0 = argv[2];
  e_argv = (char**) calloc(argc - 2 + 1, sizeof(char*));
  /* TODO: check for error */
  e_argv[argc-2] = NULL;

  for (i = 0; i < argc -2; i++)
  {
    e_argv[i] = argv[i+2];
  }

  if (execvp(e_arg0, e_argv) == -1)
  {
    free(e_argv);
    fprintf(stderr,"%s: %s\n", e_arg0, strerror(errno));
  }
}

int main(int argc, char * argv[])
{
  sem_t *sem;
  pid_t pid;
  pid_t wpid;
  int status;
  char* semname;
  size_t len;
  
  arg0 = argv[0];

  if (argc < 3) 
  {
    usage();
    return -1;
  }

  len = sizeof(char) + strlen(argv[1]) + sizeof(char);
  semname = (char*) malloc(len);
  /* TODO: check for error */
  semname[0] = '/';
  strcat(semname,argv[1]);
  /* TODO: check for error */

  sem = sem_open(semname, O_CREAT, SEM_MODE, SEM_VALUE);
  if (sem == SEM_FAILED)
  {
    fprintf(stderr,"%s: %s\n", arg0, strerror(errno));
    return -1;
  }
  /* TODO: check for SEM_FAILED & errno */
  //sem_close(sem);
  /* TODO: return value & errno */
  //sem_unlink(SEM_NAME);
  /* TODO: return value & errno */

  switch (pid = fork())
  {
    case -1:
      fprintf(stdout,"Can't fork child process!");
      return -1;
    case 0: /* Child */
      if (sem_wait(sem) == -1)
      {
        fprintf(stderr,"%s: %s\n", arg0, strerror(errno));
        return -1;
      }
      child(argc, argv);
      return -1; /* signal error to calling function */
    default: /* Parent */
      while ((wpid = wait (&status)) != pid)
      {
        if (wpid != -1) /* other child terminated? */
        {
          continue;
        }
        if (errno == EINTR) /* interrupted by signal? */
        {
          continue;
        }
        return -1;
      }
      if (sem_post(sem) == -1)
      {
        fprintf(stderr,"%s: %s\n", arg0, strerror(errno));
        return -1;
      }
      if (sem_close(sem) == -1)
      {
        fprintf(stderr,"%s: %s\n", arg0, strerror(errno));
        return -1;
      }
  }

  return WEXITSTATUS(status);
}
