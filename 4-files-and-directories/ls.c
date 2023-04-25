#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("Usage: ./a.out <pathname>\n");
        return -1;
    }

    DIR* dp;
    if((dp = opendir(argv[1])) == NULL) {
        printf("Open dir %s failed.\n", argv[1]);
        return -1;
    }

    struct dirent* dirp;
    while((dirp = readdir(dp)) != NULL) {
        if(strcmp(dirp->d_name, ".")==0 || strcmp(dirp->d_name, "..")==0) continue;
        printf("%s\n", dirp->d_name);
    }
    closedir(dp);

    return 0;
}