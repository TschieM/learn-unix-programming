#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include <setjmp.h>
#include <time.h>

static sigjmp_buf sigjmp_env;
static volatile bool can_jump = 0;

static void sig_alarm_handler(int signo) {
    fprintf(stdout, "Caught by alarm signal\n");
}

static void sig_usr1_handler(int signo) {
    if(!can_jump) return;
    fprintf(stdout, "Caught by user signal\n");
    alarm(3);
    time_t start_ts = time(NULL);
    while(time(NULL) < start_ts+5);
    fprintf(stdout, "Finishing user1 signal handler\n");
    siglongjmp(sigjmp_env, 1);
}

int main(int argc, char* argv[]) {
    signal(SIGALRM, sig_alarm_handler);
    signal(SIGUSR1, sig_usr1_handler);

    if(sigsetjmp(sigjmp_env, 1) == 0) {
        can_jump = 1;
        while(1) pause();
    } 
    fprintf(stdout, "Finishing main\n");

    return 0;
}