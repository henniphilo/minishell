#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h> //for booleans

//token types for lexing and parsing
typedef enum e_type {
	WORD,		// commands, words, flags?
	INPUT,		// <
	OUTPUT,		// >
	HEREDOC,	// <<
	APPEND,		// >>
	PIPE,		// |
	//ESTATUS,	// $?
	//BUILTIN //
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


//to store command nodes
typedef struct s_command {
	t_type				type; //IN, OUT, HERE, WORD, APPEND
	char				*cmd; //e.g. "ls", "echo", "cat", "pwd"
	char				**args; //things that come after the command e.g. pathname or string
	//char				**flags; //eg. -f -g
	//char				*infile; //for redirections e.g. 'filename' < echo
	//char				*outfile; //for redirections e.g. echo hi > 'filename'
	struct s_command	*next;
}	t_command;

/* typedef struct s_redir {
	char	*infile;
	char	*outfile;
	t_type	type;
} t_redir; */

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
	t_command	*commands; //linked list of commandlines between pipes that point to a struct of commands
	int			estatus; //for exit status of last pipe to store for the next prompt
	char		**arguments; // hen: to store all the input
	int			*fd; // hen: zum directen der fd muss noch richtig init werden
//	t_builtin	*bi; // hen : zum tracken der builtins
	bool		bi_check;
//	pid_t		*pid; //process id, evt als array fuer individuelle prozess? - doch nicht
	int			cmd_count;
//	char		**cmds;
	char		***pipeline; //hen: 3d array was auf die auszufuehrenden toex zeigt
	char		**toex; //hen: to execute as replacement for cmds arg confusion, toex is the input seperated by a pipe
}	t_data;

#endif
