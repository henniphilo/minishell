#ifndef MESSAGES_H
# define MESSAGES_H

/* header file to specify error message macros */
# define COMMAND_ERR ": command not found"
# define ALLOC_ERR "error on memory allocation"
# define QUOTE_ERR "wrong input: unclosed quotes"
# define ARG_ERR "amount of arguments incorrect"
# define RL_ERR "error on reading the line"
# define LEX_ERR "error occured during lexing"
# define PARSE_ERR "error occured during parsing"
# define EXPAN_ERR "error occured during expansion"
# define EXEC_ERR "error occured during execution"
# define NL_ERR "minishell: syntax error near unexpected token `newline'"
# define SYNTAX_ERR "minishell: syntax error near unexpected token "
# define FILE_ERR "error creating file"
# define IDENT_ERR "minishell: export: no valid identifier"
# define DIR_ERR ": Is a directory"
# define PER_ERR ": Permission denied"

# define RDEND	0
# define WREND	1


#endif
