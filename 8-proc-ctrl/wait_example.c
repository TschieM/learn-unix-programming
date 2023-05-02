#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void print_exit(int status) {
    if(WIFEXITED(status)) {
        fprintf(stdout, "Normal exist, exited with status: %d\n", WEXITSTATUS(status));
    } else if(WIFSIGNALED(status)) {
        fprintf(stdout, "Abnormal exist, exited with status: %d\n", WTERMSIG(status));
    } else if(WIFSTOPPED(status)) {
        fprintf(stdout, "child stopped, signal number = %d\n", WSTOPSIG(status));
    }
}

int main(int argc, char* argv[]) {
    pid_t pid;
    int status;

    pid = fork();
    if(pid < 0) {
        fprintf(stderr, "error fork\n");
        exit(-1);
    } else if(pid == 0) {
        exit(7);
    }

    if(wait(&status) < 0) {
        fprintf(stderr, "error waiting\n");
        exit(-1);
    } else {
        print_exit(status);
    }

    pid = fork();
    if(pid < 0) {
        fprintf(stderr, "error fork\n");
        exit(-1);
    } else if(pid == 0) {
        abort();
    }

    if(wait(&status) < 0) {
        fprintf(stderr, "error waiting\n");
        exit(-1);
    } else {
        print_exit(status);
    }

    pid = fork();
    if(pid < 0) {
        fprintf(stderr, "error fork\n");
        exit(-1);
    } else if(pid == 0) {
        // intened for triggering 0 division error
        status /= 0;
    }

    if(wait(&status) < 0) {
        fprintf(stderr, "error waiting\n");
        exit(-1);
    } else {
        print_exit(status);
    }

    return 0;
}