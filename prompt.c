#include "prompt.h"

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define BUFFER 4096

void prompt(char* homedir, int homedirlen) {
    // Do not hardcode the prmopt
    // printf("<Everything is a file> ");
    uid_t id = getuid();
    struct passwd* user;
    user = getpwuid(id);

    char sysname[BUFFER];
    gethostname(sysname, BUFFER);

    char dir[BUFFER];
    getcwd(dir, BUFFER);

    printf("<"ANSI_COLOR_GREEN"%s"ANSI_COLOR_RESET"@"ANSI_COLOR_YELLOW"%s"ANSI_COLOR_RESET": ", user->pw_name, sysname);

    int check = 1;

    for (int i = 0; i < homedirlen; i++){
        if (homedir[i] != dir[i]){
            check = 0;
            break;
        }
    }

    if (check){
        printf("~%s > ", &dir[homedirlen]);
    }
    else{
        printf("%s > ", dir);
    }
}
