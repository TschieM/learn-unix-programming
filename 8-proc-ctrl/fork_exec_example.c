#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    pid_t child_pid = fork();
    int statloc = 0;
    if(child_pid < 0) {
        fprintf(stderr, "Error fork\n");
    } else if(child_pid == 0) {
        execl("echoall", "hello", "world", NULL);
        exit(0);
    }

    wait(&statloc);

    fprintf(stdout, "Parent process with pid %d running\n", getpid());
    return 0;
}