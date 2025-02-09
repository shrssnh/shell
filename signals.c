#include "signals.h"

void ping(pid_t pid, int signal){
    
    int res = kill(pid, 0);
    if (res != 0){
        printf("%d\n", res);
    }
    
    signal = signal % 32;

    res = kill(pid, signal);
    if (res != 0){
        perror("kill");
    }
    else{
        printf("Sent signal %d to process with pid %d\n", signal, pid);
    }
}