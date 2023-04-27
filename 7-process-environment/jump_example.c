#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

static jmp_buf jmp_buffer;

void double_nested_func(int x) {
    if(x) longjmp(jmp_buffer, x);
}

void nested_func(int x) {
    double_nested_func(x);
}

void jump_identifier(int x) {
    fprintf(stderr, "jump with val: %d\n", x);
    exit(-1);
}

int main(int argc, char* argv[]) {
    if(argc < 2) {
        fprintf(stderr, "Usage: ./a.out <error input>");
    }
    int n = 0;
    if((n = setjmp(jmp_buffer)) != 0) {
        jump_identifier(n);
    }

    nested_func(atoi(argv[1]));

    return 0;
}