#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>

#define SEM_NAME "mysem"
#define SEM_MODE S_IRWXU /* read, write, execute/search by owner */
#define SEM_VALUE 1

int main(int argc, char * argv[])
{
  sem_t *sem;

  sem = sem_open(SEM_NAME, O_CREAT, SEM_MODE, SEM_VALUE);
  /* TODO: check for SEM_FAILED & errno */
  sem_close(sem);
  /* TODO: return value & errno */
  sem_unlink(SEM_NAME);
  /* TODO: return value & errno */

  printf("Hello from %s!\n", argv[0]);
  return 0;
}
