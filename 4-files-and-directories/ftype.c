#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
    struct stat buf;
    char* msg;

    for(int i=1; i<argc; i++) {
        printf("%s: ", argv[i]);
        if(lstat(argv[i], &buf) < 0) {
            printf("lstat error\n");
            return -1;
        }

        if(S_ISREG(buf.st_mode)) {
            msg = "regular file";
        } else if(S_ISDIR(buf.st_mode)) {
            msg = "directory file";
        } else if(S_ISCHR(buf.st_mode)) {
            msg = "charactor special file";
        } else if(S_ISBLK(buf.st_mode)) {
            msg = "block special file";
        } else if(S_ISFIFO(buf.st_mode)) {
            msg = "pipe or FIFO";
        } else if(S_ISLNK(buf.st_mode)) {
            msg = "symbolic link";
        } else if(S_ISSOCK(buf.st_mode)) {
            msg = "socket";
        } else {
            msg = "unknown";
        }
        printf("%s\n", msg);
    }
    
    return 0;
}