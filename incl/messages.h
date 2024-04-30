#ifndef MESSAGES_H
# define MESSAGES_H

/* header file to specify error message macros */
# define COMMAND_ERR ": command not found"
# define ALLOC_ERR "error on memory allocation"
# define ARG_ERR "amount of arguments incorrect"
# define RL_ERR "error on reading the line"
# define LEX_ERR "error occured during lexing"
# define PARSE_ERR "error occured during parsing"
# define NL_ERR "minishell: syntax error near unexpected token `newline'"
# define SYNTAX_ERR "minishell: syntax error near unexpected token "


/*macros to define builtins*/
# define ECHO "echo" // braucht es das?


#endif
