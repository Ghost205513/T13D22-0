#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int read_file(const char *path, char *output);
int write_file(const char *path, char *add);
char *read();
int cipher_files(const char *path_to_directory);
int cipher_read_file(const char *path, char *output, int shift);
char caesar_shift(char src, int shift);
int strlen_(const char *str);

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

                if (write_file(path, add)) {
                    printf("n/a\n");
                } else if (read_file(path, output)) {
                    printf("n/a\n");
                } else {
                    printf("%s\n", output);
                }

                free(output);
                free(add);
            }
        } else if (input && strlen_(input) == 1 && input[0] == '3') {
            char *path_to_dir = read();

            if (path_to_dir == NULL) {
                printf("n/a\n");
            } else {
                cipher_files(path_to_dir);
                free(path_to_dir);
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

    if (path != NULL)
        free(path);
}

int read_file(const char *path, char *output) {
    FILE *file = fopen(path, "r");
    int flag = 0, len = 0;

    if (!file) {
        flag = 1;
    } else {
        int input = fgetc(file);

        while (input != EOF) {
            output = realloc(output, len + 1);
            output[len] = (char) input;
            len++;
            input = fgetc(file);
        }

        if (feof(file) == 0 || len == 0) {
            flag = 1;
        }

        fclose(file);
    }

    return flag;
}

int write_file(const char *path, char *add) {
    FILE *file = fopen(path, "r+");
    int flag = 0;

    if (!file) {
        flag = 1;
    } else {
        fseek(file, 0, SEEK_END);
        fputs(add, file);
    }

    fclose(file);

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
            res[len] = (char) input;
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

int is_not_end_slash(const char *path, int len) {
    return path[len - 1] == '/' ? 0 : 1;
}

int cipher_files(const char *path_to_directory) {
    int shift, flag = (scanf("%d%*c", &shift) + 1) % 2, len_path_to_directory = strlen_(path_to_directory);
    DIR *directory = opendir(path_to_directory);
    if (!directory) {
        flag = 1;
    } else {
        struct dirent *current;

        while ((current = readdir(directory)) != NULL) {
            int current_len = strlen_(current->d_name);
            char *current_path = malloc(
            (len_path_to_directory + current_len +
            is_not_end_slash(path_to_directory,
            len_path_to_directory)) * sizeof(char));

            for (int i = 0; i < len_path_to_directory; i++)
                current_path[i] = path_to_directory[i];

            if (path_to_directory[len_path_to_directory - 1] != '/')
                current_path[len_path_to_directory] = '/';

            for (int i = len_path_to_directory + is_not_end_slash(path_to_directory,
                                                            len_path_to_directory);
                 i < len_path_to_directory + is_not_end_slash(path_to_directory,
                                        len_path_to_directory) + current_len; i++)
                current_path[i] = current->d_name[i - len_path_to_directory -
                is_not_end_slash(path_to_directory, len_path_to_directory)];

            if (current_len > 1 && current->d_name[current_len - 2] == '.') {
                if (current->d_name[current_len - 1] == 'c') {
                    char *buffer = malloc(1);

                    if (cipher_read_file(current_path, buffer, shift) == 1) {
                        flag = 1;
                    } else {
                        FILE *file = fopen(current_path, "w");
                        fputs(buffer, file);
                        fclose(file);
                    }

                    free(buffer);
                } else if (current->d_name[current_len - 1] == 'h') {
                    FILE *file = fopen(current_path, "w");
                    fclose(file);
                }
            }

            free(current_path);
        }

        closedir(directory);
    }

    return flag;
}

int cipher_read_file(const char *path, char *output, int shift) {
    FILE *file = fopen(path, "r");
    int flag = 0, len = 0;
    char *temp;

    if (!file) {
        flag = 1;
    } else {
        int input = fgetc(file);
        fputc(127, file);

        while (input != EOF) {
            temp = realloc(output, len + 1);
            if (temp == NULL) {
                free(output);
                flag = 1;
                break;
            }  else {
                output[len] = caesar_shift((char) input, shift);
                len++;
                input = fgetc(file);
            }
        }

        if (feof(file) == 0 || len == 0) {
            flag = 1;
        }

        fclose(file);
    }

    return flag;
}

char caesar_shift(char src, int shift) {
    char ans;

    if ('A' <= src && src <= 'Z') {
        if (shift > 0) {
            ans = (char) ((src - 'A' + shift) % 26 + 'A');
        } else {
            ans = (char) ((src - 'A' + 26 + shift % 26) % 26 + 'A');
        }
    } else if ('a' <= src && src <= 'z') {
        if (shift > 0) {
            ans = (char) ((src - 'a' + shift) % 26 + 'a');
        } else {
            ans = (char) ((src - 'a' + 26 + shift % 26) % 26 + 'a');
        }
    } else {
        ans = src;
    }

    return ans;
}

int strlen_(const char *str) {
    int len = 0;

    for (; *(str + len); len++) {}

    return len;
}

