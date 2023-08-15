#include "shell.h"

/**
 * print_err - Prints an error message to the standard error stream.
 * @progname: The name of the program.
 * @message: The error message to be printed.
 * @cmd: The command associated with the error.
 */
void print_err(const char *progname, const char *message, const char *cmd)
{
	char *count_str = NULL;
	char *colon = ": ";
	char *newline = "\n";

	write(STDERR_FILENO, progname, _strlen(progname));
	write(STDERR_FILENO, colon, _strlen(colon));

	count_str = _itoa(1);
	write(STDERR_FILENO, count_str, _strlen(count_str));

	write(STDERR_FILENO, colon, _strlen(colon));
	write(STDERR_FILENO, cmd, _strlen(cmd));
	write(STDERR_FILENO, colon, _strlen(colon));
	write(STDERR_FILENO, message, _strlen(message));
	write(STDERR_FILENO, newline, _strlen(newline));
}

/**
 * print_custom_err - Prints a custom error message
 * to the standard error stream.
 * @message: The custom error message to be printed.
 */
void print_custom_err(const char *message)
{
	size_t len = _strlen(message);

	write(STDERR_FILENO, message, len);
}
