#include "../../incl/minishell.h"

// > hallo fueht in libft folder reon
// muss noch klaeren relativen und absoluten path


int	builtin_check(char *arg)
{
	int	n;

	n = 7;

	if((ft_strncmp((const char *)arg, "cd", n) == 0)
		|| (ft_strncmp((const char *)arg, "exit", n) == 0)
		|| (ft_strncmp((const char *)arg, "unset", n) == 0)
		|| (ft_strncmp((const char *)arg, "pwd", n) == 0)
		|| (ft_strncmp((const char *)arg, "export", n) == 0))
		return(1);
	return (0);
}

int		which_builtin_parent(t_data *shell, char *arg, char **argv)
{
	int	n;

	n = 7;
	if(ft_strncmp((const char *)arg, "cd", n) == 0)
		g_estatus = bi_cd(shell);
	else if(ft_strncmp((const char *)arg, "export", n) == 0)
		g_estatus = bi_export(shell);
	else if(ft_strncmp((const char *)arg, "pwd", n) == 0)
		g_estatus = bi_pwd(shell);
	else if(ft_strncmp((const char *)arg, "unset", n) == 0)
		g_estatus = bi_unset(shell);
	else if(ft_strncmp((const char *)arg, "exit", n) == 0)
	{
		g_estatus = bi_exit(shell, argv);
		ft_putendl_fd("exit", 2);
		free_data(shell);
		exit(g_estatus);
	}
	else
		g_estatus = 1;
	return (g_estatus);
}

static int	bi_cd_check(t_data *shell, char *home_path)
{
	const char	*up;
	const char	*tilde;

	up = "..";
	tilde = "~";
	if (shell->toex && shell->toex->argv)
	{
		if(shell->toex->argv[1] != NULL && (ft_strncmp(shell->toex->argv[1], up, 3))== 0)
		{
			if(chdir("..") == 0)
			update_old_pwd(shell);
			return (0);
		}
		else if(shell->toex->argv[1] != NULL && (ft_strncmp(shell->toex->argv[1], tilde, 2)) == 0)
		{
			printf("tilde\n");
			chdir(home_path);
			update_old_pwd(shell);
			return (0);
		}
	}
	return (1);
}

int	bi_cd(t_data *shell)
{
	char	*new_path;
	char	*home_path;

	if(var_check(shell, "HOME") == 0)
	{
		home_path = find_in_env("HOME");
		if (shell->toex->args == NULL)
		{
			chdir(home_path);
			update_old_pwd(shell);
			return(0);
		}
		if (bi_cd_check(shell, home_path) == 0)
			return(0);
		if (array_len(shell->toex->args) == 1)
		{
			new_path = shell->toex->args[0];
			if(new_path != NULL)
			{
				if	(chdir(new_path) == 0)
				{
					update_old_pwd(shell);
					return(0);
				}
			}
		}
	}
	return(1);
}

void		update_envlist(t_data *shell, char *to_up, char *new)
{
	t_environ	*head;

	head = shell->env_list;

	while (head != NULL)
	{
		if (ft_strncmp(to_up, head->name, 50) == 0)
		{
			head = replace_value(head, new);
			break ;
		}
		head = head->next;
	}
}

void	update_old_pwd(t_data *shell)
{
	char	*new_path;
	char	*old_path;
	char	cwd[1024];
	t_environ *old_path_ptr;

	if(var_check(shell, "PWD") == 0)
	{
		old_path_ptr = find_name_in_envlist(shell, "PWD");
		old_path = old_path_ptr->value;
		if(var_check(shell, "OLDPWD") == 0)
			update_envlist(shell, "OLDPWD", old_path);
		new_path = getcwd(cwd, sizeof(cwd));
		update_envlist(shell, "PWD", new_path);
	}
}

t_environ	*find_name_in_envlist(t_data *shell, char *name)
{
	t_environ	*head;

	head = shell->env_list;
	while (head != NULL)
	{
		if (ft_strncmp(name, head->name, 50) == 0)
		{
			return (head);
		}
		head = head->next;
	}
	return(NULL);
}

//hier muss noch das verhalten exit + zahl bedacht werden
int		bi_exit(t_data *shell, char **argv)
{
	int	i;

	i = 0;
	(void)shell;
	if (argv[1])
	{
		if (argv[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			return (1);
		}
		if (ft_isnum(argv[1]))
			return (2);
		i = ft_atoi(argv[1]);
		return(i);
	}
	else
		return(g_estatus);
	return (0);
}


int		bi_pwd(t_data *shell)
{
	char		*current_path;
	t_environ	*head;

	head = shell->env_list;
	while (head != NULL)
	{
		if(var_check(shell, "PWD") == 0)
		{
			if (ft_strncmp(head->name, "PWD", 4) == 0)
			{
				current_path = head->value;
				printf("%s\n", current_path);
				break ;
			}
			head = head->next;
		}
		else
		{
			ft_putstr_fd("Error var doesn't exist\n", 2);
			return (1);
		}
	}
	return (0);
}
