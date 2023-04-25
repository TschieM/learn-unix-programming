#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int masks[9] = {S_IXOTH, S_IWOTH, S_IROTH, S_IXGRP, S_IWGRP, S_IRGRP, S_IXUSR, S_IWUSR, S_IRUSR};
#define RWXRWXRWX (S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP|S_IROTH|S_IWOTH|S_IXOTH)

int main(int argc, char* argv[]) {
    if(argc < 3) {
        printf("Usage: ./a.out <file> [<permission>]\n");
        return -1;
    }
    int permission = (int)strtol(argv[2], NULL, 16);
    mode_t cmask = 0;
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            if(!(permission&1)) cmask |= masks[i*3 + j];
            permission >>= 1; 
        }
        permission >>= 1;
    }
    umask(cmask);
    if(creat(argv[1], RWXRWXRWX) < 0) {
        printf("Create error for: %s\n", argv[1]);
        return -1;
    }
    return 0;
}