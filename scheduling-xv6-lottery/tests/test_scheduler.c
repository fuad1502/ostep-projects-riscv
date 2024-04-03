#include "kernel/pstat.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define N_CHILD 3

void print_pstat(struct pstat *p);
int child_pids[N_CHILD];
int in_child_pids(int pid);

int main(int argc, char *argv[]) {
  for (int i = 0; i < N_CHILD; i++) {
    int pid = fork();
    if (pid == 0) {
      settickets((i + 1) * 10);
      sleep(10);
      int x = 0;
      while(1) x += 1;
    }
    child_pids[i] = pid;
  }

  int pid = fork();
  if (pid == 0) {
    settickets(100);
    while(1) {
      struct pstat p;
      getpinfo(&p);
      print_pstat(&p);
      sleep(10);
    }
  }

  sleep(500);

  for (int i = 0; i < N_CHILD; i++) {
    kill(child_pids[i]);
  }
  kill(pid);

  return 0;
}

void print_pstat(struct pstat *p) {
  for (int i = 0; i < NPROC; i++) {
    if (p->inuse[i] && in_child_pids(p->pid[i])) {
      printf("XV6_TEST_OUTPUT (%d), %d, %d\n", p->pid[i], p->tickets[i], p->ticks[i]);
    }
  }
}

int in_child_pids(int pid) {
  for (int i = 0; i < N_CHILD; i++) {
    if (pid == child_pids[i]) {
       return 1;
    }
  }
  return 0;
}
