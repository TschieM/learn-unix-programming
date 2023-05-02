#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <pwd.h>

static char *usrname;

static void alarm_handler(int signo) {
    struct passwd* rpwd;
    fprintf(stdout, "Calling from alarm handler\n");
    if((rpwd = getpwnam("root")) == NULL) {
        fprintf(stderr, "Error get pwd for root\n");
    }
    alarm(1);
}

int main(int argc, char* argv[]) {
    if(argc < 2) {
        fprintf(stderr, "Usage: ./a.out <user name>\n");
        exit(-1);
    }
    usrname = argv[1];

    signal(SIGALRM, alarm_handler);
    alarm(1);
    
    struct passwd* pwd;
    while(1) {
        if((pwd = getpwnam(usrname)) == NULL) {
            fprintf(stderr, "Usage: ./a.out <user name>\n");
        }
        if(strcmp(pwd->pw_name, usrname) != 0) {
            fprintf(stderr, "Data corrupted\n");
        }
    }
    return 0;
}