#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

static volatile sig_atomic_t g_flag = 0;

static void sig_alarm_handler(int signo) {
    fprintf(stdout, "[SIGALRM]: Caught signal\n");
}

static void sig_quit_handler(int signo) {
    fprintf(stdout, "[SIGQUIT]: Caught signal\n");
}

static void sig_int_handler(int signo) {
    fprintf(stdout, "[SIGINT]: Caught signal\n");
    g_flag = 1;
    fprintf(stdout, "[SIGINT]: global flag set\n");
}

int main(int argc, char* argv[]) {
    fprintf(stdout, "[MAIN]: starting\n");
    signal(SIGALRM, sig_alarm_handler);
    signal(SIGINT, sig_int_handler);
    signal(SIGQUIT, sig_quit_handler);

    sigset_t zset, nset, oset;

    sigemptyset(&zset);
    sigemptyset(&nset);
    sigaddset(&nset, SIGQUIT);
    sigemptyset(&oset);

    if(sigprocmask(SIG_BLOCK, &nset, &oset) < 0) {
        fprintf(stderr, "[MAIN]: sigprocmask error\n");
        exit(-1);
    }

    while(!g_flag) {
        fprintf(stdout, "[MAIN]: suspending and waiting for INT signal\n");
        alarm(5);
        sigsuspend(&zset);
    }

    if(sigprocmask(SIG_SETMASK, &oset, NULL) < 0) {
        fprintf(stderr, "[MAIN]: sigprocmask error\n");
        exit(-1);
    }

    fprintf(stdout, "[MAIN]: finishing\n");
 
    return 0;
}