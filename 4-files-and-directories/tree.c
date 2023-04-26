#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

struct counter_t {
    uint files;
    uint dirs;
};

struct entry_t {
    char* name;
    bool is_dir;
    struct entry_t* next;
};

uint max_depth = 0;

int tree_walk(const char* path_name, const char* prefix, uint depth, struct counter_t* cnt) {
    if(max_depth>0 && depth>max_depth) return 0;

    DIR* dp;
    if((dp = opendir(path_name)) == NULL) {
        printf("%s [error opening dir]\n", path_name);
    }
    cnt->dirs++;

    struct dirent* dirp;
    struct entry_t* flist=NULL, *current, *it;
    while((dirp = readdir(dp)) != NULL) {
        if(dirp->d_name[0] == '.') continue;

        current = malloc(sizeof(struct entry_t));
        current->name = strcpy(malloc(strlen(dirp->d_name)+1), dirp->d_name);
        current->is_dir = (dirp->d_type == DT_DIR);
        current->next = NULL;

        if(!flist) {
            flist = current;
        } else if(strcmp(current->name, flist->name) < 0) {
            current->next = flist;
            flist = current;
        } else {
            for(it = flist;it->next && strcmp(current->name, it->next->name)>0; it=it->next);
            current->next = it->next;
            it->next = current;
        }
    }

    closedir(dp);
    if(!flist) return 0;

    char* tree_icon, *seg_icon;
    for(it=flist; it; it=it->next) {
        if(!it->next) {
            tree_icon = "└── ";
            seg_icon = "    ";
        } else {
            tree_icon = "├── ";
            seg_icon = "│   ";
        }

        printf("%s%s%s\n", prefix, tree_icon, it->name);
        if(it->is_dir) {
            cnt->dirs++;
            char* next_path = malloc(strlen(path_name)+strlen(it->name)+2);
            sprintf(next_path, "%s/%s", path_name, it->name);
            char* next_prefix = malloc(strlen(prefix)+strlen(seg_icon)+1);
            sprintf(next_prefix, "%s%s", prefix, seg_icon);
            tree_walk(next_path, next_prefix, depth+1, cnt);
            free(next_path);
            free(next_prefix);
        } else {
            cnt->files++;
        }
    }

    it = flist;
    while(it) {
        current = it;
        it = it->next;
        free(current->name);
        free(current);
    }

    return 0;
}


int main(int argc, char* argv[]) {
    char* pn = ".";
    struct counter_t cnt = {0, 0};
    if(argc <= 1) {
        // do nothing 
    } else if (argc <= 2) {
        pn = argv[1];
    } else if (argc <= 3) {
        max_depth = atoi(argv[1]);
        pn = argv[2];
    } else {
        printf("Usage: ./a.out <max depth> <directory>");
        return -1;
    }

    printf("%s\n", pn);

    tree_walk(pn, "", 0, &cnt);

    printf("\n%d directories, %d files\n", cnt.dirs, cnt.files);

    return 0;
}