#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <setjmp.h>

static jmp_buf buf;

static void alarm_cb(int signo) {
    // do nothing, the purpose of this function is to replace the 
    // default handler and send a signal
    longjmp(buf, 1);
}

static void sleep1(uint seconds) {
    signal(SIGALRM, alarm_cb);
    // if the context got switched between alarm and pause and the alarm triggered
    // before the pause is invoked, the jmp will catch this by the second time. 
    // if the alarm and pause is interrupted again, then the next time jmp comes back
    // the sleep1 will finish. (Since the pasued time has been expied anyway)
    if(setjmp(buf) == 0) {
        alarm(seconds);
        pause();
    }
}

int main(int argc, char* argv[]) {
    if(argc < 2) {
        fprintf(stderr, "Usage: ./a.out <Pause for seconds>\n");
        exit(-1);
    }
    struct timespec ts;
    time_t start_s, end_s;
    
    clock_gettime(CLOCK_REALTIME, &ts);
    start_s = ts.tv_sec;
    sleep1(atoi(argv[1]));
    clock_gettime(CLOCK_REALTIME, &ts);
    end_s = ts.tv_sec;
    fprintf(stdout, "Slept for %ld seconds\n", end_s-start_s);
    return 0;
}