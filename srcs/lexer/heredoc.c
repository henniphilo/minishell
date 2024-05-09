#include "../../incl/minishell.h"

int	parse_heredoc(t_lexer *tokens, int fd)
{
	char	*buf;
	char	*line;

	buf = NULL;
	while (1)
	{
		//write(1, "> ", 2);
		//buf = get_next_line(0);
		buf = readline("> "); //replace with get_next_line!!
		if (!buf)
			return (error_int(ALLOC_ERR));
		if (ft_strcmp(buf, tokens->str) == 0)
		{
			free (buf);
			return (0);
		}
		//if (!(tokens->quote == HERE))
		//expand
		line = ft_strjoin(buf, "\n");
		free(buf);
		if (!line)
			return (error_int(ALLOC_ERR));
		write(fd, line, ft_strlen(line));
		free(line);
	}
	return (0);
}

int	handle_heredoc(t_lexer *tokens) //unlink in clear data
{
	int		fd;

	fd = open("tmp_file", O_RDWR | O_TRUNC | O_APPEND | O_CREAT, 0777);
	if (fd < 0)
		return (error_int(PARSE_ERR));
	if (parse_heredoc(tokens, fd))
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
