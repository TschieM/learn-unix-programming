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

    // printf is a std io, when it is printed to output(terminal) then it is line buffered
    // In this case, the buffer will be flushed when when it hits the end of the line, so 
    // This print will be printed once
    // run with: ./a.out

    // However, if the output is redirected to a file(when the file pointer is not pointing to the terminal output)
    // then it will be fully buffered, after the buffer will not be flushed until it is full or the process terminates
    // when fork is called, the child process will copy the buffer(which contains the message). Thus the message will
    // show in the file twice
    // run with: ./a.out > out.file
    printf("Hey there, this is a buffered output\n");

    pid_t pid = fork();
    if(pid < 0) {
        fprintf(stderr, "Error fork\n");
        exit(-1); 
    } else if(pid == 0) {
        g_var *= 2;
        var++;
    } else {
        sleep(2);
    }

    fprintf(stdout, "pid-%d: g_var = %d, var = %d\n", getpid(), g_var, var);
    
    return 0;
}