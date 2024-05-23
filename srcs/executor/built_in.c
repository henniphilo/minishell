#include "../../incl/minishell.h"


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
	if(ft_strcmp((const char *)arg, "cd") == 0)
		g_estatus = bi_cd(shell);
	else if(ft_strcmp((const char *)arg, "export") == 0)
		g_estatus = bi_export(shell);
	else if(ft_strcmp((const char *)arg, "pwd") == 0)
		g_estatus = bi_pwd(shell);
	else if(ft_strcmp((const char *)arg, "unset") == 0)
	{
		bi_unset(argv, shell->env_list);
		bi_unset(argv, shell->export_list);
		g_estatus = 0;
	}
	else if(ft_strcmp((const char *)arg, "exit") == 0)
	{
		g_estatus = bi_exit(shell, argv);
		free_data(shell);
		exit(g_estatus);
	}
	else
		g_estatus = 1;
	return (g_estatus);
}

int	bi_cd(t_data *shell)
{
	char	*home_path;

	if (shell->toex->args == NULL) //cd
	{
		if (var_check(shell, "HOME"))
			return (cd_error_int("HOME"));
		home_path = find_in_env("HOME");
		chdir(home_path);
		update_old_pwd(shell);
		//free(home_path);
		return(0);
	}
	if (shell->toex->argv[1])
	{
		if (shell->toex->args[0][0] == '\0' || ft_strcmp(".", shell->toex->args[0]) == 0) //cd ""
			return(0);
		if (chdir(shell->toex->args[0]) == 0) //cd etwas
		{
			update_old_pwd(shell);
			return(0);
		}
	}
	else
		return (cd_error_int("MANY"));
	return (cd_error_int(shell->toex->args[0]));
}

void		update_envlist(t_data *shell, char *to_up, char *new)
{
	t_environ	*head;

	head = shell->env_list;

	while (head != NULL)
	{
		if (ft_strcmp(to_up, head->name) == 0)
		{
			head = replace_value(head, new);
			break ;
		}
		head = head->next;
	}
}

void	update_old_pwd(t_data *shell) // updaten im struct
{
	char	*new_pwd;
	char	*old_pwd;
	char	cwd[1024];
	t_environ *old_pwd_ptr;

	if(var_check(shell, "PWD") == 0)
	{
		old_pwd_ptr = find_name_in_envlist(shell, "PWD");
		old_pwd = ft_strdup(old_pwd_ptr->value);
		if (!old_pwd_ptr->value)
			return ;
		if(var_check(shell, "OLDPWD") == 0)
			update_envlist(shell, "OLDPWD", old_pwd);
		else
			free(old_pwd);
		new_pwd = getcwd(cwd, sizeof(cwd));
		shell->pwd = ft_strdup(new_pwd);
		//printf("new pwd %s\n", new_pwd);
		update_envlist(shell, "PWD", shell->pwd);
		free(shell->pwd); //gerade geaendert
	}
}

t_environ	*find_name_in_envlist(t_data *shell, char *name)
{
	t_environ	*head;

	head = shell->env_list;
	while (head != NULL)
	{
		if (ft_strcmp(name, head->name) == 0)
			return (head);
		head = head->next;
	}
	return (NULL);
}

t_environ	*find_name_in_exportlist(t_environ *export_list, char *name)
{
	while (export_list != NULL)
	{
		if (ft_strcmp(name, export_list->name) == 0)
			return (export_list);
		export_list = export_list->next;
	}
	return (NULL);
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
	//char		*current_path;
	char		cwd[1024];
	// t_environ	*head;

	// head = shell->env_list;
	// while (head != NULL)

		// if(var_check(shell, "PWD") == 0)
		// {
		// 	if (ft_strncmp(head->name, "PWD", 4) == 0)
		// 	{
		// 		current_path = head->value;
		// 		printf("%s\n", current_path);
		// 		break ;
		// 	}
		// 	head = head->next;
		// }
		// else
		// {

		shell->pwd = ft_strdup(getcwd(cwd, sizeof(cwd)));
		if (!shell->pwd)
			return (1);
		else
		{
			printf("%s\n", shell->pwd);
			free(shell->pwd);
			shell->pwd = NULL;
			return (0);
		}
}
