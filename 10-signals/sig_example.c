#include <stdio.h>
#include <signal.h>

/*
 Use ./a.out & to start the program in the background
 kill -USR1 <pid> to trigger signal
*/

static void sig_cb(int signo) {
    if(signo == SIGUSR1) {
        fprintf(stdout, "signal user 1 triggered\n");
    } else if (signo == SIGUSR2) {
        fprintf(stdout, "signal user 2 triggered\n");
    } else {
        fprintf(stderr, "signal %d triggered\n", signo);
    }
}

int main (int argc, char* argv[]) {
    if(signal(SIGUSR1, sig_cb) == SIG_ERR) {
        fprintf(stderr, "signal error\n");
    }
    if(signal(SIGUSR2, sig_cb) == SIG_ERR) {
        fprintf(stderr, "signal error\n");
    }
    while(1);
    return 0;
}