/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:32:28 by nakebli           #+#    #+#             */
/*   Updated: 2023/08/08 19:09:59 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"

// void	ft_lstdelone(t_cubt *lst, void (*del)(void*))
// {
// 	if (!lst || !del)
// 		return ;
// 	del(lst->content);
// 	free(lst);
// }

t_cubt	*ft_lstlast(t_cubt *cub)
{
	if (!cub)
		return (NULL);
	while (cub)
	{
		if (!cub->next)
		{
			return (cub);
		}
		cub = cub->next;
	}
	return (cub);
}

void	ft_lstadd_back(t_cubt **cub, t_cubt *new)
{
	t_cubt	*temp;

	if (cub)
	{
		if (!(*cub))
			(*cub) = new;
		else
		{
			temp = ft_lstlast(*cub);
			temp->next = new;
		}
	}
}

t_cubt	*ft_lstnew(char *line, t_info *info, t_cubt *prev)
{
	t_cubt	*new;

	new = (t_cubt *)malloc(sizeof(t_cubt));
	if (!new)
		return (NULL);
	(new)->line = line;
	new->info = info;
	(new)->next = NULL;
	(new)->prev = prev;
	return (new);
}

int	towd_arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}
