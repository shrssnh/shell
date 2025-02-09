#include "seek.h"

void seek(char** space_separated){

    int directory=0, file=0, enable=0, dircheck=0;

    if ((int) (space_separated[0]) > 5){
        print_error();
        printf("Invalid parameters in seek:\n");
        for (int i = 1; i < space_separated[0] + 1; i++){
            printf(" %s", space_separated[i]);
        }
        printf("\n\n");
        return;
    }
    else{
        for (int i = 2; i < (int)space_separated[0] + 1; i++){
            if ((char)space_separated[i][0] == '-' && strlen(space_separated[i]) == 2){
                if (space_separated[i][1] == 'd'){
                    directory = 1;
                }
                else if (space_separated[i][1] == 'f'){
                    file = 1;
                }
                else if (space_separated[i][1] == 'e'){
                    enable = 1;
                }
                else{
                    print_error();
                    printf("Invalid Flags in seek: %s\n\n", space_separated[i]);
                    return;
                }
            }
            else if (i == (int)space_separated[0]){
                dircheck = 1;
            }
            else{
                print_error();
                printf("Invalid Syntax in seek: %s\n\n", space_separated[i]);
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
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
}
