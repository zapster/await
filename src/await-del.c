#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <semaphore.h>

const char* arg0 = NULL;

inline static void usage()
{
  fprintf(stderr, "usage: %s <semname>\n", arg0);
}

int main(int argc, char * argv[])
{
  char* semname;
  size_t len;
  
  arg0 = argv[0];

  if (argc != 2) 
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

  if (sem_unlink(semname) == -1)
  {
    fprintf(stderr,"%s: %s\n", arg0, strerror(errno));
    return -1;
  }

  return 0; 
}

