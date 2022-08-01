#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "await.h"

struct list {
    pid_t pid;
    struct list *next;
};

struct list *head = NULL;

void push(pid_t pid) {
  DBG("received pid = %" PRIdMAX "\n", (intmax_t) pid);
  struct list *n = malloc(sizeof(struct list));
  n->pid = pid;
  n->next = NULL;
  if (!head) {
    head = n;
  } else {
    struct list *tail = head;
    while (tail->next != NULL) {
      tail = tail->next;
    }
    tail->next = n;
  }
}

int pop(void) {
  if (!head) {
    DBG("No more PIDs to pop\n");
    return 0;
  }
  pid_t pid = head->pid;
  head = head->next;
  DBG("sending SIGTERM to %" PRIdMAX "\n", (intmax_t) pid);
  if (kill(pid, SIGTERM)) {
    perror("kill");
  }
  return 1;
}

int main(int argc, const char *argv[]) {
  unsigned rvprio;
  int running = 1;
  DBG("server waiting for messages\n");
  while (running) {
    pid_t pid = receive_msg(argc, argv, &rvprio);

    switch (rvprio) {
      case PUSH_PRIORITY:
        push(pid);
        break;
      case POP_PRIORITY:
        running = pop();
        break;
      default:
        printf("Unknown message priority %d\n", rvprio);
    }
  }
  return 0;
}
