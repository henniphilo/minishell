#include "../incl/minishell.h"


void	print_toex(t_data *shell)
{
	int		i;

	i = 0;
	while(shell->toex[i] != NULL)
	{
		printf("toex[%d] is: %s\n", i, shell->toex[i]);
		i++;
	}
}
void	space_pipeline(t_data *shell, char ***pipeline)
{
	// int		i;
	// int		j;

	// i = 0;
	// while(pipeline[i] != NULL)
	// {
	// 	j = 0;
	// 	while(pipeline[i][j] != NULL)
	// 	{
	// 		j++;
	// 	}
	// 	shell->pipeline[i] = (char**)malloc(sizeof(char*) * j);
	// 	i++;
	// }
	// shell->pipeline = (char ***)malloc((i + 1) * sizeof(char**));
	// if(shell->pipeline == NULL)
	// {
	// 	return ;
	// }
	// shell->pipeline[i] = NULL;

    int i = 0;
    while (pipeline[i] != NULL)
    {
        int j = 0;
        while (pipeline[i][j] != NULL)
        {
            j++;
        }
        shell->pipeline[i] = (char**)malloc((j + 1) * sizeof(char*)); // +1 für das NULL-Ende
        if (shell->pipeline[i] == NULL)
        {
            // Speicherfehler, Speicherbereinigung durchführen und zurückkehren
            for (int k = 0; k < i; k++) {
                free(shell->pipeline[k]);
            }
            free(shell->pipeline);
            shell->pipeline = NULL;
            return;
        }
        i++;
    }
    // Allokiere Speicherplatz für das Array von Zeigern
    shell->pipeline = (char ***)malloc((i + 1) * sizeof(char**)); // +1 für das NULL-Ende
    if (shell->pipeline == NULL)
    {
        // Speicherfehler, Speicherbereinigung durchführen
        for (int k = 0; k < i; k++) {
            free(shell->pipeline[k]);
        }
        free(shell->pipeline);
        shell->pipeline = NULL;
        return;
    }
    // Setze das NULL-Ende
    shell->pipeline[i] = NULL;
}
void	print_pipeline(t_data *shell)
{
	int		i;
	int		j;

	i = 0;
	while(shell->pipeline[i] != NULL)
	{
		j = 0;
		while(shell->pipeline[i][j] != NULL)
		{
			printf("pipeline[%d][%d] is: %s\n", i, j, shell->pipeline[i][j]);
			j++;
		}
		i++;
	}
}
