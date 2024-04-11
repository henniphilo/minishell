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
	t_type	type;
	char	*str;
	bool	single_quote; //to store if '' was removed for $ expansion
	t_lexer	*previous;
	t_lexer	*next;
}	t_lexer;

//to store command nodes
//??? maybe better to split into pipes, redirs and simple commands?
typedef struct s_command {
	t_type	type;
	char	*simple_cmd; //builtins and executables e.g. ls
	char	**args; //everything that comes after the command e.g. flags, strings

}	t_command;

//for redirections
//???maybe store it inside commands
typedef struct s_redir {
	t_type	type;
	char	*filename; //builtins and executables e.g. ls
}	t_redir;

typedef struct s_pipe {
	t_command	*left; //points to left side of pipe
	t_command	*right; //points to right side of pipe
}	t_pipe;

//from chatgpt, not sure about keeping it
typedef struct s_environ {
	char	*name;
	char	*value;
}	t_environ;

//from chatgpt, not sure about keeping it
typedef struct s_heredoc {
	char	*delimiter;
	char	*input;	// Input associated with the here-doc
}	t_heredoc;

//struct for execution, for Henni if she needs it
typedef struct s_exec {
	//variable for return value of processes
}	t_exec;

//struct to store important data we need initially and at execution adn all other structs
typedef struct s_data {
	char		*buf; //buffer to store the line read
	char		**env; //2Darray to store environmental variables
	t_command	*cmdlist; //linked list of parsed commands
}	t_data;

#endif
