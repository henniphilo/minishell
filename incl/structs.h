/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:56:15 by pbencze           #+#    #+#             */
/*   Updated: 2024/05/23 16:11:51 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>

/*token types for lexing and parsing*/
typedef enum e_type {
	WORD,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND,
	PIPE
}	t_type;

/*types of quotes*/
typedef enum e_quote {
	NONE,
	SINGLE,
	DOUBLE,
	HERE
}	t_quote;

/*the srtuct used during lexing*/
typedef struct s_lexer {
	t_type			type;
	char			*str;
	t_quote			quote;
	bool			space_after;
	char			*ambig_redir;
	struct s_lexer	*previous;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_redir {
	t_type			type;
	char			*file;
	char			*ambig_redir;
	struct s_redir	*next;
}	t_redir;

/*struct to store the pipes split into commands, arguments,
both together (argv) and filedescriptors for redirections
- infiles and outfiles; the t_redir struct is only used during parsing*/
typedef struct s_command {
	char				*cmd;
	char				**args;
	char				**argv;
	int					fd_in;
	int					fd_out;
	t_redir				*redirs;
	struct s_command	*next;
}	t_command;

/*linked list of environment variables*/
typedef struct s_environ {
	char				*name;
	char				*value;
	struct s_environ	*next;
}	t_environ;

/*struct to store every data: buffer to store the line read,
 2D-array to store the environment variables and a linked list to
 store them and allow more flexibility, a linked list of tokens,
 a linked liost of pipes, the number of pipes, filedescriptors
 for the pipes and process ids*/
typedef struct s_data {
	char		*buf;
	char		*home;
	char		*pwd;
	char		**env;
	t_environ	*env_list;
	t_environ	*export_list;
	t_lexer		*tokens;
	t_command	*toex;
	int			cmd_count;
	int			**fd;
	bool		bi_check;
	pid_t		*pids;
}	t_data;

#endif
