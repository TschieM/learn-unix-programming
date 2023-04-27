#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define RWXRWXRWX (S_IRWXU|S_IRWXG|S_IRWXO)

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
    const char* tmpfile = "tempfile";
    if(creat(tmpfile, RWXRWXRWX) < 0) {
        fprintf(stderr, "Error creating temp file\n");
        return -1;
    }
    FILE* fp = fopen(tmpfile, "r+");
    if(!fp) {
        fprintf(stderr, "Error Opening %s\n", tmpfile);
        return -1;
    }
    if (unlink(tmpfile) < 0) {
        fprintf(stderr, "Error unlinking temp file\n");
        return -1;
    }
    
    setbuf_custmized(fp, NULL);
    if(fp->_flags & _IO_UNBUFFERED) fprintf(stdout, "file unbuffered\n");
    else if(fp->_flags & _IO_LINE_BUF) fprintf(stdout, "file linebuffered\n");
    else fprintf(stdout, "file fullbuffered\n");
    fclose(fp);
    return 0;
}