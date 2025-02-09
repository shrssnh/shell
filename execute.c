#include "execute.h"

char temp[BUFFER];

void run(char* sentence, char* inp, char* out, char* HOMEDIR, char* LASTDIR){
    
    char* space_separated[BUFFER+1];
    tokenize_space(sentence, space_separated);
    char* command = space_separated[1];

    if (strcmp(command, "warp") == 0){
        getcwd(temp, BUFFER);
        warp(space_separated, HOMEDIR, LASTDIR);
        strcpy(LASTDIR, temp);
    }
    else if (strcmp(command, "proclore") == 0){
        proclore(space_separated);
    }
    else if (strcmp(command, "ping") == 0){
        int pid, sig;
        if ((int) space_separated[0] != 3){
            print_error();
            printf("Invalid format for ping!\n\n");
        }
        char* test;
        pid = strtol(space_separated[2], &test, 10);
        if (test != space_separated[2] + strlen(space_separated[2])){
            print_error();
            printf("Invalid numbers in ping!\n\n");
            return;
        }
        sig = strtol(space_separated[3], &test, 10);
        if (test != space_separated[3] + strlen(space_separated[3])){
            print_error();
            printf("Invalid numbers in ping!\n\n");
            return;
        }
        ping(pid, sig);
    }
    else if (strcmp(command, "peek") == 0){
        if (space_separated[(int)space_separated[0]][0] == '-' || strcmp(space_separated[(int)space_separated[0]], "peek") == 0){
            space_separated[0] = space_separated[0] + 1;
            char temp[] = "~";
            space_separated[(int)space_separated[0]] = temp;
        }
        if (space_separated[(int)space_separated[0]][0] == '~'){
            char* dirpath = malloc( ( strlen(HOMEDIR) + strlen(space_separated[(int)space_separated[0]] ) ) );
            strcpy(dirpath, HOMEDIR);
            strcat(dirpath, &space_separated[(int)space_separated[0]][1]);
            space_separated[(int)space_separated[0]] = dirpath;
        }
        peek(space_separated);
    }
    else if (strcmp(command, "seek") == 0){
        if (space_separated[(int)space_separated[0]][0] == '-' || strcmp(space_separated[(int)space_separated[0]], "seek") == 0){
            space_separated[0] = space_separated[0] + 1;
            char temp[] = "~";
            space_separated[(int)space_separated[0]] = temp;
        }
        if (space_separated[(int)space_separated[0]][0] == '~'){
            char* dirpath = malloc( ( strlen(HOMEDIR) + strlen(space_separated[(int)space_separated[0]] ) ) );
            strcpy(dirpath, HOMEDIR);
            strcat(dirpath, &space_separated[(int)space_separated[0]][1]);
            space_separated[(int)space_separated[0]] = dirpath;
        }
        seek(space_separated);
    }
    else if (strcmp(command, "iMan") == 0){
        if ((int) space_separated[0] != 2){
            print_error();
            printf("Invalid command for iMan.\n\n");
        }
        else{
            iman(space_separated[2]);
        }
    }
    // else if (strcmp(command, "peek")){
    //     int res = peek(space_separated);
    //     if (res != 0) printf("Invalid Command: %s\n", sentence);
    // }
    else{
        runsystem(space_separated, inp, out);
    }
}

void run_bg(char* sentence, char* inp, char* out){

    char* space_separated[BUFFER+1];
    tokenize_space(sentence, space_separated);

    // int pid = fork();
    // if (pid < 0){
    //     print_error("Failed to launch system process. Try again\n");
    //     return;
    // }
    // else if (pid == 0){
    //     runsystem(space_separated, inp, out);
    // }
    // else{
    //     printf("Child pid: %d\n\n", pid);
    // }


    char* command = space_separated[1];
    char* args[(int)space_separated[0] + 1];

    for (int i = 0; i < (int) space_separated[0]; i++){
        args[i] = space_separated[i+1];
    }
    args[(int) space_separated[0]] = NULL;

    int pid = fork();
    int status;

    if (pid < 0){
        print_error("Failed to launch system process. Try again\n");
        return;
    }
    else if (pid == 0){
        int devnull = open("/dev/null", "w+");
        dup2(devnull, STDOUT_FILENO);
        dup2(devnull, STDERR_FILENO);
        close(devnull);

        // int stat = execvp(command, args);
        // if (stat == -1){
        //     perror("execvp");
        // }
        // printf("%s with pid %d exited succesfully.", command, pid);
        int child = fork();
        int status_child;

        if (child < 0){
            print_error("Failed to launch system process. Try again\n");
            return;
        }
        else if (child == 0){
            int stat = execvp(command, args);
            if (stat == -1){
                perror("execvp");
            }
        }
        else{
            waitpid(child, &status_child, 0);
            if (WIFEXITED(status_child)) {
                printf("Child process with pid %d exited with status %d\n", child, WEXITSTATUS(status_child));
            } else {
                printf("Child process did not exit normally\n");
            }
        }
    }
    else{
        // waitpid(pid);
        printf("Child process %s with pid %d started.\n\n", command, pid);
    }
}

void runsystem(char** space_separated, char* inp, char* out){
    char* command = space_separated[1];
    char* args[(int)space_separated[0] + 1];

    for (int i = 0; i < (int) space_separated[0]; i++){
        args[i] = space_separated[i+1];
    }
    args[(int) space_separated[0]] = NULL;

    int pid = fork();
    int status;

    if (pid < 0){
        print_error("Failed to launch system process. Try again\n");
        return;
    }
    else if (pid == 0){
        int stat = execvp(command, args);
        if (stat == -1){
            perror("execvp");
        }
    }
    else{
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("System process with pid %d exited with status %d\n", pid, WEXITSTATUS(status));
        } else {
            printf("System process did not exit normally\n");
        }
    }
}