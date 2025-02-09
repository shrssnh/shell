#include "headers.h"

void die(const char *s) {
    perror(s);
    exit(1);
}

struct termios orig_termios;

void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

void enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

int main()
{

    // Getting and storing Home Directory
    char HOMEDIR[BUFFER];
    char LASTDIR[BUFFER];
    getcwd(HOMEDIR, BUFFER);
    strcpy(LASTDIR, HOMEDIR);

    int fgcount;
    int bgcount;
    char* FG[BUFFER];
    char* BG[BUFFER];

    // Keep accepting commands

    char *input = malloc(sizeof(char) * BUFFER);
    char c;

    while (1) {
        setbuf(stdout, NULL);
        enableRawMode();
        prompt(HOMEDIR, strlen(HOMEDIR));
        memset(input, '\0', 100);
        int pt = 0;
        while (read(STDIN_FILENO, &c, 1) == 1) {
            if (iscntrl(c)) {
                if (c == 10){
                    printf("\n");
                    break;
                }
                else if (c == 27) {
                    char buf[3];
                    buf[2] = 0;
                    if (read(STDIN_FILENO, buf, 2) == 2) { // length of escape code
                        printf("\rarrow key: %s", buf);
                    }
                } else if (c == 127) { // backspace
                    if (pt > 0) {
                        if (input[pt-1] == 9) {
                            for (int i = 0; i < 7; i++) {
                                printf("\b");
                            }
                        }
                        input[--pt] = '\0';
                        printf("\b \b");
                    }
                } else if (c == 9) { // TAB character
                    input[pt++] = c;
                    for (int i = 0; i < 8; i++) { // TABS should be 8 spaces
                        printf(" ");
                    }
                } else if (c == 4) {
                    exit(0);
                } else {
                    printf("%d\n", c);
                }
            } else {
                input[pt++] = c;
                printf("%c", c);
            }
        }
        disableRawMode();

        char* colon_separated[BUFFER + 1];

        char* inp;
        char* out;

        tokenize_colon(input, colon_separated);

        for (int i = 1; i < (int) colon_separated[0] + 1; i++){
            char* and_separated[BUFFER + 1];
            tokenize_and(colon_separated[i], and_separated);

            for (int j = 1; j < (int) and_separated[0]; j++){
                inp = getinp(and_separated[j]);
                out = getout(and_separated[j]);
                run_bg(and_separated[j], inp, out);
                // bgcount++;
            }

            inp = getinp(and_separated[(int)and_separated[0]]);
            out = getout(and_separated[(int)and_separated[0]]);
            if (colon_separated[i][strlen(colon_separated[i]) - 1] == '&') run_bg(and_separated[(int) and_separated[0]], inp, out);
            else run(and_separated[(int)and_separated[0]], inp, out, HOMEDIR, LASTDIR);
        }

        // printf("\nInput Read: [%s]\n", input);
    }
}
