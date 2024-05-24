# Minishell

# Overview

Minishell is a project focused on creating a simple, custom shell similar to bash. 
It aims to provide a foundational understanding of processes, file descriptors, 
and basic shell functionalities. It is the first group project of the common core.

During this compact yet comprehensive project, I @pebencze was grateful to work 
together with Henni @henniphilo. We agreed on a main structure initially and split 
the project into two parts. Henni was working on the execution and the built-in commands
and I was responsible for the lexing, parsing and signal handling.

# Features
## Core Features

  - Prompt Display: Shows a prompt when waiting for user input.
  - Command History: Keeps a history of executed commands.
  - Executable Search: Finds and runs executables using the PATH 
   environment variable or given relative/absolute paths.
  - Signal Handling: Handles signals with minimal use of global variables.
  - Quoting: Correctly interprets single and double quotes in commands.
  - Redirections: Implements input (<), output (>), here-document (<<), 
    and append (>>) redirections.
  - Pipes: Supports piping (|) between commands.
  - Environment Variables: Expands environment variables and special parameters like $?.
  - Builtins: Implements built-in commands including echo, cd, pwd, export, unset, env, and exit.

## Interactive Mode

- Ctrl-C: Displays a new prompt on a new line.
- Ctrl-D: Exits the shell.
- Ctrl-\*: Does nothing.

## Memory Management

Ensures proper memory allocation and deallocation to prevent memory leaks, 
except for those caused by readline().

## Requirements

- Language: C
- Allowed External Functions: readline, rl_clear_history, rl_on_new_line,rl_replace_line,
rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close,
fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill,
exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir,
readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr,
tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
- Libft: Authorized to use the custom [libft](https://github.com/pebencze/Libft.git) library.

## Build and Run

 - Makefile: Includes rules for all, clean, fclean, re, and bonus.
 - Compilation: Ensure the code compiles without errors using the flags -Wall, -Wextra, and -Werror.
