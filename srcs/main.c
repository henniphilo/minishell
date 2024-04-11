/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:22:45 by hwiemann          #+#    #+#             */
/*   Updated: 2024/04/11 16:27:30 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../incl/minishell.h"

int main(char **envp)
{

	const char	*line;
	char		**arguments;
	//t_data		shell;
	//command loop


	while(1)
	{
		line = read_the_line();
		arguments = split_input(line);
		init_args(arguments);


		//execution

		free(arguments);
	}
	return (0);
}
