/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:45:18 by pbencze           #+#    #+#             */
/*   Updated: 2024/02/02 15:39:38 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*ft_readline(int fd, char *nextline);
char	*ft_trimline(char *nextline);
ssize_t	ft_strlen_gnl(char *str);
char	*ft_strchr_gnl(const char *str, int c);
char	*ft_strdup_gnl(char *str);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_line(char *nextline);
char	*ft_substr_gnl(char *s, unsigned int start, ssize_t len);
void	*ft_free(char *s1, char *s2);

#endif
