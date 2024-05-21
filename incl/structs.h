/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:56:15 by pbencze           #+#    #+#             */
/*   Updated: 2024/05/21 17:20:49 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>

/* token types for lexing and parsing */
typedef enum e_type {
	WORD,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND,
	PIPE
}	t_type;

/* types of quotes */
typedef enum e_quote {
	NONE,
	SINGLE,
	DOUBLE,
	HERE
}	t_quote;

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

//to store command nodes
typedef struct s_command {
	char				*cmd; // e.g. "ls", "echo", "cat", "pwd"
	char				**args; // things that come after the command e.g. pathname or string
	char				**argv; // command + args together of execve()
	int					fd_in; // fd for infiles and heredoc tmpfiles (-2 default)
	int					fd_out; // fd for outfiles and append (-2)
	t_redir				*redirs; // only used for parsing, not for execution
	struct s_command	*next;
}	t_command;

/*linked list of env variables*/
typedef struct s_environ {
	char				*name; //e.g. USER
	char				*value; //e.g. hwiemann
	struct s_environ	*next;
}	t_environ;

/* struct to store every data */
typedef struct s_data {
	char		*buf; // buffer to store the line read
	char		*home;
	char		**env; // 2Darray to store environmental variables
	t_environ	*env_list; // env variable list
	t_environ	*export_list; // list of exported env variables
	t_lexer		*tokens; // linked list of lexed tokens
	t_command	*toex; // toex is the input seperated by a pipe
	int			cmd_count;
	int			**fd; // pipes structure [[0,1],[0,1]...]
	bool		bi_check;
	pid_t		*pids;
	int			exit_status;
}	t_data;

#endif
