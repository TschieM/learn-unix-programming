#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int g_var = 10;
static char* buf = "hello world!\n";

int main(int argc, char* argv[]) {
    int var = 100;

    if(write(STDOUT_FILENO, buf, 13) != 13) {
        fprintf(stderr, "Error writing to terminal\n");
        exit(-1);
    }

    pid_t pid = fork();
    if(pid < 0) {
        fprintf(stderr, "Error fork\n");
        exit(-1); 
    } else if(pid == 0) {
        g_var *= 2;
        var++;
    } else {
        sleep(5);
    }

    fprintf(stdout, "pid-%d: g_var = %d, var = %d\n", getpid(), g_var, var);
    
    return 0;
}