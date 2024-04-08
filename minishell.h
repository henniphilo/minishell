#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "readline/readline.h"
# include "readline/history.h"
# include <stdio.h>      // Für printf
# include <stdlib.h>     // Für malloc, free, exit
# include <unistd.h>     // Für write, access, fork, execve, dup, dup2, pipe, close, unlink, getpid, getcwd, chdir
# include <sys/wait.h>   // Für wait, waitpid, wait3, wait4
# include <signal.h>     // Für signal, sigaction, sigemptyset, sigaddset, kill
# include <errno.h>      // Für perror, strerror
# include <sys/types.h>  // Für stat, lstat, fstat, opendir, readdir, closedir
# include <sys/stat.h>   // Für stat, lstat, fstat
# include <fcntl.h>      // Für open
# include <dirent.h>     // Für opendir, readdir, closedir
# include <termios.h>    // Für tcsetattr, tcgetattr
# include <curses.h>     // Für tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <sys/ioctl.h>  // Für ioctl
# include <string.h>     // Für strerror
# include <unistd.h>     // Für isatty, ttyname, ttyslot
# include <stdlib.h>     // Für getenv
# include <stddef.h>	 // Für Null

char	**split_input(const char *line);
const char	*read_the_line();



# endif
