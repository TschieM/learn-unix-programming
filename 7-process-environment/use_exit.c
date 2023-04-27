#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void func_exit() {
    fprintf(stdout, "Exit Function called\n");
}

int main(int argc, char* argv[]) {
    atexit(func_exit);
    if(argc < 2) {
        fprintf(stderr, "Usage: ./a.out <exit-mode: 1-force, 2-clean>\n");
        exit(-1);
    }
    if(strcmp(argv[1],"1") == 0) {
        _Exit(0);
    }
    exit(0);
}