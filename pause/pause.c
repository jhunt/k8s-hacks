#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

static void then_exit(int sig) {
  psignal(sig, "\npause: shutting down; received signal");
  exit(0);
}

static void then_wait(int _) {
  for (; waitpid(-1, NULL, WNOHANG) > 0; );
}

int main() {
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));

  sa.sa_handler = then_exit;
  if (sigaction(SIGINT,  &sa, NULL) < 0) return 1;
  if (sigaction(SIGTERM, &sa, NULL) < 0) return 2;

  sa.sa_handler = then_wait;
  sa.sa_flags = SA_NOCLDSTOP;
  if (sigaction(SIGCHLD, &sa, NULL) < 0) return 3;

  for (;;) pause();

  fprintf(stderr, "pause: uh-oh; exited internal pause-loop.\n");
  return 4;
}
