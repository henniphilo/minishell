/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:22:45 by hwiemann          #+#    #+#             */
/*   Updated: 2024/04/08 19:49:58 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../incl/minishell.h"

int main()
{

	const char	*line;
	char	**arguments;
	//command loop

	while(1)
	{
		line = read_the_line();
		arguments = split_input(line);

		//execution

		free(arguments);
	}
	return (0);
}
