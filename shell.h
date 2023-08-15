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
void handle_setenv(char **args);
void handle_unsetenv(char **args);
bool _unsetenv(const char *name);
bool _setenv(const char *name, const char *value);
void print_custom_err(const char *message);
void _memmove(char *dest, const char *src, size_t n);
void _memcpy(char *dest, const char *src, size_t n);
int my_isalnum(int c);

#endif
