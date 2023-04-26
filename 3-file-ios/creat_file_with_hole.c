#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int main(int argc, char* argv[]) {
    const char* buf = "abcdefg";

    int fd;
    if((fd = creat("file.hole", RWRWRW)) < 0) {
        printf("Error creating file\n");
        return -1;
    }

    if((write(fd, buf, 7)) < 0) {
        printf("Error writing file\n");
        return -1;
    }

    if((lseek(fd, 16384, SEEK_CUR)) < 0) {
        printf("Error setting offset to file\n");
        return -1;
    }

    if((write(fd, buf, 7)) < 0) {
        printf("Error writing file\n");
        return -1;
    }
    return 0;
}