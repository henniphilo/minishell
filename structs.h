#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum s_token {
	WORD,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND,
	PIPE,
	WSPACE
}	t_token;

typedef struct s_data {
	char	*buf;
	char	**env;
}	t_data;



#endif
