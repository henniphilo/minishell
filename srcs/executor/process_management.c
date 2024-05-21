#include "../../incl/minishell.h"


//ist nicht nur env checkt auch buildin -> umbenennen
int		exe_env(t_data *shell, pid_t *pids, int i, t_command *toex)
{
	pids[i] = fork();

	if (pids[i] < 0)
	{
		perror("fork error\n");
		return (1);
	}
	if (pids[i] == 0)
		child_process(shell, i, toex);
	else
	{
		if(i > 0)
		{
			close(shell->fd[i -1][WREND]);
			close(shell->fd[i - 1][RDEND]);
		}
		else if(shell->fd) //wenn es nur eine pipe gibt
			close(shell->fd[0][WREND]);
	}
	return (0);
}

void	wait_for_children(t_data *shell)
{
	int		i;
	int		estatus;

	i = 0;
	estatus = 0;
	while(i < shell->cmd_count)
	{
	//	printf("in wait i %d und cmd count %d \n", i, shell->cmd_count);
		waitpid(shell->pids[i], &estatus, 0);
		// ft_putstr_fd("\ng_estatus in wait davor\n", 2);
		// ft_putnbr_fd(g_estatus, 2);
		if (WIFEXITED(estatus))
		{
			if(shell->bi_check == 1)
				g_estatus = 1;
			else
				g_estatus =  WEXITSTATUS(estatus); // hier wird es mit ergebnis der letzten pipe ueberschrieben
		}
		else
			g_estatus = 1;
		// ft_putstr_fd("\ng_estatus in wait danach\n", 2);
		// ft_putnbr_fd(g_estatus, 2);
		i++;
	}
//	printf("\n%i\n", g_estatus);
}

void	child_process(t_data *shell, int i, t_command *toex)
{
	if (shell->cmd_count > 1)
		{
			if(i + 1 < shell->cmd_count)
			{
				if(dup2(shell->fd[i][WREND], STDOUT_FILENO) == -1)
				{
					perror("dup2 WREND\n");
					exit(EXIT_FAILURE);
				}
				close(shell->fd[i][RDEND]);
			}
			if(i > 0)
			{
				if(dup2(shell->fd[i - 1][RDEND], STDIN_FILENO) == -1)
				{
					perror("dup2 RDEND");
					exit(EXIT_FAILURE);
				}
				close(shell->fd[i - 1][WREND]);
				close(shell->fd[i - 1][RDEND]);
			}
			close_pipes(shell);
		}
		redirect_pipes(shell->toex);
		execution(shell, toex);
}
