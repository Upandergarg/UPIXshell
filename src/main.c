#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_INPUT 100
#define MAX_ARGS 10

void parse_command(char *input, char *args[])
{
    int count = 0;

    char *token = strtok(input, " ");

    while (token != NULL && count < MAX_ARGS - 1)
    {
        args[count] = token;
        count++;

        token = strtok(NULL, " ");
    }

    args[count] = NULL;
}

void handle_cd(char *args[])
{
    if (args[1] == NULL)
    {
        char *home = getenv("HOME");

        if (home == NULL)
        {
            printf("MiniShell: HOME directory not found\n");
            return;
        }

        if (chdir(home) != 0)
            perror("MiniShell");

        return;
    }

    if (chdir(args[1]) != 0)
        perror("MiniShell");
}

void handle_pwd(void)
{
    char current_directory[MAX_INPUT];

    if (getcwd(current_directory, sizeof(current_directory)) != NULL)
        printf("%s\n", current_directory);
    else
        perror("MiniShell");
}

void handle_echo(char *args[])
{
    for (int i = 1; args[i] != NULL; i++)
    {
        printf("%s", args[i]);

        if (args[i + 1] != NULL)
            printf(" ");
    }

    printf("\n");
}

void handle_cat(char *args[])
{
    if (args[1] == NULL)
    {
        printf("MiniShell: cat requires a file\n");
        return;
    }

    FILE *file = fopen(args[1], "r");

    if (file == NULL)
    {
        perror("MiniShell");
        return;
    }

    char line[100];

    while (fgets(line, sizeof(line), file) != NULL)
        printf("%s", line);

    fclose(file);
}

void execute_external(char *args[])
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("MiniShell");
        return;
    }

    if (pid == 0)
    {
        execvp(args[0], args);

        perror("MiniShell");
        _exit(1);
    }

      if (wait(NULL) == -1)
    {
        perror("MiniShell");
    }
}

int main(void)
{
    char input[MAX_INPUT];
    char *args[MAX_ARGS];

    printf("==============================\n");
    printf("          MiniShell\n");
    printf("==============================\n");

    while (1)
    {
        printf("MiniShell$ ");

        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        input[strcspn(input, "\n")] = '\0';

        parse_command(input, args);

        if (args[0] == NULL)
            continue;

        if (strcmp(args[0], "cd") == 0)
        {
            handle_cd(args);
        }
        else if (strcmp(args[0], "pwd") == 0)
        {
            handle_pwd();
        }
        else if (strcmp(args[0], "echo") == 0)
        {
            handle_echo(args);
        }
        else if (strcmp(args[0], "cat") == 0)
        {
            handle_cat(args);
        }
        else
        {
            execute_external(args);
        }
    }

    return 0;
}