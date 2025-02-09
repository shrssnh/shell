#include "warp.h"

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define BUFFER 4096

void change_dir(char* path){
    char dir[BUFFER];
    // printf("Warping to %s\n", path);
    int res  = chdir(path);
    if (res != 0){
        perror("chdir");
    }
    else {
        getcwd(dir, BUFFER);
        printf("%s\n", dir);
    }
}

void warp(char** space_separated, char* homedir, char* lastdir) {
    // Do not hardcode the prmopt
    // printf("<Everything is a file> ");

    for (int i = 0; i < (int) space_separated[0] - 1; i++){
        if (space_separated[i+2][0] == '~'){
            char direc[BUFFER];
            strcpy(direc, homedir);
            if (space_separated[i+2][1] != '\0') strcat(direc, &space_separated[i+2][1]);
            change_dir(direc);
        }
        if (space_separated[i+2][0] == '-'){
            change_dir(lastdir);
        }
        else change_dir(space_separated[i+2]);
    }
}
