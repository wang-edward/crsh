#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#ifdef __linux__
    #define SHUTDOWN_CMD "shutdown -h now"
#elif defined(__APPLE__)
    #define SHUTDOWN_CMD "shutdown -h now"
#else
    #error "Unsupported OS"
#endif

#define MAX_ARGS 100

int main(void) {
    char *line = NULL;
    size_t bufsize = 0;

    while (1) {
        printf("root@crsh $ ");
        fflush(stdout);

        if (getline(&line, &bufsize, stdin) == -1) {
            perror("getline");
            break;
        }

        // clean newline
        line[strcspn(line, "\n")] = '\0';

        // skip empty lines
        if (strlen(line) == 0) {
            continue;
        }

        // tokenize
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
            // child
            if (execvp(args[0], args) == -1) {
                perror("execvp");
            }
            exit(EXIT_FAILURE);
        } else {
            // parent
            int status;
            if (waitpid(pid, &status, 0) == -1) {
                perror("waitpid");
            }

            if (!WIFEXITED(status)) {
                printf("child terminated abnormally\n");
                return 1;
            }

            // shutdown if $? != 0
            if (WEXITSTATUS(status) != 0) {
                int ret = system(SHUTDOWN_CMD);
                if (ret == -1) {
                    perror("system");
                    return 1;
                }
                printf("SHUTDOWN\n");
            }
        }
    }

    free(line);
    return 0;
}
