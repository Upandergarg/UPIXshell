CC = gcc
CFLAGS = -Wall -Wextra -std=c11

minishell: src/main.c
	$(CC) $(CFLAGS) src/main.c -o minishell

clean:
	rm -f minishell