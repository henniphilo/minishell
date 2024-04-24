#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "structs.h"
# include "messages.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>      // printf
# include <stdlib.h>     // malloc, free, exit
# include <unistd.h>     // write, access, fork, execve, dup, dup2, pipe, close, unlink, getpid, getcwd, chdir
# include <sys/wait.h>   // wait, waitpid, wait3, wait4
# include <signal.h>     // signal, sigaction, sigemptyset, sigaddset, kill
# include <errno.h>      // perror, strerror
# include <sys/types.h>  // stat, lstat, fstat, opendir, readdir, closedir
# include <sys/stat.h>   // stat, lstat, fstat
# include <fcntl.h>      // open
# include <dirent.h>     // opendir, readdir, closedir
# include <termios.h>    // tcsetattr, tcgetattr
# include <curses.h>     // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <sys/ioctl.h>  // ioctl
# include <string.h>     // strerror
# include <unistd.h>     // isatty, ttyname, ttyslot
# include <stdlib.h>     // getenv
# include <stddef.h>	 // Null

/*Henni*/
//const char	*read_the_line();
char		**split_input(const char *line);
char		**no_pipe(const char *line);
char		*path_finder(char *cmd, char **envp);
void		child_process_env(char *arg, t_data *shell, int i);
void		init_args(t_data *shell, char **split);
void		env_execute(t_data *shell, char *arg);
int			execute_shell(t_data *shell);
int			count_commands(t_data *shell);
int			builtin_check(char *arg);
void		when_builtin(t_data *shell);



/*Petra*/
const char	*get_the_line(t_data *data);
int			check_line(char *buf);
int			array_len(char **ptr);
void		panic(char *str, void *ptr);
int			error_int(char *str);
void		*init_env(t_data *data, char **envp);
void		*free_data(t_data *data);
void		clear_data(t_data *data);
void		delone_tokens(t_lexer *token);
void		free_tokens(t_lexer **tokens);
void		delone_env_list(t_environ *env);
void		free_env_list(t_environ **env);
void		free_env(char **env);
int			lexer(t_data *data);
t_environ	*new_env_node(char *name, char *value);
t_environ	*env_list_last(t_environ *list);
void		add_env_back(t_environ **list, t_environ *node);
t_environ	*init_env_list(char **envp);
void		lex_list_add_back(t_lexer **lst, t_lexer *new);
t_lexer		*lex_list_last(t_lexer *lst);
t_lexer		*new_lex_list(t_type t, char *s, bool q);
int			check_more(t_type *type, char *buf);
int			check_less(t_type *type, char *buf);
int			check_pipe(char *buf);






#endif
