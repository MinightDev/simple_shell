#include "shell.h"

/**
 * _strdup - Duplicates a string in memory.
 * @str: The string to duplicate.
 * Return: A pointer to the duplicated string.
 */
char *_strdup(const char *str)
{
	size_t length = _strlen(str);
	char *new_str = (char *)malloc((length + 1) * sizeof(char));

	if (new_str != NULL)
	{
		_strcpy(new_str, str);
	}

	return (new_str);
}

/**
 * _realloc - Reallocates memory for a pointer with a new size.
 * @ptr: Pointer to the memory to be reallocated.
 * @size: The new size of the memory.
 * Return: A pointer to the reallocated memory.
 */
void *_realloc(void *ptr, size_t size)
{
	size_t old_size, copy_size;
	void *new_ptr;

	if (ptr == NULL)
	{
		return (malloc(size));
	}
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(size);
	if (new_ptr != NULL)
	{
		old_size = _strlen((const char *)ptr);
		copy_size = old_size < size ? old_size : size;
		_strncpy((char *)new_ptr, (const char *)ptr, copy_size);
		free(ptr);
	}
	return (new_ptr);
}

/**
 * _memcpy - Copies memory from source to destination.
 * @dest: Destination memory.
 * @src: Source memory.
 * @n: Number of bytes to copy.
 */
void _memcpy(char *dest, const char *src, size_t n)
{
	while (n > 0)
	{
		*dest = *src;
		dest++;
		src++;
		n--;
	}
}

/**
 * free_memory - Frees memory allocated for
 * input and arguments.
 * @input: Input string memory.
 * @args: Array of argument strings.
 */
void free_memory(char *input, char **args)
{
	free(input);
	free(args);
}
