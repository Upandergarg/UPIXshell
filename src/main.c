#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_INPUT 100
#define MAX_ARGS 10

void parse_command(char *input, char *args[])
{
    int count = 0;

   char *token = strtok(input, " \t\r\n"); 

    while (token != NULL && count < MAX_ARGS - 1)
    {
        args[count] = token;
        count++;
  token = strtok(NULL, " \t\r\n");
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
    FILE *file;

    if (args[1] == NULL)
    {
        file = stdin;
    }
    else
    {
        file = fopen(args[1], "r");

        if (file == NULL)
        {
            perror("MiniShell");
            return;
        }
    }

    char line[100];

    while (fgets(line, sizeof(line), file) != NULL)
        printf("%s", line);

    if (file != stdin)
        fclose(file);
}



void handle_redirection(char *args[], char **input_file, char **output_file)
{
    int i = 0;

    *input_file = NULL;
    *output_file = NULL;

    while (args[i] != NULL)
    {
        if (strcmp(args[i], ">") == 0)
        {
            if (args[i + 1] == NULL)
            {
                printf("MiniShell: output file missing\n");
                _exit(1);
            }

            *output_file = args[i + 1];
        }
        else if (strcmp(args[i], "<") == 0)
        {
            if (args[i + 1] == NULL)
            {
                printf("MiniShell: input file missing\n");
                _exit(1);
            }

            *input_file = args[i + 1];
        }

        i++;
    }
}

void execute_external(char *args[])
{
    char *input_file;
    char *output_file;

    char *clean_args[MAX_ARGS];

    handle_redirection(args, &input_file, &output_file);

    int i = 0;
    int count = 0;

    while (args[i] != NULL)
    {
        if (strcmp(args[i], "<") == 0 || strcmp(args[i], ">") == 0)
        {
            i += 2;
        }
        else
        {
            clean_args[count] = args[i];
            count++;
            i++;
        }
    }

    if (clean_args[0] == NULL)
{
    printf("MiniShell: command missing\n");
    return;
}

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("MiniShell");
        return;
    }

    if (pid == 0)
    {
        if (input_file != NULL)
        {
            int fd = open(input_file, O_RDONLY);

            if (fd == -1)
            {
                perror("MiniShell");
                _exit(1);
            }

            dup2(fd, STDIN_FILENO);
            close(fd);
        }

        if (output_file != NULL)
        {
            int fd = open(output_file,
                          O_WRONLY | O_CREAT | O_TRUNC,
                          0644);

            if (fd == -1)
            {
                perror("MiniShell");
                _exit(1);
            }

            dup2(fd, STDOUT_FILENO);
            close(fd);
        }

        if (strcmp(clean_args[0], "echo") == 0)
        {
            handle_echo(clean_args);
        }
        else if (strcmp(clean_args[0], "cat") == 0)
        {
            handle_cat(clean_args);
        }
        else
        {
            execvp(clean_args[0], clean_args);

            perror("MiniShell");
        }

        _exit(1);
    }

    if (wait(NULL) == -1)
    {
        perror("MiniShell");
    }
}

void execute_pipe(char *args[], int pipe_index)
{
    int fd[2];

    if (pipe(fd) == -1)
    {
        perror("MiniShell");
        return;
    }

    pid_t pid1 = fork();

    if (pid1 < 0)
    {
        perror("MiniShell");
        return;
    }

    if (pid1 == 0)
    {
        dup2(fd[1], STDOUT_FILENO);

        close(fd[0]);
        close(fd[1]);

        execvp(args[0], args);

        perror("MiniShell");
        _exit(1);
    }

    pid_t pid2 = fork();

    if (pid2 < 0)
    {
        perror("MiniShell");
        return;
    }

    if (pid2 == 0)
    {
        dup2(fd[0], STDIN_FILENO);

        close(fd[0]);
        close(fd[1]);

        execvp(args[pipe_index + 1], &args[pipe_index + 1]);

        perror("MiniShell");
        _exit(1);
    }

    close(fd[0]);
    close(fd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
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

        int pipe_index = -1;

       for (int i = 0; args[i] != NULL; i++)
        {
          if (strcmp(args[i], "|") == 0)
           {
            pipe_index = i;
             args[i] = NULL;
             break;
            }
         }


        if (args[0] == NULL)
            continue;
         if (strcmp(args[0], "exit") == 0)
        {
            break;
        }
        if (strcmp(args[0], "cd") == 0)
        {
            handle_cd(args);
        }
        else if (strcmp(args[0], "pwd") == 0)
        {
            handle_pwd();
        }
        else
        {
           if (pipe_index != -1)
           {
               execute_pipe(args, pipe_index);
            }
            else
            {
                 execute_external(args);
             }
        }
    }

    return 0;
}