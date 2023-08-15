#include "shell.h"

/**
 * _strtok - Breaks a string into a sequence of tokens.
 * @str: The string to be tokenized.
 * @delim: The delimiter characters used to tokenize the string.
 * @save_ptr: A pointer to a pointer to save the current position.
 * Return: A pointer to the next token found, or NULL if no more tokens.
 */
char *_strtok(char *str, const char *delim, char **save_ptr)
{
	char *start, *end;

	if (str == NULL)
	{
		str = *save_ptr;
	}
	start = str;
	while (*start != '\0' && _strchr(delim, *start) != NULL)
	{
		start++;
	}
	if (*start == '\0')
	{
		*save_ptr = start;
		return (NULL);
	}
	end = start + 1;
	while (*end != '\0' && _strchr(delim, *end) == NULL)
	{
		end++;
	}
	if (*end != '\0')
	{
		*end = '\0';
		*save_ptr = end + 1;
	}
	else
	{
		*save_ptr = end;
	}
	return (start);
}

/**
 * _strchr - Locates the first occurrence of a character in a string.
 * @str: The string to be searched.
 * @c: The character to be located.
 * Return: A pointer to the first occurrence of the character,
 * or NULL if not found.
 */
char *_strchr(const char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == c)
		{
			return ((char *)str);
		}
		str++;
	}
	return (NULL);
}

/**
 * my_getchar - Reads a character from standard input.
 * Return: The character read from input,
 * or EOF if end-of-file is reached.
 */
int my_getchar(void)
{
	static char buf[BUFSIZ];
	static char *bufp = buf;
	static ssize_t n;

	if (n == 0)
	{
		n = read(STDIN_FILENO, buf, sizeof(buf));
		bufp = buf;
	}
	if (n <= 0)
	{
		return (EOF);
	}
	n--;
	return ((unsigned char) *bufp++);
}

/**
 * my_isalnum - Checks if a character is alphanumeric or '?'.
 * @c: The character to be checked.
 * Return: 1 if the character is alphanumeric or '?', 0 otherwise.
 */
int my_isalnum(int c)
{
	return ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9')
		|| (c == '?'));
}
