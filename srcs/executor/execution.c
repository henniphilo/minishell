#include "../../incl/minishell.h"

void read_from_fd(int fd, const char *process)
{
    char c;

    printf ("Process [%s] Reading from descriptor %d \n", process, fd);
    while(read(fd, &c, 1) != 0)
	{
        printf("%c", c);
    }
}

static int	execute_command(t_data *shell, char *cmd)
{
	char	*path;

	//cmd_count = count_commands(shell->tokens);
//	cmd = shell->toex->cmd;
	path = path_finder(cmd, shell);
	if(!path)
	{
		free(cmd);
		perror("Error in Path\n");
		exit(1);
	}
	printf("will executen: %s\n", cmd);
	if(execve(path, shell->toex->argv, shell->env) < 0)
	{
		perror("command couldnt be executed\n");
		free(cmd);
		return (1);
	}
	free(cmd);
	free(path);
	return (0);
}

// int		piping(t_data *shell)
// {
// 	const char	*process;
// 	int			fd[2];
// 	int			pid;
// 	int			i;
// 	int			cmd_count;

// 	i = 0;
// 	shell->cmd_count = count_commands(shell->tokens);
// 	cmd_count = shell->cmd_count;
// 	if(cmd_count > 0)
// 	{
// 		process = "PARENT";
// 		//fd = ft_calloc(2, sizeof(int));
// 		if (pipe(fd) != 0)
// 		{
// 			perror ("Error creating pipe.\n");
// 			exit(-1);
// 		}
// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			perror ("Error creating pipe.\n");
// 			exit(-1);
//     	}
// 		else if (pid == 0)
// 		{
// 			process = "CHILD";
// 			dup2(fd[RDEND], 0); /*Replace standard input of child process with read end of the pipe*/
// 			close(fd[WREND]); /* Close the write end of the pipe in child process.It is not used */
// 			close(fd[RDEND]); /* Close the read end of the pipe in child process.We have a copy of it in file descriptor 0*/
// 			//create a new pipe for chaining the next two commands
// 		//	fd = ft_calloc(2, sizeof(int));
// 		//	pipe(fd);
// 			execute_command(shell);
// 		//	exit(0);
// 		}
// 		else
// 		{
// 			//parent

// 			printf("bin im parent\n");
// 			dup2(fd[WREND], 1); /*Replace standard output of parent process with write end of the pipe*/
// 			close(fd[RDEND]); /* Close the read end of the pipe in parent process.It is not used */
// 			close(fd[WREND]);/* Close the write end of the pipe in child process.We have a copy of it in file descriptor 1*/
// 		//	close(RDEND); /* After writing all data, close the write end */
// 		//	execute_command(shell);
// 			waitpid(pid, 0, 0); /* Wait for the child to finish */
// 		}
// 			cmd_count--;
// 		//i++;
// 	}
// 	return(1);
// }

// klar trennen was im parent und was im child passiert
// verstehen was process ist -> demzufolge forken (danach weil braucht ja zwei enden)
// so oft pipe bilden wie pipes vorhanden
// fd sind zahlen, die normalerweise bei der 3 starten weil 0, 1, 2(?) besondere fd sind die fuer anderes reserviert sind wie write(1, ...)

int		*creating_pipes(t_data *shell)
{
//a. Erstelle eine Pipe mit pipe() (falls nicht der erste oder letzte Befehl)
	int		*piped_fd;
	int		i;

	i = 1;
	piped_fd = (int*) ft_calloc((shell->cmd_count * 2) + 3, sizeof(int));
	if(!piped_fd)
	{
		perror("could not create pipe\n");
		return (NULL);
	}
	piped_fd[RDEND] = STDIN_FILENO; //erstes Element auf 0
	piped_fd[WREND] = -1; //markiert dass es nicht mehr gebraucht wird
	piped_fd[(shell->cmd_count * 2)] = -1; //vorletztes Element der Pipe auf -1
	piped_fd[(shell->cmd_count * 2) + 1] = STDOUT_FILENO; // letztes Element auf 1
	while(piped_fd && i < shell->cmd_count)
	{
		if (pipe(&piped_fd[i * 2]) < 0)
		{
			perror("Piping Error\n");
			free (piped_fd);
		}
		i++;
	}
	return (piped_fd);
}

int		pipeline_exe(t_data *shell)
{
	pid_t		*pids;
	t_command	*toex;
	int			i;

	i = 0;
	toex = shell->toex;
	pids = (pid_t*) ft_calloc(shell->cmd_count, sizeof(pid_t));
	if (!pids)
	{
		perror("Error pid \n");
		return (1);
	}
	shell->fd = creating_pipes(shell);
	if (!shell->fd)
	{
		perror("Error didnt create the pipes correct\n");
		return (1);
	}
	while(shell->toex)
	{
		if (builtin_check(shell->toex->cmd) == 0)
			which_builtin_parent(shell, shell->toex->cmd);
		else
		{
			if ((which_builtin_child(shell, shell->toex->cmd))== 1)
			{
				if (exe_env(shell, pids, i) == 1)
					exit(1);
			}
		}
		toex = shell->toex->next;
		i++;
	}
	free (shell->fd);
	free (pids);
	return(0);
}

int		exe_env(t_data *shell, pid_t *pids, int i)
{
	int		file_out;
	int		file_in;

	*pids =fork();
	file_in = 0;
	file_out = 0;
	if (*pids < 0)
	{
		perror("fork error \n");
		return (1);
	}
	if (pids == 0)
	{
		file_in  = dup2(shell->fd[i], STDIN_FILENO);
		file_out = dup2(shell->fd[i], STDOUT_FILENO);
		if (file_in == -1 || file_out == -1)
		{
			perror("dup error im child\n");
			exit(1);
		}
		close(shell->fd[i]);
		if (execute_command(shell, shell->toex->cmd) == 0)
			exit (0);
	}
	waitpid(*pids, 0, 0);
	close(file_in);
	close(file_out);
	return (0);
}



/*
1. Schleife für die Eingabeaufforderung:
    a. Lies die Eingabe von der Benutzerzeile
    b. Teile die Eingabe in separate Befehle auf, falls es sich um eine Pipeline handelt

2. Für jeden Befehl in der Pipeline:
    a. Erstelle eine Pipe mit pipe() (falls nicht der erste oder letzte Befehl)
    b. Fork einen neuen Prozess

    Im Kindprozess:
        i. Leite die Standardausgabe um, wenn es nicht der letzte Befehl ist
        ii. Leite die Standardeingabe um, wenn es nicht der erste Befehl ist
        iii. Führe den Befehl mit execvp() oder execve() aus
        iv. Behandele Fehler, falls exec fehlschlägt

    Im Elternprozess:
        i. Warte auf den Kindprozess, wenn es nicht der letzte Befehl ist
        ii. Schließe die Pipes entsprechend

3. Zurück zur Schleife für die Eingabeaufforderung


**umleiten:**
Im Kindprozess:
    i. Leite die Standardausgabe um, wenn es nicht der letzte Befehl ist
        a. Wenn es nicht der letzte Befehl ist:
            i. Schließe den Schreibendes-Ende der Pipe (Standardausgabe)
            ii. Dupliziere das Lesendes-Ende der Pipe auf die Standardausgabe
            iii. Schließe das Lesendes-Ende der Pipe
    ii. Leite die Standardeingabe um, wenn es nicht der erste Befehl ist
        a. Wenn es nicht der erste Befehl ist:
            i. Schließe das Lesendes-Ende der Pipe (Standardeingabe)
            ii. Dupliziere das Schreibendes-Ende der vorherigen Pipe auf die Standardeingabe
            iii. Schließe das Schreibendes-Ende der vorherigen Pipe

Im Elternprozess:
    i. Warte auf den Kindprozess, wenn es nicht der letzte Befehl ist
        a. Wenn es nicht der letzte Befehl ist:
            i. Warte auf den Kindprozess, bis er beendet ist, und überprüfe auf Fehler
            ii. Schließe das Lesendes-Ende der Pipe (Standardausgabe)
    ii. Schließe die Pipes entsprechend

*/
