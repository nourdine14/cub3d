/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:32:28 by nakebli           #+#    #+#             */
/*   Updated: 2023/07/22 04:56:00 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"

// void	ft_lstdelone(t_cub *lst, void (*del)(void*))
// {
// 	if (!lst || !del)
// 		return ;
// 	del(lst->content);
// 	free(lst);
// }

t_cub	*ft_lstlast(t_cub *cub)
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

void	ft_lstadd_back(t_cub **cub, t_cub *new)
{
	t_cub	*temp;

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

t_cub	*ft_lstnew(char *line, t_info *info, t_cub *prev)
{
	t_cub	*new;

	new = (t_cub *)malloc(sizeof(t_cub));
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
