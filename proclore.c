#include "proclore.h"

void printinfo(pid_t pid){
    
    char fileloc[25];
    sprintf(fileloc, "/proc/%d/status\0", (int)pid);
    FILE* stat_file = fopen(fileloc, "r");
    char buffer[BUFFER];
    char c = fgetc(stat_file);
    int file_length = 0;
    while(c != EOF){
        buffer[file_length] = c;
        file_length++;
        c = fgetc(stat_file);
    }
    buffer[file_length] = '\0';

    printf("pid : %d\n", pid);

    for (int i = 0; i < file_length; i++){
        if (strncmp(&buffer[i], "State:", 6) == 0){
            printf("Status: %c\n", buffer[i+7]);
        }
    }

    pid_t groupid = getpgid(pid);
    printf("Process Group : %d\n", groupid);

    for (int i = 0; i < file_length; i++){
        if (strncmp(&buffer[i], "VmSize:", 6) == 0){
            printf("Virtual Memory: %c\n", buffer[i+8]);
        }
    }

    for (int i = 0; i < file_length; i++){
        if (strncmp(&buffer[i], "State:", 6) == 0){
            printf("Status: %c\n", buffer[i+7]);
        }
    }
}

void proclore(char** space_separated){
    printf("\n");
    if ((int)space_separated[0] < 2){
        pid_t pid = getpid();
        printinfo(pid);
    }
    else {
        for (int i = 2; i < (int)space_separated[0] + 1; i++){
            pid_t pid = (pid_t) space_separated[i];
            printinfo(pid);
        }
    }
}
