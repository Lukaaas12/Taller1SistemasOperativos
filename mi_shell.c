#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define TOK_DELIM " \t\r\n\a"
int main() {
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t linelen;
    while (1) {
        printf("mi_shell> ");
        fflush(stdout);
        linelen = getline(&line, &bufsize, stdin);
        if (linelen == -1) {
            printf("\n");
            break;
        }
        if (strcmp(line, "\n") == 0) {
            continue;
        }
        int buf_args = 64;
        int position = 0;
        char **tokens = malloc(buf_args * sizeof(char*));
        char *token;
        if (!tokens) {
            fprintf(stderr, "Error de asignación de memoria\n");
            exit(EXIT_FAILURE);
        }
        token = strtok(line, TOK_DELIM);
        while (token != NULL) {
            tokens[position] = token;
            position++;
            if (position >= buf_args) {
                buf_args += 64;
                tokens = realloc(tokens, buf_args * sizeof(char*));
                if (!tokens) {
                    fprintf(stderr, "Error de reasignación de memoria\n");
                    exit(EXIT_FAILURE);
                }
            }
            token = strtok(NULL, TOK_DELIM);
        }
        tokens[position] = NULL;
        if (tokens[0] == NULL) {
            free(tokens);
            continue;
        }
        if (strcmp(tokens[0], "exit") == 0) {
            free(tokens);
            break;
        }
        pid_t pid = fork();
        if (pid == 0) {
            if (execvp(tokens[0], tokens) == -1) {
                perror("Error en mi_shell");
            }
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            perror("Error al hacer fork");
        } else {
            int status;
            waitpid(pid, &status, 0);
        }
        free(tokens);
    }
    free(line);
    return 0;
}
