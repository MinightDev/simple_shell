#include "shell.h"

/**
 * main - Entry point of the shell program
 * @argc: Number of command-line arguments
 * @argv: Array of command-line arguments
 *
 * Return: EXIT_SUCCESS upon successful completion
 */
int main(int argc, char *argv[])
{
	char *input, **args, *progname = argv[0];
	int interactive = isatty(STDIN_FILENO);

	(void)argc;
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		if (interactive)
		{
			write(STDOUT_FILENO, "$ ", 2);
			fflush(stdout);
		}
		input = read_line();
		if (input == NULL)
		{
			if (interactive)
			{
				write(STDOUT_FILENO, "\n", 1);
			}
			free(input);
			break;
		}
		args = split_input(input);
		cmd_check(args, progname);
		free_memory(input, args);
	}
	return (EXIT_SUCCESS);
}
