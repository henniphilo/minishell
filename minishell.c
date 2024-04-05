/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:22:45 by hwiemann          #+#    #+#             */
/*   Updated: 2024/04/05 19:08:26 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	char	*line;

	while (1)
	{
		line = readline("our minishell 🌺: ");

		ft_split(line, *);
		while(line != NULL)
		{
			printf("%s\n", line);
		}
	}
	return (0);
}

