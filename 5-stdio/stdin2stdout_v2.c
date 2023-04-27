#include <stdio.h>

#define BUFSIZE 4

int main(int argc, char* argv[]) {
    char buf[BUFSIZE];
    while(fgets(buf, BUFSIZE, stdin) != NULL) {
        if(fputs(buf, stdout) == -1) {
            fprintf(stderr, "Error writing to the stdout\n");
            return -1;
        }
    }

    if(ferror(stdin)) {
        fprintf(stderr, "Error reading input from stdin\n");
        return -1;
    }

    return 0;
}