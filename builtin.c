#include "shell.h"

/**
 * split_input - Splits a string into tokens.
 * @input: The input string to be split.
 *
 * Return: An array of pointers to the tokens.
 */
char **split_input(char *input)
{
	int buffer_size = BUFFER_SIZE;
	int position = 0;
	char **tokens = malloc(buffer_size * sizeof(char *));
	char *token, *save_ptr;

	if (!tokens)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, " \t\r\n\a\"", &save_ptr);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;
		if (position >= buffer_size)
		{
			buffer_size += BUFFER_SIZE;
			tokens = _realloc(tokens, buffer_size * sizeof(char *));
			if (!tokens)
			{
				perror("Memory allocation error");
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, " \t\r\n\a\"", &save_ptr);
	}
	tokens[position] = NULL;
	return (tokens);
}

/**
 * get_full_path - Returns the full path of a command.
 * @command: The command to find the full path for.
 * Return: A pointer to the full path string, or NULL if not found.
 */
char *get_full_path(const char *command)
{
	char *full_path = NULL;
	char *path_env, *path_copy, *save_ptr, *path_token;

	if (_strchr(command, '/') != NULL)
	{
		full_path = _strdup(command);
	} else
	{
		path_env = _getenv("PATH");
		path_copy = _strdup(path_env);
		path_token = _strtok(path_copy, ":", &save_ptr);

		while (path_token != NULL)
		{
			full_path = malloc(_strlen(path_token) + _strlen(command) + 2);
			if (full_path == NULL)
			{
				perror("Memory allocation error");
				exit(EXIT_FAILURE);
			}
			_strcpy(full_path, path_token);
			_strcat(full_path, "/");
			_strcat(full_path, command);

			if (access(full_path, X_OK) == 0)
			{
				break;
			}
			free(full_path);
			full_path = NULL;
			path_token = _strtok(NULL, ":", &save_ptr);
		}
		free(path_copy);
	}

	return (full_path);
}

/**
 * cmd_check - Checks and executes various built-in commands
 * or external programs.
 * @args: An array of command arguments.
 * @progname: The name of the program.
 */
void cmd_check(char **args, const char *progname)
{
	if (args[0] != NULL)
	{
		if (args[0][0] == '$')
		{
			handle_special_env(args[0] + 1, progname);
		}
		else if (_strcmp(args[0], "setenv") == 0)
		{
			handle_setenv(args);
		}
		else if (_strcmp(args[0], "unsetenv") == 0)
		{
			handle_unsetenv(args);
		}
		else if (_strcmp(args[0], "exit") == 0)
		{
			handle_exit(args);
		}
		else if (_strcmp(args[0], "echo") == 0)
		{
			execute_echo(args);
		}
		else
		{
			execute_command(args, progname);
		}
	}
}

/**
 * execute_external_command - Executes an external command.
 * @args: An array of command arguments.
 * @full_path: The full path of the command to execute.
 */
void execute_external_command(char **args, const char *full_path)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(full_path, args, environ) == -1)
		{
			perror("Error");
		}
		exit(EXIT_FAILURE);
	} else if (pid < 0)
	{
		perror("Error forking");
	} else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	free((char *)full_path);
}

/**
 * execute_command - Executes a command
 * either built-in or external.
 * @args: An array of command arguments.
 * @progname: The name of the program.
 */
void execute_command(char **args, const char *progname)
{
	char *command = args[0];
	char *full_path = get_full_path(command);

	if (full_path != NULL)
	{
		execute_external_command(args, full_path);
	} else
	{
		print_err(progname, "not found", args[0]);
	}
}
