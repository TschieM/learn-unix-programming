#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/*

 compile with gcc -D_GNU_SOURCE file_cp.c

*/

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int main(int argc, char* argv[]) {
    if(argc < 3) {
        printf("Usage: ./a.out <original file> <copied file>\n");
        return -1;
    }

    int fd_origin = 0;
    if((fd_origin = open(argv[1], O_RDONLY)) < 0) {
        printf("Error opening file: %s\n", argv[1]);
        return -1;
    }

    int fd_copy = 0;
    if((fd_copy = creat(argv[2], RWRWRW)) < 0) {
        printf("Error creating file: %s\n", argv[2]);
        return -1;
    }

    char* buf = malloc(sizeof(char));
    size_t buf_size = 0;
    ssize_t n = 0;
    off_t hole_offset = 0, data_offset = 0;

    while(1) {
        if((data_offset = lseek(fd_origin, hole_offset, SEEK_DATA)) < 0) {
            printf("Error seek to next data offset in file: %s\n", argv[1]);
            return -1;
        }

        if(lseek(fd_copy, data_offset, SEEK_SET) < 0) {
            printf("Error seek to next data offset in file: %s\n", argv[1]);
            return -1;
        }

        if((hole_offset = lseek(fd_origin, data_offset, SEEK_HOLE)) < 0) {
            printf("Error seek to next hole offset in file: %s\n", argv[1]);
            return -1;
        }
        
        buf_size = hole_offset-data_offset;
        buf = realloc(buf, buf_size*sizeof(char));
        
        n = read(fd_origin, buf, hole_offset-data_offset);
        if(n == 0) {
            break;
        } else if(n < 0) {
            printf("Error reading file: %s\n", argv[1]);
            return -1;
        }

        if(write(fd_copy, buf, n) < 0) {
            printf("Error coping content to file: %s\n", argv[2]);
            return -1;
        }
    }

    free(buf);
    
    return 0;
}