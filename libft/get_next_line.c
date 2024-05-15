/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:43:34 by pbencze           #+#    #+#             */
/*   Updated: 2024/02/02 15:39:07 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*nextline;
	static char	*remainder;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	nextline = ft_readline(fd, remainder);
	remainder = ft_trimline(nextline);
	nextline = ft_line(nextline);
	return (nextline);
}

char	*ft_readline(int fd, char *nextline)
{
	char	*buf;
	ssize_t	count;

	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (ft_free(buf, nextline));
	while (!(ft_strchr_gnl(nextline, '\n')))
	{
		count = read(fd, buf, BUFFER_SIZE);
		if (count == -1)
			return (ft_free(buf, nextline));
		if (count == 0)
			break ;
		else
		{
			buf[count] = '\0';
			nextline = ft_strjoin_gnl(nextline, buf);
		}
	}
	free (buf);
	return (nextline);
}

char	*ft_trimline(char *nextline)
{
	char	*linebreak;
	char	*remainder;

	remainder = NULL;
	linebreak = ft_strchr_gnl(nextline, '\n');
	if (!linebreak)
		return (NULL);
	if (*(++linebreak))
		remainder = ft_strdup_gnl(linebreak);
	return (remainder);
}

char	*ft_line(char *nextline)
{
	char	*line;
	char	*nl;

	nl = ft_strchr_gnl(nextline, '\n');
	if (!nl)
		return (nextline);
	nl++;
	if (*nl == '\0')
		return (nextline);
	line = ft_substr_gnl(nextline, 0, (nl - nextline));
	free (nextline);
	return (line);
}

void	*ft_free(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (NULL);
}
