#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* th1(void* args) {
    fprintf(stdout, "[TH1]: Running thread function 1\n");
    return (void*) 1;
}

void* th2(void* args) {
    fprintf(stdout, "[TH2]: Running thread function 2\n");
    pthread_exit((void*)2);
}

int main(int argc, char* argv[]) {
    pthread_t nth;
    void* th_ret;
    if(pthread_create(&nth, NULL, th1, NULL) != 0) {
        fprintf(stderr, "[Main]: Error creating thread 1\n");
        exit(-1);
    }

    if(pthread_join(nth, &th_ret) != 0) {
        fprintf(stderr, "[Main]: Error joining thread 1\n");
        exit(-1);
    }

    fprintf(stdout, "[Main]: thread 1 exit code is %d\n", (int)th_ret);

    if(pthread_create(&nth, NULL, th2, NULL) != 0) {
        fprintf(stderr, "[Main]: Error creating thread 2\n");
        exit(-1);
    }

    if(pthread_join(nth, &th_ret) != 0) {
        fprintf(stderr, "[Main]: Error joining thread 2\n");
        exit(-1);
    }

    fprintf(stdout, "[Main]: thread 2 exit code is %d\n", (int)th_ret);

    return 0;
}