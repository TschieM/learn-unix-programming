#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

/*
Use ctrl+\ to trigger quit signal
*/

static void quit_handler(int signo) {
    fprintf(stdout, "Caught QUIT SIG\n");
    if(signal(SIGQUIT, SIG_DFL) == SIG_ERR) {
        fprintf(stderr, "Reset quit signal failed\n");
    } else {
        fprintf(stdout, "Reset quit signal\n");
    }
}

int main(int argc, char* agrv[]) {
    sigset_t newmask, oldmask, pendingmask;

    if(signal(SIGQUIT, quit_handler) == SIG_ERR) {
        fprintf(stderr, "Reset quit signal failed\n");        
    }
    
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);
    
    if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        fprintf(stderr, "block signals failed\n");        
    }

    sleep(5);

    if(sigpending(&pendingmask) < 0) {
        fprintf(stderr, "Getting pending signal mask failed\n");                
    }
    if(sigismember(&pendingmask, SIGQUIT)) {
        fprintf(stdout, "quit signal is pending\n");
    }

    if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        fprintf(stderr, "block signals failed\n");        
    }
    fprintf(stdout, "unblock signal\n");

    while(1) pause();

    return 0;
}