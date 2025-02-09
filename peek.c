#include "peek.h"

void peek(char** space_separated){

    int all=0, list=0, allcheck=0, listcheck=0, dircheck=0;

    if ((int) (space_separated[0]) > 4){
        print_error();
        printf("Invalid parameters in peek:\n");
        for (int i = 1; i < space_separated[0] + 1; i++){
            printf(" %s", space_separated[i]);
        }
        printf("\n\n");
        return;
    }
    else{
        for (int i = 2; i < (int)space_separated[0] + 1; i++){
            if ((char)space_separated[i][0] == '-' && strlen(space_separated[i]) == 2){
                if (space_separated[i][1] == 'a'){
                    all = 1;
                }
                else if (space_separated[i][1] == 'l'){
                    list = 1;
                }
                else{
                    print_error();
                    printf("Invalid Flags in peek: %s\n\n", space_separated[i]);
                    return;
                }
            }
            else if (i == (int)space_separated[0]){
                dircheck = 1;
            }
            else{
                print_error();
                printf("Invalid Syntax in peek: %s\n\n", space_separated[i]);
                return;
            }
        }
    }

    char* dirpath = space_separated[(int)space_separated[0]];

    errno = 0;
    DIR* dir = opendir(dirpath);
    struct dirent* entry;
    
    if (dir == NULL && errno != 0){
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir))) {
        if (all && entry->d_name[0] == '.') printf("%s\n", entry->d_name);
        else if (entry->d_name[0] != '.') printf("%s\n", entry->d_name);
    }

    closedir(dir);
}
