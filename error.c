#include "error.h"

#define ANSI_COLOR_RED   "\x1b[1;31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void print_error(){
    printf(ANSI_COLOR_RED"\nERROR: "ANSI_COLOR_RESET);
    // printf("%s\n", error);
    // for (int i = 0; i < len; i++){
    //     printf("%s", error[i]);
    // }
    // printf("\n");
}