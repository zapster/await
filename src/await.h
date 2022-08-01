#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>

#define SEM_MODE S_IRWXU     /* read, write, execute/search by owner */
#define SEM_VALUE 1

#ifdef NDEBUG
#define DBG(...)
#else
#define DBG(...) \
    fprintf (stderr, "%s:%d: ", __FILE__, __LINE__); \
    fprintf (stderr, __VA_ARGS__)
#endif

#define PUSH_PRIORITY 1
#define POP_PRIORITY  5

void push_pid(int argc, const char *argv[], pid_t *pid);

void pop_pid(int argc, const char *argv[]);

pid_t receive_msg(int argc, const char *argv[], unsigned int *rvprio);