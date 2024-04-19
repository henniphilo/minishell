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
	ESTATUS,	// $?
	//BUILTIN //
	//ENV, // environment vars, but they will be handled probably differently
}	t_type;

typedef struct s_lexer {
	t_type			type;
	char			*str;
	bool			single_quote; //to store if '' was removed for $ expansion
	struct t_lexer	*previous;
	struct t_lexer	*next;
}	t_lexer;

//to store command nodes
typedef struct s_command {
	t_type	type;
	char	*cmd; //e.g. "ls", "echo", "cat", "pwd"
	char	**flags; //eg. -f -g
	char	**args; //things that come after the command e.g. pathname or string
	char	*filename; //for redirections

}	t_command;

/* typedef struct s_pipe {
	t_command	*left; //points to left side of pipe
	t_command	*right; //points to right side of pipe
}	t_pipe; */

//from chatgpt, not sure about keeping it
/* typedef struct s_heredoc {
	char	*delimiter;
	char	*input;	// Input associated with the here-doc
}	t_heredoc; */

//from chatgpt, not sure about keeping it
typedef struct s_environ {
	char	*name;
	char	*value;
}	t_environ;

typedef struct s_builtin {
	const char	*cd;
	const char	*echo;
	const char	*alias;
	const char	*export;
	const char	*unset;
	const char	*source;
	const char	*exit;
	const char	*env;
}	t_builtin; //struct ueberdenken bringt nicht so viel besser als macro?


//struct for execution, for Henni if she needs it
typedef struct s_exec {
	//variable for return value of processes
}	t_exec;

//struct to store important data we need initially and at execution adn all other structs
typedef struct s_data {
	char		*buf; //buffer to store the line read
	char		**env; //2Darray to store environmental variables
	t_lexer		*tokens; //linked list of lexed tokens
	t_command	**cmdlist; //linked list of commandlines between pipes that point to a struct of commands
	char		**arguments; // hen: to store all the input
	int			*fd; // hen: zum directen der fd muss noch richtig init werden
	t_builtin	*bi; // hen : zum tracken der builtins
}	t_data;

#endif
