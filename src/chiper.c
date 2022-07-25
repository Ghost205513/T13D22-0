#include <stdio.h>
#include <stdlib.h>

int read_file(char *path);
char *read();
int strlen_(char *str);

int main() {
    char *input = NULL;
    input = read();

    while (!(input && strlen_(input) == 2 && input[0] == '-' && input[1] == '1')) {
        if (input && strlen_(input) == 1 && input[0] == '1') {
            char *path = read();

            if (path == NULL) {
                printf("n/a\n");
            } else {
                if (read_file(path)) {
                    printf("n/a\n");
                }

                free(path);
            }
        } else {
            printf("n/a\n");
        }

        if (input != NULL)
            free(input);

        input = read();
    }

    if (input != NULL)
        free(input);
}

int read_file(char *path) {
    FILE *file = fopen(path, "r");
    char *output = NULL;
    int flag = 0, len = 0;

    if (!file) {
        flag = 1;
    } else {
        int input = fgetc(file);

        while (input != EOF) {
            output = realloc(output, len + 1);
            output[len] = input;
            len++;
            input = fgetc(file);
        }

        if (feof(file) == 0) {
            flag = 1;
        } else {
            printf("%s\n", output);
            free(output);
        }

        fclose(file);
    }

    return flag;
}

char *read() {
    char *res = NULL, *temp;
    int input, flag = 0, len = 0;

    input = getchar();

    while (input != '\n') {
        temp = realloc(res, len + 1);

        if (temp == NULL) {
            free(res);
            flag = 1;
            break;
        } else {
            res = temp;
            res[len] = input;
            len++;
            input = getchar();
        }
    }

    if (flag == 1) {
        res = NULL;
    } else {
        temp = realloc(res, len + 1);

        if (temp == NULL) {
            free(res);
            res = NULL;
        }

        temp[len] = '\0';
    }

    return res;
}

int strlen_(char *str) {
    int len = 0;

    for (; *(str + len); len++) {}

    return len;
}
