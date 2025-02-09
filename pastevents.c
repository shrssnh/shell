#include "pastevents.h"

#define BUFFER 4096

int store(char** statement){
    FILE* file = fopen("history.txt", "a+");
}


int pe_access(int n){

}


int manage(char** statement){
    char* space_separated[BUFFER+1];
    tokenize_space(statement, space_separated);
    if (space_separated[0] == 1){
        pe_access(15);
    }
}