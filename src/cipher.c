#include <stdio.h>
#include <stdlib.h>

int read_file(char *path, char *output);
int write_file(char *path, char *add, char *output);
char *read();
int strlen_(char *str);

int main() {
    char *input = NULL, *path = NULL;
    input = read();

    while (!(input && strlen_(input) == 2 && input[0] == '-' && input[1] == '1')) {
        if (input && strlen_(input) == 1 && input[0] == '1') {
            if (path != NULL)
                free(path);

            path = read();

            if (path == NULL) {
                printf("n/a\n");
            } else {
                char *output = malloc(1);

                if (read_file(path, output)) {
                    printf("n/a\n");
                } else {
                    printf("%s\n", output);
                }

                free(output);
            }
        } else if (input && strlen_(input) == 1 && input[0] == '2') {
            char *add = read();

            if (path == NULL || add == NULL) {
                printf("n/a\n");
            } else {
                char *output = malloc(1);

                if (write_file(path, add, output)) {
                    printf("n/a\n");
                } else {
                    printf("%s\n", output);
                }

                free(output);
                free(add);
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

int read_file(char *path, char *output) {
    FILE *file = fopen(path, "r");
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
        }

        fclose(file);
    }

    return flag;
}

int write_file(char *path, char *add, char *output) {
    FILE *file = fopen(path, "r+");
    int flag = 0, len = 0;

    if (!file) {
        flag = 1;
    } else {
        fseek(file, 0, SEEK_END);
        fputs(add, file);
    }

    if (!file) {
        flag = 1;
    } else {
        fseek(file, 0, SEEK_SET);
        int input = fgetc(file);

        while (input != EOF) {
            output = realloc(output, len + 1);
            output[len] = input;
            len++;
            input = fgetc(file);
        }

        if (feof(file) == 0) {
            flag = 1;
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
