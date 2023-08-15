#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <ctype.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024

extern char **environ;

void free_memory(char *input, char **args);
char **split_input(char *input);
char *read_line(void);
void execute_command(char **args, const char *progname);
void handle_exit(char **args);
void handle_env();
char *_getenv(const char *name);
void handle_special_env(const char *name, const char *progname);
char *get_full_path(const char *command);
void execute_external_command(char **args, const char *full_path);
void execute_command(char **args, const char *progname);
void cmd_check(char **args, const char *progname);
void print_err(const char *progname, const char *message, const char *cmd);
char *_strtok(char *str, const char *delim, char **save_ptr);
void replace_env_vars(char *input);
char* get_env_var_value(const char *var_name);
void replace_env_var(char **start, const char *var_value, char *end);
void execute_echo(char **args);
int my_getchar(void);
size_t _strlen(const char *str) ;
char *_strchr(const char *str, int c);
char *_strcpy(char *dest, const char *src);
char *_strncpy(char *dest, const char *src, size_t n);
int _strncmp(const char *s1, const char *s2, size_t n);
int _strcmp(const char *s1, const char *s2);
void *_realloc(void *ptr, size_t size);
char *_strdup(const char *str);
char *_strcat(char *dest, const char *src);
int _atoi(const char *str);
int _puts(const char *str);
void _putchar(char c);
char *_itoa(int num);
bool _unsetenv(const char *name);
bool _setenv(const char *name, const char *value);
void print_custom_err(const char *message);
void _memmove(char *dest, const char *src, size_t n);
void _memcpy(char *dest, const char *src, size_t n);
int my_isalnum(int c);
int exit_status = 0;

#endif

bool _setenv(const char *name, const char *value)
{
     size_t name_length, value_length;
     char *new_entry;
     int env_index = 0;
     char **env;
     
    if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL)
    {
        print_custom_err("Invalid environment variable name.\n");
        return false;
    }
    name_length = _strlen(name);
    value_length = value ? _strlen(value) : 0;

    new_entry = (char *)malloc(name_length + value_length + 2);
    if (new_entry == NULL)
    {
        print_custom_err("Memory allocation error.\n");
        return false;
    }
    _strcpy(new_entry, name);
    if (value != NULL) {
        _strcat(new_entry, "=");
        _strcat(new_entry, value);
    }

    env = environ;
    while (*env != NULL) {
        if (_strncmp(name, *env, name_length) == 0 && (*env)[name_length] == '=')
        {
            free(*env);
            environ[env_index] = new_entry;
            return true;
        }
        env++;
        env_index++;
    }

    environ[env_index] = new_entry;
    environ[env_index + 1] = NULL;
    return true;
}

bool _unsetenv(const char *name) 
{
    char **current, **env = environ;
    size_t name_length;

    if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL) 
    {
        print_custom_err("Invalid environment variable name.\n");
        return false;
    }
    name_length = _strlen(name);

    while (*env != NULL) 
    {
        if (_strncmp(name, *env, name_length) == 0 && (*env)[name_length] == '=') 
        {
            free(*env);
            current = env;
            while (*(current + 1) != NULL) 
            {
                *current = *(current + 1);
                current++;
            }
            *current = NULL;

            return true;
        }
        env++;
    }
    
    print_custom_err("Environment variable not found.\n");
    return false;
}


void handle_setenv(char **args)
{
    if (args[1] == NULL || args[2] == NULL) 
    {
        print_custom_err("Usage: setenv VARIABLE VALUE\n");
        return;
    }

    if (_setenv(args[1], args[2])) 
    {
        print_custom_err("Environment variable set.\n");
    }
}

void handle_unsetenv(char **args) {
    if (args[1] == NULL || args[2] != NULL) {
        print_custom_err("Usage: unsetenv VARIABLE\n");
        return;
    }

    _unsetenv(args[1]);
}
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
void print_custom_err(const char *message)
{
    size_t len = _strlen(message);
    write(STDERR_FILENO, message, len);
}

char *_itoa(int num)
{
    static char str[12];
    int i = 0, j = 0, k = 0, l = 0, m = 0;
    if (num == 0)
    {
        str[0] = '0';
        str[1] = '\0';
        return str;
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
    return str;
}

void _putchar(char c) 
{
    write(STDOUT_FILENO, &c, 1);
}

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

    return characters_written;
}

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
    return original_dest;
}

char *_strdup(const char *str) 
{
    size_t length = _strlen(str);
    char *new_str = (char *)malloc((length + 1) * sizeof(char));

    if (new_str != NULL) 
    {
        _strcpy(new_str, str);
    }

    return new_str;
}

void *_realloc(void *ptr, size_t size) 
{
    size_t old_size, copy_size;
    void *new_ptr;
    
    if (ptr == NULL) 
    {
        return malloc(size);
    }

    if (size == 0) 
    {
        free(ptr);
        return NULL;
    }

    new_ptr = malloc(size);
    if (new_ptr != NULL) 
    {
        old_size = _strlen((const char *)ptr);
        copy_size = old_size < size ? old_size : size;
        _strncpy((char *)new_ptr, (const char *)ptr, copy_size);
        free(ptr);
    }
    
    return new_ptr;
}


int _strcmp(const char *s1, const char *s2) 
{
    while (*s1 != '\0' || *s2 != '\0') 
    {
        if (*s1 != *s2) 
        {
            return (*s1 - *s2);
        }
        s1++;
        s2++;
    }

    return 0;
}

int _strncmp(const char *s1, const char *s2, size_t n) 
{
    while (n > 0 && (*s1 != '\0' || *s2 != '\0')) 
    {
        if (*s1 != *s2) 
        {
            return (*s1 - *s2);
        }
        s1++;
        s2++;
        n--;
    }
    return 0;
}


char *_strncpy(char *dest, const char *src, size_t n) 
{
    char *original_dest = dest;

    while (n > 0 && *src != '\0') 
    {
        *dest = *src;
        dest++;
        src++;
        n--;
    }
    while (n > 0) 
    {
        *dest = '\0';
        dest++;
        n--;
    }

    return original_dest;
}

char *_strcpy(char *dest, const char *src) 
{
    char *original_dest = dest;
    while (*src != '\0') 
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return original_dest;
}

size_t _strlen(const char *str)
{
    size_t len = 0;
    
    while (str[len] != '\0')
    {
        len++;
    }
    return len;
}

char *_strchr(const char *str, int c) 
{
    while (*str != '\0') 
    {
        if (*str == c) 
        {
            return (char *)str;
        }
        str++;
    }

    return NULL;
}

int my_getchar(void)
{
    static char buf[BUFSIZ];
    static char *bufp = buf;
    static ssize_t n = 0;

    if (n == 0) {
        n = read(STDIN_FILENO, buf, sizeof(buf));
        bufp = buf;
    }

    if (n <= 0) {
        return EOF;
    }

    n--;
    return (unsigned char) *bufp++;
}

int my_isalnum(int c) 
{
    return (c >= 'A' && c <= 'Z') 
    || (c >= 'a' && c <= 'z') 
    || (c >= '0' && c <= '9') 
    || (c == '?');
}

char* get_env_var_value(const char *var_name)
{
    char *var_value = NULL;

    if (var_name[0] == '?')
    {
        var_value = _itoa(exit_status);
    }
    else if (var_name[0] == '$')
    {
        var_value = _itoa(getpid());
    }
    else
    {
        var_value = _getenv(var_name);
    }

    return var_value;
}

void replace_env_var(char **start, const char *var_value, char *end)
{
    size_t var_value_length = _strlen(var_value);
    size_t remaining_length = _strlen(end);
    _memmove(*start + var_value_length, end, remaining_length + 1);
    _memcpy(*start, var_value, var_value_length);
    *start += var_value_length;
}

void replace_env_vars(char *input)
{
    char *start = input;
    char *end = input;
    char *dollar_sign, *var_name, *var_value;

    while ((dollar_sign = strchr(start, '$')) != NULL)
    {
        end = dollar_sign;
        while (*end != '\0' && (*end == '$' || my_isalnum(*end) || *end == '_'))
        {
            end++;
        }
        if (end > dollar_sign + 1)
        {
            var_name = dollar_sign + 1;
            var_value = get_env_var_value(var_name);

            if (var_value != NULL)
            {
                replace_env_var(&start, var_value, end);
            }
            else
            {
                start = end;
            }
        }
        else
        {
            start = end;
        }
    }
}




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
        return NULL;
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

    return start;
}

void handle_special_env(const char *name, const char *progname)
{
    char *value = _getenv(name);
    if (value != NULL)
    {
        _puts(value);
    }
    else
    {
        print_err(progname, "not found", name);
    }
}


char *_getenv(const char *name)
{
    extern char **environ;
    size_t name_len = _strlen(name);
    char **env;
    
    if (name == NULL || *name == '\0') {
        return NULL;
    }
    for (env = environ; *env != NULL; env++)
    {
        if (_strncmp(name, *env, name_len) == 0 && (*env)[name_len] == '=') 
        {
            return *env + name_len + 1;
        }
    }
    return NULL;
}
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
    while (token != NULL) {
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
    return tokens;
}

void free_memory(char *input, char **args)
{
    free(input);
    free(args);
}

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

    return full_path;
}

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


void execute_external_command(char **args, const char *full_path)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        if (execve(full_path, args, environ) == -1) 
        {
            perror("Error");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("Error forking");
    } else {
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    exit_status = WEXITSTATUS(status);

    free((char *)full_path);
}

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
    return EXIT_SUCCESS;
}



void handle_exit(char **args)
{
    if (args[1] != NULL)
    {
        int exit_status = _atoi(args[1]);
        exit(exit_status);
    }
    else
    {
        exit(EXIT_SUCCESS);
    }
}

void handle_env()
{
    char **env = environ;
    int i = 0;

    while (env[i] != NULL) 
    {
        _puts(env[i]);
        i++;
    }
}

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
    while (1) {
        c = my_getchar();

        if (c == EOF || c == '\n') {
            if (c == EOF && position == 0) {
                free(buffer);
                return NULL;
            }
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
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
