/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:50:51 by hwiemann          #+#    #+#             */
/*   Updated: 2024/05/23 17:51:30 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	swap(t_environ *a, t_environ *b)
{
	char	*temp_name;
	char	*temp_value ;

	temp_name = a->name;
	temp_value = a->value;
	a->name = b->name;
	a->value = b->value;
	b->name = temp_name;
	b->value = temp_value;
}

void	sort_export_list(t_data *shell)
{
	t_environ	*head;
	t_environ	*current;
	t_environ	*last_sort;
	int			swapped;

	head = shell->export_list;
	last_sort = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = head;
		while (current->next != last_sort)
		{
			if (ft_strcmp(current->name, current->next->name) > 0)
			{
				swap(current, current->next);
				swapped = 1;
			}
			current = current->next;
		}
		last_sort = current;
	}
}
