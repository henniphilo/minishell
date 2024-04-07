/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:22:45 by hwiemann          #+#    #+#             */
/*   Updated: 2024/04/07 18:17:46 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int main()
{
	char	*line;
	char	**split_line;
	char	pipe;
	int		i;

	pipe = '|';
	while (1)
	{
		line = readline("our minishell 🌺: ");
		split_line = ft_split(line, pipe);
		i = 0;

		while(split_line[i])
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

