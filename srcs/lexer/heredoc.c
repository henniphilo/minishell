#include "../../incl/minishell.h"

int	parse_heredoc(t_lexer *tokens, int fd)
{
	char	*buf;
	char	*line;

	buf = NULL;
	while (ft_strcmp(buf, tokens->str) != 0)
	{
		write(1, "> ", 2);
		if (buf)
		{
			line = ft_strjoin(buf, "\n");
			free(buf);
			if (!line)
				return (error_int(ALLOC_ERR));
			write(fd, buf, ft_strlen(buf));
			free(line);
		}
		buf = get_next_line(0);
		if (!buf)
			return (error_int(ALLOC_ERR));
	}
	return (0);
}

int	handle_heredoc(t_lexer *tokens) //unlink in clear data
{
	char	*tmp_file;
	int		fd;

	fd = open(tmp_file, O_APPEND | O_RDWR | O_TRUNC, 0777);
	if (fd < 0)
		return (error_int(FILE_ERR));
	if (!parse_heredoc(tokens->next, fd));
	{
		close(fd);
		return (1);
	}
	close(fd);
	free(tokens->next->str);
	tokens->next->str = ft_strdup("tmp_file");
	if (!tokens->next->str)
		return (error_int(ALLOC_ERR));
	return (0);
}
