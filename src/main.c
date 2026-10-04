#include <stdio.h>

int main(void)
{
    char command[100];

    printf("==============================\n");
    printf("          MiniShell\n");
    printf("==============================\n");

    while (1)
    {
        printf("MiniShell$ ");

        fgets(command, 100, stdin);

        printf("You entered: %s", command);
    }

    return 0;
}