/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_empty_lines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 05:08:08 by nakebli           #+#    #+#             */
/*   Updated: 2023/08/20 13:52:14 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	if (!line[0])
		return (0);
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && \
		line[i] != ' ' && line[i] != '\t' && \
		line[i] != 'N' && line[i] != 'S' && \
		line[i] != 'W' && line[i] != 'E' && \
		line[i] != 'D' && line[i] != 'C')
			return (0);
		i++;
	}
	return (1);
}

static int	is_empty_line(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	delete_prefixes_empty_lines(t_cubt **cub, t_cubt *tmp)
{
	t_cubt	*to_delete;
	t_cubt	*prev;

	prev = NULL;
	while (tmp != NULL && !is_map_line(tmp->line))
	{
		if (tmp->line[0] == '\0')
		{
			if (prev == NULL)
				*cub = tmp->next;
			else
				prev->next = tmp->next;
			to_delete = tmp;
			tmp = tmp->next;
			free(to_delete->line);
			free(to_delete);
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
	if (tmp == NULL)
		print_errors("Error\nNo map");
}

void	delte_empty_lines(t_cubt **cub)
{
	t_cubt	*to_delete;
	t_cubt	*tmp;

	tmp = *cub;
	delete_prefixes_empty_lines(cub, tmp);
	tmp = ft_lstlast(*cub);
	while (tmp && is_empty_line(tmp->line))
	{
		to_delete = tmp;
		tmp = tmp->prev;
		tmp->next = NULL;
		free(to_delete->line);
		free(to_delete);
	}
}

void	check_doors(t_cubt *cub, int i, int j)
{
	(void)j;
	if (is_a_door(cub->line[i]))
	{
		if ((cub->line[i + 1] == '1' && cub->line[i - 1] == '1' && \
			cub->prev->line[i] == '0' && cub->next->line[i] == '0') || \
			(cub->line[i + 1] == '0' && cub->line[i - 1] == '0' && \
			cub->prev->line[i] == '1' && cub->next->line[i] == '1'))
			return ;
		else
			print_errors("Error\nInvalid door");
	}
}
