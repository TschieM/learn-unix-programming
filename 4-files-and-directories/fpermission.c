#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
    struct stat buf;
    char msg[9];

    for(int i=1; i<argc; i++) {
        printf("%s: ", argv[i]);
        if(lstat(argv[i], &buf) < 0) {
            printf("lstat error\n");
            return -1;
        }
        msg[0] = (buf.st_mode & S_IRUSR) ? 'r':'-';
        msg[1] = (buf.st_mode & S_IWUSR) ? 'w':'-';
        msg[2] = (buf.st_mode & S_IXUSR) ? 'x':'-';
        msg[3] = (buf.st_mode & S_IRGRP) ? 'r':'-';
        msg[4] = (buf.st_mode & S_IWGRP) ? 'w':'-';
        msg[5] = (buf.st_mode & S_IXGRP) ? 'x':'-';
        msg[6] = (buf.st_mode & S_IROTH) ? 'r':'-';
        msg[7] = (buf.st_mode & S_IWOTH) ? 'w':'-';
        msg[8] = (buf.st_mode & S_IXOTH) ? 'x':'-';
        printf("%s\n", msg);
    }

    return 0;
}