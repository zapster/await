/* src/await.c: main file

    Copyright 2012 Josef Eisl <zapster@zapster.cc>

    This file is part of await.

    await is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    await is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with await.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "await.h"
#include <mqueue.h>

static struct mq_attr get_mq_attr() {
  struct mq_attr attr;
  attr.mq_msgsize = sizeof(pid_t);
  attr.mq_maxmsg = 10;
  return attr;
}

static const char *get_mq_name(int argc, const char *argv[]) {
  const char *mqname = "/await-pid-queue";
  return mqname;
}


static mqd_t open_queue(int argc, const char *argv[], const int oflag) {
  mqd_t mqdes;
  const char *mqname = get_mq_name(argc, argv);
  struct mq_attr attr = get_mq_attr();

  mqdes = mq_open(mqname, oflag, S_IRUSR | S_IWUSR, &attr);
  if (mqdes == (mqd_t) -1) {
    perror("mq_open");
  }
  return mqdes;
}

void push_pid(int argc, const char *argv[], pid_t *pid) {
  mqd_t mqdes = open_queue(argc, argv, O_CREAT | O_WRONLY);

  if (mq_send(mqdes, (const char *) pid, sizeof(pid_t), PUSH_PRIORITY) != 0) {
    perror("mq_send");
  }
}

void pop_pid(int argc, const char *argv[]) {
  mqd_t mqdes = open_queue(argc, argv, O_CREAT | O_WRONLY);

  pid_t pid = 0;
  if (mq_send(mqdes, (const char *) &pid, sizeof(pid_t), POP_PRIORITY) != 0) {
    perror("mq_send");
  }
}

pid_t receive_msg(int argc, const char *argv[], unsigned int *rvprio) {
  mqd_t mqdes = open_queue(argc, argv, O_CREAT | O_RDONLY);
  // read PID
  pid_t pid;
  if (mq_receive(mqdes, (char *) &pid, sizeof(pid_t), rvprio) == -1) {
    perror("mq_receive");
  }
  return pid;
}

#if 0
const char* arg0 = NULL;
pid_t pid = 0;

void sigint_handler (int signum)
{
  if (pid != 0)
  {
    /* parent */
    if(kill(pid, signum) == -1)
    {
      fprintf(stderr,"%s: %s\n", arg0, strerror(errno));
      abort();
    }
  }
  signal(signum, sigint_handler);
}

inline static void usage()
{
  fprintf(stderr, "usage: %s <semname> cmd arg0 arg1 ....\n", arg0);
}

inline static void child(int argc, char * argv[])
{
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

  DBG("sem_wait()\n");
  if (sem_wait(sem) == -1)
  {
    fprintf(stderr,"%s: %s\n", arg0, strerror(errno));
    return -1;
  }
  DBG("entering mutex section\n");

  switch (pid = fork())
  {
    case -1:
      fprintf(stdout,"Can't fork child process!");
      return -1;
    case 0: /* Child */
      child(argc, argv);
      return -1; /* signal error to calling function */
    default: /* Parent */
      if (signal (SIGINT, sigint_handler) == SIG_ERR)
      {
        fprintf(stderr,"%s: %s\n", arg0, strerror(errno));
        return -1;
      }

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
  }
  DBG("sem_post()\n");
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
  DBG("unlinking file: %s\n",semname);
  if ((sem_unlink(semname) == -1) && (errno != ENOENT)) /* ignore if the semaphore does no longer exists */
  {
    fprintf(stderr,"%s: sem_unlink(%s): %s\n", arg0, semname, strerror(errno));
    return -1;
  }

  return WEXITSTATUS(status);
}
#endif