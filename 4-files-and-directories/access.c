#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>

int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("Usage: ./a.out <file>\n");
        return -1;
    }

    if(access(argv[1], R_OK) < 0) {
        printf("No read access for %s\n", argv[1]);
    } else {
        printf("Read access ok for %s\n", argv[1]);
    }

    if(access(argv[1], W_OK) < 0) {
        printf("No write access for %s\n", argv[1]);
    } else {
        printf("Write access ok for %s\n", argv[1]);
    }

    if(access(argv[1], X_OK) < 0) {
        printf("No execute access for %s\n", argv[1]);
    } else {
        printf("Execute access ok for %s\n", argv[1]);
    }

    return 0;
}