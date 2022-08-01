#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <mqueue.h>
#include "await.h"

void term(int signum) {
  // do nothing
}

int main(int argc, const char *argv[]) {
  // install sig handler
  struct sigaction action;
  memset(&action, 0, sizeof(action));
  action.sa_handler = term;
  sigaction(SIGTERM, &action, NULL);

  // publish PID
  pid_t pid = getpid();
  push_pid(argc, argv, &pid);

  // wait for signal
  DBG("waiting for SIGTERM (pid = %" PRIdMAX ")\n", (intmax_t) pid);
  pause();
  DBG("Received SIGTERM\n");
  return 0;
}
