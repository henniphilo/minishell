#include "../../incl/minishell.h"

static int	expand_heredoc(t_lexer *tokens, t_data *shell)
{
	char	*line;

	line = ft_strjoin(tokens->str, "\n");
	free(tokens->str);
	tokens->str = line;
	if (!tokens->str)
		return (1);
	if (!(tokens->quote == HERE))
	{
		if (find_and_replace(tokens, shell))
			return (1);
	}
	return (0);
}

static int	return_and_free( char *str)
{
	free(str);
	return (0);
}

int	parse_heredoc(t_lexer *tokens, int fd, t_data *shell)
{
	char	*delimiter;
	int		linenum;

	delimiter = ft_strdup(tokens->str);
	if (!delimiter)
		return (error_int(ALLOC_ERR));
	free(tokens->str);
	linenum = 0;
	signal(SIGINT, here_sig_handler);
	while (g_estatus != 148)
	{
		//write(0, "> ", 2);
		//tokens->str = get_next_line(0);
		tokens->str = readline("> ");
		if (!tokens->str)
			return (eof_error(delimiter, linenum));
		linenum++;
		if (ft_strcmp(tokens->str, delimiter) == 0)
			return (return_and_free(delimiter));
		if (expand_heredoc(tokens, shell))
		{
			free(delimiter);
			return (error_int(ALLOC_ERR));
		}
		write(fd, tokens->str, ft_strlen(tokens->str));
		free(tokens->str);
		tokens->str = NULL;
	}
	return (return_and_free(delimiter));
}

int	handle_heredoc(t_lexer *tokens, t_data *shell)
{
	int		fd;

	fd = open("tmp_file", O_RDWR | O_TRUNC | O_APPEND | O_CREAT, 0777);
	if (fd < 0)
		return (error_int(PARSE_ERR));
	if (parse_heredoc(tokens, fd, shell))
	{
		close(fd);
		return (1);
	}
	close(fd);
	free(tokens->str);
	tokens->str = ft_strdup("tmp_file");
	if (!tokens->str)
		return (error_int(ALLOC_ERR));
	return (0);
}
