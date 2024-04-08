#ifndef STRUCTS_H
# define STRUCTS_H



typedef enum s_token {
	WORD, //commands, words, flags?
	INPUT, //<
	OUTPUT, //>
	HEREDOC, // <<
	APPEND, // >>
	PIPE, // |
	WSPACE, //white space
	ESTATUS, //$?
	//ENV, //environment vars, but they will be handled probably differently
}	t_token;

typedef struct s_data {
	char	*buf;
	char	**env;
}	t_data;



#endif
