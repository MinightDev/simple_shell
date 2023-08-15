#include "shell.h"

/**
 * _putchar - Writes a character to the standard output.
 * @c: The character to be written.
 */
void _putchar(char c)
{
	write(STDOUT_FILENO, &c, 1);
}

/**
 * _puts - Writes a string to the standard output followed by a newline.
 * @str: The string to be written.
 * Return: The number of characters written.
 */
int _puts(const char *str)
{
	int characters_written = 0;

	while (*str != '\0')
	{
		_putchar(*str);
		characters_written++;
		str++;
	}
	_putchar('\n');
	characters_written++;
	return (characters_written);
}

/**
 * _atoi - Converts a string to an integer.
 * @str: The string to be converted.
 * Return: The integer value.
 */
int _atoi(const char *str)
{
	int result = 0;
	int sign = 1;

	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
	{
		str++;
	}
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
		{
			sign = -1;
		}
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

/**
 * _strcat - Concatenates two strings.
 * @dest: The destination string.
 * @src: The source string to be appended.
 * Return: A pointer to the destination string.
 */
char *_strcat(char *dest, const char *src)
{
	char *original_dest = dest;

	while (*dest != '\0')
	{
		dest++;
	}
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (original_dest);
}
