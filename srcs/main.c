/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:22:45 by hwiemann          #+#    #+#             */
/*   Updated: 2024/04/08 10:56:10 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int main()
{

	char	*line;
	//command loop

	while(1)
	{
		line = read_the_line();
		if(!split_input(line))
			return (1);
	}
	return (0);
}

char	read_the_line()
{
	char	*line;

	line = readline("our minishell 🌺: ");
	if(!line)
	{
		perror("rl_error\n");
		exit(1);
	}
	return(line);
}


int	split_input(char *line)
{
	char	**split_line;
	char	pipe;
	int		i;

	pipe = '|';
	while (1)
	{
		split_line = ft_split(line, pipe);
		if(!split_line)
			{
				perror("split error\n");
				return (1);
			}
		i = 0;
		while (split_line[i])
		{
			ft_printf("%s\n", split_line[i]);
			free(split_line[i]);
			i++;
		}
		free(split_line);
		free(line);
	}
	return (0);
}
