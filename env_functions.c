#include "shell.h"

/**
 * _setenv - Sets a new environment variable or updates its value.
 * @name: The name of the environment variable.
 * @value: The value to assign to the environment variable.
 * Return: True if successful, false otherwise.
 */
bool _setenv(const char *name, const char *value)
{
	size_t name_length, value_length;
	char *new_entry;
	int env_index = 0;
	char **env;

	if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL)
	{
		print_custom_err("Invalid environment variable name.\n");
		return (false);
	}
	name_length = _strlen(name);
	value_length = value ? _strlen(value) : 0;
	new_entry = (char *)malloc(name_length + value_length + 2);
	if (new_entry == NULL)
	{
		print_custom_err("Memory allocation error.\n");
		return (false);
	}
	_strcpy(new_entry, name);
	if (value != NULL)
	{
		_strcat(new_entry, "=");
		_strcat(new_entry, value);
	}
	env = environ;
	while (*env != NULL)
	{
		if (_strncmp(name, *env, name_length) == 0 && (*env)[name_length] == '=')
		{
			free(*env);
			environ[env_index] = new_entry;
			return (true);
		}
		env++;
		env_index++;
	}
	environ[env_index] = new_entry;
	environ[env_index + 1] = NULL;
	return (true);
}

/**
 * _unsetenv - Removes an environment variable.
 * @name: The name of the environment variable to remove.
 * Return: True if successful, false otherwise.
 */
bool _unsetenv(const char *name)
{
	char **current, **env = environ;
	size_t name_length;

	if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL)
	{
		print_custom_err("Invalid environment variable name.\n");
		return (false);
	}
	name_length = _strlen(name);
	while (*env != NULL)
	{
		if (_strncmp(name, *env, name_length) == 0
				&& (*env)[name_length] == '=')
		{
			free(*env);
			current = env;
			while (*(current + 1) != NULL)
			{
				*current = *(current + 1);
				current++;
			}
			*current = NULL;
			return (true);
		}
		env++;
	}
	print_custom_err("Environment variable not found.\n");
	return (false);
}

/**
 * handle_setenv - Handles the "setenv" built-in command.
 * @args: An array of command arguments.
 */
void handle_setenv(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		print_custom_err("setenv VARIABLE VALUE\n");
		return;
	}
	if (_setenv(args[1], args[2]))
	{
		print_custom_err("Environment variable set.\n");
	}
}

/**
 * handle_unsetenv - Handles the "unsetenv" built-in command.
 * @args: An array of command arguments.
 */
void handle_unsetenv(char **args)
{
	if (args[1] == NULL || args[2] != NULL)
	{
		print_custom_err("unsetenv VARIABLE\n");
		return;
	}
	_unsetenv(args[1]);
}
