#include <stdio.h>

int main(int argc, char* argv[]) {
    int c = -1;
    while((c = fgetc(stdin)) != -1) {
        if(fputc(c, stdout) == -1) {
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