#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

static void print_sig_mask(void) {
    sigset_t sigmask;
    if(sigprocmask(0, NULL, &sigmask) < 0) {
        fprintf(stderr, "[Print Sig Mask] Error getting signal mask\n");
        return;
    } else {
        fprintf(stdout, "[SIGMASK]: ");
        if(sigismember(&sigmask, SIGALRM)) fprintf(stdout, " SIGALRM");
        if(sigismember(&sigmask, SIGQUIT)) fprintf(stdout, " SIGQUIT");
        if(sigismember(&sigmask, SIGUSR1)) fprintf(stdout, " SIGUSR1");
        if(sigismember(&sigmask, SIGINT)) fprintf(stdout, " SIGINT");
        fprintf(stdout, "\n");
    }
}

static void sig_int_handler(int signo) {
    fprintf(stdout, "[SIGINT Handler]");
    print_sig_mask();
}

int main(int argc, char* argv[]) {
    fprintf(stdout, "[MAIN] Starting\n");
    print_sig_mask();

    sigset_t waitset, nset, oset;
    
    signal(SIGINT, sig_int_handler);
    
    sigemptyset(&waitset);
    sigaddset(&waitset, SIGUSR1);
    sigemptyset(&nset);
    sigaddset(&nset, SIGINT);

    if(sigprocmask(SIG_BLOCK, &nset, &oset) < 0) {
        fprintf(stderr, "[MAIN] Error sigprocmask\n");
        exit(-1);
    }

    fprintf(stdout, "[MAIN] Critic section\n");
    print_sig_mask();

    sigsuspend(&waitset);
    print_sig_mask();

    if(sigprocmask(SIG_SETMASK, &oset, NULL) < 0) {
        fprintf(stderr, "[MAIN] Error sigprocmask\n");
        exit(-1);
    }

    fprintf(stdout, "[MAIN] finishing\n");
    print_sig_mask();

    return 0;
}

