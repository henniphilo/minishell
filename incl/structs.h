#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h> //for booleans

//token types for lexing and parsing
typedef enum e_type {
	WORD,		// commands, words, flags
	INPUT,		// <
	OUTPUT,		// >
	HEREDOC,	// <<
	APPEND,		// >>
	PIPE		// |
}	t_type;

typedef enum e_quote {
	NONE,
	SINGLE, //'ab'
	DOUBLE, //"ab"
	HERE // << a'b'
}	t_quote;

typedef struct s_lexer {
	t_type			type;
	char			*str;
	t_quote			quote;
	bool			space_after; //to check if a space follows the quoted word e.g. 'l's vs. 'l' s
	char			*ambig_redir;
	struct s_lexer	*previous;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_redir {
	t_type			type; //HERE, APPEND, IN, OUT
	char			*file; //or int fd;
	char			*ambig_redir;
	struct s_redir	*next;
	//char *heredoc;
} t_redir;

//to store command nodes
typedef struct s_command {
	char				*cmd; //e.g. "ls", "echo", "cat", "pwd"
	char				**args; //things that come after the command e.g. pathname or string
	char				**argv; //command + args together of execve()
	int					fd_in; //fd for infiles (and maybe heredoc tmpfiles)
	int					fd_out; //fd for outfiles and append
	t_redir				*redirs; //only used for parsing, not for execution
	struct s_command	*next;
}	t_command;

/*linked list of env variables*/
typedef struct s_environ {
	char				*name; //e.g. USER
	char				*value; //e.g. hwiemann
	struct s_environ	*next;
}	t_environ;

//struct to store important data we need initially and at execution adn all other structs
typedef struct s_data {
	char		*buf; //buffer to store the line read
	char		**env; //2Darray to store environmental variables
	t_environ	*env_list;
	t_environ	*export_list; //hen: Liste von Umgebungsvariablen die auch nicht deklarierte Export Variablen enhalten
	t_lexer		*tokens; //linked list of lexed tokens
	t_command	*toex; //hen: to execute as replacement for cmds arg confusion, toex is the input seperated by a pipe
	int			estatus; //for exit status of last pipe to store for the next prompt
	int			cmd_count; // wird von petra upgedatet in pipe count
	int			**fd; //= pipes structure [[0,1],[0,1]...] hen: zum directen der fd muss noch richtig init werde
	bool		bi_check; //hen: built_in check - brauch ich nicht
	pid_t		*pids;

//	pid_t		*pid; //process id, evt als array fuer individuelle prozess? - doch nicht
}	t_data;

#endif
