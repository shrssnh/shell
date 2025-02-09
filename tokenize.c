#include "tokenize.h"

void tokenize_colon(char* input_string, char** token_array){
    char* saveptr = NULL;
    int token_array_len;

    char* token = strtok_r(input_string, ";", &saveptr);
    token_array_len = 0;
    if (token != NULL){
        for (int i = 1; token!=NULL; i++){
            token_array[i] = token;
            token_array_len = i;
            token = strtok_r(NULL, ";", &saveptr);
        }
    }
    token_array[0] = token_array_len;
}

void tokenize_and(char* input_string, char** token_array){
    char* saveptr = NULL;
    int token_array_len;

    char* token = strtok_r(input_string, "&", &saveptr);
    token_array_len = 0;
    if (token != NULL){
        for (int i = 1; token!=NULL; i++){
            token_array[i] = token;
            token_array_len = i;
            token = strtok_r(NULL, "&", &saveptr);
        }
    }
    token_array[0] = token_array_len;
}

void tokenize_space(char* input_string, char** token_array){
    char* saveptr = NULL;
    int token_array_len;

    char* token = strtok_r(input_string, " ", &saveptr);
    token_array_len = 0;
    if (token != NULL){
        for (int i = 1; token!=NULL; i++){
            token_array[i] = token;
            token_array_len = i;
            token = strtok_r(NULL, " ", &saveptr);
        }
    }
    token_array[0] = token_array_len;
}

char* getinp(char* statement){

}

char* getout(char* statement){
    
}