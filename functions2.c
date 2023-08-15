#include "shell.h"

/**
 * _memmove - Copies a block of memory from source to destination.
 * @dest: Pointer to the destination buffer.
 * @src: Pointer to the source buffer.
 * @n: Number of bytes to copy.
 */
void _memmove(char *dest, const char *src, size_t n)
{
	if (dest > src)
	{
		dest += n - 1;
		src += n - 1;
		while (n > 0)
		{
			*dest = *src;
			dest--;
			src--;
			n--;
		}
	}
	else if (dest < src)
	{
		while (n > 0)
		{
			*dest = *src;
			dest++;
			src++;
			n--;
		}
	}
}

/**
 * _itoa - Converts an integer to a string.
 * @num: The integer to be converted.
 * Return: A pointer to the converted string.
 */
char *_itoa(int num)
{
	static char str[12];
	int i = 0, j = 0, k = 0, l = 0, m = 0;

	if (num == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	if (num < 0)
	{
		l = 1;
		num = -num;
	}
	m = num;
	while (m != 0)
	{
		m /= 10;
		i++;
	}
	j = i - 1 + l;

	if (l == 1)
		str[0] = '-';

	for (; j >= l; j--)
	{
		k = num % 10;
		str[j] = k + '0';
		num /= 10;
	}
	str[i + l] = '\0';
	return (str);
}
