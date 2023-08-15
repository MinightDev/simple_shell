# Custom Shell

A custom shell implemented in C that supports executing commands, handling environment variables, and built-in commands like `setenv`, `unsetenv`, `exit`, and `echo`. It provides a basic interactive shell interface where you can enter commands and receive output.

## Features

- Execute external commands and handle built-in commands.
- Environment variable management with `setenv` and `unsetenv` commands.
- Handle special environment variables like `$?` and `$$`.
- Replace environment variables in strings using the `$` syntax.
- Basic error handling and memory management.


## Usage

The custom shell supports basic shell commands and built-in commands. You can execute external commands and use the built-in commands by typing them into the shell.

Example of built-in commands:
- `echo [text]`: Display text to the console.
- `setenv [variable] [value]`: Set or update an environment variable.
- `unsetenv [variable]`: Remove an environment variable.
- `exit [status]`: Exit the shell with an optional status code.

To execute external commands, simply type the command name followed by any required arguments.

## Notes

- Built-in commands are handled within the shell program.
- Environment variable expansion is supported using `$VARNAME` syntax.

Feel free to explore this custom shell implementation according to your needs!


