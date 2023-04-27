#include <stdio.h>

void setbuf_custmized(FILE *restrict fp, char *restrict buf ) {
    if(!buf) {
        if(setvbuf(fp, buf, _IONBF, 0) != 0) {
            fprintf(stderr, "Error set stream unbuffered\n");
        }
    } else {
        if(setvbuf(fp, buf, _IOFBF, BUFSIZ) != 0) {
            fprintf(stderr, "Error set stream fully buffered\n");
        }
    }
}

int main(int argc, char* argv[]) {
    if(argc < 2) {
        fprintf(stderr, "Usage: ./a.out <filename>\n");
        return -1;
    }
    FILE* fp = fopen(argv[1], "r+");
    if(!fp) {
        fprintf(stderr, "Error Opening file %s\n", argv[1]);
        return -1;
    }
    setbuf_custmized(fp, NULL);
    fclose(fp);
    return 0;
}