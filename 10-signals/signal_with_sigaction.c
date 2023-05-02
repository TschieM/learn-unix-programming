#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/*
 Usage instruction is the same as sig_mask_and_pending.c
*/

void* my_signal(int signo, void *func) {
    struct sigaction act, oact;

    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if(signo == SIGALRM) {
#ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;
#endif
    } else {
        act.sa_flags |= SA_RESTART;
    }
    if(sigaction(signo, &act, &oact) < 0) return SIG_ERR;
    // oact.as_handler is pointing to an existing function handler, which is not local
    return (&oact.sa_handler);
}

static void quit_handler(int signo) {
    fprintf(stdout, "Caught QUIT SIG\n");
    if(signal(SIGQUIT, SIG_DFL) == SIG_ERR) {
        fprintf(stderr, "Reset quit signal failed\n");
    } else {
        fprintf(stdout, "Reset quit signal\n");
    }
}


int main(int argc, char* argv[]) {
    sigset_t newmask, oldmask, pendingmask;

    if(my_signal(SIGQUIT, quit_handler) == SIG_ERR) {
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
    return 0;
}