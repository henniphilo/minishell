#include "../../incl/minishell.h"

char	**split_input(const char *line)
{
	char	**split_line;
	char	pipe;
	int		i;

	pipe = ' ';
	i = 0;
	split_line = NULL;
	if(line == NULL)
	{
		perror("line error\n");
		exit (0);
	}
	while(line[i] != '\0')
	{
		if(line[i] == ' ')
		{
			split_line = ft_split(line, pipe);
			return (split_line);
		}
		i++;
	}
	split_line = no_pipe(line);
	return (split_line);
}

char	**no_pipe(const char *line)
{
	char	**wo_split;
	int		len;

	if(line == NULL)
		exit(0);
	len = ft_strlen(line);
	wo_split = (char**)malloc(sizeof(wo_split) * len);
	wo_split[0] = ft_strdup((char *)line);
	wo_split[1] = NULL;
	return(wo_split);
}

static void	space_args(t_data *shell, char **args)
{
	int		i;

	i = 0;
	while(args[i] != NULL)
	{
		i++;
	}
	shell->arguments = (char **)ft_calloc(sizeof(args) * i, sizeof(char));
}

static char	*line_trim(const char *line)
{
	//ausdehnen auf alle white spaces
	const char	*set;
	char	*trim;

	set = " ";
	trim = ft_strtrim(line, set);

	return(trim);
}

void	init_args(t_data *shell, char **split)
{
	int		i;

	i = 0;

	space_args(shell, split);

	while(split[i] != NULL)
	{
		split[i] = line_trim(split[i]);
		shell->arguments[i] = ft_strdup(split[i]);
		printf("args[%d]: %s\n",i, shell->arguments[i]);
		free (split[i]);
		i++;
	}
	free(split[i]);
	shell->arguments[i] = NULL;
	printf("args[%d]: %s\n",i, shell->arguments[i]);

}




