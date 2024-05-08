#include "../../incl/minishell.h"

int	parse_heredoc(t_lexer *tokens, int fd)
{
	char	*buf;

	buf = NULL;
	while (ft_strcmp(buf, tokens->str) != 0)
	{
		write(1, "> ", 2);
		buf = get_next_line(buf, 0);
		if (buf)
		{
			write(fd, buf, ft_strlen(buf));
			write(fd, "\n", 1);
			free(buf);
		}
	}
	return (0);
}

int	handle_heredoc(t_lexer *tokens) //unlink in clear data
{
	char	*tmp_file;
	int		fd;

	fd = open(tmp_file, O_APPEND | O_RDWR, 0777);
	if (fd < 0)
		return (error_int(FILE_ERR));
	free(tokens->str);
	tokens->str = ft_strdup("tmp_file");
	if (!tokens->str)
		return (error_int(ALLOC_ERR));
	if (!parse_heredoc(tokens, fd));
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
