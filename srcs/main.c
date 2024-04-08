/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:22:45 by hwiemann          #+#    #+#             */
/*   Updated: 2024/04/08 11:27:43 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

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
