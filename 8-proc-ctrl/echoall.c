#include <stdio.h>

int main(int argc, char* argv[]) {
    char **ptr;
    extern char **environ;

    for(int i=0; i<argc; i++) {
        fprintf(stdout, "argv[%d]: %s\n", i, argv[i]);
    }

    for(ptr=environ; *ptr!=NULL; ptr++) {
        fprintf(stdout, "%s\n", *ptr);
    }
    return 0;
}
