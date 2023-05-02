#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int g_var = 10;
static char* buf = "hello world!\n";

int main(int argc, char* argv[]) {
    int var = 100;

    // write function is not buffered, so this output should only happen once
    if(write(STDOUT_FILENO, buf, 13) != 13) {
        fprintf(stderr, "Error writing to terminal\n");
        exit(-1);
    }
    printf("Hey there, this is a buffered output\n");

    pid_t pid = vfork();
    if(pid < 0) {
        fprintf(stderr, "Error fork\n");
        exit(-1); 
    } else if(pid == 0) {
        g_var *= 2;
        var++;
        // It is important to call _exit instead of exit
        // exit does clean up and flushes the buffer.
        // since the child process doesn't have its own address space
        // we don't want it to have anything done for the parent process
        _exit(0);
    }

    fprintf(stdout, "pid-%d: g_var = %d, var = %d\n", getpid(), g_var, var);
    
    return 0;
}