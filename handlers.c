#include "shell.h"

/**
 * execute_echo - Implements the 'echo' built-in command.
 * @args: Array of command arguments.
 */
void execute_echo(char **args)
{
	if (args[1] != NULL)
	{
		char *output = args[1];

		replace_env_vars(output);
		_puts(output);
	}
	else
	{
		_putchar('\n');
	}
}

/**
 * handle_exit - Handles the 'exit' built-in command.
 * @args: Array of command arguments.
 */
void handle_exit(char **args)
{
	int exit_stat;

	if (args[1] != NULL)
	{
		exit_stat = _atoi(args[1]);
		exit(exit_stat);
	}
	else
	{
		exit(0);
	}
}

/**
 * handle_env - Handles the 'env' built-in command.
 */
void handle_env(void)
{
	char **env = environ;
	int i = 0;

	while (env[i] != NULL)
	{
		_puts(env[i]);
		i++;
	}
}

/**
 * read_line - Reads a line of input from the user.
 * Return: A pointer to the input line.
 */
char *read_line(void)
{
	int buffer_size = BUFFER_SIZE;
	int position = 0;
	char *buffer = malloc(buffer_size * sizeof(char));
	int c;

	if (!buffer)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		c = my_getchar();

		if (c == EOF || c == '\n')
		{
			if (c == EOF && position == 0)
			{
				free(buffer);
				return (NULL);
			}
			buffer[position] = '\0';
			return (buffer);
		}
		buffer[position] = c;
		position++;
		if (position >= buffer_size)
		{
			buffer_size += BUFFER_SIZE;
			buffer = _realloc(buffer, buffer_size * sizeof(char));
			if (!buffer)
			{
				perror("Memory allocation error");
				exit(EXIT_FAILURE);
			}
		}
	}
}
