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
	{
		printf("is a builtin in parent \n");
		return(1);
	}
	return (0);
}
// alles was path verwendet muss protectet werden, checken ob path exists
// 15.5: unset und export updaten gerade nicht mehr env_list
// aber export list wird upgedatet
// nur export segfaulted

void	which_builtin_parent(t_data *shell, char *arg)
{
	int	n;

	n = 7;
	shell->bi_check = 1;
	if(ft_strncmp((const char *)arg, "cd", n) == 0)
	{
		if(change_directory(shell) != 0)
			perror("error in \n");
	}
	if(ft_strncmp((const char *)arg, "export", n) == 0)
	{
		bi_export(shell);
	}
	if(ft_strncmp((const char *)arg, "pwd", n) == 0)
	{
		bi_pwd(shell);
	}
	if(ft_strncmp((const char *)arg, "unset", n) == 0)
	{
		bi_unset(shell);
	}
	if(ft_strncmp((const char *)arg, "exit", n) == 0)
	{
		bi_exit(shell);
	}
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
				printf("goes up\n");
			update_old_pwd(shell);
			return (0);
		}
		else if(shell->toex->argv[1] != NULL && (ft_strncmp(shell->toex->argv[1], tilde, 2)) == 0)
		{
			printf("tilds\n");
			chdir(home_path);
			update_old_pwd(shell);
			return (0);
		}
	}
	return (1);
}

//noch path protecten
int	change_directory(t_data *shell)
{
	char	*new_path;
	char	*home_path;

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
			chdir(new_path);
			update_old_pwd(shell);
			return(0);
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

	old_path_ptr = find_name_in_envlist(shell, "PWD");
	old_path = old_path_ptr->value;
	update_envlist(shell, "OLDPWD", old_path);
	new_path = getcwd(cwd, sizeof(cwd));
	update_envlist(shell, "PWD", new_path);
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


void	bi_exit(t_data *shell)
{
	free_data(shell);
	exit(0);
}

void		bi_pwd(t_data *shell)
{
	char		*current_path;
	t_environ	*head;

	head = shell->env_list;
	while (head != NULL)
	{
		if (ft_strncmp(head->name, "PWD", 4) == 0)
		{
			current_path = head->value;
			printf("%s\n", current_path);
			break ;
		}
		head = head->next;
	}
}
