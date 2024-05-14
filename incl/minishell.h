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

char		*path_finder(char *cmd, t_data *shell);
void		child_process_env(char *toex, t_data *shell, int i);

void		env_execute(t_data *shell, char *arg);
int			count_commands(t_lexer *tokens);
void		print_path(char *path);

void		execute_one_envcmd(t_data *shell, pid_t pid);
void		execute_more_envcmd(t_data *shell, pid_t pid, int i);
void		print_toex(t_data *shell);
int			execute_shell(t_data *shell);
void		read_from_fd(int fd, const char *process);
//int			piping(t_data *shell);
int			**creating_pipes(t_data *shell);
int			exe_env(t_data *shell, pid_t *pids, int i, t_command *toex);
int			pipeline_exe(t_data *shell);



/*built-ins*/
void		which_builtin_parent(t_data *shell, char *arg);
void		print_env(t_environ *env_ptr);
int			builtin_check(char *arg);
int			which_builtin_child(t_data *shell, char *arg);
int			change_directory(t_data *shell);
void		bi_pwd(t_data *shell);
char		*find_in_env(char *to_find);
void		bi_exit(t_data *shell);
void		bi_unset(t_data *shell);
void		bi_export(t_data *shell);
void		bi_echo(t_data *shell);
void		export_env(t_data *shell);
void		echo_env(t_data *shell, char *str);
void		update_old_pwd(t_data *shell);
void		update_envlist(t_data *shell, char *to_up, char *new);
void		print_export_list(t_data *shell);
void		init_export_list(t_data *shell);
void		sort_export_list(t_data *shell);
void		to_export_list(t_data *shell);
t_environ	*list_duplicate(t_environ *lst_ptr);
t_environ	*replace_value(t_environ *list_ptr, char *replace);
t_environ	*find_name_in_envlist(t_data *shell, char *name);


/*Petra*/

/*read line*/
const char	*get_the_line(t_data *shell);
int			check_line(char *buf);

/*utils*/
int			array_len(char **ptr);
char		**free_arr(char **arr1, char **arr2);
char		**append_arr(char **arr, char *new_str);
int			check_syntax_and_here(t_lexer *tokens);

/*error*/
void		panic(char *str, void *ptr);
int			error_int(char *str);
void		*error_ptr(char *str);
void		*cmd_error_ptr(char *str);
int			infile_err_int(char *str);
int			synt_error_int(t_type type);
int			ambig_redir_err_int(char *str);

/*init*/
void		*init_env(t_data *shell, char **envp);
t_environ	*init_env_list(char **envp);
t_environ	*new_env_node(char *name, char *value);
t_environ	*env_list_last(t_environ *list);
void		add_env_back(t_environ **list, t_environ *node);

/*free*/
void		*free_data(t_data *shell);
void		clear_data(t_data *shell);
void		delone_tokens(t_lexer *token);
void		free_tokens(t_lexer **tokens);
void		delone_commands(t_command *cmds);
void		free_commands(t_command **cmds);
void		delone_redirs(t_redir *redirs);
void		free_redirs(t_redir **redirs);
void		delone_env_list(t_environ *env);
void		free_env_list(t_environ **env);
void		free_env(char **env);

/*lexer*/
int			lexer(t_data *shell);
void		lex_list_add_back(t_lexer **lst, t_lexer *new);
t_lexer		*lex_list_last(t_lexer *lst);
t_lexer		*new_lex_list(t_type t, char *s, bool sq, bool dq);
int			check_append(t_type *type, char *buf);
int			check_here(t_type *type, char *buf);
int			join_words(t_data *shell);
int			expand_env(t_lexer *tokens, t_data *shell);
char		*expand(t_lexer *tokens, char *dollar, char *limit, char *value);
int			ft_trim_last(t_lexer *tokens);
char		*find_limit(char *start);
int			expand_tilde(t_lexer *tokens, t_environ *env);
char		*expand_estatus(t_lexer *tokens, char *dollar, char *limit, int estatus);

/*parser*/
int			parser(t_data *shell);
t_command	*new_cmd_list(void);
t_command	*cmd_list_last(t_command *lst);
t_command	*create_cmdlist(t_lexer *tokens);
int			init_cmd_list(t_lexer *tokens, t_data *shell);
void		cmd_list_add_back(t_command **lst, t_command *new);
int			add_redir(t_lexer *tokens, t_command *toex);
int			handle_redirs(t_command *toex);

/*test*/
void	test(t_data *shell);

#endif
