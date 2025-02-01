#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/wait.h>

#define MAX_ARGS 100

int main(void) {
    char *line = NULL;
    size_t bufsize = 0;

    while (1) {
        printf("$ ");
        fflush(stdout);

        if (getline(&line, &bufsize, stdin) == -1) {
            perror("getline");
            break;
        }

        // remove trailing newlin
        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0) {
            continue;
        }

        // parse
        char *args[MAX_ARGS];
        int arg_count = 0;
        char *token = strtok(line, " ");
        while (token != NULL && arg_count < MAX_ARGS - 1) {
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL;

        // handle "exit"
        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        // fork
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            continue;
        }

        if (pid == 0) {
            // within child process
            if (execvp(args[0], args) == -1) {
                perror("execvp");
            }
            exit(EXIT_FAILURE);
        } else {
            // within parent
            int status;
            if (waitpid(pid, &status, 0) == -1) {
                perror("waitpid");
            }

            // parse return code
            if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                int ret = system("shutdown -h now");
                if (ret == -1) {
                    perror("system");
                    return 1;
                }
            } else {
                printf("child terminated abnormally\n");
                assert(false);
            }
        }
    }

    free(line);
    return 0;
}
