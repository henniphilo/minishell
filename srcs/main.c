/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:22:45 by hwiemann          #+#    #+#             */
/*   Updated: 2024/04/11 18:31:45 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../incl/minishell.h"

static void	envp_care(t_data *shell, char **envp)
{
	int		i;

	i = 0;
	while(envp[i] != NULL)
	{
		i++;
	}
	shell->env = (char **)malloc(sizeof(envp) * i);
	shell->env = envp;
}

int main(int argc, char **argv, char **envp)
{
	const char	*line;
	char		**arguments;
	t_data		shell;

	if(argc == 1 || argv[0] == NULL)
	//command loop
	while(1)
	{
		line = read_the_line();
		arguments = split_input(line);
		init_args(&shell, arguments);
		envp_care(&shell, envp);
		launch_shell(&shell);


		//execution

		free(arguments);
	}
	return (0);
}
