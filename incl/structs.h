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
	PIPE,		// |
	//ESTATUS,	// $?
	//ENV, // environment vars, but they will be handled probably differently
}	t_type;

typedef struct s_lexer {
	t_type			type;
	char			*str;
	bool			single_quote; //to store if '' was removed for $ expansion
	bool			space_after; //to check if a space follows the quoted word e.g. 'l's vs. 'l' s
	struct s_lexer	*previous;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_redir {
	t_type	type; //HERE, APPEND, IN, OUT
	char	*file; //int fd;
	//char *heredoc;
} t_redir;

//to store command nodes
typedef struct s_command {
	t_type				type; //IN, OUT, HERE, WORD, APPEND
	char				*cmd; //e.g. "ls", "echo", "cat", "pwd"
	char				**args; //things that come after the command e.g. pathname or string
	//char				**flags; //eg. -f -g
	t_redir				*redirs;
	struct s_command	*next;
}	t_command;

//from chatgpt, not sure about keeping it
/* typedef struct s_heredoc {
	char	*delimiter;
	char	*input;	// Input associated with the here-doc
}	t_heredoc; */

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
	t_lexer		*tokens; //linked list of lexed tokens
	t_command	*toex; //hen: to execute as replacement for cmds arg confusion, toex is the input seperated by a pipe
	int			estatus; //for exit status of last pipe to store for the next prompt
	int			*fd; // hen: zum directen der fd muss noch richtig init werden
	bool		bi_check; //hen: built_in check
//	pid_t		*pid; //process id, evt als array fuer individuelle prozess? - doch nicht
	int			cmd_count; // wird von petra upgedatet in pipe count
	char		***pipeline; //hen: 3d array was auf die auszufuehrenden toex zeigt
}	t_data;

#endif
