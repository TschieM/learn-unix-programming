#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

static void alarm_cb(int signo) {
    // do nothing, the purpose of this function is to replace the 
    // default handler and send a signal
}

int main(int argc, char* argv[]) {
    if(argc < 2) {
        fprintf(stderr, "Usage: ./a.out <Pause for seconds>\n");
    }
    struct timespec ts;
    time_t start_s, end_s;
    signal(SIGALRM, alarm_cb);
    clock_gettime(CLOCK_REALTIME, &ts);
    start_s = ts.tv_sec;
    alarm(atoi(argv[1]));
    pause();
    clock_gettime(CLOCK_REALTIME, &ts);
    end_s = ts.tv_sec;
    fprintf(stdout, "Paused for %ld nano seconds\n", end_s-start_s);
    return 0;
}