# Minishell
```
Run with:
make
```
## Description
This is a custom shell implementation written in C, designed to mimic the basic functionalities of a Unix-like shell. It provides a prompt for users to enter commands and executes them accordingly. The shell supports various features including history, redirections, pipes, environment variables, signal handling, and built-in commands.

## Features
Prompt: Displays a prompt for users to input commands.

History: Maintains a working history of previously executed commands.

Executable Launch: Searches and launches the correct executable based on the PATH variable or using relative/absolute paths.

Signal Handling: Utilizes a single global variable to indicate a received signal, ensuring signal handlers do not access main data structures.

Quoting: Handles single and double quotes to prevent interpretation of metacharacters.

## Redirections:

**```<: Redirects input.```**

**```>: Redirects output.```**

**```<<: Reads input until a specified delimiter is seen.```**

**```>>: Redirects output in append mode.```**

**Pipes (|)**: Connects the output of one command to the input of the next command via a pipe.
**Environment Variables**: Handles expansion of environment variables ($ followed by a sequence of characters) to their values.
**Exit Status ($?)**: Expands to the exit status of the most recently executed foreground pipeline.

## Signal Handling:

**```ctrl-C: Displays a new prompt on a new line in interactive mode.```**

**```ctrl-D: Exits the shell.```**

**```ctrl-\: No action.```**

## Built-in Commands:
**```echo: Supports option -n.```**

**```cd: Supports only relative or absolute paths.```**

**```pwd: No options.```**

**```export: No options.```**

**```unset: No options.```**

**```env: No options or arguments.```**

**```exit: No options.```**

## Usage:

**Compile**: Compile the shell program using a C compiler (e.g., gcc).

**Run**: Execute the compiled program to start the custom shell.

**Enter Commands**: Use the prompt to input commands. Execute built-in commands or external executables with appropriate options.

**Exit**: To exit the shell, use the exit command or press ctrl-D.

## Limitations
**Memory Leaks**: The readline() function may cause memory leaks, but efforts have been made to ensure the custom code does not contain memory leaks.

## Notes
This shell implementation adheres to the specified requirements and aims to provide a basic interactive shell experience similar to Unix-like shells.
Additional features or enhancements can be implemented based on specific requirements or preferences.
haha
